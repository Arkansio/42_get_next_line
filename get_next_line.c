/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:47:06 by mgessa            #+#    #+#             */
/*   Updated: 2018/11/18 19:03:10 by mgessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"	

int		ft_getline(char **line, char *str, char *over)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if(!(line[0] = ft_strsub(str, 0, i)))
		return (-1);
	ft_memmove(over, str + i + 1, ft_strlen(str) - i);
	over[i] = '\0';
	free(str);
	return (0);
}

char	*str_realloc(char *str, char *buf)
{
	char	*tmp;

	if(!(tmp = ft_strjoin(str, buf)))
		return (NULL);
	free(str);
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*str;
	static char		over[BUFF_SIZE + 1];

	if (!(str = ft_strnew(0)))
		return (-1);
	if (ft_strlen(over) > 0)
	{
		str = ft_strjoin(str, over);
		over[0] = '\0';
		if (ft_strchr(str, '\n'))
		{
			if (ft_getline(line, str, over) == -1)
				return (-1);
			else
				return (1);
		}
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if(!(str = str_realloc(str, buf)))
			return (-1);
		if (ft_strchr(str, '\n'))
			break;
	}
	if (ft_getline(line, str, over) == -1)
		return (-1);
	else
		return (1);
	return (0);
}
