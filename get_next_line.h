/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takenakatakeshiichirouta <takenakatakes    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:26:18 by takenakatak       #+#    #+#             */
/*   Updated: 2025/06/07 16:08:20 by takenakatak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd_data
{
	int					fd;
	char				*remainder;
	struct s_fd_data	*next;
}	t_fd_data;

char		*get_next_line(int fd);

size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin_and_free(char *s1, char *s2);
void		free_and_null(char **ptr);
void		free_node(t_fd_data **head, int fd);

#endif