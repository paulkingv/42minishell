# Planning Solve 230
validate_tokens -> objective: We go through cmdline to make sure that our paresed tokens are correct

```
token types:
typedef enum e_token_type
{
	TYPE_EOF = 0 << 0,	// 0x00000000 0
	WORD = 1 << 0,		// 0x00000001 1
	PIPE = 1 << 1,		// 0x00000010 2		( |  )
	REDIR_OUT = 1 << 2,	// 0x00000100 4		( >  )
	REDIR_IN = 1 << 3,	// 0x00001000 8		( <  )
	APPEND = 1 << 4,	// 0x00010000 16	( >> )
	HEREDOC = 1 << 5,	// 0x00100000 32	( << )
}	t_token_type;
```

int		print_errors(int code) //needs better name
{
	if (code == 1)

	if (code == 2)

	if (code == 3)

	//if (code == 4)
	//if (code == 5)
}
	if ((clone->type == REDIR) && (clone->next != WORD || clone->next == NULL))
```
int validate_tokens(t_token *token) // exit value needs to get changed
{
	t_token *clone;
	int 	error;

	error = 0;
	clone = token;
	if (!clone)
		return (-1);
	if ((clone->type == PIPE)) //only happens first time funct runs - check pipe as first
		error = print_error(1);
	while (clone) // check the rest of tokens
	{
// first, we cannot have redir without a filename after
		if ((clone->type == PIPE)) // >,<,>>
		{
			if ((clone->next == NULL) || (clone->next->type == PIPE))
				error = print_error(2);
		}
	/* second, we have consecutive redirects (wiring gets scrambled) < >
		also checks the case where we have an ending pipe/redir 
	*/
	
// if clone & next are redirs/pipe (not hd) / clone & !next // 
		if (((clone->type & 0x00011110) && (clone->next->type & 0x00011110)) 
		|| ((clone->type & 0x00011110) && (clone->next == NULL)))
			error = print_error(3);

// third, check if token after redir is WORD
		if ((clone->type == REDIR) && (clone->next->type != WORD || clone->next == NULL))
			error = print_error(4);
		clone = clone->next;
	}
	return (error);
}
```