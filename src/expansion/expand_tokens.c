/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:06:01 by jfox              #+#    #+#             */
/*   Updated: 2026/08/12 18:10:12 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_string(char *s1, char *s2)
{
	char	*tmp;

	if (!s2)
		s2 = "";
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

static char	*append_char(char *string, char c)
{
	char	r[2];
	char	*tmp;

	r[0] = c;
	r[1] = '\0';
	tmp = ft_strjoin(string, r);
	free(string);
	return (tmp);
}

static char	*find_word(char *word)
{
	char	*ret;
	int		i;

	ret = "";
	i = 0;
	while (ft_isalnum(word[i]))
		i++;
	i++;
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, word, i);
	return (ret);
}

static char	*expansion(t_shell *shell, char *word, int *i)
{
	t_env	*tenv;
	char	*tmp;
	char	*value;
	char	*string;

	tenv = shell->env;
	word++;
	if (!ft_strcmp(word, "?"))
	{
		value = ft_itoa(shell->exit);
		*i += ft_strlen(word);
		return (value);
	}
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
			tmp = expansion(shell, &word[i], &i);
			string = append_string(string, tmp);
			free(tmp);
		}
		else
			string = append_char(string, word[i]);
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
			free(tmptok->value);
			tmptok->value = expanded;
		}
		tmptok = tmptok->next;
	}
	return (0);
}
