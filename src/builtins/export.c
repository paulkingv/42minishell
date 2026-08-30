/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:19:26 by jfox              #+#    #+#             */
/*   Updated: 2026/08/30 21:32:14 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// adjust this to print in alpha order. add helper
static void	ft_print_export(t_shell *shell)
{
	t_env	**tmp;
	int		i;

	tmp = export_array(shell->env);
	if (!tmp)
		return ;
	sort_array(tmp);
	i = 0;
	while (tmp[i])
	{
		ft_printf("declare -x ");
		if (!tmp[i]->value)
			ft_printf("%s\n", tmp[i]->key);
		else if (!ft_strcmp(tmp[i]->value, "\"\""))
			ft_printf("%s=\n", tmp[i]->key);
		else
			ft_printf("%s=\"%s\"\n", tmp[i]->key, tmp[i]->value);
		i++;
	}
	free(tmp);
	return ;
}

// break the valid command argument into a string array holding key and value
static char	**ft_export_util(t_cmd *cmd, int i)
{
	char	**strings;
	char	*equal;
	int		key_len;

	strings = ft_calloc(3, sizeof(char *));
	if (!strings)
		return (NULL);
	equal = ft_strchr(cmd->args[i], '=');
	if (!equal)
	{
		strings[0] = ft_strdup(cmd->args[i]);
		return (strings);
	}
	key_len = equal - cmd->args[i];
	if (key_len > 0 && cmd->args[i][key_len - 1] == '+')
		key_len = key_len - 1;
	strings[0] = ft_substr(cmd->args[i], 0, key_len);
	strings[1] = ft_strdup(equal + 1);
	if (!strings [0] || !strings [1])
	{
		free_array(strings);
		return (NULL);
	}
	return (strings);
}

// print the error report from export.
void	print_export_error(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
	return ;
}

// take printing of export errors and return the valid exit value
void	handle_no_valid_export(t_shell *shell, char *args, int *i)
{
	print_export_error(args);
	shell->exit = 1;
	*i += 1;
	return ;
}

// export with no options
int	ft_export(t_shell *shell, t_cmd *cmd, t_cmd *tcmd)
{
	char	**strings;
	int		i;

	tcmd = cmd;
	i = 1;
	shell->exit = 0;
	if (!tcmd->args[i])
		ft_print_export(shell);
	while (tcmd->args[i])
	{
		if (!valid_export(tcmd->args[i]))
		{
			handle_no_valid_export(shell, tcmd->args[i], &i);
			continue ;
		}
		strings = ft_export_util(tcmd, i);
		if (!strings)
			return (2);
		if (append(tcmd->args[i]))
			append_env(shell, strings[0], strings[1]);
		else
			set_env(&shell->env, strings[0], strings[1]);
		free_array(strings);
		i++;
	}
	return (shell->exit);
}
