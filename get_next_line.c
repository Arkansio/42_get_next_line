/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:47:06 by mgessa            #+#    #+#             */
/*   Updated: 2018/11/18 19:49:01 by mgessa           ###   ########.fr       */
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
	ft_memcpy(over, str + i + 1, ft_strlen(str + i));
	free(str);
	return (ft_strlen(str + i + 1));
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

	if (fd < 0 || !line)
		return (-1);
	if (!(str = ft_strnew(0)))
		return (-1);
	if (ft_strlen(over) > 0)
	{
		str = str_realloc(str, over);
		over[0] = '\0';
		if (ft_strchr(str, '\n'))
		{
//			printf("value over: %s\n", over);
			ft_getline(line, str, over);
			return (1);
//			printf("real Value %s: \n", over);
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
	if (ft_strlen(str) <= 0)
		return (0);
	if (ft_getline(line, str, over) == -1)
		return (-1);
	else
		return (1);
	return (0);
}
