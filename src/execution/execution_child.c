/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:43:59 by pking             #+#    #+#             */
/*   Updated: 2026/08/28 05:39:51 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Actual child executing the cmd part
static void child_execute_command(t_shell *shell, t_cmd *tmp_cmd)
{
	char	*valid_cmd;
	char	**envp;
	int		exit_code;
	
	if (!tmp_cmd->args || !tmp_cmd->args[0])
		exit(free_shell(shell));
	if (is_builtin(tmp_cmd))
		exec_child_builtin(shell, tmp_cmd);
	envp = env_to_array(shell->env);
	valid_cmd = exec_get_valid_path(shell, tmp_cmd->args[0], &exit_code);
	if (valid_cmd == NULL)
		invalid_cmd_cleanup(shell, tmp_cmd, envp, exit_code);
	execve(valid_cmd, tmp_cmd->args, envp);
	perror(tmp_cmd->args[0]);
	free(valid_cmd);
	free_array(envp);
	free_shell(shell);
	exit(126);
}

// setup fds and redirections of child process
static void child_setup_io(int prev_fd, int pipe_fd[2], t_cmd *tmp_cmd,
	t_shell *shell)
{

	if (tmp_cmd->redirections
		&& read_heredocs(tmp_cmd->redirections, shell) == -1)
		{
			if (g_signal_status == SIGINT)
				exit(130);
			exit(1);
		}
	is_prevfd_registered(prev_fd);
	if (tmp_cmd->next)
		safe_dup2(pipe_fd[1], STDOUT_FILENO);
	if (tmp_cmd->next)
		exec_close_pipe(pipe_fd);
	if (tmp_cmd->redirections)
		handle_redirects(tmp_cmd->redirections, shell->env, shell);
}

//main entry
void	child_exe_cmd(int prev_fd, int pipe_fd[2],
	t_shell *shell, t_cmd *tmp_cmd)
{
	default_signals();
	child_setup_io(prev_fd, pipe_fd, tmp_cmd, shell);
	child_execute_command(shell, tmp_cmd);
}
