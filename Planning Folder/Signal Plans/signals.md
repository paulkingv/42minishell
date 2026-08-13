# What is <signals.h> and What are Signals?
`<signals.h>` is a library that describes a struct called `sigaction`, contains functions, and **MACROS**.\
Signals are used to send things like Ctrl+C, Ctrl+D, Ctrl+/ .\
The program wont know what do do on reciept of one of these, so we have to point it to the **handler**.\
## The function(s)
To do that, we need to use one of two functions:--\
### Sigaction
`sigaction(signal_type, &your_sigaction_struct, what_to_do)`

this is the modern way

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