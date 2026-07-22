/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/07/22 03:58:41 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Here we will start working on the main built in functions.
// useful now that we have environmental table made!

// echo with option -n
// void	ft_echo(t_shell *shell)
// {

// }

// cd with only a relative or absolute path


// ****NOTE FROM PAUL:**** 
// 				The functions need to access shell->exit and set the int from the exit code of the builtin
//				Alternatively, you can return an int upwards, and we will accomodate the setting of shell->exit above
//				I prefer option 2 because we can use exit(exec_builtin(cmd))
void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*new_path;
	char	*old_path;

	old_path = get_env(shell->env, "PWD");
	if (cmd->args[1])
		new_path = cmd->args[1];
	else
		new_path = get_env(shell->env, "HOME");
	if (!(chdir(new_path)))
	{
		set_env(&shell->env, "OLDPWD", old_path);
		set_env(&shell->env, "PWD", new_path);
	}
	else
		ft_printf("No such file or directory.\n");
}

// pwd with no options
void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
}

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

// exit with no options
void	ft_exit(t_shell *shell)
{
	shell->status = 0;
	shell->exit = 0;
	ft_printf("exit\n");
}
