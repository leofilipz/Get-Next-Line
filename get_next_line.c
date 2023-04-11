/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:06:01 by leborges          #+#    #+#             */
/*   Updated: 2022/11/28 13:19:54 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_whatsleft(char *stash)
{
	char	*whatsleft;
	size_t	jump;
	size_t	len;

	len = ft_strlen(stash, '\0');
	jump = ft_strlen(stash, '\n');
	if (stash[jump] == '\n')
		jump++;
	whatsleft = ft_strndup(stash + jump, len - jump + 1);
	if (!whatsleft)
		return (NULL);
	free (stash);
	return (whatsleft);
}

char	*get_line(char *stash)
{
	char	*line;
	size_t	len;

	len = ft_strlen(stash, '\n');
	if (stash[len] == '\n')
		len++;
	line = ft_strndup(stash, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*store_pieces(int fd, char *stash)
{
	char	*piece;
	ssize_t	bytes;

	bytes = 1;
	piece = (char *)malloc(BUFFER_SIZE + 1);
	if (!piece)
		return (NULL);
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, piece, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free(piece);
			return (NULL);
		}
		piece[bytes] = '\0';
		stash = ft_strjoin(stash, piece);
	}
	free(piece);
	if (ft_strlen(stash, '\0') > 0)
		return (stash);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = store_pieces(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = get_whatsleft(stash);
	if (!stash[0])
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}
