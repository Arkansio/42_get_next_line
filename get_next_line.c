/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:47:06 by mgessa            #+#    #+#             */
/*   Updated: 2018/11/17 20:03:32 by mgessa           ###   ########.fr       */
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

int		get_next_malloc(char **line, char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if(!(line[0] = ft_strnew(i)))
		return (-1);
	ft_strncpy(line[0], str, i);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static char		*str;
	int				sz_return;

	if (fd == -1 || !line)
		return (-1);
	if (!str)
	{
		if (!(str = ft_strnew(0)))
			return (-1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if(!(str = ft_realloc(str, buf)))
			return (-1);
	}
	if (ft_strlen(str) > 0)
	{
		if ((sz_return = get_next_malloc(line, str)) == -1)
			return (-1);
		ft_memmove(str, str + sz_return + 1, ft_strlen(str) - sz_return);
		return (1);	
	}
	line[0] = NULL;
	return (0);
}
