
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/29 19:11:44 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

static	char	*ft_strcdup(char *s, char c)
{
	char	*copy;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(copy = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (*s && *s != c)
		copy[i++] = *s++;
	copy[i] = '\0';
	return (copy);
}

static st_list		*add(st_list *list, int fd)
{
	st_list		*temp;
	st_list		*new;

	if (!(new = (st_list *)ft_memalloc(sizeof(st_list))))
		return (0);
	new->fd = fd;
	new->stock = ft_strdup("");
	new->next = NULL;
	if (!list)
		return (new);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (list);
}

static	st_list		*find(st_list *list, int fd)
{
	char	*temp;

	if (!list)
		list = add(list, fd);
	while (fd != list->fd && list->next)
		list = list->next;
	if (fd != list->fd)
	{
		list = add(list, fd);
		list = list->next;
	}
	return (list);
}

int		get_next_line(const int fd, char **line)
{
	static	st_list		*list = NULL;
	char		buff[BUFF_SIZE + 1];
	st_list		*begin;
	char		*temp;
	int			ret;

	if (fd < 0 || BUFF_SIZE < 1 || read(fd, "", 0))
		return (-1);
	begin = list;
	list = find(list, fd);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		temp = list->stock;
		buff[ret] = '\0';
		list->stock = ft_strjoin(list->stock, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break;
	}
	if (!(*(list->stock)))
		return (0);
	if (ft_strchr(list->stock, '\n'))
	{
		temp = list->stock;
		*line = ft_strcdup(list->stock, '\n');
		list->stock = ft_strdup(ft_strchr(list->stock, '\n') + 1);
		free(temp);
	}
	else
	{
		*line = ft_strdup(list->stock);
		list->stock = "";
	}
	list = begin;
	return (1);
}
