/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/27 14:37:44 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "includes/libft.h"

int		get_next_line(const int fd, char **line)
{
	int		i;
	int		j;
	int		line_ct;
	char	*buff;
	static	char stock[BUFF_SIZE];
	char	*temp;
	char	*add;

	i = 0;
	j = 0;
	line_ct = 0;
	while (i < BUFF_SIZE && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
	{
		if (!(*line = (char *)malloc(i + 1)))
			return (-1);
		*line = ft_strncpy(*line, stock, i);
		while (i + 1 < BUFF_SIZE)
			stock[j++] = stock[i++ + 1];
		return (1);
	}
	line_ct = i;
	if (!(temp = (char *)malloc(line_ct)))
		return (-1);
	temp = strncpy(temp, (const char *)stock, i);
	i = 0;
	j = 0;
	while (1)
	{
		if (!(buff = (char *)malloc(BUFF_SIZE)))
			return (-1);
		i = read(fd, buff, BUFF_SIZE);
		if ( i == -1)
			return (-1);
		if (!i)
			return (0);
		while (j < BUFF_SIZE && buff[j] != '\n')
			j++;
		if (buff[j] != '\n')
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			add = strcpy (add, temp);
			add = strncat(add, (const char *)buff, BUFF_SIZE);
			free(temp);
			free(buff);
			temp = add;
		}
		else
		{
			if (!(*line = (char *)malloc(line_ct + j + 1)))
				return (-1);
			*line = strcpy(*line, temp);
			*line = strncat(*line, (const char *)buff, j);
			free(temp);
			bzero(stock, BUFF_SIZE);
			temp = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 2), BUFF_SIZE - j - 1);
			free (temp);
			return (1);
		}
	}
}
/*
int main()
{
	char *line;
	get_next_line(0, &line);
}*/
