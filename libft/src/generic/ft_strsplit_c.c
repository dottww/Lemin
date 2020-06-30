/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:30:23 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 21:08:15 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit_c(char const *s, char c)
{
	char	**mx;
	int		count;
	int		i;
	int		j;
	int		end;

	if (!s || !c || !(mx = (char**)malloc(sizeof(char*) * (ft_wdc(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	count = -1;
	while (s[i] && count++ < ft_wdc(s, c) && i != -42)
	{
		while (s[i] == c && s[i])
			i++;
		j = (s[i] != c) ? i : j;
		while (s[i] != c && s[i])
			i++;
		end = i;
		if ((end != j) && !(mx[count] = ft_strdup_sec(s, j, end)))
			i = -42;
	}
	mx[ft_wdc(s, c)] = NULL;
	i == -42 ? ft_strtab_free(mx) : 0;
	return (mx);
}
