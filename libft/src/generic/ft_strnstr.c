/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:40:41 by weilin            #+#    #+#             */
/*   Updated: 2018/11/23 17:28:55 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnstr(const char *src, const char *find, size_t len)
{
	unsigned int	i;
	size_t			l_find;

	if (*find == '\0')
		return (char *)(src);
	i = 0;
	l_find = ft_strlen(find);
	while (*src)
	{
		if (i + l_find > len)
			return (NULL);
		if (ft_strncmp(src, find, l_find) == 0)
			return (char *)(src);
		src++;
		i++;
	}
	return (NULL);
}
