/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/07/20 16:37:59 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Here we will start working on the main built in functions.
// useful now that we have environmental table made!

// // echo with option -n
// ft_echo(t_shell *shell)
// // cd with only a relative or absolute path
// ft_cd(t_shell *shell)
// // pwd with no options
// ft_pwd(t_shell *shell)
// export with no options
void	ft_export(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp = NULL;
	t_cmd	*tmp_cmd = NULL;
	char	**strings;

	tmp = shell->env;
	tmp_cmd = cmd;
	strings = ft_split(tmp_cmd->args[1], '=');
	set_env(&tmp, strings[0], strings[1]);
	free_array(strings);
}

// unset with no options
void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	unset_env(&shell->env, cmd->args[1]);
}

// env with no options or arguments
void	ft_env(t_shell *shell)
{
	t_env	*tmp = NULL;

	tmp = shell->env;
	while(tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
// // exit with no options
// ft_exit(t_shell *shell)
