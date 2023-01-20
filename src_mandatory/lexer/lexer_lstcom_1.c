/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lstcom_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:53:12 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 21:53:12 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lstcom	*ft_lstcom_new(char *input, int i)
{
	t_lstcom	*lstcom;

	lstcom = (t_lstcom *)malloc(sizeof(t_lstcom));
	if (lstcom == NULL)
		return (NULL);
	lstcom->input = ft_strdup(input);
	lstcom->input2 = ft_strdup(input);
	lstcom->args = NULL;
	lstcom->cmd = NULL;
	lstcom->path = NULL;
	lstcom->fd_in_str = NULL;
	lstcom->fd_out_str = NULL;
	lstcom->fd_in = 0;
	lstcom->fd_out = 1;
	lstcom->hd_flag = 0;
	lstcom->append_flag = 0;
	lstcom->built_in_flag = 0;
	lstcom->number = i;
	lstcom->next = NULL;
	return (lstcom);
}

void	ft_lstcom_print(t_lstcom **lst)
{
	t_lstcom	*begin;

	begin = *lst;
	while (begin)
	{
		printf("LSTCOM_PRINT n%i = |%s|\n", begin->number, begin->input);
		begin = begin->next;
	}
}

t_lstcom	*ft_lstcom_last(t_lstcom *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstcom_add_back(t_lstcom **lst, t_lstcom *new)
{
	t_lstcom	*begin;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		begin = ft_lstcom_last(*lst);
		begin->next = new;
	}
}
/*
t_lstcom	*ft_lstcom_init(char **cmdarr, int i)
{
	t_lstcom	*lstcom;

	lstcom = ft_lstcom_new(cmdarr[0], 0);
	i = 0;
	while (cmdarr[++i])
		ft_lstcom_add_back(&lstcom, ft_lstcom_new(cmdarr[i], i));
	printf("PAST LSTCOM I: |%i|\n", i - 1);
	return (lstcom);
}*/
