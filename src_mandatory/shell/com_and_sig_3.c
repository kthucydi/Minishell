/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_and_sig_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:51:01 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/03 23:51:01 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*path to working directory*/
int	ft_pwd_fd(int fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 1000);
	if (!cwd)
		cwd = getcwd(NULL, 10000);
	ft_putendl_fd(cwd, fd);
	free(cwd);
	return (0);
}

char	*ft_gnl(int fd)
{
	char	*s;
	char	*c;

	s = malloc(10000);
	c = s;
	while (read(fd, c, 1) > 0 && *c != '\n')
		c++;
	if (c > s || *c == '\n')
	{
		*c = 0;
		return (s);
	}
	else
	{
		free(s);
		return (NULL);
	}
}

void	ft_exit_st(int status)
{
	ft_exitst_set((long long int)status);
	ft_putendl_fd("exit", 1);
	exit(status % 256);
}
