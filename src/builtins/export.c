/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/07/29 15:12:25 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_export_util(t_cmd *cmd, int i)
{
	char	**strings;

	if (!ft_strchr(cmd->args[i], '='))
	{
		strings = ft_split(cmd->args[i], '=');
		return (strings);
	}
	strings = ft_split(cmd->args[i], '=');
	if (strings && !strings[1])
		strings[1] = "\"\"";
	return (strings);
}

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd, t_env *tmp, t_cmd *tmp_cmd)
{
	char	**strings;
	int		i;

	tmp = shell->env;
	tmp_cmd = cmd;
	i = 1;
	if (!tmp_cmd->args[i])
		ft_env(shell);
	while (tmp_cmd->args[i])
	{
		if (ft_isdigit(tmp_cmd->args[i][0]))
		{
			if (tmp_cmd->args[i + 1] == NULL)
				break ;
			i++;
		}
		strings = ft_export_util(tmp_cmd, i);
		set_env(&tmp, strings[0], strings[1]);
		i++;
	}
	return (0);
}
