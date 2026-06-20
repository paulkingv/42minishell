/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:31:46 by pking             #+#    #+#             */
/*   Updated: 2026/06/20 15:45:54 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/header/libft.h"
#include <stdio.h> // printf
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
    TOKEN_EOF = 0,
    TOKEN_WORD = 1 << 0,        // 0x00000001
    TOKEN_PIPE = 1 << 1,        // 0x00000010
    TOKEN_REDIR_OUT = 1 << 2,   // 0x00000100
    TOKEN_REDIR_IN = 1 << 3,    // 0x00001000
    TOKEN_APPEND = 1 << 4,      // 0x00010000
    TOKEN_HEREDOC = 1 << 5     // 0x00100000
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next_token;
}   t_token;

/*-----FUNCTIONS-----*/

#endif