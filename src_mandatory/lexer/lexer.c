/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:48:32 by kthucydi          #+#    #+#             */
/*   Updated: 2022/06/27 21:48:32 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lstcom	*ft_lexer(char *input, char ***env)
{
	char		*tmp;
	char		*cmdln;
	t_lstcom	*lstcom;

	tmp = malloc(10000);
	cmdln = ft_env_var_include(ft_strtrim_n(input, ' ', 0), env, 0);
	printf("AFTER ENV INCLUDE\n");
	lstcom = ft_parsing_iter1(&cmdln, &tmp, 0);
	printf("AFTER ITER 1\n");
	ft_parsing_iter2(&lstcom, env);
	printf("AFTER ITER 2\n");
	free(input);
	free(tmp);
	free(cmdln);
	return (lstcom);
}
