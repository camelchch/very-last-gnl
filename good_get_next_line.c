
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

char	*ft_strcdup(char *s, char c)
{
	char *copy;
	int	 i;

	i = 0;
	if (!(copy = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
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
	new->stock = NULL;
	new->next = NULL;
	if (!list)
		return (new);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (list);
}

/*
static st_list		*find(st_list *list, int fd)
{
	st_list		*temp;
	st_list		*new;

	if (list)
	{
	while (fd != list->fd && list->next)
		list = list->next;
	if (fd != list->fd)
	{
		new = (st_list *)malloc(sizeof(*new));
		new->fd = fd;
		new->stock = ft_strdup("");
		list->next = new;
		list = list->next;
	}
	return (list);
	}
	if (!(new = (st_list *)ft_memalloc(sizeof(st_list))))
		return (0);
	new->fd = fd;
	new->stock = ft_strdup("");
	new->next = NULL;
		return (new);
}
*/

int		get_next_line(const int fd, char **line)
{
	static	st_list		*list = NULL;
	char		buff[BUFF_SIZE + 1];
	int			ret;
	st_list		*begin;
	char		*temp;

	if(fd < 0 || BUFF_SIZE < 1 || read(fd, "", 0))
		return (-1);
	if (!list)
		list = add(list, fd);
	begin = list;
	while (fd != list->fd && list->next)
		list = list->next;
	if (fd != list->fd)
	{
		list = add(list, fd);
		list = list->next;
	}
	if (!(list->stock))
		list->stock = ft_strdup("");
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
/*
#include <fcntl.h>

int main(int ac, char **av)
{
	char *line;
	int		fd1;
	int		fd2;
	(void) ac++;
	(void) av;

	fd1 = open("1file", O_RDONLY);
	fd2 = open("2file", O_RDONLY);
	while (get_next_line(fd1,&line))
	{
		ft_putendl(line);
		free(line);
		line = NULL;
	}
	get_next_line(fd1 ,&line);
	//ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd2 ,&line);
	//ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd1 ,&line);
	//ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd2 ,&line);
//	ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd1 ,&line);
//	ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd2 ,&line);
//	ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd1 ,&line);
//	ft_putendl("main here");
		ft_putendl(line);
	get_next_line(fd2 ,&line);
//	ft_putendl("main here");
		ft_putendl(line);
	return (0);
}
*/
