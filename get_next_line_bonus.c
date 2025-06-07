/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takenakatakeshiichirouta <takenakatakes    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:27:47 by takenakatak       #+#    #+#             */
/*   Updated: 2025/06/07 16:11:18 by takenakatak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd_data	*get_node(t_fd_data **head, int fd)
{
	t_fd_data	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_fd_data));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->remainder = NULL;
	node->next = *head;
	*head = node;
	return (node);
}

static char	*extract_line(char **rem)
{
	char	*line;
	char	*next_rem_start;
	size_t	line_len;

	if (!*rem || !**rem)
		return (NULL);
	next_rem_start = ft_strchr(*rem, '\n');
	if (!next_rem_start)
		return (line = *rem, *rem = NULL, line);
	line_len = (next_rem_start - *rem) + 1;
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line[line_len] = '\0';
	while (line_len-- > 0)
		line[line_len] = (*rem)[line_len];
	next_rem_start = ft_strjoin_and_free(NULL, next_rem_start + 1);
	free(*rem);
	*rem = next_rem_start;
	if (*rem && !**rem)
		free_and_null(rem);
	return (line);
}

static int	read_into_remainder(int fd, char **remainder)
{
	char	*buf;
	ssize_t	bytes_read;

	if (ft_strchr(*remainder, '\n'))
		return (0);
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), -1);
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		*remainder = ft_strjoin_and_free(*remainder, buf);
		if (!*remainder)
			return (free(buf), -1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (free(buf), 0);
}

char	*get_next_line(int fd)
{
	static t_fd_data	*head;
	t_fd_data			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&head, fd);
	if (!node)
		return (NULL);
	if (read_into_remainder(fd, &node->remainder) < 0)
	{
		free_node(&head, fd);
		return (NULL);
	}
	line = extract_line(&node->remainder);
	if (!line)
	{
		free_node(&head, fd);
		return (NULL);
	}
	return (line);
}

// # include <stdio.h>
// # include <fcntl.h>

// int main()
// {
// 	int fd1 = open("sample1",O_RDONLY);
// 	int fd2 = open("sample2",O_RDONLY);
// 	int fd3 = open("sample3",O_RDONLY);
// 	int fd4 = open("sample4",O_RDONLY);
// 	int fd5 = open("sample5",O_RDONLY);

// 	printf("\033[0;32m%s",get_next_line(fd1));
// 	printf("%s",get_next_line(fd2));
// 	printf("\033[0;32m%s",get_next_line(fd1));
// 	printf("%s",get_next_line(fd1));
// 	printf("%s",get_next_line(fd1));
// 	printf("%s",get_next_line(fd2));
// 	printf("%s",get_next_line(fd3));
// 	printf("%s",get_next_line(fd3));
// 	printf("%s",get_next_line(fd4));
// 	printf("%s",get_next_line(fd2));
// 	printf("%s",get_next_line(fd5));
// 	printf("%s",get_next_line(fd4));
// 	return 0;
// }