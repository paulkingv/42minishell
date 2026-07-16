# What is the sys/wait.h header?
This header is useful for when we want to create programs that have children, because it gives us access to some very useful macros. The macros in question are:

`WIFEXITED`\
For if the process exited normally via `exit()` or `return`;\
`WEXITSTATUS`\
For converting the encoded exit status to decimal;\
`WIFSIGNALED`\
For if the process was terminated by a signal;\
`WIFSTOPPED`\
For if the process was stopped (not terminated);\
`WIFCONTINUED`\
Process was resumed (requires `WCONTINUED` flag)
`WTERMSIG`\
VERY USEFUL for understanding which signal number killed the child.\
	SIGINT (Ctrl+C) = 2\
	SIGTERM			= 15\
	SIGKILL			= 9

## Wait and WaitPID
It also gives us access to important functions:

`wait()` and `waitpid()`;

`waitpid(pid, wstatus, option_code)`
This is very important to understand. This function awaits a certain *PID* and when it recieves it, it puts the exit code of the child inside the wstatus parameter. Option_code is used for specifying specific options (idk them), just used 0 in minish.

