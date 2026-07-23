/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/07/23 11:51:47 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo with option -n
void	ft_echo(t_shell *shell)
{
	t_cmd	*tmp = NULL;
	char	**arg;
	int		i;

	tmp = shell->cmdline;
	arg = tmp->args;
	i = 1;
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i+1])
			ft_printf(" ", arg[i]);
		i++;
	}
	ft_printf("\n", arg[i]);
}

// cd with only a relative or absolute path


// ****NOTE FROM PAUL:****
// 				The functions need to access shell->exit and set the int from the exit code of the builtin
//				Alternatively, you can return an int upwards, and we will accomodate the setting of shell->exit above
//				I prefer option 2 because we can use exit(exec_builtin(cmd))
int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*new_path;
	char	*old_path;
	int		status;

	status = 0;
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
	return (status);
}

// pwd with no options
int	ft_pwd(void)
{
	char	cwd[PATH_MAX];
	int		status;

	status = 0;
	if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
	return (status);
}

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp = NULL;
	t_cmd	*tmp_cmd = NULL;
	char	**strings;
	int		status;

	status = 0;
	tmp = shell->env;
	tmp_cmd = cmd;
	strings = ft_split(tmp_cmd->args[1], '=');
	set_env(&tmp, strings[0], strings[1]);
	free_array(strings);
	return (status);
}

// unset with no options
int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int status;

	status = 0;
	unset_env(&shell->env, cmd->args[1]);
	return (status);
}

// env with no options or arguments
int	ft_env(t_shell *shell)
{
	t_env	*tmp = NULL;
	int		status;

	status = 0;
	tmp = shell->env;
	while(tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (status);
}

// exit with no options
int	ft_exit(t_shell *shell)
{
	shell->status = 0;
	shell->exit = 0;
	ft_printf("exit\n");
	return (0);
}
