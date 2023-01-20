/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:44:22 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/29 21:07:24 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_perror(const char *message, int err_code)
{
	if (err_code)
		perror(message);
	else
		ft_putendl_fd((char *)message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/*вывод ошибок*/
int	ft_puterror(int fd, char *message, int len)
{
	while (message && message[len] != '\n')
		len++;
	return (write (fd, message, len));
}
