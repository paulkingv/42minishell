/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:06:01 by jfox              #+#    #+#             */
/*   Updated: 2026/08/28 23:10:27 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper to resolve if the current character is either a single doller,
// or if it needs to be exanded to the exit status.
// edge case handling for multiple $$$
static char	*find_value(t_shell *shell, char *word, int *i)
{
	char	*value;

	if (!word[1])
	{
		value = ft_strdup("$");
		return (value);
	}
	if (word[1] == '?')
	{
		value = ft_itoa(shell->exit);
		*i += 1;
		return (value);
	}
	if (!ft_isalnum(word[1]) && word[1] != '_')
	{
		value = ft_strdup("$");
		return (value);
	}
	return (NULL);
}

// using our environment we look for value of the desired variable name
// returning it to be appended by expand word.
// before that we check the value is simply a $ or needs to expand to exit state
char	*expansion(t_shell *shell, char *word, int *i)
{
	t_env	*tenv;
	char	*tmp;
	char	*value;
	char	*string;

	tenv = shell->env;
	value = find_value(shell, word, i);
	if (value)
		return (value);
	word++;
	string = find_word(word);
	if (!find_env(tenv, string))
	{
		*i += ft_strlen(string);
		free(string);
		return (NULL);
	}
	tmp = get_env(tenv, string);
	value = ft_strdup(tmp);
	*i += ft_strlen(string);
	free(string);
	return (value);
}

// simple helper to set quote bools to 0 or 1 depending on the char recieved
// this is critical following the execution of this function as it helps us
// determine if strings are literal or need expanding
static int	set_quotes(char c, int *dquote, int *squote)
{
	if (c == '\'' && !*dquote)
	{
		*squote = !*squote;
		return (1);
	}
	else if (c == '"' && !*squote)
	{
		*dquote = !*dquote;
		return (1);
	}
	return (0);
}

// we initially decide if the word is quoted in single or double quotes
// tokenize has already removed any cases of words with missing quotes, so here
// we check for quotes at the start of the word and then what follows.
// if we detect $ we move to expansion, but before that we check and we can
// even handle $" situations by simply appending an empty string, then we move
// into expansion on the next pass of the while loop.
// expansion will return us a string value that we can append onto the string
// we currently have, we use a pointer to i to move through the string in this
// function and in the other, so we can jump over the word we are expanding.
static char	*expand_word(t_shell *shell, char *word, char* string, int i)
{
	string = ft_strdup("");
	if (!string)
		return (NULL);
	while (word[i])
	{
		if (!set_quotes(word[i], &shell->dquote, &shell->squote))
		{
			if (word[i] == '$' && !shell->squote)
				string = help_expand_dollar(shell, string, word, &i);
			else
				string = append_char(string, word[i]);
			if (!string)
				return (NULL);
		}
		i++;
	}
	return (string);
}

// work though a list of tokens finding quotes, $ and ? and expanding all cases
// we take the next token in the list, then expand the token we are on.
// pass to expand word.
// expand word returns a fully expanded and complete string, if that string is
// empty we free the string and remove the token.
// if the expansion resolves we replace the value at our current position with
// the new value.
int	expand_tokens(t_shell *shell, t_token *tok, t_token *ttok, t_token *n)
{
	char	*expanded;

	ttok = tok;
	while (ttok)
	{
		n = ttok->next;
		if (ttok->type == HEREDOC && ttok->next)
		{
			ttok = ttok->next->next;
			continue;
		}
		if (ttok->type == WORD)
		{
			expanded = expand_word(shell, ttok->value, NULL, 0);
			if (!expanded)
				return (1);
			if (expanded[0] == '\0' && !is_quoted(ttok->value))
			{
				free(expanded);
				remove_token(&shell->tokens, ttok);
			}
			else
			{
				free(ttok->value);
				ttok->value = expanded;
			}
		}
		ttok = n;
	}
	return (0);
}
