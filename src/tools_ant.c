/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:37:25 by weilin            #+#    #+#             */
/*   Updated: 2020/06/29 19:37:49 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_ant_one_step(t_room *curr, t_room *next)
{
	curr->population--;
	next->population++;
	next->ant_id = curr->ant_id;
}

static void		move_all_ants_at_once(t_antfarm *atf)
{
	int		i;
	t_room	*end;

	i = 0;
	end = (t_room *)atf->end->content;
	while (i < atf->ant_qty)
	{
		i++;
		ft_printf("L%d-%s%s", i, end->name, i < atf->ant_qty ? " " : "\n");
	}
	end->population += i;
	((t_room *)atf->start->content)->population -= i;
}

static void		move_ant_from_start(t_list *ant, t_room *start, t_list *pth)
{
	t_list	*path;
	t_room	*dst;
	bool	eol;

	path = pth;
	while (ant && path && ((t_path *)path->content)->pending > 0)
	{
	eol = false;
		dst = (t_room *)((t_path *)path->content)->room->content;
		move_ant_one_step(start, dst);
		start->ant_id++;
		if (!path->next || !((t_path *)path->next->content)->pending)
			eol = true;
		ft_printf("L%d-%s%s", dst->ant_id, dst->name, eol ? "" : " ");
		((t_ant *)ant->content)->at_room = dst;
		((t_path *)path->content)->pending--;
		path = path->next;
		ant = ant->next;
	}
	ft_putchar('\n');
}

static t_list	*move_ant_on_the_way(t_list *ant)
{
	t_room	*curr;
	t_room	*next;
	bool	eol;

	while (ant && !is_start(((t_ant *)ant->content)->at_room))
	{
		curr = ((t_ant *)ant->content)->at_room;
		next = curr->next ? (t_room *)curr->next->content : NULL;
		eol = false;
		if (curr && next)
		{
			move_ant_one_step(curr, next);
// if (!ant->next || (is_start(((t_ant *)ant->next->content)->at_room)
// 	&& !start->population))
			if (!ant->next)
				eol = true;
			ft_printf("L%d-%s%s", curr->ant_id,	next->name, eol ? "" : " ");
			curr->ant_id = 0;
			((t_ant *)ant->content)->at_room = next;
		}
		ant = ant->next;
	}
	return (ant);
}

void			print_ant_moves(t_antfarm *atf, t_list *pth)
{
	t_path	*path;
	t_list	*ant;
	t_room	*start_room;

	path = pth->content;
	start_room = (t_room *)atf->start->content;
	start_room->ant_id = 1;
	start_room->population = atf->ant_qty;
	if (!(atf->options & ONLY_SOLUTION))
		ft_putchar('\n');
	if (ft_lstlen(pth) == 1 && path->len == 1)
		move_all_ants_at_once(atf);
	else
		while (((t_room *)atf->end->content)->population < atf->ant_qty)
		{
			ant = move_ant_on_the_way(atf->ants);
			move_ant_from_start(ant, start_room, pth);
		}
}

// static void		move_ants(t_antfarm *atf, t_list *pth)  //wei
// {
// 	t_list	*ant;
// 	t_room	*curr;

// 	ant = atf->ants;
// 	curr = ((t_ant *)ant->content)->at_room;
// 	ant = move_ant_on_the_way(ant, (t_room *)atf->start->content, curr);
// 	move_ants_in_start(ant, (t_room *)atf->start->content, pth);
// }