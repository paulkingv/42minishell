/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_stat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfox <jfox.42angouleme@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 02:28:38 by pking             #+#    #+#             */
/*   Updated: 2026/08/30 15:22:57 by jfox             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// these are the new functions created to fix the exit code issues
// we use the <sys/stat.h> in order to access the struct
// ~~~~~~ USED INSIDE EXEC_GET_PATH.C ~~~~~ //

// is_directory:
/*
	A directory can pass access(X_OK)
	This is a failsafe
	Catches the case directly
*/
int	is_directory(char *path)
{
	struct stat	st;
	int			result;

	result = (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
	return (result);
}

// classify_existing_path:
/*
	candidate exists, cant be exec'd;
	determine if its a dir, or if we
	dont have X perm. Modify MSG, return exit
*/
int	path_exists(char *path)
{
	int	found;

	found = (access(path, F_OK) == 0);
	return (found);
}
