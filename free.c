/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:15:45 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/07 19:31:26 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_minishell *lst)
{
	t_minishell *tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&(lst->var));
		ft_memdel((void **)&(lst->data));
		ft_memdel((void **)&(lst));
		lst = tmp;
	}
}

void	free_tab(char **tab)
{
	int			i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			ft_memdel((void **)&(tab[i++]));
		}
		ft_memdel((void **)&tab);
	}
}

void	listadd(t_minishell **head, char *path)
{
	t_minishell	*new;
	t_minishell	*last;
	char		**tmp;
	int			i;

	i = 0;
	tmp = ft_strsplit(path, '=');
	if (!(new = malloc(sizeof(t_minishell))))
		exit(1);
	last = *head;
	new->var = ft_strdup(tmp[0]);
	new->data = ft_strdup(tmp[1]);
	new->next = NULL;
	free_tab(tmp);
	if (!(*head))
		*head = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	main_help(t_minishell **init, char **av)
{
	t_parse	*args;
	int		i;

	i = 0;
	while (av[i])
	{
		args = parsing(av[i]);
		if (!(parse_exp(args, init[0])))
			break ;
		if (args->command[0][0])
			builtin_funs(args, &init[0], av);
		i++;
		if (args->command)
			free_tab(args->command);
		if (args->options)
			free_tab(args->options);
		ft_memdel((void **)&args);
	}
}
