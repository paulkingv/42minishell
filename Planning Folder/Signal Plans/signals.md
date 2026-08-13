# What is <signals.h> and how did we use it?
`<signals.h>` is a library that describes a struct called `sigaction`, contains functions, and **MACROS**.

Signals are used to send things like Ctrl+C, Ctrl+D, Ctrl+\ .\
The program wont know what do do on reciept of one of these, so we have to point it to the **handler**.\
## The signals
This is important because for minishell we need to handle 2 signal types (and one Ctrl+D):
d
	Ctrl+C = SIGINT signal
	Ctrl+\ = SIGQUIT signal
	Ctrl+D = EOF

### Ctrl+C 
Is the first half of the actual problem
### Ctrl+\
Is the second half of the problem
### Ctrl+D
The actual - non problem

The three are handled by the minishell code with the following 
## The function(s)
To do that, we need to use one of two functions:--\
### Sigaction
`sigaction(signal_type, &your_sigaction_struct, NULL (IDK))`

this is the modern way. Describe your signal type, and handle it with your struct. \

### Signal
`signal()`

Original way

## The struct
Here is the sigaction struct \
```
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
```

