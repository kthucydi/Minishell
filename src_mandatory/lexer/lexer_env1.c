/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:46:05 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/03 23:46:05 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_exit_status(char *cmdln, int *i)
{
	int		k_start;
	int		fd_estatus;
	char	*tmp;

	tmp = malloc(10);
	k_start = (*i)++;
	fd_estatus = open_file("mes", F_READ);
	tmp = ft_gnl(fd_estatus);
	close(fd_estatus);
	cmdln = ft_substr_change(cmdln, k_start, k_start + ft_strlen(tmp) + 1, tmp);
	*i = 0;
	return (cmdln);
}
