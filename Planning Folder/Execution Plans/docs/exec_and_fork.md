# Execv and Fork

First, what am i even talking about?
**Execv** is a function that allows you to turn the current process into a different program. For example, we can use it to run `/bin/ls`, which is the ls command.

When we use execv it *kills* the process that called it. So we need a "decoy" of sorts to use it effectively in this case.

The whole design of Minishell is to  execute and then continue, returning the prompt back to the user. so we cant use execv in the actual program; that would kill the whole thing every time we ran a command, and we would need to restart the minishell program

*Instead*, we use the **fork()** command to *create a child process*. A child process is meant to be killed eventually. So by using **execv** in the child process, it just goes back up one layer, returning us to the parent. 

**fork()** can be used to run commands in parallel, but because of how our shell wants to run things one after another, we do not have to do that. 

Here is the prototype of **execv:**
`int execv(const char *pathname, char *const argv[]);`
Essentially, execv needs two things: where the program is located, and what arguments you want to pass to it.
Therefore, when we call it, we need to specify the path, and then we place the whole input as argv (parameter 2).