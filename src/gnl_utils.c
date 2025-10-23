/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:57:45 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 11:50:47 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*join;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	join = malloc(lens1 + lens2 + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		join[i] = s1[i];
		i++;
	}
	while (i < lens1 + lens2)
	{
		join[i++] = *s2;
		s2++;
	}
	join[i] = '\0';
	return (join);
}

char	*clean(char **stash)
{
	char	*line;
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	j = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = (*stash)[j];
		j++;
	}
	line[j] = '\0';
	rest = ft_strdup(*stash + i);
	free(*stash);
	*stash = rest;
	return (line);
}

void	ft_switchup(char **stash, char **buffer)
{
	char	*tmp;

	tmp = ft_strdup(*stash);
	free(*stash);
	*stash = ft_strjoin(tmp, *buffer);
	free(tmp);
	free(*buffer);
}

int	tchek(int fd, char **stash)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(*stash);
		*stash = NULL;
		return (0);
	}
	return (1);
}
