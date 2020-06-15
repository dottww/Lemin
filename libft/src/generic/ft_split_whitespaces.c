/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:58:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/13 19:46:10 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_split_whitespaces(const char *s, int wd)
{
	char	**mx;
	int		count;
	int		i;
	int		j;
	int		end;

	if (!wd || !(mx = (char**)malloc(sizeof(char*) * (wd + 1))))
		return (NULL);
	i = 0;
	j = 0;
	count = -1;
	while (s[i] != '\0' && count++ < wd && i != -42)
	{
		while (!ft_isprint(s[i]) && s[i] != '\0')
			i++;
		if (ft_isprint(s[i]))
			j = i;
		while (ft_isprint(s[i]) && s[i] != '\0')
			i++;
		end = i;
		i = ((end != j) && !(mx[count] = ft_strdup_sec(s, j, end))) ? -42 : i;
	}
	mx[wd] = NULL;
	i == -42 ? ft_strtab_free(mx) : 0;
	return (mx);
}
