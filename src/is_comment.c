/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_comment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 00:06:23 by weilin            #+#    #+#             */
/*   Updated: 2020/06/12 03:14:46 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_comment(char *line)
{
	return (line[0] == '#');
}

int	is_start_end(char *line)
{
	return (ft_strequ("##start", line) || ft_strequ("##end", line));
}
