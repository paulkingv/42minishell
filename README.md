*This project was created as a part of the 42 curriculum by pking and jfox.*

# Minishell
*Because making our own shell will come in handy someday, right?*

# Description
Minishell is a 42 project where students are tasked with creating their own Shell as a team. That means we need to handle **parsing** and **execution**.
## Parsing
**Tokenize** -> **Parse**
### Tokenizing
**Version1:parsing.c:** Using the parsing.c file (will be renamed to tokenizing.c) we create a linked list of structs. Input values are deliminated by space or tab.\
As we read through the inputs, we check if the first char is a PIPE, a REDIR_IN, or a REDIR_OUT, and skip whitespace. If we detect a SPECIAL, we set the type of a token to said type.\
Otherwise, we assume it is a word.
## Execution 

# Instructions

# Resources

## LLMs Used:
 - Claude
 - Gemini
**Claude**: Used for project planning.
**Gemini**: Used to help understand Valgrind output and helped find & fix leaks.
