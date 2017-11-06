/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:52:02 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/06 14:38:35 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	keyrot(int key, t_map *map)
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

static void	keytrans(int key, t_map *map)
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

static void	keyzoom(int key, t_map *map)
{
	if (key == 24)
		map->scale += 15;
	if (key == 27)
		map->scale -= 15;
}

static void	keyrothue(int key, t_map *map)
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

int			keyz(int key, t_map *map)
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
	return (1);
}
