/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:00:49 by weilin            #+#    #+#             */
/*   Updated: 2018/11/19 18:10:19 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	int i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack != *needle)
			haystack++;
		else
		{
			i = 1;
			while (haystack[i] && needle[i] && haystack[i] == needle[i])
				i++;
			if (needle[i] == '\0')
				return ((char *)haystack);
			else
				haystack++;
		}
	}
	return (NULL);
}
