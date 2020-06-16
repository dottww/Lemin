/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:17:44 by weilin            #+#    #+#             */
/*   Updated: 2020/06/16 02:40:55 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;

	if (!size || !(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	s[size] = '\0';
	while (size)
		s[size--] = '\0';
	return (s);
}
