/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:20:56 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/03 22:15:06 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_builtin(t_lstcom *begin, char ***envp)
{
	if (ft_check_exit(begin))
	{
		if (begin->args[1])
			ft_exit_st(ft_atoi(begin->args[1]));
		else
			ft_exit_st(0);
	}
	if ((ft_lstcom_last(begin))->number == 0
		&& ft_findln_inarr("cd export unset", begin->cmd))
	{
		ft_builtin_parse(begin->input2, envp);
		return (1);
	}	
	return (0);
}

void	ft_last_exec(t_lstcom *begin, char ***envp)
{
	if (begin->fd_in != 0)
		dup2(begin->fd_in, STDIN_FILENO);
	if (begin->fd_out != 1)
		dup2(begin->fd_out, STDOUT_FILENO);
	if (!ft_strncmp(begin->args[0], "", 1))
		exit (1);
	if (begin->hd_flag == 1)
		here_doc(begin->fd_in_str);
	if (ft_builtin_parse(begin->input2, envp))
		if (execve(begin->path, begin->args, *envp) == -1)
			put_perror("Error: failed to execute the command.", ERR);
	exit(0);
}

void	ft_last_parent(t_lstcom *begin, int *mes)
{
	int	fd_mes;

	wait(mes);
	fd_mes = open_file("mes", F_WRITE);
	ft_putnbr_fd((int)WEXITSTATUS(*mes), fd_mes);
	close(fd_mes);
	if (begin->fd_in != 0)
		close(begin->fd_in);
	if (begin->fd_out != 1)
		close(begin->fd_out);
}

void	ft_pipe(t_lstcom **begin, char ***envp, int *mes)
{
	int	pid;

	while (*begin)
	{
		if (!((*begin)->next))
		{
			pid = fork();
			if (pid == -1)
				put_perror("\033[31mError: fork cannot create a new \
					process.\033[0m", ERR);
			if (!pid)
				ft_last_exec(*begin, envp);
			else
				ft_last_parent(*begin, mes);
			*begin = (*begin)->next;
		}
		else if ((*begin)->next)
		{	
			dup2((*begin)->fd_in, STDIN_FILENO);
			child_process(*begin, envp);
			*begin = (*begin)->next;
		}
	}
	exit(1);
}

void	start_pipe(t_lstcom **lstcom, char ***envp)
{
	t_lstcom	*begin;
	int			pid1;
	int			mes;

	mes = 0;
	begin = *lstcom;
	if (ft_check_builtin(begin, envp))
		return ;
	pid1 = fork();
	if (pid1 == -1)
		put_perror("Error: fork cannot create a new process.", ERR);
	if (!pid1)
		ft_pipe(&begin, envp, &mes);
	else
		waitpid(pid1, NULL, 0);
}
