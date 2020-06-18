/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 12:49:21 by pimichau          #+#    #+#             */
/*   Updated: 2020/06/17 17:56:27 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_ants_from_start(t_list *ant, t_antfarm *atf
				, t_list *paths)
{
	t_list	*path;
	t_room	*dest_room;
	int		is_nexted;

	path = paths;
	is_nexted = 1;
	while (ant && path && ((t_path *)path->content)->sent > 0)
	{
		dest_room = ((t_path *)path->content)->room->content;
		((t_room *)atf->start->content)->population--;
		dest_room->population++;
		dest_room->ant_id = ((t_room *)atf->start->content)->ant_id++;
		if (!path->next || ((t_path *)path->next->content)->sent == 0)
			is_nexted = 0;
		ft_printf("L%d-%s%s", dest_room->ant_id,
		dest_room->name, is_nexted ? " " : "");
		((t_ant *)ant->content)->position = dest_room;
		((t_path *)path->content)->sent--;
		path = path->next;
		ant = ant->next;
	}
	ft_putchar('\n');
}

static void		move_ants_forward(t_antfarm *atf, t_list *paths)
{
	t_list	*ant;
	t_room	*position;
	int		is_nexted;

	ant = atf->ants;
	position = ((t_ant *)ant->content)->position;
	while (ant && ((t_ant *)ant->content)->position->end != 0)
	{
		position = ((t_ant *)ant->content)->position;
		if (position && position->next && (is_nexted = 1))
		{
			position->population--;
			((t_room *)position->next->content)->population++;
			((t_room *)position->next->content)->ant_id = position->ant_id;
			if (!ant->next || (((t_ant *)ant->next->content)->position->end == 0
			&& ((t_room *)atf->start->content)->population == 0))
				is_nexted = 0;
			ft_printf("L%d-%s%s", position->ant_id,
			((t_room *)position->next->content)->name, is_nexted ? " " : "");
			position->ant_id = 0;
			((t_ant *)ant->content)->position = position->next->content;
		}
		ant = ant->next;
	}
	move_ants_from_start(ant, atf, paths);
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
	((t_room *)atf->start->content)->population = atf->ant_qty;
	((t_room *)atf->start->content)->ant_id = 1;
	if (!(atf->option & ONLY_DISPLAY_SOLUTION))
		ft_putchar('\n');
	((t_room *)atf->start->content)->population = atf->ant_qty;
	((t_room *)atf->start->content)->ant_id = 1;
	if (ft_lstcount(paths) == 1 && path->len == 1)
	{
		move_all_ants(atf);
		return ;
	}
	while (((t_room *)atf->end->content)->population < atf->ant_qty)
		move_ants_forward(atf, paths);
}
