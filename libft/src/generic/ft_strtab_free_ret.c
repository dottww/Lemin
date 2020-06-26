/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_free_ret.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 20:28:07 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 15:01:39 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtab_free_ret(char **tab, int ret)
{
	if (tab)
	{
		ft_strtab_free(tab);
		return (ret);
	}
	else
		return (-1);
}