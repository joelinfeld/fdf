/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:23:35 by jinfeld           #+#    #+#             */
/*   Updated: 2017/10/05 17:26:26 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include "fdf.h"

int		findwidth(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
	{	
	}
	return (i);
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
			*width = findwidth(ft_strsplit(stuff, ' ' ));
			first = 0;
		}
		if (*width != findwidth(ft_strsplit(stuff, ' ')))
			//errror
		ft_strdel(&stuff);
	}
	close(fd);
}	

void		getmatrix(char *str, t_map *map)
{
	char **split;
	int		i;
	int		j;
	char	*stuff;
	int		fd;

	fd = open(str, O_RDONLY);
	map->matrix = (int**)malloc(sizeof(int*) * map->height);
	if (!map->matrix)
		return ;
		//error
	i = -1;
	while (++i < map->height)
	{
		map->matrix[i] = (int*)ft_memalloc(sizeof(int) * map->width);
		if(!map->matrix[i])
			return ;
	}
	i = 0;
	while (gnl(fd, &stuff))
	{
		split = ft_strsplit(stuff, ' ');
		j = -1;
		while (++j < map->width)
		{
			map->matrix[i][j] = ft_atoi(split[j]);
			if (map->matrix[i][j] < map->minz)
				map->minz = map->matrix[i][j];
			if (map->matrix[i][j] > map->maxz)
				map->maxz = map->matrix[i][j];
		}
		i++;
		ddelete(split);
		ddelete(&stuff);
	}
	close(fd);
}

int		stepcount(t_p p1, t_p p2, int dx, int dy)
{
	int stepct;
	int x0;
	int y0;
	int err;
	int e2;
	int sx;
	int sy;
	stepct = 0;
	x0 = p1.x;
	y0 = p1.y;
	sx = x0<(int)p2.x ? 1 : -1;
	sy = y0<(int)p2.y ? 1 : -1;
	err = (dx>dy ? dx : -dy)/2;
	while(1)
	{
		stepct++;
		if (x0 == (int)p2.x && y0 == (int)p2.y) break;
		e2 = err;
		if (e2 > -dx) 
		{
			err -= dy; 
			x0 += sx;
		}
		if (e2 < dy) 
		{
			err += dx; 
			y0 += sy;
		}
	}
	return (stepct);
}

int		rgb(t_clr clr)
{
	int	color;

	color = clr.r;
	color = (color << 8) + clr.g;
	color = (color << 8) + clr.b;

	return (color);
}

int		colorgrade(t_p p1, t_p p2, t_clr bound0, t_clr bound1, int stepct, int i, t_map *map)
{
	t_clr	ret;
	
	if (p1.z == p2.z)
	{
		return(rgb(bound0));
	}

	float redstep, greenstep, bluestep;
	redstep = (bound1.r - bound0.r)/(float)stepct;
	greenstep = (bound1.g - bound0.g)/(float)stepct;
	bluestep = (bound1.b - bound0.b)/(float)stepct;
	ret.r = bound0.r + i * redstep;
	ret.g = bound0.g + i * greenstep;
	ret.b = bound0.b + i * bluestep;
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
		return(map->clr0);
	ret.r = map->clr0.r + (map->clr1.r - map->clr0.r) * (zmag / zdiff);
	ret.g = map->clr0.g + (map->clr1.g - map->clr0.g) * (zmag / zdiff);
	ret.b = map->clr0.b + (map->clr1.b - map->clr0.b) * (zmag / zdiff);
	return(ret);
}	

void	drawline(t_p p1, t_p p2, t_map *map)
{
	int x0 = p1.x;
	int x1 = p2.x;
	int y0 = p1.y;
	int y1 = p2.y;
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
	int	i;
	int r, g, b;
	int stepct;
	
	t_clr	bound0;
	t_clr	bound1;
	ft_bzero(&bound0, sizeof(t_clr));
	ft_bzero(&bound1, sizeof(t_clr));
	bound0 = colorbound(p1, map);
	bound1 = colorbound(p2, map);
	stepct = stepcount(p1, p2, dx, dy);
	i = -1;
	while (1)
	{
		++i;
		mlx_pixel_put(map->mlx, map->win, map->trans[0] + x0, map->trans[1] + y0, colorgrade(p1, p2, bound0, bound1, stepct, i, map));
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy; 
			x0 += sx;
		}
	 	if (e2 < dy) 
		{
			err += dx; 
			y0 += sy;
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
void	rotz(t_p *p, float *z, t_map *map)
{
	p->x = p->x * cos(map->rot[2]) - (p->y * sin(map->rot[2]));
	p->y = p->x * sin(map->rot[2]) + p->y * cos(map->rot[2]);
}
void	rotate(t_p *p, t_map *map)
{
	float	xtrans;
	float 	ytrans;
	float	ztrans;
	float	z;
	int		i;
	
	i = -1;
	xtrans = (float)map->width/2 * map->scale;
	ytrans = (float)map->height/2 * map->scale;
	ztrans = (float)(map->maxz - map->minz)/2 * map->scale;
	z = p->z;
	p->x -= xtrans;
	p->y -= ytrans;
	z -= ztrans;
	rotx(p, &z, map);
	roty(p, &z, map);
	rotz(p, &z, map);
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

int		drawgrid(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	int	i;
	int	j;
	t_p p[3];

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
	return (0);
}
void	defaultmap(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->maxz = 0;
	map->minz = 0;
	map->trans[0] = 150;
	map->trans[1] = 150;
	map->scale = 30;
	map->rot[0] = 0;
	map->rot[1] =  0;
	map->rot[2] = 0;
	map->clr0.r = 0;
	map->clr0.g = 255;
	map->clr0.b = 100;
	map->clr1.r = 255;
	map->clr1.g = 100;
	map->clr1.b = 0;
}

int		keyz(int key, t_map *map)
{

	if (key == 123)
		map->trans[0] -= 10;
	if (key == 124)
		map->trans[0] += 10;
	if (key == 125)
		map->trans[1] += 10;
	if (key == 126)
		map->trans[1] -= 10;
	if (key == 6 && key == 257)
		map->rot[2] += .1;
	if (key == 7)
		map->rot[0] += .05;
	if (key == 16)
		map->rot[1] += .05;
	if (key == 18)
		map->scale += 15;
	if (key == 19)
		map->scale -= 15;
	ft_printf("%d\n", key);
	return (1);
}

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_map	map;
	if (argc != 2)
		return (0);
	//error
	defaultmap(&map);
	dims(argv[1], &(map.width), &(map.height));
	getmatrix(argv[1], &map);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, 2000, 2000, "mlx 42");
	mlx_do_key_autorepeaton(map.mlx);
	mlx_key_hook(map.win, &keyz, &map);
	mlx_loop_hook(map.mlx, &drawgrid, &map);
	mlx_loop(map.mlx);
	return (0);
}
