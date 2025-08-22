/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:23:16 by mekaplan          #+#    #+#             */
/*   Updated: 2025/05/29 18:23:25 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*dp;
	const unsigned char		*sp;

	if ((!dst && !src) && n > 0)
		return (0);
	if (n == 0)
		return (dst);
	dp = (unsigned char *)dst;
	sp = (const unsigned char *)src;
	while (n--)
		*dp++ = *sp++;
	return (dst);
}
