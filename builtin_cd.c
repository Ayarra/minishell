/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:21:58 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/08 03:15:54 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd_minus(t_minishell *env)
{
	char *past_dir;
	char *current_dir;
	char *get;

	chdir(var_val(env, "OLDPWD"));
	past_dir = ft_strjoin("OLDPWD=", var_val(env, "PWD"));
	search_env(&env, past_dir);
	get = getcwd(0, 0);
	ft_putendl(get);
	current_dir = ft_strjoin("PWD=", get);
	ft_memdel((void **)&get);
	search_env(&env, current_dir);
	ft_memdel((void **)&current_dir);
	ft_memdel((void **)&past_dir);
}

void		builtin_cd_normal(t_minishell **env, char *path)
{
	char *past_dir;
	char *current_dir;
	char *get;

	get = getcwd(NULL, 256);
	past_dir = ft_strjoin("OLDPWD=", get);
	ft_memdel((void **)&get);
	if (search_env(&env[0], past_dir) == 0)
		listadd(&env[0], past_dir);
	ft_memdel((void **)&past_dir);
	chdir(path);
	get = getcwd(NULL, 256);
	current_dir = ft_strjoin("PWD=", get);
	ft_memdel((void **)&get);
	search_env(&env[0], current_dir);
	ft_memdel((void **)&current_dir);
}

void		cd_error(char *name, int i)
{
	if (i == 1)
	{
		ft_putstr(name);
		ft_putendl(": no such file or directory.");
	}
	else if (i == 2)
	{
		ft_putstr("cd: permission denied: ");
		ft_putendl(name);
	}
	else if (i == 3)
		ft_putendl("cd: Too many arguments.");
}

void		builtin_cd_tilde(t_minishell *env, char **av)
{
	if (av[1][1] == '/')
	{
		av[1]++;
		av[1] = ft_strjoin(var_val(env, "HOME"), av[1]);
		builtin_cd_normal(&env, av[1]);
		ft_memdel((void **)&av[1]);
	}
	else if (!av[1][1])
		builtin_cd_normal(&env, var_val(env, "HOME"));
	else
	{
		av[1]++;
		av[1] = ft_strjoin("/Users/", av[1]);
		if (access(av[1], F_OK))
			cd_error(av[1], 1);
		else
			builtin_cd_normal(&env, av[2]);
		ft_memdel((void **)&av[1]);
	}
}

void		builtin_cd(t_minishell **env, char **av)
{
	int length;

	length = 0;
	while (av[length])
		length++;
	if (length == 1)
		builtin_cd_normal(&env[0], var_val(env[0], "HOME"));
	else if (length == 2)
	{
		if (av[1][0] == '~')
			builtin_cd_tilde(env[0], av);
		else if (ft_strequ(av[1], "-"))
			builtin_cd_minus(env[0]);
		else if (access(av[1], F_OK))
			cd_error(av[1], 1);
		else if (access(av[1], X_OK))
			cd_error(av[1], 2);
		else
			builtin_cd_normal(&env[0], av[1]);
	}
	else if (length > 2)
		cd_error("null", 3);
}
