/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lstcom_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:53:01 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 21:53:01 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstcom_print_all(t_lstcom **lst)
{
	t_lstcom	*begin;

	begin = *lst;
	printf("\n***PRINTING LIST_OF_COMMAND***\n\n");
	while (begin)
	{
		printf("COMMAND N%i\n", begin->number);
		printf("INPUT = |%s|\n", begin->input);
		printf("INPUT2 = |%s|\n", begin->input2);
		printf("CMD = |%s|\n", begin->cmd);
		printf("PATH = |%s|\n", begin->path);
		printf("FD_IN_STR = |%s|\n", begin->fd_in_str);
		printf("FD_OUT_STR = |%s|\n", begin->fd_out_str);
		printf("FD_IN = |%i|\n", begin->fd_in);
		printf("FD_OUT = |%i|\n", begin->fd_out);
		printf("HDOC_FLAG = |%i|\n", begin->hd_flag);
		printf("APPEND_FLAG = |%i|\n", begin->append_flag);
		printf("BUILT_IN_FLAG = |%i|\n", begin->built_in_flag);
		printf("----------------------------\n");
		if (!(begin->next))
			printf("*******************************\n\n");
		begin = begin->next;
	}
}

void	ft_lstcom_free(t_lstcom *lstcom, int i)
{
	t_lstcom	*lsttemp;

	while (lstcom)
	{
		i = 0;
		free(lstcom->input);
		free(lstcom->input2);
		free(lstcom->cmd);
		if (lstcom->path && i == 0)
			free(lstcom->path);
		if (lstcom->fd_in_str)
			free(lstcom->fd_in_str);
		if (lstcom->fd_out_str)
			free(lstcom->fd_out_str);
		lsttemp = lstcom;
		lstcom = lstcom->next;
		free(lsttemp);
	}
}
