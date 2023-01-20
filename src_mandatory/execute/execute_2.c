/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:21:49 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/29 14:21:49 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_fork(t_lstcom *begin, char ***envp, int (*fd_pipe)[2])
{
	close((*fd_pipe)[0]);
	dup2((*fd_pipe)[1], STDOUT_FILENO);
	if (ft_builtin_parse(begin->input2, envp))
		if (execve(begin->path, begin->args, *envp) == -1)
			put_perror("\033[31mError: failed to execute the \
				command.\033[0m", ERR);
	exit(1);
}

void	child_process(t_lstcom *begin, char ***envp)
{
	int		fd_pipe[2];
	int		pid;

	if (begin->hd_flag == 1 && begin->number == 0)
	{
		here_doc(begin->fd_in_str);
	}
	if (pipe(fd_pipe) == -1)
		put_perror("\033[31mError: pipe cannot create descriptor pair.", ERR);
	pid = fork();
	if (pid == -1)
		put_perror("\033[31mError: fork cannot create a new process.", ERR);
	if (!pid)
		child_fork(begin, envp, &fd_pipe);
	else
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *limiter)
{
	int	fd_pipe[2];
	int	pid;

	if (pipe(fd_pipe) == -1)
		put_perror("\033[31mError: pipe cannot create descriptor pair.", ERR);
	pid = fork();
	if (pid == -1)
		put_perror("\033[31mError: fork cannot create a new process.", ERR);
	if (!pid)
	{
		close(fd_pipe[0]);
		here_doc2(limiter, fd_pipe[1]);
	}
	else
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc2(char *limiter, int fdpipe1)
{
	char	*line;
	char	*ret;

	ret = ft_strdup("");
	while (1)
	{
		line = ft_gnl(STDIN_FILENO);
		if (!line)
		{
			exit(EXIT_SUCCESS);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 \
			&& ft_strlen(limiter) == ft_strlen(line))
		{
			free(line);
			ft_putstr_fd(ret, fdpipe1);
			exit(EXIT_SUCCESS);
		}
		copy_free(&ret, line);
		copy_free(&ret, "\n");
		free(line);
	}
}

void	hera_doc(char *eof, char **ret)
{
	char	*readed;

	*ret = ft_strdup("");
	while (1)
	{
		readed = readline("here_doc < ");
		if (!readed)
			put_perror("\033[31mError: cannot get new line.", ERR);
		if (ft_strncmp(readed, eof, ft_strlen(eof)) == 0 \
			&& ft_strlen(eof) == ft_strlen(readed))
		{
			free(readed);
			(*ret)++;
			return ;
		}
		copy_free(ret, "\n");
		copy_free(ret, readed);
		printf("%s\n", readed);
		free(readed);
	}
}
