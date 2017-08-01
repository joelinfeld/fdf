/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:40:37 by jinfeld           #+#    #+#             */
/*   Updated: 2017/06/19 16:47:09 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(uintmax_t n, int base)
{
	int dig;

	dig = 1;
	while (n /= base)
		dig++;
	return (dig);
}

char		*ft_itoa_base(uintmax_t n, int base, int caseflag)
{
	int		dig;
	char	*res;
	char	sym[16];
	int i;
	
	i = -1;
	while (++i < 16)
	{
		if (i < 10)
			sym[i] = '0' + i;
		else
			sym[i] = (caseflag ? 'A' + i - 10 : 'a' + i - 10);		
	}
	dig = digits(n, base);
	if (!(res = ft_strnew(dig)))
		return (NULL);
	if (n == 0)
		res[0] = '0';
	while (n)
	{
		res[dig - 1] = sym[n % base];
		n /= base;
		dig--;
	}
	return (res);
}
