# Control Flow Keywords
Want to be able to control logic flow? You'll need these keywords!

| Keyword | Purpose | Usage Context | Example (JavaScript-like Syntax) | Notes |
| --- | --- | --- | --- | --- |
| `break` | Exits the current loop or `switch` statement immediately. | `for`, `while`, `do...while`, `switch` | `break;` in a loop or `switch` case. | Only exits the **innermost** loop or `switch`. |
| `continue` | Skips the current iteration and moves to the next iteration of a loop. | `for`, `while`, `do...while` | `continue;` in a loop. | Does not exit the loop; only skips to the next iteration. |
| `return` | Exits the current function and returns a value (or `undefined`). | Functions | `return value;` or `return;` | If no value is provided, returns `undefined`. |
| `exit` | Terminates the entire program immediately. | Shell scripts, some languages (e.g., PHP) | `exit(1);` (exit code 1 for error) | Not available in JavaScript (use `process.exit()` in Node.js). |
| `throw` | Throws a custom error to interrupt normal execution. | Anywhere (usually in functions) | `throw new Error("Message");` | Used for exception handling; caught with `try...catch`. |
| `yield` | Pauses a generator function and returns a value. | Generator functions (`function*`) | `yield value;` | Resumes execution when the generator's `next()` is called. |
| `await` | Pauses an `async` function until a `Promise` resolves. | `async` functions | `const result = await promise;` | Only valid in `async` functions. |
| `goto` | Jumps to a labeled statement (avoid in modern code). | Rare (e.g., C, C++) | `goto label;` and `label:` | Considered harmful; avoid in structured programming. |