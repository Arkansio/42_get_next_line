/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:47:06 by mgessa            #+#    #+#             */
/*   Updated: 2018/11/17 14:00:58 by mgessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"	

char    *ft_realloc(char *str, char *buf)
{
	int     j;
	int     i;
	char    *new;

	i = ft_strlen(str);
	j = ft_strlen(buf);
	new = NULL;
	if (!(new = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	j = 0;
	while (buf[j] != '\0')
	{
		new[i + j] = buf[j];
		j++;
	}
	new[i + j] = '\0';
	if (str != NULL)
		free(str);
	return (new);
}

int		get_malloc_line(char **line, char *pnt)
{
	int			i;
	int			sz;

	sz = 0;
	i = 0;
	while (pnt[sz] != '\0' && pnt[sz] != '\n')
		sz++;
	if (!((*line) = ft_strnew(sz)))
		return (-1);
	while (i < sz)
	{
		(*line)[i] = pnt[i];
		i++;
	}
	(*line)[i] = '\0';
	return (sz);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static char		*str;
	static char		*pnt;
	int				sz_return;

	if ((fd < 0 || !line) || (buf[0] == '\0' && (!(str = ft_strnew(0)))))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if(!(str = ft_realloc(str, buf)))
			return (-1);
		pnt = str;
	}
	if (pnt >= str + ft_strlen(str))
	{
		return (0);
	}
	if((sz_return = get_malloc_line(line, pnt)) == -1)
		return (-1);
	pnt = pnt + sz_return + 1;
	return (1);
}
