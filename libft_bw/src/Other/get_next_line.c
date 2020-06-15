/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:56:09 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/12 01:41:05 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int		update_line(t_gnl *elem, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = elem->str;
	while (elem->str[i] && elem->str[i] != '\n')
		i++;
	if (i == 0)
		*line = ft_strnew(0);
	else
		*line = ft_strsub(elem->str, 0, i);
	if (ft_strchr(elem->str, '\n'))
		elem->str = ft_strdup(ft_strchr(elem->str, '\n') + 1);
	else
		elem->str = ft_strnew(0);
	ft_strdel(&tmp);
	return (1);
}

static t_list	*init_list(t_list **list, const int fd)
{
	t_gnl	new;
	t_list	*node;

	new.fd = fd;
	new.str = NULL;
	if (!(node = ft_lstnew(&new, sizeof(t_gnl))))
		return (NULL);
	ft_lstappend(list, node);
	return (node);
}

static void		del_list(void *content, size_t size)
{
	t_gnl	*elem;

	elem = (t_gnl *)content;
	if (content && size)
	{
		ft_strdel(&elem->str);
		free(content);
	}
}

static int		update_str(const int fd, char **str, t_list **list)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buffer);
		ft_strdel(&tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	if (!str_isascii(str, ret))
	{
		ft_lstdel(list, del_list);
		return (0);
	}
	return (1);
}
static char	*ft_strreset(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	ft_strdel(&s1);
	s1 = s2;
	return (s1);
}

static int	ft_return_line(char **s, char **line, const int fd, int rd)
{
	char		*n;
	int			len;
	int			slen;

	if (s[fd] != '\0' && (n = ft_strchr(s[fd], '\n')))
	{
		len = n - s[fd];
		slen = ft_strlen(s[fd]);
		*line = ft_strsub(s[fd], 0, len);
		s[fd] = ft_strreset(s[fd], ft_strsub(s[fd], len + 1, slen - len - 1));
		return (1);
	}
	else if (s[fd] != '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
		if (ft_strlen(*line) == 0 && rd == 0)
		{
			*line = ft_strreset(*line, "\0");
			return (0);
		}
		return (1);
	}
	ft_strdel(&s[fd]);
	return (0);
}
int			get_next_line(const int fd, char **line)
{
	static char	*s[256];
	int			rd;
	char		*buff;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0 || BUFF_SIZE < 1 ||
		!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (s[fd])
			s[fd] = ft_strreset(s[fd], ft_strjoin(s[fd], buff));
		else
			s[fd] = ft_strdup(buff);
		if (ft_strchr(buff, '\n'))
			break ;
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	return (ft_return_line(s, line, fd, rd));
}
int				get_next_L2(const int fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*elem;

	if (read(fd, 0, 0) == -1 || BUFF_SIZE <= 0)
		return (-1);
	elem = list;
	while (elem)
	{
		if (((t_gnl *)elem->content)->fd == fd)
			break ;
		elem = elem->next;
	}
	if (elem == NULL)
		if (!(elem = init_list(&list, fd)))
			return (-1);
	if (((t_gnl *)elem->content)->str == NULL)
		((t_gnl *)elem->content)->str = ft_strnew(0);
	if (!ft_strchr(((t_gnl *)elem->content)->str, '\n'))
		if (!update_str(fd, &(((t_gnl *)elem->content)->str), &list))
			return (-1);
	if (((t_gnl *)elem->content)->str[0])
		return (update_line(elem->content, line));
	ft_lstdel(&list, del_list);
	return (0);
}
