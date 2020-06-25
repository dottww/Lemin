/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_antfarm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:45:37 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 23:20:46 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Description:
**	Function skip the link in the list input(alst) that are comments.
**	When the content of the link is not a comment, it is supposedly a number
**	(for the number of ants). Thus we stock the number in ant_qty. If this is
**	not a number in the end, nothing is stock in ant_qty.
** Return:
**	1: the number of ants is stocked in ant_qty and the number is a positive int
**	0: otherwise
*/

static int		get_ant_qty(t_antfarm *atf, t_list **alst)
{
	while (*alst && is_comment(L2))
		*alst = (*alst)->next;
	if (*alst && ft_isnumber(L2) == 1)
	{
		if (!ft_atoi_int(L2, &atf->ant_qty))
			return (0);
		*alst = (*alst)->next;
		return ((atf->ant_qty > 0) && *alst);
	}
	return (0);
}

/*
** Description:
**	Check if the line (content of the input list)
**	is either a comment or command and if the line does not have a '-'
**	within (if there is a '-', the line is either a edge description or a
**	wrong formated input line)
** Return:
**	0: if the line is a possible link/edge description or a wrong formated line
**	1: otherwise (a room, a command or a comment)
*/

static int		the_rooms(char *line)
{
	if (line[0] == '#') //command or comment
		return (1);
	else if (ft_strchr(line, '-')) //is a link/edge
		return (0);
	return (1);
}

/*
** Description:
**	Initialization of all the inner variables of t_antfarm struct var
**	except ant_qty which is initialized by another function just after
*/

static void		init_antfarm_values(t_antfarm *atf)
{
	atf->rooms = NULL;
	atf->start = NULL;
	atf->end = NULL;
	atf->rounds = LONG_MAX; //pending
	atf->id = 0;
	atf->options = 0;
	atf->ants = NULL;
}

/*
** Description:
**	
**
*/

static int		init_links(t_antfarm *atf, t_list *alst)
{
	if (!alst || !add_link(atf, L1))
	// {ft_printf("init_link0\n");	return (0);}
		return (0);
	alst = alst->next;
	while (alst)
	{
		if (is_start_end(L1) || (!is_comment(L1) && !add_link(atf, L1)))
			return (0);
		// {ft_printf("init_link1={%s}\n", L1);	return (0);}
		alst = alst->next;
	}
	return (1);
}

/*
** Parameters:
**	t_antfarm *atf: struct variable representing the graph
**	t_list *alst: list where each link content is a string/line from input
** Description:
**	Initialization of t_antfarm *atf.
**	The list of input is roamed one time, comment are always skipped,
**	after possible comments a positive integer is expected and stock in
**	ant_qty
**	Then rooms, commands and comments are expected (rooms are stocked in
**	atf->rooms), pointers atf->start/end are set.
**	Comments and commands others than start/end are ignored.
**	
*/

int				get_antfarm(t_antfarm *atf, t_list *alst)
{
	init_antfarm_values(atf);
	if (!get_ant_qty(atf, &alst))
	// {ft_printf("here_rr1={%s}\n",L1);return (0);}
		return (0);
	while (atf->ant_qty && alst && the_rooms(L1))
	{
		if (!add_rooms(atf, &alst))
		// {ft_printf("here_rr2={%s}\n",L1);return (0);}
			return (0);
		alst = alst->next;
	}
	return ((!atf->start || !atf->end) ? 0 : init_links(atf, alst));
}
