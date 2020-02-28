/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:16:41 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/01 15:18:27 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	int		ptr;
	int		words;

	if (!s)
		return (0);
	words = ft_count_words(s, c);
	ptr = 0;
	i = -1;
	split = malloc(sizeof(char*) * (words + 1));
	if (!split)
		return (0);
	while (++i < words)
		split[i] = ft_count_chars(s, &ptr, c);
	split[i] = 0;
	return (split);
}
