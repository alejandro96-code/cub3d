/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:29:25 by alejanr2          #+#    #+#             */
/*   Updated: 2024/12/17 13:29:26 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (a[i] && b[i] && n--)
	{
		if (a[i] != b[i] || !n)
			return (a[i] - b[i]);
		i++;
	}
	return (a[i] - b[i]);
}
