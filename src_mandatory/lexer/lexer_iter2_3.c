/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_iter2_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:11:56 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 21:11:56 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_str_rmchar_all(char **str, char *c, int len)
{
	int	k;

	while (--len >= 0)
	{
		if ((*str)[len] == c[0] || (*str)[len] == c[1] || (*str)[len] == c[2])
		{
			k = len;
			while ((*str)[++k] != '\0')
				(*str)[k - 1] = (*str)[k];
			(*str)[k - 1] = '\0';
		}
	}
	while ((*str)[0] == ' ')
	{
		len = 0;
		while ((*str)[++len] != '\0')
			(*str)[len - 1] = (*str)[len];
		(*str)[len - 1] = '\0';
	}
	while ((*str)[--len - 1] == ' ')
		(*str)[len - 1] = '\0';
}

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			paths = ft_split(envp[i] + ft_strlen("PATH="), ':');
			break ;
		}
		++i;
	}
	if (!envp[i])
		return (NULL);
	if (!paths)
		put_perror("\033[31mError: failed to split the paths.\033[0m", ERR);
	return (paths);
}

void	ft_free_path(char ***paths, int i)
{
	while ((*paths)[i])
		free((*paths)[i++]);
}

char	*get_command(char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	if (paths == NULL)
		return (ft_strdup(cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (!(tmp && command))
			put_perror("\033[31mError: failed to join the path.\033[0m", ERR);
		free(tmp);
		if (!access(command, X_OK))
		{
			ft_free_path(&paths, 0);
			return (command);
		}
		free(command);
		++paths;
	}
	ft_free_path(&paths, 0);
	return (NULL);
}

int	open_file(const char *pathname, int mode)
{
	int	fd;

	if (mode == F_READ)
	{
		fd = open(pathname, O_RDONLY);
		if (fd < 0)
			put_perror("\033[31mError: failed to open input file.\033[0m", ERR);
		return (fd);
	}
	else if (mode == F_WRITE)
	{
		fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd < 0)
			put_perror("\033[31mError: failed to open output file.\033[0m", ERR);
		return (fd);
	}
	else if (mode == F_APPEND)
	{
		fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd < 0)
			put_perror("\033[31mError: failed to open output file.\033[0m", ERR);
		return (fd);
	}
	put_perror("\033[31mError: wrong file opening mode.\033[0m", ERR_NULL);
	exit(EXIT_FAILURE);
}
