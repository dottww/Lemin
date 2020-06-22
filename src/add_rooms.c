/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 03:08:07 by weilin            #+#    #+#             */
/*   Updated: 2020/06/21 19:54:38 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Description:
**	Check if the room where the inner variables values have just being set does not
**	already exist. name and couple of coordinates are inspected.
** Return:
**	1: the room is not already present in the list of rooms (atf->rooms)
**	0: if the room is repeated.
*/

static int		room_repeat(t_antfarm *atf, char **tab)
{
	t_list	*elem;
	t_room	*tmp;

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

/*
** Description:
**	function detects the commands "##start" and "##end".
**	The detection of these 2 conmmands is traduced by a state variable s_t
**	s_t in struct variable room, s_t = {-1; 0; 1} if the room is 
**	{not start or end; start, end}.
** Return:
**	1 : there is still link to process and not error raised (2 starts or ends)
**	0 : if command start/end has been already encounter or if end of list
**		reached after the specification of command "#start"/"#end"
*/

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
			room->s_t = 0;
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
			room->s_t = 1;
			*alst = (*alst)->next;
		}
	}
	return (*alst != NULL);
}

/*
** Description:
**
*/

static void		init_pointer_to_end(t_antfarm *atf, t_list *lst, int end)
{
	if (end == 0)
		atf->start = lst;
	else
		atf->end = lst;
}

/*
** Description:
**	Function check if the 2 last entries of tab are integers (CHECK if negative integers is allowed)
**	if the 2 entries are valid formated coordinates, then they are stocked in room.x/y
**	The function also initialized a all the other inner variables.
** Return:
**	1: if coordinates are valid and if no issue during mem allocation for name
**	0: if coordinates are not integer, or if memory allocation for room->name
*/

static int		set_room_val(t_room *room, char **tab)
{
	if (!ft_atoi_int(tab[1], &room->x) || !ft_atoi_int(tab[2], &room->y))
		return (0);
	if (!(room->name = ft_strdup(tab[0])))
		return (0);
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

/*
** Description:
**	Creation and initialization of room:
**	  - s_t: {-1;0;1} for {common room;start room;end room}
**	  - line has to be made of 3 words corresponding to the name and coord
**		of the room (room.name, room.x and room.y)
**	  - all the inner variables of room are initialized
**	  - Check if the room is already present within atf->rooms
**	  - set pointer atf->start and atf->end if room is start/end
** Return:
**	1: if the room is correct, fully initialized and has been add to atf->rooms
**		or if the line is a comment or not ignored command.
**	0: otherwise
*/

int				add_room(t_antfarm *atf, t_list **alst)
{
	char			**tab;
	t_room			room;
	t_list			*new_list;

	room.s_t = -1;
	if (!mark_start_end(&room, alst))
		return (0);
	else if ((L2)[0] == '#')
		return (1);
	if (!(tab = ft_split_whitespaces(L2, (ft_wd(L2) == 3) ? 3 : 0)))
		return (0);
	if (!(tab[0] && tab[1] && tab[2] && !tab[3]) || !set_room_val(&room, tab))
		return (ret_strtab_free(tab, 0));
	if (!room_repeat(atf, tab) || !(new_list = ft_lstnew(&room, sizeof(t_room))))
	{
		ft_strdel(&room.name);
		return (ret_strtab_free(tab, 0));
	}
	(room.s_t != -1) ? init_pointer_to_end(atf, new_list, room.s_t) : 0;
	ft_lstappend(&atf->rooms, new_list);
	return (ret_strtab_free(tab, 1));
}
