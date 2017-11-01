/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:23:35 by jinfeld           #+#    #+#             */
/*   Updated: 2017/10/31 19:42:56 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include "fdf.h"

int		findwidth(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void		error(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
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

void		mapalloc(t_map *map)
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

void		mapzset(t_map *map, int z)
{
	if (z < map->minz)
		map->minz = z;
	if (z > map->maxz)
		map->maxz = z;
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

int		stepcount(t_node node)
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

int		rgb(t_clr clr)
{
	int	color;

	color = clr.r;
	color = (color << 8) + clr.g;
	color = (color << 8) + clr.b;
	return (color);
}

int		colorgrade(t_node node, int i)
{
	t_clr		ret;
	float		redstep;
	float		greenstep;
	float		bluestep;

	if (node.p[0].z == node.p[1].z)
		return (rgb(node.bound[0]));
	redstep = (node.bound[1].r - node.bound[0].r) / (float)node.stepct;
	greenstep = (node.bound[1].g - node.bound[0].g) / (float)node.stepct;
	bluestep = (node.bound[1].b - node.bound[0].b) / (float)node.stepct;
	ret.r = node.bound[0].r + i * redstep;
	ret.g = node.bound[0].g + i * greenstep;
	ret.b = node.bound[0].b + i * bluestep;
	return (rgb(ret));
}

t_clr	colorbound(t_p p, t_map *map)
{
	t_clr	ret;
	float	zmag;
	float	zdiff;

	zmag = p.z - (map->minz * map->scale);
	zdiff = (map->maxz - map->minz) * map->scale;
	if (zdiff == 0)
		return (map->clr0);
	ret.r = map->clr0.r + (map->clr1.r - map->clr0.r) * (zmag / zdiff);
	ret.g = map->clr0.g + (map->clr1.g - map->clr0.g) * (zmag / zdiff);
	ret.b = map->clr0.b + (map->clr1.b - map->clr0.b) * (zmag / zdiff);
	return (ret);
}

t_node	setnode(t_p p1, t_p p2, t_map *map)
{
	t_node	ret;

	ft_bzero(&ret, sizeof(t_node));
	ret.p[0] = p1;
	ret.p[1] = p2;
	ret.dx = abs((int)p2.x - (int)p1.x);
	ret.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	ret.dy = abs((int)p2.y - (int)p1.y);
	ret.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	ret.err = (ret.dx > ret.dy ? ret.dx : -ret.dy) / 2;
	ret.bound[0] = colorbound(p1, map);
	ret.bound[1] = colorbound(p2, map);
	ret.stepct = stepcount(ret);
	return (ret);
}

void	drawline(t_p p1, t_p p2, t_map *map)
{
	t_node	node;
	int		i;

	map->image.data = mlx_get_data_addr(map->image.ptr, &(map->image.bpp), &(map->image.size_line), &(map->image.endian));
	node = setnode(p1, p2, map);
	i = -1;
	while (1)
	{
		++i;
		if ((int)p1.y + map->trans[1] < 3000 && (int)p1.x + map->trans[0] < 3000 && (int)p1.y + map->trans[1] >= 0 && (int)p1.x + map->trans[0] >= 0)
			*(int *)(map->image.data + map->image.size_line * ((int)p1.y + map->trans[1]) + ((int)p1.x + map->trans[0]) * sizeof(map->image.bpp)) = mlx_get_color_value(map->mlx, colorgrade(node, i));
		if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
			break ;
		node.e2 = node.err;
		if (node.e2 > -node.dx)
		{
			node.err -= node.dy;
			p1.x += node.sx;
		}
		if (node.e2 < node.dy)
		{
			node.err += node.dx;
			p1.y += node.sy;
		}
	}
}

void	rotx(t_p *p, float *z, t_map *map)
{
	p->y = p->y * cos(map->rot[0]) - (p->z * sin(map->rot[0]));
	*z = p->y * sin(map->rot[0]) + *z * cos(map->rot[0]);
}

void	roty(t_p *p, float *z, t_map *map)
{
	p->x = p->x * cos(map->rot[1]) + *z * sin(map->rot[1]);
	*z = -(p->x * sin(map->rot[1]) + *z * cos(map->rot[1]));
}

void	rotz(t_p *p, t_map *map)
{
	p->x = p->x * cos(map->rot[2]) - (p->y * sin(map->rot[2]));
	p->y = p->x * sin(map->rot[2]) + p->y * cos(map->rot[2]);
}

void	rotate(t_p *p, t_map *map)
{
	float	xtrans;
	float	ytrans;
	float	ztrans;
	float	z;
	int		i;

	i = -1;
	xtrans = (float)map->width / 2 * map->scale;
	ytrans = (float)map->height / 2 * map->scale;
	ztrans = (float)(map->maxz - map->minz) / 2 * map->scale;
	z = p->z;
	p->x -= xtrans;
	p->y -= ytrans;
	z -= ztrans;
	rotx(p, &z, map);
	roty(p, &z, map);
	rotz(p, map);
	p->x += xtrans;
	p->y += ytrans;
}

t_p		setpoint(int y, int x, int z, int scale)
{
	t_p	p;

	p.x = (float)x * scale;
	p.y = (float)y * scale;
	p.z = (float)z * scale;
	return (p);
}

void	drawgridhelp(t_p p[3], t_map *map, int i, int j)
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

int		drawgrid(t_map *map)
{
	int	i;
	int	j;
	t_p p[3];
	
	i = 0;
	j = 0;
	mlx_clear_window(map->mlx, map->win);
	map->image.ptr = mlx_new_image(map->mlx, 3000, 3000);
	drawgridhelp(p, map, i, j);
	mlx_put_image_to_window(map->mlx, map->win, map->image.ptr, 0, 0);
	mlx_destroy_image(map->mlx, map->image.ptr);
	return (0);
}

void	defaultmap(t_map *map, char c)
{
	if (c != 'r')
	{
		map->width = 0;
		map->height = 0;
		map->maxz = 0;
		map->minz = 0;
	}
	map->trans[0] = 0;
	map->trans[1] = 0;
	map->scale = 20;
	map->rot[0] = 0;
	map->rot[1] = 0;
	map->rot[2] = 0;
	map->clr0.r = 0;
	map->clr0.g = 0;
	map->clr0.b = 255;
	map->clr1.r = 255;
	map->clr1.g = 0;
	map->clr1.b = 0;
}

void	keyrot(int key, t_map *map)
{
	if (key == 6)
		map->rot[2] += .1;
	if (key == 7)
		map->rot[0] += .1;
	if (key == 16)
		map->rot[1] += .1;
	if (key == 0)
		map->rot[2] -= .1;
	if (key == 1)
		map->rot[0] -= .1;
	if (key == 4)
		map->rot[1] -= .1;
}

void	keytrans(int key, t_map *map)
{
	if (key == 123)
		map->trans[0] -= 10;
	if (key == 124)
		map->trans[0] += 10;
	if (key == 125)
		map->trans[1] += 10;
	if (key == 126)
		map->trans[1] -= 10;
}

void	keyzoom(int key, t_map *map)
{
	if (key == 24)
		map->scale += 15;
	if (key == 27)
		map->scale -= 15;
}

void	keyreset(int key, t_map *map)
{
	if (key == 15)
	{
		defaultmap(map, 'r');	
	}
}

void	keyrothue(int key, t_map *map)
{

	if (key == 50)
	{
		if (map->clr0.r == 0 && map->clr0.b == 255 && map->clr0.g == 0)
		{
			map->clr0.b = 0;
			map->clr0.r = 255;
			map->clr1.g = 255;
			map->clr1.r = 0;
		}
		else if (map->clr0.r == 255 && map->clr0.b == 0 && map->clr0.g == 0)
		{
			map->clr0.r = 0;
			map->clr0.g = 255;
			map->clr1.g = 0;
			map->clr1.b = 255;
		}
		else if (map->clr0.r == 0 && map->clr0.b == 0 && map->clr0.g == 255)
		{
			map->clr0.g = 0;
			map->clr0.b = 255;
			map->clr1.r = 255;
			map->clr1.b = 0;
		}

	}
}


int		keyz(int key, t_map *map)
{
	int rev;

	rev = 1;
	if (key == 123 || key == 124 || key == 125 || key == 126)
		keytrans(key, map);
	if (key == 6 || key == 7 || key == 16 || key == 0 || key == 1 || key == 4)
		keyrot(key, map);
	if (key == 24 || key == 27)
		keyzoom(key, map);
	if (key == 50)
		keyrothue(key, map);
	if (key == 53)
		exit(EXIT_SUCCESS);
	if (key == 15)
		keyreset(key, map);
	ft_printf("%d\n", key);
	return (1);
}

int		main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (0);
	defaultmap(&map, 'a');
	dims(argv[1], &(map.width), &(map.height));
	getmatrix(argv[1], &map);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, 3000, 3000, "mlx 42");
	mlx_key_hook(map.win, &keyz, &map);
	mlx_loop_hook(map.mlx, &drawgrid, &map);
	mlx_loop(map.mlx);
	return (0);
}
