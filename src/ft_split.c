/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:34:32 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 14:03:48 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

int	len_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

void	free_all(char **tab, int i)
{
	while (i--)
		free(tab[i]);
	free(tab);
}

static int	allocate_word(char **result, int i, const char *s, char c)
{
	int	len;

	len = len_word(s, c);
	result[i] = malloc((len + 1) * sizeof(char));
	if (!result[i])
	{
		free_all(result, i);
		return (0);
	}
	ft_strlcpy(result[i], s, len + 1);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!allocate_word(result, i, s, c))
				return (NULL);
			s += len_word(s, c);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}
