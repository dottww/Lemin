/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:58:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/15 22:14:12 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_ants(t_antfarm *atf)
{
	int		i;

	atf->ants = NULL;
	i = atf->ant_qty + 1;
	while (--i)
	{
		if (!add_ant(i, atf))
			return (0);
	}
	return (1);
}
