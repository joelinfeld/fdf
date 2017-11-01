/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:23:35 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/01 15:29:20 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	error(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int		main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		error("Invalid number of arguments");
	defaultmap(&map, 'a');
	dims(argv[1], &(map.width), &(map.height));
	getmatrix(argv[1], &map);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, map.ww, map.wh, "mlx 42");
	mlx_key_hook(map.win, &keyz, &map);
	mlx_loop_hook(map.mlx, &drawgrid, &map);
	mlx_loop(map.mlx);
	return (0);
}
