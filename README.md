*This project was created as a part of the 42 curriculum by pking and jfox.*

# Minishell
*Because making our own shell will come in handy someday, right?*

# Description
**Minishell** is a 42 project where students are tasked with creating their own Shell as a team.\
**pking** will handle **execution** and **jfox** will handle **parsing**. Both teammates must understand and be able to adjust each other's code if need be.
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
- Compile with `make`.
- Recompile with `make re`.
- Clean the dir with `clean`.
- Fully reset the project with `make fclean`.
- Run with `./minishell`.

# Resources
[Medium:--MannBell](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
## LLMs Used:
- **Claude**: Used for project planning. Used extensively for HEREDOC implementation.
- **Gemini**: Used to help understand Valgrind output and helped find & fix leaks.
- **ChatGPT**: Used for creating the Parsing and Built-In commands.
