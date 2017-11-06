/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:00:02 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/06 14:37:11 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	findwidth(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static void	mapalloc(t_map *map)
{
	int	i;

	map->matrix = (int**)ft_memalloc(sizeof(int*) * map->height);
	if (!map->matrix)
		error("Malloc Error");
	i = -1;
	while (++i < map->height)
	{
		map->matrix[i] = (int*)ft_memalloc(sizeof(int) * map->width);
		if (!map->matrix[i])
			error("Malloc Error");
	}
}

static void	mapzset(t_map *map, int z)
{
	if (z < map->minz)
		map->minz = z;
	if (z > map->maxz)
		map->maxz = z;
}

void		dims(char *filename, int *width, int *height)
{
	int		fd;
	char	*stuff;
	int		first;

	first = 1;
	fd = open(filename, O_RDONLY);
	while (gnl(fd, &stuff))
	{
		(*height)++;
		if (first)
		{
			*width = findwidth(ft_strsplit(stuff, ' '));
			first = 0;
		}
		if (*width != findwidth(ft_strsplit(stuff, ' ')))
			error("Invalid Map: varying width");
		ft_strdel(&stuff);
	}
	close(fd);
}

void		getmatrix(char *str, t_map *map)
{
	char	**split;
	int		i;
	int		j;
	char	*stuff;
	int		fd;

	mapalloc(map);
	fd = open(str, O_RDONLY);
	i = 0;
	while (gnl(fd, &stuff))
	{
		split = ft_strsplit(stuff, ' ');
		j = -1;
		while (++j < map->width)
		{
			map->matrix[i][j] = ft_atoi(split[j]);
			mapzset(map, map->matrix[i][j]);
		}
		i++;
		ddelete(split);
		ddelete(&stuff);
	}
	close(fd);
}
