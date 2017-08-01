/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:50:50 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 18:20:14 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		len;

	len = ft_strlen(s1) + 1;
	res = (char *)malloc(sizeof(char) * len);
	if (res)
		ft_strcpy(res, s1);
	return (res);
}
