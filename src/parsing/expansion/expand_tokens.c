/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:06:01 by jfox              #+#    #+#             */
/*   Updated: 2026/08/11 19:40:37 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(t_shell *shell, char *word)
{
	(void)shell;

	word = ft_strdup("EXPANSION");
	return (word);
}

// this segfaults. fix ft_strjoin here
char	*expand_word(t_shell *shell, char *word)
{
	int		dquote = 0;
	int		squote = 0;
	int		i;
	char	*string;
	char	*tmp;

	i = 0;
	string = "";
	tmp = "";
	while (word[i])
	{
		if (word[i] == '\'' && !dquote)
			squote = !squote;
		else if (word[i] == '"' && !squote)
			dquote = !dquote;
		else if (word[i] == '$' && !squote)
		{
			tmp = expansion(shell, word);
			string = ft_strjoin(string, tmp);
		}
		else
			string = ft_strjoin(string, &word[i]);
		i++;
	}
	return (string);
}

int	expand_tokens(t_shell *shell, t_token *tokens)
{
	t_shell	*tmpshel;
	t_token	*tmptok;
	char	*expanded;

	tmptok = tokens;
	tmpshel = shell;
	while (tmptok)
	{
		if (tmptok->type == WORD)
		{
			expanded = expand_word(tmpshel, tmptok->value);
			if (!expanded)
				return (1);
			// free(tmptok->value);
			tmptok->value = expanded;
		}
		tmptok = tmptok->next;
	}
	return (0);
}
