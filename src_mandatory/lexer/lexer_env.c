/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:46:57 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 20:46:57 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_env_var(char **env, char *par)
{
	size_t	len;
	size_t	d;

	len = ft_strlen(par);
	while (*env)
	{
		if (!ft_strncmp(*env, par, len))
		{
			d = ft_strchr((*env), '=') - (*env) + 1;
			free(par);
			return (ft_substr((*env), d, ft_strlen(*env) - d));
		}
		(*env)++;
	}
	return (ft_strdup(" "));
}

char	*ft_substr_change(char *cmdln, int k_start, int k_end, char *env_var)
{
	char	*newcmdln;
	int		size;
	int		len_env;
	int		len_cmd;

	len_env = ft_strlen(env_var);
	len_cmd = ft_strlen(cmdln);
	size = len_cmd - k_end + k_start + len_env;
	newcmdln = (char *)malloc(size + 1);
	if (size == 0)
		newcmdln[0] = '\0';
	else
	{
		ft_memcpy(&(newcmdln[0]), cmdln, k_start);
		ft_memcpy(&(newcmdln[k_start]), env_var, len_env);
		ft_memcpy(&(newcmdln[k_start + len_env]), &(cmdln[k_end]), len_cmd - k_end);
		newcmdln[size] = '\0';
	}
	free(cmdln);
	free(env_var);
	return (newcmdln);
}

char	*ft_env_var_name(char *cmdln, int *i, char ***env)
{
	int	k_start;

	k_start = (*i)++;
	while (cmdln[*i] != '\0' && cmdln[*i] != ' ' && cmdln[*i] != '<'
		&& cmdln[*i] != '>' && cmdln[*i] != '\'' && cmdln[*i] != '\"')
		(*i)++;
	cmdln = ft_substr_change(cmdln, k_start, *i, ft_env_var(*env,
				ft_substr(cmdln, k_start + 1, *i - k_start - 1)));
	*i = 0;
	return (cmdln);
}

void	ft_env_var_include2(char **cmdln, char ***env, int *i)
{
	(*i)++;
	while ((*cmdln)[*i] && (*cmdln)[*i] != '\"')
	{
		if ((*cmdln)[*i] == '$' && (*cmdln)[*i + 1] == ' ')
			(*i) += 2;
		else if ((*cmdln)[*i] == '$' && (*cmdln)[*i + 1] == '?')
			(*cmdln) = ft_exit_status(*cmdln, i);
		else if ((*cmdln)[*i] == '$' && (*cmdln)[*i + 1] == '\0')
			i++;
		else if ((*cmdln)[*i] == '$' && (*cmdln)[*i + 1] != ' ')
			(*cmdln) = ft_env_var_name(*cmdln, i, env);
		else
			(*i)++;
	}
}

char	*ft_env_var_include(char *cmdln, char ***env, int i)
{
	while (cmdln[i])
	{
		if (cmdln[i] == '\'')
			ft_skip_quot(&cmdln, '\'', &i);
		else if (cmdln[i] == '\"')
			ft_env_var_include2(&cmdln, env, &i);
		else if (cmdln[i] == '$' && cmdln[i + 1] == ' ')
			i += 2;
		else if (cmdln[i] == '$' && cmdln[i + 1] == '?')
			cmdln = ft_exit_status(cmdln, &i);
		else if (cmdln[i] == '$' && cmdln[i + 1] == '\0')
			i++;
		else if (cmdln[i] == '$' && cmdln[i + 1] != ' ')
			cmdln = ft_env_var_name(cmdln, &i, env);
		else
			i++;
	}
	return (cmdln);
}
/*
char	*ft_env_var_include(char *cmdln, char ***env, int i)
{
	while (cmdln[i])
	{
		if (cmdln[i] == '\'')
			ft_skip_quot(&cmdln, '\'', &i);
		else if (cmdln[i] == '$' && cmdln[i + 1] == ' ')
			i += 2;
		else if (cmdln[i] == '$' && cmdln[i + 1] == '?')
			cmdln = ft_exit_status(cmdln, &i);
		else if (cmdln[i] == '$' && cmdln[i + 1] == '\0')
			i++;
		else if (cmdln[i] == '$' && cmdln[i + 1] != ' ')
			cmdln = ft_env_var_name(cmdln, &i, env);
		else
			i++;
	}
	return (cmdln);
}*/
