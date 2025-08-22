/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:50:25 by mekaplan          #+#    #+#             */
/*   Updated: 2025/05/30 11:50:28 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*p;
	unsigned char	ch;
	size_t			offset;

	ch = (unsigned char)c;
	offset = ft_strlen(s);
	p = (char *)s + offset;
	while (p >= s)
	{
		if (*p == ch)
			return (p);
		p--;
	}
	return (NULL);
}
