/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_iter2_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:03:30 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 21:03:30 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_str_rmsubstr(char **str, int k_start, int k_end)
{
	while ((*str)[k_end] != '\0')
		(*str)[k_start++] = (*str)[k_end++];
	(*str)[k_start] = '\0';
	while ((*str)[--k_start] == ' ')
		(*str)[k_start] = '\0';
	while ((*str)[0] == ' ')
	{
		k_start = 0;
		while ((*str)[++k_start] != '\0')
			(*str)[k_start - 1] = (*str)[k_start];
		(*str)[k_start - 1] = '\0';
	}
}

void	ft_redir_flags(t_lstcom **b, char c, int *i)
{
	if (c == '<')
		(*b)->hd_flag = 0;
	else if (c == '>')
		(*b)->append_flag = 0;
	if ((*b)->input2[*i] == '<')
	{
		(*b)->hd_flag = 1;
		(*b)->fd_in = 0;
		(*i)++;
	}
	else if ((*b)->input2[*i] == '>')
	{
		(*b)->append_flag = 1;
		(*i)++;
	}
}

void	ft_redir_name(t_lstcom **b, char c, int *i)
{
	ft_redir_flags(b, c, i);
	while ((*b)->input2[*i] == ' ')
		(*i)++;
	while ((*b)->input2[*i] != '\0' && (*b)->input2[*i] != ' '
		&& (*b)->input2[*i] != '<' && (*b)->input2[*i] != '>')
	{
		if ((*b)->input2[*i] == '\"')
			ft_skip_quot(&((*b)->input2), '\"', i);
		else if ((*b)->input2[*i] == '\'')
			ft_skip_quot(&((*b)->input2), '\'', i);
		else
			(*i)++;
	}
}

void	ft_pars_redirout_change(t_lstcom **bg, int *i, char *str, char c)
{
	int	k_start;

	k_start = (*i)++;
	ft_redir_name(bg, c, i);
	if ((*bg)->fd_out_str)
		free((*bg)->fd_out_str);
	(*bg)->fd_out_str = ft_substr((*bg)->input2, k_start, *i - k_start);
	ft_str_rmchar_all(&((*bg)->fd_out_str), str, ft_strlen((*bg)->fd_out_str));
	ft_str_rmsubstr(&((*bg)->input2), k_start, *i);
}

void	ft_pars_redirin_change(t_lstcom **bg, int *i, char *str, char c)
{
	int	k_start;

	k_start = (*i)++;
	ft_redir_name(bg, c, i);
	if ((*bg)->fd_in_str)
		free((*bg)->fd_in_str);
	(*bg)->fd_in_str = ft_substr((*bg)->input2, k_start, *i - k_start);
	ft_str_rmchar_all(&((*bg)->fd_in_str), str, ft_strlen((*bg)->fd_in_str));
	ft_str_rmsubstr(&((*bg)->input2), k_start, *i);
}
