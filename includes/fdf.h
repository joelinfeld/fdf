/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:32:59 by jinfeld           #+#    #+#             */
/*   Updated: 2017/11/06 15:54:08 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct		s_img
{
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;
}					t_img;
typedef struct		s_clr
{
	int				r;
	int				g;
	int				b;
}					t_clr;
typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_p;
typedef struct		s_node
{
	t_p				p[2];
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
	t_clr			bound[2];
	int				stepct;
}					t_node;
typedef struct		s_map
{
	int				**matrix;
	void			*mlx;
	void			*win;
	t_img			image;
	int				width;
	int				height;
	int				maxz;
	int				minz;
	int				trans[2];
	int				scale;
	int				last;
	int				ww;
	int				wh;
	float			rot[3];
	t_clr			clr0;
	t_clr			clr1;
}					t_map;
void				defaultmap(t_map *map, char c);
int					keyz(int key, t_map *map);
void				getmatrix(char *str, t_map *map);
void				dims(char *filename, int *width, int *height);
void				error(char *str);
int					drawgrid(t_map *map);
t_clr				colorbound(t_p p, t_map *map);
int					colorgrade(t_node node, int i);
void				rotate(t_p *p, t_map *map);
void				keyreset(int key, t_map *map);
t_p					setpoint(int y, int x, int z, int scale);
t_node				setnode(t_p p1, t_p p2, t_map *map);
int					stepcount(t_node node);

#endif
