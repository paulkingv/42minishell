# 230 FAIL Sort (by ChatGPT)

### 1. Syntax validation / parser — **largest category**

Your parser accepts malformed operator sequences instead of stopping with Bash-style syntax errors.

**Tests:**
`5, 6, 18–21, 30, 31, 155–169, 171–173, 264–280, 283–289, 341–346, 358, 363–364, 408–409, 515, 521–529, 530–532, 535–538`

Typical problems:

* missing command around `|`
* missing filename after `<`, `>`, `<<`, `>>`
* consecutive redirects
* redirect followed immediately by another operator
* invalid combinations such as `<|`, `<<|`, `>|<`
* consecutive pipes
* pipe at beginning/end

For example, `| ls` currently executes `ls`, while Bash returns syntax error 2. 

**Root cause:** parser/token validation, not execution.

---

### 2. `exit` implementation — **major category**

This is another very large cluster.

**Tests:**
`118–120, 181–207, 638–653`

Subcategories:

#### Numeric validation

`118, 119, 182, 184–186, 199–206, 642, 646, 649`

You're accepting things Bash rejects, especially overflow/underflow and malformed signs. For example, `exit 9223372036854775808` should return **2 / numeric argument required**, but yours returns 0. 

#### Too many arguments

`120, 193, 194, 643`

Example: `exit 42 abc` should leave the shell running with status 1, whereas yours exits with 42. 

#### Sign handling

`187–190, 201–206, 640–641, 650–653`

Some of these are actually **behaviorally correct** but marked FAIL because your minishell prints `exit` while the Bash comparison doesn't. For example `exit +42` has the same exit code but differs on stdout. 

#### Whitespace / quoted numeric arguments

`196–198`

`exit ' 5'` and `exit '5 '` work, but `exit '5     x'` is incorrectly accepted as 5 instead of being rejected. 

#### `exit` inside pipelines

`254, 257, 329, 389–402, 644`

These are a **separate pipeline/builtin execution problem**: which process runs the builtin and which status becomes the pipeline status.

---

### 3. Pipeline execution semantics

**Tests:**
`251, 254, 257, 324, 325, 329, 389–402, 462, 510–512, 673–676, 704–705, 742, 747`

The big issue is that your pipeline stages aren't behaving like independent processes with proper stdin/stdout connections.

The clearest examples:

* `echo hola | echo que tal` → yours outputs `hola`, Bash outputs `que tal`. 
* `echo a | echo b | echo c` → yours outputs `a`, Bash outputs `c`. 
* `printf a | pwd | cat -e` → yours outputs nothing, Bash outputs the working directory. 

**Root cause:** pipe fd setup / stdin-stdout inheritance / builtin execution in pipeline.

This is probably one of the highest-priority areas after syntax parsing.

---

### 4. Heredoc

**Tests:**
`21, 262–263, 304, 340, 357–360, 363–364, 408–409, 425–438, 495, 515, 667`

There are two different problems here.

**Invalid heredoc syntax:**

`21, 263, 363, 364, 408, 409, 515, 667`

For example, `cat <<` should be a syntax error, but yours accepts it. 

**Heredoc execution / fd handling:**

`304, 357, 360, 425–438, 495`

The especially interesting one is:

`cat <<A | cat <<B`

Yours outputs the first heredoc, Bash outputs the second. Valgrind also reports `unterminated hd_loop`, so this looks like an actual heredoc/fd lifecycle problem rather than merely an error-message mismatch. 

---

### 5. `cd` semantics

**Tests:**
`69, 72, 73, 224–226, 230`

Issues:

* nonexistent directory error message differs
* too many arguments accepted
* `cd ''` handled incorrectly
* special arguments such as `--` / `+` / `?`
* invalid argument handling

For example, `cd /tmp /var` should return 1 with `cd: too many arguments`; yours returns 0. 

---

### 6. `PWD` / `OLDPWD` / empty-environment handling

**Tests:**
`467–495`

This is basically its own subsystem.

Failures cover:

* `PATH` missing/present incorrectly
* `PWD` missing/present incorrectly
* `PWD` not updated after `cd`
* `OLDPWD` not created/updated
* `unset PWD`
* `export` state with an initially empty environment
* commands such as `grep` becoming unavailable because PATH is absent

For example, after `cd /`, Bash reports `/`, while yours still reports the original directory. 

**Root cause:** environment initialization + maintaining `PWD`/`OLDPWD`, not really `cd` itself.

---

### 7. Command execution / exit codes 126 vs 127

**Tests:**
`133, 134, 348, 349, 355`

You're confusing:

* **126** = found but cannot execute
* **127** = command not found

For `/tmp/ra_noperm.sh`, Bash returns 126, yours returns 127. 

Empty quoted commands have the same issue: Bash treats `""""` / `''''''` as an empty command and returns 127, while yours attempts `execve` and gets 126. 

---

### 8. Expansion / tokenizer edge cases

**Tests:**
`231, 347, 376, 377, 590, 596, 611, 523`

Examples:

* `echo $U/SER`
* `echo$HOME`
* literal `\n` / `\t`
* `$$`
* `$"hello"`
* complicated quote/variable combinations

`echo$HOME` is particularly useful: Bash resolves it to a path and gets 126 because it's not a directory, while yours reports command-not-found 127. 

This points toward **tokenization/expansion occurring in the wrong order or with incorrect command classification**.

---

### 9. `export` parsing/state

**Tests:**
`625, 629, 637, 730`

These appear to be smaller export-specific edge cases, particularly around assignment syntax and matching/export state.

I'd investigate these **after** the environment/PWD work, because some of the later export failures are likely consequences of the environment implementation.

---

## Priority order I'd use

| Priority | Area                                           | Tests |
| -------- | ---------------------------------------------- | ----: |
| 🔴 1     | **Syntax parser / invalid operator sequences** |   ~70 |
| 🔴 2     | **Pipeline fd / execution semantics**          |   ~25 |
| 🔴 3     | **`exit` parsing + numeric overflow**          |   ~40 |
| 🔴 4     | **Heredoc parsing/fd lifecycle**               |   ~25 |
| 🟠 5     | **Environment / PWD / OLDPWD / PATH**          |   ~30 |
| 🟠 6     | **126 vs 127 command execution**               |     5 |
| 🟡 7     | **cd edge cases**                              |     7 |
| 🟡 8     | **Expansion/tokenization edge cases**          |    ~8 |
| 🟡 9     | **Export edge cases**                          |    ~4 |

### The important takeaway

I **wouldn't fix these 230 individually**. There are probably only **5–8 underlying bugs** generating most of them:

1. **Parser doesn't reject invalid operator sequences**
2. **Pipeline fd wiring is wrong**
3. **Builtins in pipelines aren't handled correctly**
4. **`exit` numeric parser is incorrect**
5. **Heredoc parser/fd lifecycle is incorrect**
6. **Environment initialization / `PWD` / `OLDPWD` is incomplete**
7. **`execve` error classification is wrong**
8. **A few expansion/tokenization edge cases**

Also, some `[FAIL]` entries are **not actual functional bugs**: the mini and Bash exit codes match, but your shell prints `exit` and Bash doesn't in the comparison. The `exit +42` case is an example. 

If you're fixing the minishell, **start with #1 (syntax parser), then #2 (pipes), then #3 (`exit`)**. Those should collapse a very large portion of the failure count at once.


# Paul Notes:
1. ^C should return something but doesnt (run $? after)
2. ^C blocks the next line from executing, needs to execute



