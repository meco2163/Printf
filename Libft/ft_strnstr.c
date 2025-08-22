/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:45:48 by mekaplan          #+#    #+#             */
/*   Updated: 2025/05/30 11:45:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	s2len;
	size_t	i;
	size_t	j;

	s2len = ft_strlen(little);
	if (s2len == 0)
		return ((char *)big);
	i = 0;
	while (i < n && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] != '\0' && little[j] != '\0'
			&& (i + j) < n && big[i + j] == little[j])
		{
			j++;
			if (j == s2len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
