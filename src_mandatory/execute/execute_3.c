/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:24:10 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/29 14:24:10 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_free(char **dst, char *src)
{
	char	*q;

	q = *dst;
	*dst = ft_strjoin(*dst, src);
	free(q);
}

int	ft_check_exit(t_lstcom *begin)
{
	while (begin)
	{
		if (!ft_strncmp(begin->cmd, "exit", 5))
			return (1);
		begin = begin->next;
	}
	return (0);
}
