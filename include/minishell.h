/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:46 by pking             #+#    #+#             */
/*   Updated: 2026/06/20 15:10:36 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/header/libft.h"
#include <stdio.h> //debugging
#include <unistd.h> // pipes, fork, getpid, execve, dup2
#include <sys/wait.h> // waitpid(),
#include <sys/types.h> // pid_t datatype,
#include <readline/readline.h> // for readline
#include <readline/history.h> //for readline's history (sh history)
#include <stdlib.h> //malloc

/*------STRUCTS------*/

// TOKENS
// 2 Structs: Token and Token Type (Token Type first because Token needs it)

typedef enum e_token_type
{
    //CHECK WITH OTHERS IF ENUMS ARE ALLOWED
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_IN,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_EOF
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next_token;
}   t_token;

/*-----FUNCTIONS-----*/

#endif