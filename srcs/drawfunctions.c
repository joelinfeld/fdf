/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:07:14 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/06 15:55:56 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				stepcount(t_node node)
{
	node.stepct = 0;
	while (1)
	{
		node.stepct++;
		if (node.p[0].x == node.p[1].x && node.p[0].y == node.p[1].y)
			break ;
		node.e2 = node.err;
		if (node.e2 > -node.dx)
		{
			node.err -= node.dy;
			node.p[0].x += node.sx;
		}
		if (node.e2 < node.dy)
		{
			node.err += node.dx;
			node.p[0].y += node.sy;
		}
	}
	return (node.stepct);
}

static void		errorcheck(t_node *node, t_p *p1)
{
	if (node->e2 > -node->dx)
	{
		node->err -= node->dy;
		p1->x += node->sx;
	}
	if (node->e2 < node->dy)
	{
		node->err += node->dx;
		p1->y += node->sy;
	}
}

static void		drawline(t_p p1, t_p p2, t_map *map)
{
	t_node	node;
	int		i;

	map->image.data = mlx_get_data_addr(map->image.ptr, &(map->image.bpp),
		&(map->image.size_line), &(map->image.endian));
	node = setnode(p1, p2, map);
	i = -1;
	while (1)
	{
		++i;
		if ((int)p1.y + map->trans[1] < map->wh && (int)p1.x
		+ map->trans[0] < map->ww &&
		(int)p1.y + map->trans[1] >= 0 && (int)p1.x + map->trans[0] >= 0)
			*(int *)(map->image.data + map->image.size_line
			* ((int)p1.y + map->trans[1]) + ((int)p1.x + map->trans[0])
			* sizeof(map->image.bpp)) =
			mlx_get_color_value(map->mlx, colorgrade(node, i));
		if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
			break ;
		node.e2 = node.err;
		errorcheck(&node, &p1);
	}
}

static void		drawgridhelp(t_p p[3], t_map *map, int i, int j)
{
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			p[0] = setpoint(i, j, map->matrix[i][j], map->scale);
			rotate(&p[0], map);
			if (j + 1 < map->width)
			{
				p[1] = setpoint(i, j + 1, map->matrix[i][j + 1], map->scale);
				rotate(&p[1], map);
				drawline(p[0], p[1], map);
			}
			if (i + 1 < map->height)
			{
				p[2] = setpoint(i + 1, j, map->matrix[i + 1][j], map->scale);
				rotate(&p[2], map);
				drawline(p[0], p[2], map);
			}
		}
	}
}

int				drawgrid(t_map *map)
{
	int	i;
	int	j;
	t_p p[3];

	i = 0;
	j = 0;
	mlx_clear_window(map->mlx, map->win);
	map->image.ptr = mlx_new_image(map->mlx, map->ww, map->wh);
	drawgridhelp(p, map, i, j);
	mlx_put_image_to_window(map->mlx, map->win, map->image.ptr, 0, 0);
	mlx_destroy_image(map->mlx, map->image.ptr);
	return (0);
}
