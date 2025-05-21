/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takenakatakeshiichirouta <takenakatakes    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:16:33 by takenakatak       #+#    #+#             */
/*   Updated: 2025/05/22 01:17:27 by takenakatak      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lst_search(t_list *lst, int fd)
{
	if (!lst)
		return (lst);
	while (lst && lst->fd != fd)
		lst = lst->next;
	return (lst);
}

void	lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		(*lst)->back = new;
		*lst = new;
	}
}

t_list	*lst_new(int fd)
{
	t_list	*res;

	if (fd < 0)
		return (NULL);
	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->fd = fd;
	res->content = NULL;
	res->back = NULL;
	res->next = NULL;
	return (res);
}

void	lst_free(char *res, t_list *lst, t_list **head)
{
	if (!res && lst)
	{
		if (lst->back)
		{
			lst->back->next = lst->next;
		}
		else
		{
			*head = lst->next;
		}
		if (lst->next)
			lst->next->back = lst->back;
		free(lst);
	}
}

ssize_t	str_len(char *str, int v)
{
	int	cnt;

	cnt = 0;
	if (v == 0)
	{
		while (str[cnt] != '\0')
			cnt++;
	}
	else
	{
		while (str[cnt] != '\n' && str[cnt] != '\0')
			cnt++;
	}
	return (cnt);
}
