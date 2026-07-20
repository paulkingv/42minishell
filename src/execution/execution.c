/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:09:24 by pking             #+#    #+#             */
/*   Updated: 2026/07/20 15:45:30 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the number of the write end of pipe to the prev_fd for use in next iter
// Also handles cleaning up (closing)
// Added tmp struct to not touch shell.
static int parent_cleanup_exe_cmd(int prev_fd, int pipe_fd[2], t_shell *shell)
{
	t_cmd	*cmd_line = NULL;

	cmd_line = shell->cmdline;
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd_line)
	{
		close(pipe_fd[1]);
		return(pipe_fd[0]);
	}
	return (-1);
}
// Actual child executing the cmd part
// Added temp structs to not mess with shell.
static void child_exe_cmd(int prev_fd, int pipe_fd[2], t_shell *shell)
{
	t_cmd	*cmdline = NULL;
	t_redir	*is_redir = NULL;
	char	**envp;

	cmdline = shell->cmdline;
	is_redir = cmdline->redirections;
	if (prev_fd != -1) // if prev_fd is registered
	{
	// HOOK Up the content as the STDIN
		safe_dup2(prev_fd, STDIN_FILENO);
		close(prev_fd); // unmaps the value of prev_fd (val points to no existing FD)
	}
	if (cmdline->next) // have to set up where we write to. Pipe FD overwrite STDOUT
		safe_dup2(pipe_fd[1], STDOUT_FILENO);

	exec_close_pipe(pipe_fd);
	if (is_redir)
		handle_redirects(is_redir);
	envp = env_to_array(shell->env);
	execve(cmdline->args[0], cmdline->args, envp);
	perror("execve error in child");
	exit(1);
}
// The meat function. This is called in order to execute the line that has been parsed.
// Added tmp structs to not touch shell. This function needs allot of work as it's too big.
void exe_cmdline(t_shell *shell)
{
	t_shell	*tmp = NULL;
	t_cmd	*tmp_cmd = NULL;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t 	pid;

	tmp = shell;
	tmp_cmd = shell->cmdline;
	prev_fd = -1;		// Prev FD exists out of Bounds (aka not registered)
	while (tmp_cmd)
	{
		if (is_builtin(tmp_cmd))
		{
			exec_builtin(shell, tmp_cmd);
			tmp_cmd = tmp_cmd->next;
			continue; // this keyword resets the while(cmd) loop from the top
		}
		if (tmp->cmdline->next)
			safe_pipe(pipe_fd); // error handling pipe improved function
		pid = safe_fork(); // error handling fork improved function
		if (pid == 0)
			child_exe_cmd(prev_fd, pipe_fd, shell);
		prev_fd = parent_cleanup_exe_cmd(prev_fd, pipe_fd, shell);
		tmp_cmd = tmp_cmd->next;
	}
	while (waitpid(-1, &shell->exit, 0) > 0) // Special waiting line (Need 2 research)
		safe_exit(&shell->exit, shell);
}
