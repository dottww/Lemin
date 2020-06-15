/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:05:53 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/10 18:23:02 by weilin           ###   ########.fr       */
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
