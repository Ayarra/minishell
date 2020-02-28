/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:34:17 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/07 19:32:50 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_minishell(char **env)
{
	t_minishell *init;

	init = NULL;
	while (*env)
	{
		listadd(&init, *env);
		env++;
	}
	return (init);
}

char		*search_command(char *command,
			char **files, t_minishell *env)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	i = 0;
	if (*command == '/' && (!access(command, X_OK) || !access(command, R_OK) ||
							!access(command, W_OK) || !access(command, F_OK)))
		return (ft_strdup(command));
	if (files)
		while (files[i])
		{
			if (!(search_dollar(command, env, tmp)))
				return (0);
			tmp1 = ft_strjoin(files[i], "/");
			tmp = ft_strjoin(tmp1, command);
			ft_memdel((void **)&tmp1);
			if (!access(tmp, X_OK) ||
				!access(tmp, R_OK) ||
				!access(tmp, W_OK) || !access(tmp, F_OK))
				return (tmp);
			ft_memdel((void **)&tmp);
			i++;
		}
	return (0);
}

char		**get_env(t_minishell *env)
{
	t_minishell	*head;
	char		*tmp;
	char		**result;
	int			length;
	int			i;

	i = 0;
	length = 0;
	head = env;
	while (head)
	{
		length++;
		head = head->next;
	}
	result = (char **)malloc(sizeof(char *) * (length + 1));
	while (env)
	{
		tmp = ft_strjoin(env->var, "=");
		result[i] = ft_strjoin(tmp, env->data);
		ft_memdel((void **)&tmp);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}

char		*mini_read(t_minishell *init)
{
	char	buff[BUFF_SIZE + 1];
	char	*str;
	int		r;

	signal(SIGINT, nothing);
	write(1, "$>", 2);
	if (!(r = read(1, buff, BUFF_SIZE)))
	{
		free_list(init);
		return (0);
	}
	buff[r - 1] = '\0';
	str = ft_strdup(buff);
	return (str);
}

int			main(int ac, char **argv, char **env)
{
	char		*buff;
	t_minishell	*init;
	char		**av;

	if (ac == 1 && argv[0])
	{
		init = init_minishell(env);
		while (1)
		{
			if (!(buff = mini_read(init)))
				exit(1);
			av = ft_strsplit(buff, ';');
			ft_memdel((void **)&buff);
			main_help(&init, av);
			free_tab(av);
		}
	}
}
