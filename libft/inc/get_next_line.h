/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:29:30 by weilin            #+#    #+#             */
/*   Updated: 2020/06/12 02:53:32 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_L1_H
# define GET_NEXT_L1_H
# define BUFF_SIZE 5

# include "libft.h"
# include <fcntl.h>

int get_next_line(const int fd, char **line);

#endif
