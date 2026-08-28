/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:46 by pking             #+#    #+#             */
/*   Updated: 2026/08/28 05:39:00 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
// # if defined(__APPLE__)
// # include <sys/syslimits.h> //PATH_MAX, ARG_MAX on macOS
// # else
// # include <linux/limits.h>
// # endif
# include <stdio.h> // printf
# include <unistd.h> // pipes, fork, getpid, execve, dup2
# include <fcntl.h> // FOR READ
# include <sys/wait.h> // waitpid(), WIFEXITED, WEXITSTATUS
# include <sys/types.h> // pid_t datatype,
# include <readline/readline.h> // for readline
# include <readline/history.h> //for readline's history (sh history)
# include <stdlib.h> //malloc
# include <signal.h> // signals
# include <limits.h>
# include <errno.h> // EINTR
# include <sys/stat.h> // stat: file info, lstat: stat no symlink, fstat: on open fds

//**********************************GLOBAL************************************//
extern volatile sig_atomic_t	g_signal_status; // pk- I will finish this l8r

//**********************************DEFINES***********************************//
typedef unsigned long long		t_ull;
// # define REDIR_MASK (REDIR_OUT | REDIR_IN | APPEND | HEREDOC)
// # define OPERATOR_MASK (REDIR_OUT | REDIR_IN | APPEND | HEREDOC | PIPE)
# define DFLT_PTH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

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
	SEMICOLON = 1 << 6, // 0x01000000 64
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/*~~~~~~~~~~~PARSING~~~~~~~~~~~*/
// CMD: Linked List of each Command, with flags. Stores REDIR struct
// REDIR: Linked List of REDIR and where to direct the output.
// Only Used if REDIR detected.
typedef struct s_redir
{
	char			*file_name;		// Output file name
	t_token_type	type;			// Type of REDIR
	int				quoted;			// Quoted Status
	int				heredoc_fd;
	struct s_redir	*next;			// Pointer to next REDIR node
}	t_redir;

typedef struct s_cmd
{
	char			**args;			// ARGV: [cmd] [flag]
	t_redir			*redirections;	// Only used if REDIR is used
	int				separator;
	struct s_cmd	*next;			// Pointer to next CMD node
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
	char	*input;
	int		status;
	int		exit;
	int		dquote;
	int		squote;
	int		path_was_unset;
}	t_shell;

//******************************FOLDERS/FUNCTIONS*****************************//

//**********************************SRC/SHELL*********************************//
//------------SHELL.C------------//
// t_shell	*shell_init(char **envp);
char	*ft_path(t_shell *minishell);

//-----------FREE_SHELL.C--------//
int		free_shell(t_shell *shell);

//-----------free_utils.C-------------//
void	free_tokens(t_token **tokens);
void	free_env(t_env **s_env);
void	free_cmd(t_cmd **cmdline);
void	free_array(char **array);
//static void	free_redirections(t_cmd *current);

//**********************************SRC/TOKENIZE******************************//
//--------TOKENIZING.C---------//
t_token	*make_new_token(t_token_type type, char *input);
t_token	*tokenize(char *input, t_shell *shell);

//-------token_utils.C--------//
void	remove_token(t_token **head, t_token *key);

//-------token_validation.C--------//
int		token_validation(t_token *token, t_shell *shell);

//**********************************SRC/ENVIRONMENT***************************//
//--------ENVIRONMENT.C-------//
t_env	*init_env(char **envp, t_env *head, t_env *new);
t_env	*edit_env(t_env *s_env, char *key, char *new_node);
void	set_env(t_env **s_env, char *key, char *value);
void	unset_env(t_env **head, char *key);
void	env_add_back(t_env **head, t_env *new_node);

//----environment_utils.c-----//
t_env	*new_env(char *key, char *value);
t_env	*find_env(t_env *s_env, char *key);
char	*get_env(t_env *s_env, char	*key);
void	free_vals(char *key, char *value);
void	setpwd(t_env **head);

//*********************************SRC/EXPANSION******************************//
//-----------process.C-----------//
int		process(t_shell *shell, t_token *tokens);

//--------expand_tokens.c--------//
int		expand_tokens(t_shell *shell, t_token *tok, t_token *ttok, t_token *n);
char	*expansion(t_shell *shell, char *word, int *i);
// static char	*find_value(t_shell *shell, char *word, int *i);
// static char	*expand_word(t_shell *shell, char *word, char* string, int i);
// static int	set_quotes(char c, int *dquote, int *squote);

//---------expand_utils.c--------//
char	*help_expand_dollar(t_shell *shell, char *string, char *word, int *i);
char	*append_char(char *string, char c);
char	*append_string(char *s1, char *s2);
char	*find_word(char *word);
int		is_quoted(char *word);

