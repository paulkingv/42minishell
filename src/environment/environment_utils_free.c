/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 13:23:14 by jfox              #+#    #+#             */
/*   Updated: 2026/08/29 13:59:11 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free the 2 strings used in init env to save some lines.
void	free_vals(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
	return ;
}
