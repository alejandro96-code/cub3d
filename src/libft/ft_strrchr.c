/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:30:54 by alejanr2          #+#    #+#             */
/*   Updated: 2024/12/17 13:30:55 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	a;

	i = 0;
	while (s[i] != '\0')
		i++;
	a = c;
	while (i >= 0)
	{
		if (s[i] == a)
		{
			return (&((char *)s)[i]);
		}
		i--;
	}
	return (0);
}
