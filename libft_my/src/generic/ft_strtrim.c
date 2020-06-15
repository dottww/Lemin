/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:43:18 by weilin            #+#    #+#             */
/*   Updated: 2018/11/30 15:12:29 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ws(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	unsigned int	i;
	size_t			len;
	char			*t;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (ft_ws(s[i]))
		i++;
	if (i != len)
		while (ft_ws(s[len - 1]))
			len--;
	if (!(t = ft_strsub(s, i, len - i)))
		return (NULL);
	return (t);
}
