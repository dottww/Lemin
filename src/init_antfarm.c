/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_antfarm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:45:37 by weilin            #+#    #+#             */
/*   Updated: 2020/06/19 17:47:18 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_ant_qty(t_antfarm *atf, t_list **alst)
{
	while (*alst && is_comment(L2))
		*alst = (*alst)->next;
	if (*alst && ft_isnumber(L2) == 1)
	{
		ft_atoi_int(L2, &atf->ant_qty);
		*alst = (*alst)->next;
		return ((atf->ant_qty > 0) && *alst);
	}
	return (0);
}

static int		the_rooms(char *line)
{
	if (line[0] == '#') //command or comment
		return (1);
	else if (ft_strchr(line, '-')) //is a link
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

static int		init_links(t_antfarm *atf, t_list *alst)
{
	if (!alst || !add_link(atf, L1))
	// {ft_printf("init_link0\n");	return (0);}
		return (0);
	alst = alst->next;
	while (alst)
	{
		if (!is_comment(L1) && !add_link(atf, L1))
			// return (0);
		{ft_printf("init_link1={%s}\n", L1);	return (0);}
		alst = alst->next;
	}
	return (1);
}

int				register_rooms(t_antfarm *atf, t_list *alst)
{
	init_antfarm_values(atf);
	if (!init_ant_qty(atf, &alst))
	// {ft_printf("here_rr1={%s}\n",L1);return (0);}
		return (0);
	while (atf->ant_qty && alst && the_rooms(L1))
	{
		if (!add_room(atf, &alst))
		// {ft_printf("here_rr2={%s}\n",L1);return (0);}
			return (0);
		alst = alst->next;
	}
	return ((!atf->start || !atf->end) ? 0 : init_links(atf, alst));
}
