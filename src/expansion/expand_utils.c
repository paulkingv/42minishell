/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 14:33:29 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 14:38:13 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// confirms simply if the word specifically is quoted
int	is_quoted(char *word)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

// a strjoin helper to append our exapnded string onto the original
char	*append_string(char *s1, char *s2)
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
char	*help_expand_dollar(t_shell *shell, char *string, char *word, int *i)
{
	char	*tmp;

	if (word[*i + 1] == '"' && !shell->dquote)
		return (append_string(string, ""));
	tmp = expansion(shell, &word[*i], i);
	string = append_string(string, tmp);
	free(tmp);
	return (string);
}
