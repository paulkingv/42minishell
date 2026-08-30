/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j.fox <jfox.42angouleme@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 14:33:29 by jfox              #+#    #+#             */
/*   Updated: 2026/08/30 10:04:48 by j.fox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a strjoin helper to append our exapnded string onto the original
char	*ap_string(char *s1, char *s2)
{
	char	*tmp;

	if (!s1)
		return (NULL);
	if (!s2)
		s2 = "";
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	free(s1);
	return (tmp);
}

// a strjoin helper but for appending a single char
char	*append_char(char *string, char c)
{
	char	r[2];
	char	*tmp;

	if (!string || ! c)
		return (NULL);
	r[0] = c;
	r[1] = '\0';
	tmp = ft_strjoin(string, r);
	if (!tmp)
		return (NULL);
	free(string);
	return (tmp);
}

// as we already know if we are dealing with an exapansion that is not
// single $ or $?, $" we can now find the word we need to exapand before
// we pass it to find env.
char	*find_word(char *word)
{
	char	*ret;
	int		i;

	ret = "";
	i = 0;
	while (ft_isalnum(word[i]) || word[i] == '_')
		i++;
	i++;
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, word, i);
	return (ret);
}

// covers if the word is a single $ followed by ", in this case returning
// an empty string
void	expand_dollar(t_shell *shell, t_exp *fields, char *w, int *i)
{
	char	*tmp;

	if (w[*i + 1] == '"' && !shell->dquote)
	{
		fields->string = ap_string(fields->string, "");
		return ;
	}
	if (!w[*i + 1] || (!ft_isalnum(w[*i + 1]) && w[*i + 1] != '_' 
		&& w[*i + 1] != '?'))
	{
		fields->string = ap_string(fields->string, "$");
		return ;
	}
	tmp = expansion(shell, &w[*i], i);
	if (!tmp)
		return ;
	if (shell->dquote)
		fields->string = ap_string(fields->string, tmp);
	else
	{
		split_expansion(fields, tmp);
		if (fields->tokens)
			fields->string = ap_string(fields->string, fields->tokens->value);
	}
	free(tmp);
}