//**********************************SRC/PARSING*******************************//
//-----------PARSING.C-----------//
t_cmd	*parse(t_shell *shell, t_cmd *head, t_cmd *current, t_token *tmp);
// static t_cmd	*new_cmd(void);
// static int	count_args(t_token *tokens);
// static void	sort_tokens(t_cmd *cmd_current, t_token *token, int count)

//------parsing_redirects.c------//
void	sort_redirections(t_shell *shell, t_cmd *cmd_current, t_token **tmp);
// static int	hd_error(t_redir *new, char *value, int qstatus, int etype);
// static t_redir	*new_redir(char *value, t_token_type num);
// static void		redir_add_back(t_redir **head, t_redir *new);

//------parsing_heredoc.c------//
int		is_hd_quoted(char *value);
int		strip_quotes(char *value);

//**********************************SRC/BUILTINS******************************//
//-------builtin-utils.c-------//
int		ft_unset(t_shell *shell, t_cmd *cmd);
int		ft_env(t_shell *shell);

//------------cd.c-------------//
int		ft_cd(t_shell *shell, t_cmd *cmd, char *new_path, char *old_path);
// static int	no_chdir(t_shell *shell, char *old_path, char *new_path);
// static void	print_newpath(char *new_path);
// static int act_cd(t_shell *shell, t_cmd *cmd, char *new_path, char *old_path)

//-----------echo.c------------//
int		ft_echo(t_cmd *cmd, int newline, int i);
// static int	is_n_option(char *arg);

//-----------exit.c------------//
int		ft_exit(t_shell *shell, t_cmd *cmd);
// static int  check_number(char *str, long long *val);

//--------exit_utils.c---------//
void	require_number(t_shell *shell, char *arg);
void	handle_whitespace(char *str, int *i);
t_ull	find_limit(int sign);
int		set_sign(char c, int *i);

//----------export.c-----------//
int		ft_export(t_shell *shell, t_cmd *cmd, t_cmd *tcmd);
// static void	ft_print_export(t_shell *shell);
// static char	**ft_export_util(t_cmd *cmd, int i);
// static int	append(char *arg);
// static void	append_env(t_shell *shell, char *key, char *value);

//-------export_utils.c--------//
t_env	**export_array(t_env *env);
void	sort_array(t_env **array);
int		valid_export(char *arg);
void	print_export_error(char *arg);
//static int		env_count(t_env	*env);

//------------pwd.c------------//
int		ft_pwd(t_shell *shell);

//**********************************SRC/EXECUTION*****************************//
//--------EXECUTION.c----------//
void	exe_cmdline(t_shell *shell);
void	invalid_cmd_cleanup(t_shell *shell, t_cmd *cmdline,
	char **envp, int exit_code);

//------execution_child.c------//
void	child_exe_cmd(int prev_fd, int pipe_fd[2],
	t_shell *shell, t_cmd *tmp_cmd);

//--------env_to_array.c-------//
char	**env_to_array(t_env *env);

//------exec_utils.c------//
void	exec_close_pipe(int pipe_fd[2]);
void	is_prevfd_registered(int prev_fd);

//--------env_to_array.c-------//
char	**env_to_array(t_env *env);

//-----exec_handle_redir.c-----//
int		open_redir_file(t_redir *redir);
int		read_heredocs(t_redir *redir, t_shell *shell);
int		handle_redirects(t_redir *redir, t_env *env, t_shell *shell);

//-----exec_safety_funct.c-----//
int		safe_dup2(int fd, int target_fd);
pid_t	safe_fork(void);
int		safe_pipe(int pipe_fd[2]);
void	wait_for_children(pid_t last_pid, t_shell *shell);

//-----exec_check_stat.c----------//
int		path_exists(char *path);
int		is_directory(char *path);

//-----exec_get_path.c----------//
char	*exec_get_valid_path(t_shell *shell, char *cmd, int *exit_code);

//**********************************SRC/EXECUTION/INIT************************//
//-----EXEC_INIT_PIPEFD.C-------//
void	exec_init_pipefd(int pipe_fd[2]);

//**********************************SRC/EXECUTION/EXEC_BUILTIN****************//
//--------EXEC_BUILTIN.C-------//
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_shell *shell, t_cmd *cmd);

//--------exec_child_builtin.c--//
void	exec_child_builtin(t_shell *shell, t_cmd *cmd);

//**********************************SRC/EXECUTION/EXEC_HEREDOC****************//
int		handle_heredoc(t_redir *redir, t_shell *shell);
char	*expand_heredoc(t_shell *shell, char *line);
void	finish_heredoc(char *line, int fd);

//**********************************SRC/SIGNAL****************//
//--------signal_parent.C-------//
void	init_signals(int argc, char **argv);
void	reset_signals(void);
void	parent_wait_signals(void);

//--------signal_child.C--------//
void	default_signals(void);
void	heredoc_signals(void);

#endif