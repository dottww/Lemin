/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:55:11 by weilin            #+#    #+#             */
/*   Updated: 2020/06/08 22:56:03 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isinteger(const char *str)
{
	char	*tmp;
	int		len;
	int		value;

	tmp = NULL;
	if (!ft_isnumber(str))
		return (0);
	if (*str == '+')
		return (ft_isinteger(str + 1));
	len = ft_strlen(str);
	if (len > (*str == '-' ? 11 : 10))
		return (0);
	else if (len == (*str == '-' ? 11 : 10))
	{
		tmp = ft_strsub(str, *str == '-' ? 1 : 0, 9);
		if ((value = ft_atoi(tmp)) > 214748364)
			return (0);
		else if (value == 214748364)
			if (str[ft_strlen(str) - 1] - 48 > (*str == '-' ? 8 : 7))
				return (0);
	}
	if (tmp)
		ft_strdel(&tmp);
	return (1);
}
