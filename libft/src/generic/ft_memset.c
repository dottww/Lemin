/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:23:47 by weilin            #+#    #+#             */
/*   Updated: 2018/11/19 18:09:20 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	while (len > 0 && (unsigned char *)(b + len))
	{
		((unsigned char*)b)[len - 1] = (unsigned char)c;
		len--;
	}
	return (b);
}
