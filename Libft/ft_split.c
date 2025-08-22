/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:13:33 by mekaplan          #+#    #+#             */
/*   Updated: 2025/06/12 12:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_free_words(char **words)
{
	size_t	i;

	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (NULL);
}

static size_t	ft_word_counter(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s || !s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		count++;
	return (count);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i] && (*next_word)[i] != c)
	{
		(*next_word_len)++;
		i++;
	}
}

static int	ft_set_word(char **words, char *src, size_t len, size_t idx)
{
	words[idx] = malloc(len + 1);
	if (!words[idx])
		return (0);
	ft_strlcpy(words[idx], src, len + 1);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**words;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	wc = ft_word_counter(s, c);
	words = malloc(sizeof(char *) * (wc + 1));
	if (!words)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < wc)
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		if (!ft_set_word(words, next_word, next_word_len, i))
			return (ft_free_words(words));
		i++;
	}
	words[i] = NULL;
	return (words);
}
