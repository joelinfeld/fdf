/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:32:59 by jinfeld           #+#    #+#             */
/*   Updated: 2017/10/31 13:11:14 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include <math.h>
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
	int			 	scale;
	int				last;
	float			rot[3];
	t_clr			clr0;
	t_clr			clr1;
}					t_map;

#endif
