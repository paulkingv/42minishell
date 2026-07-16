/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:46 by pking             #+#    #+#             */
/*   Updated: 2026/07/16 14:30:21 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h> // printf
#include <unistd.h> // pipes, fork, getpid, execve, dup2
#include <sys/wait.h> // waitpid(),
#include <sys/types.h> // pid_t datatype,
#include <readline/readline.h> // for readline
#include <readline/history.h> //for readline's history (sh history)
#include <stdlib.h> //malloc

/*~~~~~~~~~~~~!!STRUCTS!!~~~~~~~~~~~~*/

/*~~~~~~~~TOKENIZATION~~~~~~~~~*/
typedef enum e_token_type
{
	TYPE_EOF = 0 << 0,	// 0x00000000 0
	WORD = 1 << 0,		// 0x00000001 1
	PIPE = 1 << 1,		// 0x00000010 2
	REDIR_OUT = 1 << 2,	// 0x00000100 4
	REDIR_IN = 1 << 3,	// 0x00001000 8
	APPEND = 1 << 4,	// 0x00010000 16
	HEREDOC = 1 << 5	// 0x00100000 32
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
	char 			**args;			// ARGV: [cmd] [flag]
	t_redir			*redirections;	// Only used if REDIR is used
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
	int		exit;
}	t_shell;

/*~~~~~~~~~~~!!FUNCTIONS!!~~~~~~~~~~~*/

//------------SHELL------------//
t_shell	*shell_init(char **envp);
char	*ft_path(t_shell *minishell);

//--------TOKENIZATION---------//
t_token	*make_new_token(t_token_type type, char *input);
t_token	*tokenize(char *input);

//---------ENVIRONMENT---------//
t_env	*init_env(char **envp);
t_env	*edit_env(t_env *s_env, char *key, char *new);
void	set_env(t_env **s_env, char *key, char *value);
void	env_add_back(t_env **head, t_env *new);
void	unset_env(t_env **head, char *key);

//------ENVIRONMENT UTILS------//
t_env	*new_env(char *key, char *value);
char	*get_env(t_env *s_env, char	*key);
t_env	*find_env(t_env *s_env, char *key);

//-----------PARSING-----------//
t_cmd	*parse(t_token *tokens);
// static t_cmd	*new_cmd(void);
// static int	count_args(t_token *tokens);
// static void	sort_tokens(t_cmd *cmd_current, t_token *token, int count)

//------PARSING_REDIRECTS------//
void	sort_redirections(t_cmd *cmd_current, t_token **tmp);
// static t_redir	*new_redir(char *value, t_token_type num);
// static void	redir_add_back(t_redir **head, t_redir *new);

//----------BUILT-IN-----------//

//----------EXECUTION----------//
// void exe_cmdline(t_cmd cmdline);
// everything else is static in here

//-----------FREEING-----------//
void	free_tokens(t_token **tokens);
void	free_env(t_env **s_env);
void	free_cmd(t_cmd **cmdline);

#endif