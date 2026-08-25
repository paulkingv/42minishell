/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:06:01 by jfox              #+#    #+#             */
/*   Updated: 2026/08/25 00:07:16 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expansion(t_shell *shell, char *word, int *i)
{
	t_env	*tenv;
	char	*tmp;
	char	*value;
	char	*string;

	tenv = shell->env;
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

static char	*expand_word(t_shell *shell, char *word)
{
	int		dquote = 0;
	int		squote = 0;
	int		i;
	char	*string;
	char	*tmp;

	i = 0;
	string = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'' && !dquote)
			squote = !squote;
		else if (word[i] == '"' && !squote)
			dquote = !dquote;
		else if (word[i] == '$' && !squote)
		{
			if (word[i + 1] == '"' && !dquote)
        		string = append_string(string, "");
    		else
			{
				tmp = expansion(shell, &word[i], &i);
				string = append_string(string, tmp);
				free(tmp);
			}
		}
		else
			string = append_char(string, word[i]);
		i++;
	}
	return (string);
}

int	expand_tokens(t_shell *shell, t_token *tok, t_token *ttok, t_token *n)
{
	char	*expanded;

	ttok = tok;
	while (ttok)
	{
		n = ttok->next;
		if (ttok->type == WORD)
		{
			expanded = expand_word(shell, ttok->value);
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
