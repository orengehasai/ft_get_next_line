/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takenakatakeshiichirouta <takenakatakes    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 03:31:51 by takenakatak       #+#    #+#             */
/*   Updated: 2025/05/22 01:17:55 by takenakatak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_consisted_n(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

void	*concat(char *str1, char *str2, ssize_t newlen)
{
	char	*new;
	char	*start;
	char	*tmp;

	new = malloc(sizeof(char) * (newlen + 1));
	if (!new || !newlen)
	{
		if (new)
			free(new);
		if (str1)
			free(str1);
		return (NULL);
	}
	start = new;
	tmp = str1;
	while (str1 && *str1 && newlen--)
		*new++ = *str1++;
	while (str2 && newlen--)
		*new++ = *str2++;
	*new = '\0';
	if (tmp)
		free(tmp);
	return ((void *)start);
}

char	*fnc(ssize_t len, char *buf, ssize_t end, void **content)
{
	char		*res;
	char		*tmp;
	ssize_t		buf_len;

	if (buf)
	{
		buf_len = str_len(buf, 1);
		res = concat(*content, buf, len);
		if (end != buf_len + 1 && res)
			*content = concat(NULL, &buf[buf_len + 1], end - (buf_len + 1));
	}
	else
	{
		tmp = *content;
		res = concat(NULL, *content, len);
		if (res)
		{
			buf_len = str_len(*content, 0) - len;
			*content = concat(NULL, &((char *)*content)[len], buf_len);
		}
		free(tmp);
	}
	if (!res || end == buf_len + 1)
		*content = NULL;
	return (res);
}

char	*read_line(t_list *lst, ssize_t len)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		end;
	char		*res;

	while (1)
	{
		end = read(lst->fd, buf, BUFFER_SIZE);
		if (end == -1)
			return (free(lst->content), lst->content = NULL, NULL);
		else if (end == 0)
		{
			if (!lst->content)
				return (NULL);
			res = concat(lst->content, NULL, len);
			return (lst->content = NULL, res);
		}
		buf[end] = '\0';
		len += str_len(buf, 1);
		if (is_consisted_n(buf))
			return (fnc(++len, buf, end, &lst->content));
		lst->content = concat(lst->content, buf, len);
		if (!lst->content)
			return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	t_list			*lst;
	ssize_t			len;
	char			*res;

	len = 0;
	lst = lst_search(head, fd);
	if (!lst)
	{
		lst = lst_new(fd);
		if (!lst)
			return (NULL);
		lstadd_front(&head, lst);
	}
	if (lst->content)
	{
		len = str_len(lst->content, 0);
		if (is_consisted_n(lst->content))
		{
			res = fnc(str_len(lst->content, 1) + 1, NULL, 0, &lst->content);
			return (lst_free(res, lst, &head), res);
		}
	}
	return (res = read_line(lst, len), lst_free(res, lst, &head), res);
}

// # include <stdio.h>

// int main()
// {
// 	int fd1 = open("sample1",O_RDONLY);
// 	int fd2 = open("sample2",O_RDONLY);
// 	int fd3 = open("sample3",O_RDONLY);
// 	int fd4 = open("sample4",O_RDONLY);
// 	int fd5 = open("sample5",O_RDONLY);

// 	printf("%s",get_next_line(fd1));
// 	printf("%s",get_next_line(fd2));
// 	printf("%s",get_next_line(fd1));
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
