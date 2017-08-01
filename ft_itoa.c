/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:40:37 by jinfeld           #+#    #+#             */
/*   Updated: 2017/06/20 15:01:03 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(intmax_t n)
{
	int	dig;

	dig = 0;
	if (n < 0)
	{
		n *= -1;
		dig++;
	}
	while (n >= 10)
	{
		n /= 10;
		dig++;
	}
	if (n < 10)
		dig++;
	return (dig);
}

char		*ft_itoa(intmax_t n)
{
	int		dig;
	char	*res;

	dig = digits(n);
	if (!(res = (char *)malloc(sizeof(char) * dig + 1)))
		return (NULL);
	res[dig] = '\0';
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	while (n >= 10)
	{
		res[--dig] = n % 10 + '0';
		n /= 10;
	}
	res[--dig] = n + '0';
	return (res);
}
