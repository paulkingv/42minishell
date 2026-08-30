*This project was created as a part of the 42 curriculum by pking and jfox.*

# Minishell
*Because making our own shell will come in handy someday, right?*

# Description
**Minishell** is a 42 project where students are tasked with creating their own Shell as a team.

The goal is to create a program that permits communication between the computer and its user in a simple, constructive and human readable way.

**pking** will handle **execution** and **jfox** will handle **parsing**. Both teammates must understand and be able to adjust each other's code if need be.

**The subject outlined clear parameters for us to follow, this became the base of our implimention:**
```
Display a prompt while waiting for a new command and have a working history to cycle through those commands.

We must be able to use a PATH to search and execute commands.

Only one global variable was allowed and specifically in the scope of handling a signal. This allowed us to consider the implications of a signal handler that does not need to enter into our main data structures.
```
We were told not to handle unclosed quotes or special characters such as:
```
\ ;
```
Handle quotes to create literal or expanding values, and this was expecially relevant with heredoc implimentation and ECHO, EXPORT variable expansion where dollar signs were involved.
```
' " $
```
We had to handle all kinds of Redirections:
```
< << >> >
```
Pipes, Exit expansion were also essential:
```
| $?
```
CTRL-C, CTRL-D and CTRL-\ were all expected to work as in bash.

Beyond this we had to make several builtins that would work as in bash with specific options:
```
-echo with option -n
-cd with only a relative or absolute path
-pwd with no options
-export with no options
-unset with no options
-env with no options or arguments
-exit with no options (however exit values were still expected to be handled)
```
**We did not complete the bonus.**
```
An important note on leaks, it was outlined in the subject that READLINE is known to leak, as such we built a readline supression file to truncate any leaks we had to make parsing and triage easier.
```

## Parsing
**Tokenize** -> **Parse** ; Also handles **Expansion**
### Lexar
**tokenizing.c**\
Used to create a linked list of token structs. Input values are deliminated by space or tab.\
As we read through the inputs, we check if the first char is a PIPE, a REDIR_IN, or a REDIR_OUT, and skip whitespace. If we detect a SPECIAL, we set the type of a token to said type.\
Otherwise, we assume it is a word.
### Parsing
**parsing.c**\
(WRITE STUFF HERE)
### Expansion
**expansion.c**\
(WRITE STUFF HERE)
## Execution
**execve** ; **built-ins**
### HEREDOC
**HEREDOC** is a way to create a temp file to use as STDIN for another command.\
Invoked with: `<< EOF` where `EOF` is a custom "end word" (delimiter). \
HEREDOC will write to a temporary file, and once the delimiter is found, will output the contents
of the temporary file to STDIN. This makes it a useful tool for writing multiple lines to STDIN.\
A HEREDOC natively expands environment variables, script variables, can run commands and even calculate math. However, in our implementation, it will only expand environment variables. If the HEREDOC is called with the delimiter inside of quotes (`'EOF'` or `"EOF"`), the HEREDOC will not expand anything inside the content of the HEREDOC.
# Instructions

Clone the repository:
```
git clone "repo goes here"
```

Build with make:
```
make
```
Run with:
```
./minishell
```
We have the following additonal makefile rules:
```
re, clean, fclean
```

# Resources
[Medium:--MannBell]\
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

[Lets build a Shell:--Video]\
https://www.youtube.com/watch?v=yTR00r8vBH8

[Bash Manual]\
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/
## LLMs Used:
- **Claude**: Used for project planning. Used extensively for HEREDOC implementation.
- **Gemini**: Used to help understand Valgrind output and helped find & fix leaks.
- **ChatGPT**: Used for creating the Parsing and Built-In commands.
