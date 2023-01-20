/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_and_sig_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:33:27 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/20 18:33:27 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_str_rmchar(char **str, int k)
{
	while ((*str)[++k] != '\0')
		(*str)[k - 1] = (*str)[k];
	(*str)[k - 1] = '\0';
}

void	ft_open_quots(char **str)
{
	int	i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			ft_str_rmchar(str, i);
			i--;
			ft_skip_quot(str, '\'', &i);
			ft_str_rmchar(str, i - 1);
		}
		else if ((*str)[i] == '\"')
		{
			ft_str_rmchar(str, i);
			i--;
			ft_skip_quot(str, '\"', &i);
			ft_str_rmchar(str, i - 1);
		}
		else
			i++;
	}
}

int	ft_export_print(char **env, int i)
{
	while (env[i] && printf("declare -x %s\n", env[i++]))
		;
	ft_exitst_set(0);
	return (0);
}

int	ft_export(char **args, char ***env)
{
	ft_open_quots(&(args[1]));
	if (args[1])
	{
		if (!ft_strchr(args[1], '='))
		{
			ft_exitst_set(0);
			return (0);
		}
	}
	else
	{
		ft_export_print(*env, 0);
		return (0);
	}
	if (ft_strarr_find_var(*env, args[1], 0))
		ft_strarr_changeline(ft_strarr_find_var(*env, args[1], 0), args[1]);
	else
		ft_strarr_addline(env, args[1]);
	ft_exitst_set(0);
	return (0);
}

int	ft_unset(char **args, char ***env)
{
	if (ft_strarr_find_var(*env, args[1], 0))
		ft_strarr_delline(*env, ft_strarr_find_var(*env, args[1], 0));
	ft_exitst_set(0);
	return (0);
}
