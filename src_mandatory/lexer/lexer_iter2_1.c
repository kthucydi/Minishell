/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_iter2_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:54:23 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 20:54:23 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_skip_quot(char **str, char c, int *i)
{
	(*i)++;
	while ((*str)[*i] != c)
		(*i)++;
	(*i)++;
}

void	ft_pars_redir_out(t_lstcom **bg, int i)
{
	while ((*bg)->input2[i])
	{
		if ((*bg)->input2[i] == '\"')
			ft_skip_quot(&((*bg)->input2), '\"', &i);
		else if ((*bg)->input2[i] == '\'')
			ft_skip_quot(&((*bg)->input2), '\'', &i);
		else if ((*bg)->input2[i] == '>')
		{
			ft_pars_redirout_change(bg, &i, "\"\'>", '>');
			if ((*bg)->append_flag == 0)
				(*bg)->fd_out = open_file((*bg)->fd_out_str, F_WRITE);
			else
				(*bg)->fd_out = open_file((*bg)->fd_out_str, F_APPEND);
			i = 0;
		}
		else
			i++;
	}
}

void	ft_pars_redir_in(t_lstcom **bg, int i)
{
	while ((*bg)->input2[i])
	{
		if ((*bg)->input2[i] == '\"')
			ft_skip_quot(&((*bg)->input2), '\"', &i);
		else if ((*bg)->input2[i] == '\'')
			ft_skip_quot(&((*bg)->input2), '\'', &i);
		else if ((*bg)->input2[i] == '<')
		{
			ft_pars_redirin_change(bg, &i, "\"\'<", '<');
			if ((*bg)->hd_flag == 0 && (*bg)->fd_in_str)
				(*bg)->fd_in = open_file((*bg)->fd_in_str, F_READ);
			i = 0;
		}
		else
			i++;
	}
}

int	ft_findln_inarr(char *str1, char *str2)
{
	char	**arr;
	int		i;

	arr = ft_split(str1, ' ');
	i = -1;
	while (arr[++i])
	{
		if (!ft_strncmp(str2, arr[i], ft_strlen(arr[i])))
		{
			i = -1;
			while (arr[++i])
				free (arr[i]);
			free(arr);
			return (1);
		}
	}
	i = -1;
	while (arr[++i])
		free (arr[i]);
	free(arr);
	return (0);
}

void	ft_parsing_iter2(t_lstcom **lstcom, char ***env)
{
	t_lstcom	*begin;

	begin = *lstcom;
	while (begin)
	{
		ft_pars_redir_in(&begin, 0);
		ft_pars_redir_out(&begin, 0);
		begin->args = ft_split(begin->input2, ' ');
		begin->cmd = begin->args[0];
		if (ft_findln_inarr(BUIL_IN_CMD, begin->cmd) && *env)
			begin->built_in_flag = 1;
		else
		{	
			if (ft_strchr(begin->cmd, '/') == NULL)
				begin->path = get_command(get_paths(*env), begin->cmd);
			else
				begin->path = ft_strdup(begin->cmd);
		}
		begin = begin->next;
	}
}
