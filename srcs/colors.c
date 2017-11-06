/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:19:27 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/01 15:30:57 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	rgb(t_clr clr)
{
	int	color;

	color = clr.r;
	color = (color << 8) + clr.g;
	color = (color << 8) + clr.b;
	return (color);
}

int			colorgrade(t_node node, int i)
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

t_clr		colorbound(t_p p, t_map *map)
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
