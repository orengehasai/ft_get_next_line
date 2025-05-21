/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takenakatakeshiichirouta <takenakatakes    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:16:24 by takenakatak       #+#    #+#             */
/*   Updated: 2025/05/22 01:11:40 by takenakatak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	int				fd;
	void			*content;
	struct s_list	*next;
	struct s_list	*back;
}	t_list;

t_list	*lst_search(t_list *lst, int fd);

void	lstadd_front(t_list **lst, t_list *new);

t_list	*lst_new(int fd);

void	lst_free(char *res, t_list *lst, t_list **head);

ssize_t	str_len(char *str);

ssize_t	nulllen(char *str);

int		is_consisted_n(char *str);

void	*concat(char *str1, char *str2, ssize_t newlen);

char	*fnc(ssize_t len, char *buf, ssize_t end, void **content);

char	*read_line(t_list *lst, ssize_t len);

char	*get_next_line(int fd);

#endif