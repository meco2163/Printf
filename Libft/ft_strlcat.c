/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:40:12 by mekaplan          #+#    #+#             */
/*   Updated: 2025/05/29 20:40:14 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	d_size;
	size_t	s_size;

	if (!dst && !src)
		return (0);
	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (n <= d_size)
		return (n + s_size);
	i = d_size;
	j = 0;
	while ((i + j) < (n - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (d_size + s_size);
}
