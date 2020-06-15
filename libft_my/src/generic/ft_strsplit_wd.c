/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_wd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:30:23 by weilin            #+#    #+#             */
/*   Updated: 2020/06/13 19:44:03 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit_wd(char const *s, char c, int wd)
{
	char	**mx;
	int		count;
	int		i;
	int		j;
	int		end;

	if (!s || !c || !(mx = (char**)malloc(sizeof(char*) * (wd + 1))))
		return (NULL);
	i = 0;
	j = 0;
	count = -1;
	while (s[i] && count++ < wd && i != -42)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c)
			j = i;
		while (s[i] != c && s[i])
			i++;
		end = i;
		i = ((end != j) && !(mx[count] = ft_strdup_sec(s, j, end))) ? -42 : i;
	}
	mx[wd] = NULL;
	i == -42 ? ft_strtab_free(mx) : 0;
	return (mx);
}
