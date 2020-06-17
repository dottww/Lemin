/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 17:55:33 by weilin            #+#    #+#             */
/*   Updated: 2020/06/17 16:53:52 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_int(const char *str, int *num)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	if (!str || !num)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648 && sign == -1)
		|| *str != '\0')
		return (0);
	*num = (int)(nbr * sign);
	return (1);
}
