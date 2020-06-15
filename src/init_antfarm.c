/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_antfarm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:28:21 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/16 00:01:59 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_ant_qty(t_antfarm *atf, t_list **alst)
{
	while (*alst && is_comment(L2))
		*alst = (*alst)->next;
	if (*alst && ft_isnumber(L2) == 1)
	{
		atf->ant_qty = ft_atoull(L2);
		*alst = (*alst)->next;
		return ((atf->ant_qty > 0) && *alst);
	}
	return (0);
}

static int		the_rooms(char *line)
{
	if (line[0] == '#')
		return (1);
	else if (ft_strchr(line, '-'))
		return (0);
	return (1);
}

static void		init_antfarm_values(t_antfarm *atf)
{
	atf->rooms = NULL;
	atf->start = NULL;
	atf->end = NULL;
	atf->rounds = LONG_MAX;
	atf->id = 0;
	atf->option = 0;
	atf->ants = NULL;
}

static int		init_tunnels(t_antfarm *atf, t_list *alst)
{
	if (!alst || !add_tunnel(atf, L1))
	// {ft_printf("here_x0\n");	return (0);}
		return (0);
	alst = alst->next;
	while (alst)
	{
		if (!is_comment(L1) && !add_tunnel(atf, L1))
		{ft_printf("here_xa1\n");	return (0);}
		alst = alst->next;
	}
	return (1);
}

int				register_rooms(t_antfarm *atf, t_list *alst)
{
	init_antfarm_values(atf);
	if (!init_ant_qty(atf, &alst))
		return (0);
	while (atf->ant_qty && alst && the_rooms(L1))
	{
		if (!add_room(atf, &alst))
		{ft_printf("here_ia2={%s}\n",L1);return (0);}// return (0);
		alst = alst->next;
	}
	return ((!atf->start || !atf->end) ? 0 : init_tunnels(atf, alst));
}
