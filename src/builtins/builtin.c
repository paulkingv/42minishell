/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:35:37 by jfox              #+#    #+#             */
/*   Updated: 2026/07/20 12:43:19 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Here we will start working on the main built in functions.
// useful now that we have environmental table made!

// echo with option -n
ft_echo();
// cd with only a relative or absolute path
ft_cd();
// pwd with no options
ft_pwd();
// export with no options
ft_export();
// unset with no options
ft_unset();
// env with no options or arguments
ft_env();
// exit with no options
ft_exit();
