/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:42:39 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/16 16:42:39 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_parse2(char ***args, char ***env, int i)
{
	if (!ft_strncmp((*args)[0], "env", 4))
		return (ft_env_print(*env, 0));
	else if (!ft_strncmp((*args)[0], "pwd", 4))
		return (ft_pwd_fd(1));
	else if (!ft_strncmp((*args)[0], "echo", 5))
		return (ft_echo_fd((*args), 1));
	else
	{
		i = -1;
		while ((*args)[++i])
			free((*args)[i]);
		free(*args);
		return (1);
	}
}

/*обработка встроенных команд*/
int	ft_builtin_parse(char *s, char ***env)
{
	char	**args;

	args = ft_split_quot(&s, 0, 0, 0);
	if (!ft_strncmp(args[0], "exit", 5))
	{
		if (args[1])
			ft_exit_st(ft_atoi(args[1]));
		else
			ft_exit_st(0);
	}
	if (!ft_strncmp(args[0], "cd", 3))
		return (ft_cd(args[1]));
	if (!ft_strncmp(args[0], "export", 7))
		return (ft_export(args, env));
	if (!ft_strncmp(args[0], "unset", 6))
		return (ft_unset(args, env));
	return (ft_builtin_parse2(&args, env, 0));
}

char	*ft_substr_won(char const *s, size_t len)
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	str = (char *)malloc(len + 1);
	i = -1;
	while (++i < len)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim_n(char *s1, char set, int i)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!(s1))
		return (NULL);
	start = 0;
	while (s1[start] && s1[start] == (char)set)
		start++;
	end = ft_strlen((char *)s1);
	while (end > start && s1[end - 1] == (char)set)
		end--;
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

char	**ft_strarr_cpy(int argc, char **argv, char **env_shit, int len)
{
	char	**ret;

	if (argc == 1 && argv[0][0] != 0)
		argc = 1;
	while (env_shit[len])
		len++;
	ret = malloc(sizeof(char *) * len + 1);
	len = -1;
	while (env_shit[++len])
		ret[len] = ft_strdup(env_shit[len]);
	ret[len] = NULL;
	return (ret);
}
