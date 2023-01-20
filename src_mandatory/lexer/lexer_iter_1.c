/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_iter_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:16:16 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 21:16:16 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parsing_quot(char **cmdln, char **tmp, int *i, int *k)
{
	if (((*cmdln)[*i]) == '\'')
	{
		(*tmp)[(*k)++] = (*cmdln)[(*i)++];
		while ((*cmdln)[*i] && (*cmdln)[*i] != '\'')
			(*tmp)[(*k)++] = (*cmdln)[(*i)++];
		if (((*cmdln)[*i]) == '\0')
			exit(ft_puterror(2, "Error: lonely quot1\n", 20));
		(*tmp)[(*k)++] = (*cmdln)[(*i)++];
	}
	else if ((*cmdln)[*i] == '\"')
	{
		(*tmp)[(*k)++] = (*cmdln)[(*i)++];
		while ((*cmdln)[*i] && (*cmdln)[*i] != '\"')
			(*tmp)[(*k)++] = (*cmdln)[(*i)++];
		if (!((*cmdln)[*i]))
			exit(ft_puterror(2, "Error: lonely quot2\n", 20));
		(*tmp)[(*k)++] = (*cmdln)[(*i)++];
	}
}

char	*ft_parsing_pipe(char **tmp, int *i, int *k)
{
	(*tmp)[*k] = '\0';
	(*k) = 0;
	(*i)++;
	return (ft_strtrim_n(*tmp, ' ', 0));
}

t_lstcom	*ft_parsing_iter1(char **cmdln, char **tmp, int i)
{
	int			k;
	int			j;
	t_lstcom	*lstcom;

	k = 0;
	j = 0;
	lstcom = NULL;
	while ((*cmdln)[i])
	{
		if (((*cmdln)[i]) == '\'' || ((*cmdln)[i]) == '\"')
			ft_parsing_quot(cmdln, tmp, &i, &k);
		else if ((*cmdln)[i] == '|')
			ft_lstcom_add_back(&lstcom,
				ft_lstcom_new(ft_parsing_pipe(tmp, &i, &k), j++));
		else
			(*tmp)[k++] = (*cmdln)[i++];
	}
	if (k != 0)
	{
		(*tmp)[k] = '\0';
		ft_lstcom_add_back(&lstcom,
			ft_lstcom_new(ft_strtrim_n(*tmp, ' ', 0), j++));
	}
	return (lstcom);
}

char	**ft_split_quot(char **cmdln, int i, int k, int j)
{
	char		**argarr;
	char		*tmp;

	tmp = malloc(1000);
	argarr = (char **)malloc(sizeof(char *) * 100);
	while ((*cmdln)[i])
	{
		if (((*cmdln)[i]) == '\'' || ((*cmdln)[i]) == '\"')
			ft_parsing_quot(cmdln, &tmp, &i, &k);
		else if ((*cmdln)[i] == ' ')
			argarr[j++] = ft_parsing_pipe(&tmp, &i, &k);
		else
			(tmp)[k++] = (*cmdln)[i++];
	}
	if (k != 0)
	{
		(tmp)[k] = '\0';
		argarr[j++] = ft_strtrim_n(tmp, ' ', 0);
	}
	argarr[j] = NULL;
	free(tmp);
	return (argarr);
}
