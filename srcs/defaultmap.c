/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaultmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:36:46 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/06 14:52:08 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		defaultmap(t_map *map, char c)
{
	if (c != 'r')
	{
		map->width = 0;
		map->height = 0;
		map->maxz = 0;
		map->minz = 0;
	}
	map->trans[0] = 150;
	map->trans[1] = 150;
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
	map->ww = 1500;
	map->wh = 1500;
}
