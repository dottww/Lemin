/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:49:21 by pimichau          #+#    #+#             */
/*   Updated: 2020/06/19 13:44:00 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_ants_from_start(t_list *ant_troop, t_antfarm *atf
				, t_list *paths)
{
	t_list	*path;
	t_room	*dest_room;
	int		is_nexted;

	path = paths;
	is_nexted = 1;
	while (ant_troop && path && ((t_path *)path->content)->sent > 0)
	{
		dest_room = ((t_path *)path->content)->room->content;
		STARTROOM->population--;
		dest_room->population++;
		dest_room->ant_id = STARTROOM->ant_id++;
		if (!path->next || ((t_path *)path->next->content)->sent == 0)
			is_nexted = 0;
		ft_printf("L%d-%s%s", dest_room->ant_id,
		dest_room->name, is_nexted ? " " : "");
		ANT = dest_room;
		((t_path *)path->content)->sent--;
		path = path->next;
		ant_troop = ant_troop->next;
	}
	ft_putchar('\n');
}

static void		move_ants_forward(t_antfarm *atf, t_list *paths)
{
	t_list	*ant_troop;
	t_room	*position;
	int		is_nexted;

	ant_troop = atf->ants;
	position = ANT;
	while (ant_troop && ANT->s_t != 0)
	{
		position = ANT;
		if (position && position->next && (is_nexted = 1))
		{
			position->population--;
			NEXTROOM->population++;
			NEXTROOM->ant_id = position->ant_id;
			if (!ant_troop->next || NEXTANT->s_t == 0 && STARTROOM->population == 0))
				is_nexted = 0;
			ft_printf("L%d-%s%s", position->ant_id,	NEXTROOM->name, is_nexted ? " " : "");
			position->ant_id = 0;
			ANT = NEXTROOM;
		}
		ant_troop = ant_troop->next;
	}
	move_ants_from_start(ant_troop, atf, paths);
}

static void		move_all_ants(t_antfarm *atf)
{
	int	i;

	i = 0;
	while (++i < atf->ant_qty)
		ft_printf("L%d-%s ", i, ((t_room *)atf->end->content)->name);
	ft_printf("L%d-%s\n", i, ((t_room *)atf->end->content)->name);
	atf->rounds = 1;
}

void			print_output(t_antfarm *atf, t_list *paths)
{
	t_path	*path;

	path = paths->content;
	STARTROOM->population = atf->ant_qty;
	STARTROOM->ant_id = 1;
	if (!(atf->option & ONLY_DISPLAY_SOLUTION))
		ft_putchar('\n');
	STARTROOM->population = atf->ant_qty;
	STARTROOM->ant_id = 1;
	if (ft_lstlen(paths) == 1 && path->len == 1)
	{
		move_all_ants(atf);
		return ;
	}
	while (((t_room *)atf->end->content)->population < atf->ant_qty)
		move_ants_forward(atf, paths);
}
