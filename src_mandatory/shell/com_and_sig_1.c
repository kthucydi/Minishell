/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_and_sig_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:37:47 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/03 23:50:41 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*signal handling*/
void	ft_sigint_handle(int i)
{
	if (i == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*print evaironment var*/
int	ft_env_print(char **env, int i)
{
	while (env[i] && printf("%s\n", env[i++]))
		;
	ft_exitst_set(0);
	return (0);
}

/*change working dir*/
int	ft_cd(char *folder)
{
	if (folder && chdir(folder))
	{
		ft_putstr_fd("-minishell: cd: ", 1);
		ft_putstr_fd(folder, 1);
		ft_putendl_fd(": No such file or directory", 1);
		ft_exitst_set(1);
		return (1);
	}
	ft_exitst_set(0);
	return (0);
}

int	ft_echo_fd2(char ***args, int *i)
{
	if ((*args)[1])
	{
		if (ft_strncmp((*args)[1], "-n", 2))
			*i = 1;
	}
	else
	{
		printf("\n");
		ft_exitst_set(0);
		return (1);
	}
	return (0);
}

int	ft_echo_fd(char **args, int fd)
{
	int	i;

	i = fd;
	i = 2;
	if (ft_echo_fd2(&args, &i))
		return (0);
	while (args[i])
	{
		if (*args[i])
		{
			ft_open_quots(&(args[i]));
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
		}
		if (ft_strncmp(args[1], "-n", 2) && !args[i + 1])
			printf("\n");
		i++;
	}
	ft_exitst_set(0);
	return (0);
}
