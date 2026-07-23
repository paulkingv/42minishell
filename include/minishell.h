/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:46 by pking             #+#    #+#             */
/*   Updated: 2026/07/23 11:59:05 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <linux/limits.h>
#include <stdio.h> // printf
#include <unistd.h> // pipes, fork, getpid, execve, dup2
#include <fcntl.h> // FOR READ
#include <sys/wait.h> // waitpid(), WIFEXITED, WEXITSTATUS
#include <sys/types.h> // pid_t datatype,
#include <readline/readline.h> // for readline
#include <readline/history.h> //for readline's history (sh history)
#include <stdlib.h> //malloc

//**********************************STRUCTS***********************************//

/*~~~~~~~~TOKENIZATION~~~~~~~~~*/
typedef enum e_token_type
{
	TYPE_EOF = 0 << 0,	// 0x00000000 0
	WORD = 1 << 0,		// 0x00000001 1
	PIPE = 1 << 1,		// 0x00000010 2
	REDIR_OUT = 1 << 2,	// 0x00000100 4		( >  )
	REDIR_IN = 1 << 3,	// 0x00001000 8		( <  )
	APPEND = 1 << 4,	// 0x00010000 16	( >> )
	HEREDOC = 1 << 5,	// 0x00100000 32	( << )
	D_QUOTED = 1 << 6,	// 0x01000000 64
	S_QUOTED = 1 << 7	// 0x10000000 128
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/*~~~~~~~~~~~PARSING~~~~~~~~~~~*/
// CMD: Linked List of each Command, with flags. Stores REDIR struct
// REDIR: Linked List of REDIR and where to direct the output. Only Used if REDIR detected.
typedef struct	s_redir
{
	char			*file_name;		// Output file name
	t_token_type	type;			// Type of REDIR
	struct s_redir	*next;			// Pointer to next REDIR node
}	t_redir;

typedef struct	s_cmd
{
	char 				**args;			// ARGV: [cmd] [flag]
	t_redir				*redirections;	// Only used if REDIR is used
	struct s_cmd		*next;			// Pointer to next CMD node
}	t_cmd;

/*~~~~~~ENVIRONMENT VARS~~~~~~~*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*~~~~~~~~~~~~SHELL~~~~~~~~~~~~*/
typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmdline;
	int		status;
	int		exit;
}	t_shell;

//******************************FOLDERS/FUNCTIONS*****************************//

//**********************************SRC/SHELL*********************************//
//------------SHELL.C------------//
t_shell	*shell_init(char **envp);
char	*ft_path(t_shell *minishell);

//-----------FREE_SHELL.C--------//
int free_shell(t_shell *shell);

//-----------free_utils.C-------------//
void	free_tokens(t_token **tokens);
void	free_env(t_env **s_env);
void	free_cmd(t_cmd **cmdline);
void	free_array(char **array);
//static void	free_redirections(t_cmd *current);

//**********************************SRC/TOKENIZE******************************//
//--------TOKENIZING.C---------//
t_token *make_new_token(t_token_type type, char *input);
t_token *tokenize(char *input);

//**********************************SRC/ENVIRONMENT***************************//
//--------ENVIRONMENT.C-------//
t_env	*init_env(char **envp);
t_env	*edit_env(t_env *s_env, char *key, char *new_node);
void	set_env(t_env **s_env, char *key, char *value);
void	env_add_back(t_env **head, t_env *new_node);
void	unset_env(t_env **head, char *key);

//----environment_utils.c-----//
t_env	*new_env(char *key, char *value);
t_env	*find_env(t_env *s_env, char *key);
char	*get_env(t_env *s_env, char	*key);

//**********************************SRC/PARSING*******************************//
//-----------PARSING.C-----------//
t_cmd	*parse(t_token *tokens);
// static t_cmd	*new_cmd(void);
// static int	count_args(t_token *tokens);
// static void	sort_tokens(t_cmd *cmd_current, t_token *token, int count)

//------parsing_redirects.c------//
void	sort_redirections(t_cmd *cmd_current, t_token **tmp);
// static t_redir	*new_redir(char *value, t_token_type num);
// static void	redir_add_back(t_redir **head, t_redir *new);

//**********************************SRC/BUILTINS******************************//
//-----------BUILTIN.C-----------//
void	ft_echo(t_shell *shell);
void	ft_cd(t_shell *shell, t_cmd *cmd);
void	ft_pwd();
void	ft_env(t_shell *shell);
void	ft_unset(t_shell *shell, t_cmd *cmd);
void	ft_export(t_shell *shell, t_cmd *cmd);
void	ft_exit(t_shell *shell);

//**********************************SRC/EXECUTION*****************************//
//--------EXECUTION.c----------//
void 	exe_cmdline(t_shell *shell);

//--------env_to_array.c-------//
char	**env_to_array(t_env *env);

//------exec_close_pipe.c------//
void	exec_close_pipe(int pipe_fd[2]);

//--------env_to_array.c-------//
char	**env_to_array(t_env *env);

//-----exec_handle_redir.c-----//
int		open_redir_file(t_redir *redir);
int		handle_redirects(t_redir *redir);

//-----exec_safety_funct.c-----//
int 	safe_dup2(int fd, int target_fd);
pid_t	safe_fork(void);
int		safe_pipe(int pipe_fd[2]);
void 	wait_for_children(pid_t last_pid, t_shell *shell);

//-----exec_get_path.c----------//
char	*exec_get_valid_path(t_shell *shell, char *cmd);

//**********************************SRC/EXECUTION/INIT************************//
//-----EXEC_INIT_PIPEFD.C-------//
void	exec_init_pipefd(int pipe_fd[2]);

//**********************************SRC/EXECUTION/EXEC_BUILTIN****************//
//--------EXEC_BUILTIN.C-------//
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

//--------exec_child_builtin.c--//
void exec_child_builtin(t_shell *shell, t_cmd *cmd);

#endif