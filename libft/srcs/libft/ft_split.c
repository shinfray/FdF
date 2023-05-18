/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:01:23 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/18 17:20:34by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_separator(const char c, const char *sep)
{
	while (*sep != '\0')
	{
		if (c == *sep)
			return (1);
		++sep;
	}
	return (0);
}

static size_t	ft_wordcounter(const char *s, const char *sep)
{
	size_t	wordcount;

	wordcount = 0;
	while (*s != '\0')
	{
		if (ft_is_separator(*s, sep) == 0)
		{
			++wordcount;
			while (*s != '\0' && ft_is_separator(*s, sep) == 0)
				++s;
		}
		else
			++s;
	}
	return (wordcount);
}

static size_t	ft_strlen_split(const char *s, const char *sep)
{
	const char	*ptr;

	ptr = s;
	while (*ptr != '\0' && ft_is_separator(*ptr, sep) == 0)
		++ptr;
	return (ptr - s);
}

static char	**ft_free_whole_tab(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (*tab != NULL)
		free(*tab++);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, const char *sep)
{
	char	**tab;
	char	**o_tab;
	size_t	wordcount;

	if (s == NULL)
		return (NULL);
	wordcount = ft_wordcounter(s, sep);
	tab = ft_calloc(wordcount + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	o_tab = tab;
	while (wordcount-- != 0)
	{
		while (*s != '\0' && ft_is_separator(*s, sep) == 1)
			++s;
		*tab = ft_substr(s, 0, ft_strlen_split(s, sep));
		if (*tab == NULL)
			return (ft_free_whole_tab(o_tab));
		s += ft_strlen_split(s, sep);
		++tab;
	}
	return (o_tab);
}
