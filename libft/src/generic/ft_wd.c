/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 19:24:16 by weilin            #+#    #+#             */
/*   Updated: 2020/06/13 19:30:07 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wd(const char *src)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!src)
		return (0);
	while (src[i] != '\0')
	{
		while (!ft_isprint(src[i]) && src[i] != '\0')
			i++;
		if (ft_isprint(src[i]))
			count++;
		while (ft_isprint(src[i]) && src[i] != '\0')
			i++;
	}
	return (count);
}
