/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kthucydi <kthucydi@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:54:51 by kthucydi          #+#    #+#             */
/*   Updated: 2022/07/05 21:15:34 by kthucydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src_lib/libft.h"

# define F_READ 0	// file open mode: 0 - opening a file for reading
# define F_WRITE 1	// file open mode: 1 - opening a file for writing
# define F_APPEND 2	// file open mode: 2 - opening a file for append
# define ERR_NULL 0	// errno not exists
# define ERR 1		// errno exists
# define BUIL_IN_CMD "pwd exit env echo"

typedef struct s_lstcom
{
	char			*input;
	char			*input2;
	char			*cmd;
	char			*path;
	char			**args;
	char			*fd_in_str;
	char			*fd_out_str;
	int				fd_in;
	int				fd_out;
	int				hd_flag;
	int				append_flag;
	int				built_in_flag;
	int				number;
	struct s_lstcom	*next;
}	t_lstcom;

/*______minishell.c______*/
void		ft_start(char *input, int rlend, char ***env);
char		*ft_input_cwd(const char *inp, char *cwd,
				const char *end, char *prev);
void		ft_exitst_set(long long int c);

/*______lexer.c______*/
t_lstcom	*ft_lexer(char *input, char ***env);

/*______lexer_lstcom_1.c______*/
t_lstcom	*ft_lstcom_new(char *input, int i);
void		ft_lstcom_print(t_lstcom **lst);
t_lstcom	*ft_lstcom_last(t_lstcom *lst);
void		ft_lstcom_add_back(t_lstcom **lst, t_lstcom *new);
t_lstcom	*ft_lstcom_init(char **cmdarr, int i);

/*______lexer_lstcom_2.c______*/
void		ft_lstcom_print_all(t_lstcom **lst);
void		ft_lstcom_free(t_lstcom *lstcom, int i);

/*______lexer_env.c______*/
char		*ft_env_var(char **env, char *par);
char		*ft_substr_change(char *cmdln, int k_start, int k_end,
				char *env_var);
char		*ft_env_var_name(char *cmdln, int *i, char ***env);
char		*ft_env_var_include(char *cmdln, char ***env, int i);
void		ft_env_var_include2(char **cmdln, char ***env, int *i);

/*______lexer_env1.c______*/
char		*ft_exit_status(char *cmdln, int *i);

/*______lexer_iter1.c______*/
void		ft_parsing_quot(char **cmdln, char **tmp, int *i, int *k);
char		*ft_parsing_pipe(char **tmp, int *i, int *k);
t_lstcom	*ft_parsing_iter1(char **cmdln, char **tmp, int i);
char		**ft_split_quot(char **cmdln, int i, int k, int j);

/*______lexer_iter2_1.c______*/
void		ft_skip_quot(char **str, char c, int *i);
void		ft_pars_redir_out(t_lstcom **bg, int i);
void		ft_pars_redir_in(t_lstcom **bg, int i);
int			ft_findln_inarr(char *str1, char *str2);
void		ft_parsing_iter2(t_lstcom **lstcom, char ***env);

/*______lexer_iter2_2.c______*/
void		ft_str_rmsubstr(char **str, int k_start, int k_end);
void		ft_redir_flags(t_lstcom **b, char c, int *i);
void		ft_redir_name(t_lstcom **b, char c, int *i);
void		ft_pars_redirout_change(t_lstcom **bg, int *i, char *str, char c);
void		ft_pars_redirin_change(t_lstcom **bg, int *i, char *str, char c);

/*______lexer_iter2_3.c______*/
void		ft_str_rmchar_all(char **str, char *c, int len);
char		**get_paths(char **envp);
char		*get_command(char **paths, char *cmd);
int			open_file(const char *pathname, int mode);

/*______com_and_sig_2.c______*/
int			ft_export_print(char **env, int i);
int			ft_export(char **args, char ***env);
int			ft_unset(char **args, char ***env);
void		ft_str_rmchar(char **str, int k);
void		ft_open_quots(char **str);

/*______com_and_sig_1.c______*/
void		ft_sigint_handle(int i);
int			ft_env_print(char **env, int i);
int			ft_cd(char *folder);
int			ft_echo_fd2(char ***args, int *i);
int			ft_echo_fd(char **args, int fd);

/*______com_and_sig_3.c______*/
int			ft_pwd_fd(int fd);
char		*ft_gnl(int fd);
void		ft_exit_st(int status);

/*______com_and_sig_4.c______*/
char		*ft_strarr_find_var(char **env, char *var, int i);
int			ft_strarr_count(char **env);
void		ft_strarr_addline(char ***env, char *stradd);
void		ft_strarr_delline(char **env, char *var);
void		ft_strarr_changeline(char *old, char *new);

/*_______utils_1.c______*/
int			ft_builtin_parse(char *s, char ***env);
char		*ft_substr_won(char const *s, size_t len);
char		*ft_strtrim_n(char *s1, char set, int i);
char		**ft_strarr_cpy(int argc, char **argv, char **env_shit, int len);

/*_______error1.c______*/
int			ft_puterror(int fd, char *message, int len);
void		put_perror(const char *message, int err_code);

/*_______execute1.c______*/
int			ft_check_builtin(t_lstcom *begin, char ***envp);
void		ft_last_exec(t_lstcom *begin, char ***envp);
void		ft_last_parent(t_lstcom *begin, int *mes);
void		ft_pipe(t_lstcom **begin, char ***envp, int *mes);
void		start_pipe(t_lstcom **lstcom, char ***envp);

/*_______execute2.c______*/
void		child_fork(t_lstcom *begin, char ***envp,
				int (*fd_pipe)[2]);
void		child_process(t_lstcom *lstcom, char ***envp);
void		here_doc(char *limiter);
void		here_doc2(char *limiter, int fdpipe1);
void		hera_doc(char *eof, char **ret);

/*_______execute3.c______*/
void		copy_free(char **dst, char *src);
int			ft_check_exit(t_lstcom *begin);

void		shit_handle(char **arg, char **env);

#endif
