/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 11:10:00 by jfox              #+#    #+#             */
/*   Updated: 2026/08/28 07:49:23 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// count the number of env structs in the environment list
static int	env_count(t_env	*env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

// build an array that holds addresses to environment variables
t_env	**export_array(t_env *env)
{
	t_env	**array;
	int		i;
	int		size;

	size = env_count(env);
	array = ft_calloc(size + 1, sizeof(t_env *));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i] = env;
		env = env->next;
		i++;
	}
	return (array);
}

// sort the environment array into alphabetical list
void	sort_array(t_env **array)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (array[i] && array[i + 1])
	{
		if (ft_strcmp(array[i]->key, array[i + 1]->key) > 0)
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return ;
}

// check that the export is valid, return a 1 if it is.
int	valid_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || (!ft_isalpha(arg[i]) && arg[i] != '_'))
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// print the error report from export.
void	print_export_error(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
	return ;
}
