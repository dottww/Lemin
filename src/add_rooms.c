/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 03:08:07 by weilin            #+#    #+#             */
/*   Updated: 2020/06/16 01:24:40 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_repeat(t_antfarm *atf, char **tab)
{
	t_list	*elem;
	t_room	*tmp;

	if (!(tab[0] && tab[1] && tab[2] && !tab[3]))
		return (0);
	elem = atf->rooms;
	while (elem)
	{
		tmp = (t_room *)elem->content;
		if ((ft_atoi(tab[1]) == tmp->x && ft_atoi(tab[2]) == tmp->y)
			|| ft_strequ(tmp->name, tab[0]))
			return (0);
		elem = elem->next;
	}
	return (1);
}

static int		mark_start_end(t_room *room, t_list **alst)
{
	static int		t[2] = {0, 0};

	if (ft_strequ(L2, "##start"))
	{
		if (t[0] == 1)
			return (0);
		else
		{
			t[0] = 1;
			room->end = 0;
			*alst = (*alst)->next;
		}
	}
	else if (ft_strequ(L2, "##end"))
	{
		if (t[1] == 1)
			return (0);
		else
		{
			t[1] = 1;
			room->end = 1;
			*alst = (*alst)->next;
		}
	}
	return (*alst != NULL);
}

static void		init_pointer_to_end(t_antfarm *atf, t_list *ptr, int end)
{
	if (end == 0)
		atf->start = ptr;
	else
		atf->end = ptr;
}

static int		set_room_val(t_room *room, char **tab)
{
	if (!ft_atoi_int(tab[1], &room->x) || !ft_atoi_int(tab[2], &room->y))
		return (0);
	if (!(room->name = ft_strdup(tab[0])))
		return (0);
	room->path_id = 0;
	room->links = NULL;
	room->next = NULL;
	room->previous = NULL;
	room->new_next = NULL;
	room->visited = false;
	room->deviation = false;
	room->path_id = 0;
	room->new_path_id = 0;
	room->dead_end = false;
	room->population = 0;
	room->ant_id = 0;
	return (1);
}

int				add_room(t_antfarm *ath, t_list **alst)
{
	char			**tab;
	t_room			room;
	t_list			*new;

	room.end = -1;
	if (!mark_start_end(&room, alst))
		return (0);
	else if ((L2)[0] == '#')
		return (1);
	if (!(tab = ft_split_whitespaces(L2, (ft_wd(L2) == 3) ? 3 : 0)))
		return (0);
	if (!(tab[0] && tab[1] && tab[2] && !tab[3]) || !set_room_val(&room, tab))
		return (ret_strtab_free(tab, 0));
	if (!room_repeat(ath, tab) || !(new = ft_lstnew(&room, sizeof(t_room))))
	{
		ft_strdel(&room.name);
		return (ret_strtab_free(tab, 0));
	}
	(room.end != -1) ? init_pointer_to_end(ath, new, room.end) : 0;
	ft_lstappend(&ath->rooms, new);
	return (ret_strtab_free(tab, 1));
}
