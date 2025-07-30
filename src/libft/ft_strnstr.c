/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanr2 <alejanr2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:30:49 by alejanr2          #+#    #+#             */
/*   Updated: 2024/12/17 13:30:49 by alejanr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *) haystack);
	if (len == 0)
		return (0);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i] == needle[j] && i < len && needle[j] != '\0')
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i - j]);
		i++;
		i = i - j;
	}
	return (0);
}
