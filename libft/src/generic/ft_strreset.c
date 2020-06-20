/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:04:37 by weilin            #+#    #+#             */
/*   Updated: 2020/06/20 15:13:56 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreset(char *s1, char *s2)
{
	if (s1 && !s2)
	{	
		ft_strdel(&s1);
		return (NULL);
	}
	if (!s1 || !s2)
		return (NULL);
	ft_strdel(&s1);
	s1 = s2;
	return (s1);
}
