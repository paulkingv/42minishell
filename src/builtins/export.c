/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/07/28 16:50:19 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_export_util(t_env *tmp, t_cmd *cmd, char **string, int i)
// {
// 	if (!ft_strchr(cmd->args[i], '='))
// 	{
// 		set_env(&tmp, string[0], NULL);
// 		return (1);
// 	}
// 	if (string && !string[1])
// 	{
// 		set_env(&tmp, string[0], "\"\"");
// 		return (1);
// 	}
// 	return (0);
// }

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd, t_env *tmp, t_cmd *tmp_cmd)
{
	// char	**strings;
	int		i;

	tmp = shell->env;
	tmp_cmd = cmd;
	i = 1;
	if (!cmd->args[1])
		ft_env(shell);
	while (tmp_cmd->args[i])
	{

		i++;
	}
	return (0);
}

	// while (tmp_cmd->args[i])
	// {

	// 	exit = ft_export_util(tmp, tmp_cmd, &tmp_cmd->args[i], i);
	// 	if (exit == 1)
	// 		return (exit);
	// 	strings = ft_split(tmp_cmd->args[i], '=');
	// 	exit = ft_export_util(shell, tmp, tmp_cmd, strings);
	// 	if (exit == 1)
	// 		return (exit);
	// 	set_env(&tmp, strings[0], strings[1]);
	// 	free_array(strings);


	// 	i++;
	// }