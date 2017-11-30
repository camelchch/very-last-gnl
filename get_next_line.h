/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:56:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/29 17:34:13 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFF_SIZE 15

int		get_next_line(const int fd, char **line);

typedef struct	stock_list
{
	int			fd;
	char		*stock;
	struct	stock_list		*next;
}				st_list;


#endif
