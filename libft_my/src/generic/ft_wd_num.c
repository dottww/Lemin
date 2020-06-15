/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wd_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 19:37:05 by weilin            #+#    #+#             */
/*   Updated: 2020/05/28 18:28:32 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strnum(char const *s, char c)
{
	int		i;
	int		ctl;

	i = 0;
	ctl = 1;
	while (s[i])
	{
		if (s[i] != c && s[i] != '-' && !ft_isdigit(s[i]))
			ctl = 0;
		i++;
	}
	return (ctl);
}

int			ft_wd_num(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!strnum(s, c))
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c)
			count++;
	}
	return (count);
}
