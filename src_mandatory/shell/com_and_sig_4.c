/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_and_sig_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:56:08 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/03 23:56:08 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strarr_find_var(char **env, char *var, int i)
{
	size_t	len;
	char	*var_name;

	while (var[i] && var[i] != '=')
		i++;
	var_name = ft_substr(var, 0, i + 1);
	len = ft_strlen(var_name);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var_name, len))
		{
			free(var_name);
			return (env[i]);
		}
	}
	return (NULL);
}

int	ft_strarr_count(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

void	ft_strarr_addline(char ***env, char *stradd)
{
	char	**tmp;
	int		i;

	if (stradd)
		tmp = *env;
	*env = (char **)malloc(sizeof(char *) * (ft_strarr_count(*env) + 2));
	i = 0;
	while (tmp[i])
	{
		(*env)[i] = tmp[i];
		i++;
	}
	(*env)[i] = ft_strdup(stradd);
	(*env)[i + 1] = NULL;
	free(tmp);
}

void	ft_strarr_delline(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i] != var)
		i++;
	free(env[i]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

void	ft_strarr_changeline(char *old, char *new)
{
	free(old);
	old = ft_strdup(new);
}
