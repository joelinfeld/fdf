/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 14:50:02 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/26 01:03:06 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				i;
	int				sign;
	int				nbr;
	unsigned char	*s;

	s = (unsigned char *)str;
	sign = 1;
	nbr = 0;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
			s[i] == '\f' || s[i] == '\v' || s[i] == '\r')
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
	{
		nbr = (s[i] - '0') + (10 * nbr);
		i++;
	}
	return (nbr * sign);
}
