/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 20:38:11 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/19 14:34:20 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sqrt2(int nb, int cap)
{
	if (nb < 0)
		return (0);
	if (cap / nb != nb)
		return (ft_sqrt2(nb - 1, cap));
	if (nb == cap / nb)
		return (nb);
	else
		return (0);
}

int			ft_sqrt(int nb)
{
	return (ft_sqrt2(nb, nb));
}
