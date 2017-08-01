/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:41:04 by jinfeld           #+#    #+#             */
/*   Updated: 2017/05/16 17:14:38 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		linefill(char **line, char **save)
{
	char *end;
	char *tmp;

	if (ft_strlen(*save))
	{
		end = ft_strchr(*save, '\n');
		if (end != NULL)
		{
			*end++ = '\0';
			*line = ft_strdup(*save);
			tmp = ft_strdup(end);
			ft_strdel(save);
			*save = ft_strdup(tmp);
			ft_strdel(&tmp);
			return (1);
		}
		else
		{
			*line = ft_strdup(*save);
			ft_strclr(*save);
			return (1);
		}
	}
	return (0);
}

void	bufind(t_list **bufd, t_list **current, int fd)
{
	*current = *bufd;
	while (*current)
	{
		if ((int)(*current)->content_size == fd)
			return ;
		*current = (*current)->next;
	}
	ft_lstadd(bufd, ft_lstnew(NULL, 0));
	(*bufd)->content_size = fd;
	(*bufd)->content = ft_strnew(0);
	*current = *bufd;
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*bufd;
	t_list			*current;
	char			*buf;
	char			*tmp;
	int				ret;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	bufind(&bufd, &current, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		tmp = ft_strjoin(current->content, buf);
		ft_strdel((char**)&current->content);
		current->content = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (ft_strchr(current->content, '\n'))
			break ;
	}
	ft_strdel(&buf);
	return (linefill(line, (char**)&current->content));
}
