/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:46:29 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 21:06:46 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long	ft_atoull(const char *str)
{
	unsigned long long		res;
	int						i;
	int						j;

	i = 0;
	j = -1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i + ++j] >= '0' && str[i + j] <= '9')
		res = res * 10 + (str[i + j] - 48);
	return (res);
}
