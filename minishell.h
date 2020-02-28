/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 03:57:34 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/08 03:25:47 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>

typedef struct			s_minishell
{
	char				*var;
	char				*data;
	struct s_minishell	*next;
}						t_minishell;

typedef struct			s_parse
{
	char				**command;
	char				**options;
}						t_parse;

char					*ft_strndup(const char *s1, int l);
void					listadd(t_minishell **head, char *path);
void					nothing(int n);
void					main_help(t_minishell **init, char **av);
int						parse_exp(t_parse *args, t_minishell *init);
t_parse					*parsing(char *str);
char					*get_command(char *str, int *i);
char					**get_options(char *str, int *i);
int						expansions(char **args, t_minishell *env);
char					*exp_dollar(t_minishell *env,
						char *result, char *holder);
int						parse_exp(t_parse *args, t_minishell *init);
char					*exp_chyata(char **holder, t_minishell *env);
char					*characters(char **str);
int						quotes(char *av, int *i);
void					unkow_tilde(char *str);
char					*unique_tilde(char **str, t_minishell *env);
char					*tilde_dollar(char **str, t_minishell *env, char *tmp);
int						search_dollar(char *command,
						t_minishell *env, char *tmp);
char					*dollar_sign(char **str, t_minishell *env, int *error);
char					*tilde_cases(char **str, char *tmp, t_minishell *env);
char					*unique_dollar(char **str);
char					*dollar_etc(char *tmp, char *head, int *error);
int						dollar_counter(char **str);
char					*quotes_trim(char *s);
void					builtin_funs(t_parse *args,
						t_minishell **init, char **av);
void					builtin_env(t_minishell *env);
void					builtin_setenv(t_minishell **env, char **av);
void					builtin_unsetenv(t_minishell **env, char **var);
void					builtin_echo(char **av);
void					builtin_cd(t_minishell **env, char **av);
void					builtin_cd_normal(t_minishell **env, char *path);
char					*var_val(t_minishell *env, char *var);
int						search_env(t_minishell **env, char *info);
int						mini_alnum(char *str);
void					delete_var(t_minishell **env, char *var);
char					*tilde(char **str, t_minishell *env);
char					**get_env(t_minishell *env);
char					*search_command(char *command,
						char **files, t_minishell *env);
void					free_list(t_minishell *lst);
void					free_tab(char **tab);
void					free_jooj(char *str1, char *str2);
#endif
