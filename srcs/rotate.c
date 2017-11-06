/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:21:48 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/01 15:29:54 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotx(t_p *p, float *z, t_map *map)
{
	p->y = p->y * cos(map->rot[0]) - (p->z * sin(map->rot[0]));
	*z = p->y * sin(map->rot[0]) + *z * cos(map->rot[0]);
}

static void	roty(t_p *p, float *z, t_map *map)
{
	p->x = p->x * cos(map->rot[1]) + *z * sin(map->rot[1]);
	*z = -(p->x * sin(map->rot[1]) + *z * cos(map->rot[1]));
}

static void	rotz(t_p *p, t_map *map)
{
	p->x = p->x * cos(map->rot[2]) - (p->y * sin(map->rot[2]));
	p->y = p->x * sin(map->rot[2]) + p->y * cos(map->rot[2]);
}

void		rotate(t_p *p, t_map *map)
{
	float	xtrans;
	float	ytrans;
	float	ztrans;
	float	z;

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
