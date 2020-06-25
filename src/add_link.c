/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 03:01:12 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 22:42:50 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	link_exists(t_list *origin, t_list *dest)
{
	t_list	*elem;

	elem = origin;
	while (elem)
	{
		if (((t_link *)elem->content)->room == dest)
			return (1);
		elem = elem->next;
	}
	return (0);
}

/*
** Description:
**	Function check if the link exists already (via link_already_exits)
**	by this it means that the dest room (room2)
** Return:
**	-1: if the room2 is already in the list of links/edges
**	0: if mem allocation issue for add a new link/edge to the list of links/edges
**	1: link/edge has been added to the list.
*/

static int	create_link(t_list *room1, t_list *room2)
{
	t_list		*tlist_of_a_link;
	t_link		new_link;
	t_room		*origin_room;

	origin_room = (t_room *)(room1->content);
	new_link.usage = 0;
	new_link.room = NULL;
	if (link_exists(origin_room->links, room2))
		return (-1);
	if (!(tlist_of_a_link = ft_lstnew(&new_link, sizeof(t_link))))
		return (0);
	((t_link *)tlist_of_a_link->content)->room = room2;
	ft_lstappend(&origin_room->links, tlist_of_a_link);
	return (1);
}

/*
** Parameters:
**	t_list *head: list of roomsm head = atf->rooms
**	t_list **room1: pointer of type t_list initiate at NULL
**	t_list **room2: pointer of type t_list initiate at NULL
**	char **tab: name of the 2 rooms constituting the edge
** Description:
**	Check for the existence of the rooms named tab[0] and tab[1].
**	The name catched in line containing an edge are searched in the list
**	of rooms. If the 2 rooms existed corresponding links are pointed by
**	room1 and room2.
** Return:
**	1: if the 2 rooms named tab[0] and tab[1] exist within atf->rooms
**	0: if one of the 2 rooms tab[0]/tab[1] does not exist
*/

static int	room_exist(t_list *head, t_list **room1,
			t_list **room2, char **tab)
{
	t_list	*elem;
	t_room	*tmp;
	int		check;

	check = 0;
	elem = head;
	while (elem && check < 2)
	{
		tmp = (t_room *)elem->content;
		if (ft_strequ(tab[0], tmp->name))
		{
			check++;
			*room1 = elem;
		}
		if (ft_strequ(tab[1], tmp->name))
		{
			check++;
			*room2 = elem;
		}
		elem = elem->next;
	}
	return (check == 2);
}

/*
** Description:
**	Function check if the 2 rooms in the link/edge existed.
**	If so, link/edge are recorded
** Return:
**	1:
**	0:
*/

static int	link_checker(t_antfarm *atf, char **tab)
{
	t_list	*head;
	t_list	*room1;
	t_list	*room2;

	room1 = NULL;
	room2 = NULL;
	if (tab[0][0] == '#') //should also test tab[1][0]
		return (1);
	head = atf->rooms;
	if (!tab[0] || !tab[1] || tab[2]
		|| !room_exist(head, &room1, &room2, tab))
		return (0);
	// {ft_printf("link_checker1\n");	return (0);}
	return (create_link(room1, room2) * create_link(room2, room1));
}

/*
** Description:
**	Ignores commands/comments (Should there be command ? not precise in pdf)
**	Verification that the line has only one '-',
**	The links is added to the list of links/edges of both room.
*/

int			add_link(t_antfarm *atf, char *line)
{
	char	**tab;

	tab = NULL;
	if (line[0] == '#')
		return (1);
	if (ft_count_c(line, '-') != 1 || !(tab = ft_strsplit_c(line, '-')))
	// {ft_printf("addlink2\n");	return (0);}
		return (0);
	if (!link_checker(atf, tab))
	// {ft_printf("addlink3\n");	return (ret_strtab_free(tab, 0));}
		return (ret_strtab_free(tab, 0));
	return (ret_strtab_free(tab, 1));
}
