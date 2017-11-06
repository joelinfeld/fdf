/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setpoint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:49:01 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/06 15:49:51 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_p		setpoint(int y, int x, int z, int scale)
{
	t_p	p;

	p.x = (float)x * scale;
	p.y = (float)y * scale;
	p.z = (float)z * scale;
	return (p);
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
