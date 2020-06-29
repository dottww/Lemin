/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:37:25 by weilin            #+#    #+#             */
/*   Updated: 2020/06/29 04:07:01 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_ant(t_room *curr, t_room *next)
{
	curr->population--;
	next->population++;
	next->ant_id = curr->ant_id;
}

static void		move_ants_in_start(t_list *ant_lst, t_room *start_room
				, t_list *pth)
{
	t_list	*path;
	t_room	*dest_room;
	int		is_nexted;

	path = pth;
	is_nexted = 1;
	while (ant_lst && path && ((t_path *)path->content)->sent > 0)
	{
		dest_room = (t_room *)((t_path *)path->content)->room->content;
		move_ant(start_room, dest_room);
		// start_room->population--;
		// dest_room->population++;
		// dest_room->ant_id = start_room->ant_id;
		start_room->ant_id++;
		if (!path->next || ((t_path *)path->next->content)->sent == 0)
			is_nexted = 0;
		ft_printf("L%d-%s%s", dest_room->ant_id,
		dest_room->name, is_nexted ? " " : "");
		((t_ant *)ant_lst->content)->at_room = dest_room;
		((t_path *)path->content)->sent--;
		path = path->next;
		ant_lst = ant_lst->next;
	}
	ft_putchar('\n');
}

static void		move_ants(t_antfarm *atf, t_list *pth)  //wei
{
	t_list	*ant;
	t_room	*curr;
	int		is_nexted;
// static int x=0;
	ant = atf->ants;
	curr = ((t_ant *)ant->content)->at_room;
	while (ant && !is_start(((t_ant *)ant->content)->at_room))
	{
		curr = ((t_ant *)ant->content)->at_room;
		if (curr && curr->next && (is_nexted = 1))
		{
			move_ant(curr, (t_room *)(curr->next->content));
			// curr->population--;
			// ((t_room *)(curr->next->content))->population++;
			// ((t_room *)(curr->next->content))->ant_id = curr->ant_id;
			if (!ant->next || (((t_ant *)ant->next->content)->at_room->s_t == 0
			&& ((t_room *)atf->start->content)->population == 0))
				is_nexted = 0; //wei
// ft_printf("L[%d]%d-%s%s",x++, curr->ant_id,
			ft_printf("L%d-%s%s", curr->ant_id,
			((t_room *)(curr->next->content))->name, is_nexted ? " " : "");
			curr->ant_id = 0;
			((t_ant *)ant->content)->at_room = (t_room *)curr->next->content;
		}
		ant = ant->next;
	}
	move_ants_in_start(ant, (t_room *)atf->start->content, pth); //wei
	// move_ants_in_start(ant, atf, pth); //wei
}
// static void		move_ants(t_antfarm *atf, t_list *pth)  //wei
// {
// 	t_list	*ant;
// 	t_room	*at_room;
// 	int		is_nexted;

// 	ant = atf->ants;
// 	at_room = ((t_ant *)ant->content)->at_room;
// 	while (ant && ((t_ant *)ant->content)->at_room->s_t != 0)
// 	{
// 		at_room = ((t_ant *)ant->content)->at_room;
// 		if (at_room && at_room->next && (is_nexted = 1))
// 		{
// 			at_room->population--;
// 			((t_room *)at_room->next->content)->population++;
// 			((t_room *)at_room->next->content)->ant_id = at_room->ant_id;
// 			if (!ant->next || (((t_ant *)ant->next->content)->at_room->s_t == 0
// 			&& ((t_room *)atf->start->content)->population == 0))
// 				is_nexted = 0; //wei
// 			ft_printf("L%d-%s%s", at_room->ant_id,
// 			((t_room *)at_room->next->content)->name, is_nexted ? " " : "");
// 			at_room->ant_id = 0;
// 			((t_ant *)ant->content)->at_room = at_room->next->content;
// 		}
// 		ant = ant->next;
// 	}
// 	move_ants_in_start(ant, atf, pth); //wei
// }

static void		move_all_ants_at_once(t_antfarm *atf)
{
	int	i;

	i = 0;
	while (++i < atf->ant_qty)
		ft_printf("L%d-%s ", i, ((t_room *)atf->end->content)->name);
	ft_printf("L%d-%s\n", i, ((t_room *)atf->end->content)->name);
	((t_room *)atf->end->content)->population += i;
	((t_room *)atf->start->content)->population -= i;
	atf->rounds = 1;
}

void			print_ant_moves(t_antfarm *atf, t_list *pth)
{
	t_path	*path;

	path = pth->content;
	if (!(atf->options & ONLY_SOLUTION))
		ft_putchar('\n');
	((t_room *)atf->start->content)->population = atf->ant_qty;
	((t_room *)atf->start->content)->ant_id = 1;
	if (ft_lstlen(pth) == 1 && path->len == 1)
	{
		move_all_ants_at_once(atf);
		// ft_printf("((t_room *)atf->start->content)->population = %d\n",  ((t_room *)atf->start->content)->population);
		// ft_printf("((t_room *)atf->end->content)->population = %d\n",  ((t_room *)atf->end->content)->population);
		return ;
	}
	while (((t_room *)atf->end->content)->population < atf->ant_qty)
		move_ants(atf, pth);
}
