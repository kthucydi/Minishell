/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:45:43 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/05 20:41:27 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exitst_set(long long int c)
{
	int	fd_estatus;

	fd_estatus = open_file("mes", F_WRITE);
	ft_putnbr_fd((int)(c % 256), fd_estatus);
	close(fd_estatus);
}

void	ft_start(char *input, int rlend, char ***env)
{
	t_lstcom	*lstcom;
	char		*input_new;

	if (*input == 0)
		return ;
	input_new = ft_substr_won(input, rlend);
	ft_str_rmchar_all(&input_new, "\t  ", ft_strlen(input_new));
	if (*input_new == 0)
	{
		free (input_new);
		return ;
	}
	free (input_new);
	lstcom = ft_lexer(ft_substr_won(input, rlend), env);
	free(input);
	if (lstcom != NULL)
	{
		ft_lstcom_print_all(&lstcom);
		start_pipe(&lstcom, env);
		ft_lstcom_free(lstcom, 0);
		lstcom = NULL;
	}
	rl_replace_line("", 0);
}

char	*ft_input_cwd(const char *inp, char *cwd, const char *end, char *prev)
{
	char	*cwd3;
	char	*cwd2;

	if (prev)
		free (prev);
	cwd2 = ft_strjoin(inp, cwd);
	cwd3 = ft_strjoin(cwd2, end);
	free (cwd);
	free (cwd2);
	return (cwd3);
}

static char	**ft_init(int *argc, char ***argv, char ***env_shit)
{
	ft_exitst_set(0);
	signal(SIGINT, ft_sigint_handle);
	return (ft_strarr_cpy(*argc, *argv, *env_shit, 0));
}

int	main(int argc, char **argv, char **env_shit)
{
	char	*input;
	char	*cwd;
	char	**env;

	env = ft_init(&argc, &argv, &env_shit);
	while (1)
	{
		cwd = NULL;
		cwd = ft_input_cwd("minishell: ", getcwd(NULL, 1000), "$ ", cwd);
		input = readline(cwd);
		if (!input)
			ft_exit_st(0);
		add_history(input);
		if (!(*input == 0))
		{
			ft_start(input, rl_end, &env);
			rl_replace_line("", 0);
		}
		else
			free(input);
		free(cwd);
	}
	return (0);
}

/*	print commands   ft_lstcom_print_all(&lstcom);*/
