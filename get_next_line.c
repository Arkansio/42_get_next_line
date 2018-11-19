/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:47:06 by mgessa            #+#    #+#             */
/*   Updated: 2018/11/19 14:22:57 by mgessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_getline(char **line, char *str, char *over)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(line[0] = ft_strsub(str, 0, i)))
		return (-1);
	ft_memcpy(over, str + i + 1, ft_strlen(str + i));
	free(str);
	return (1);
}

char	*str_realloc(char *str, char *buf)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(str, buf)))
		return (NULL);
	free(str);
	return (tmp);
}

char	*read_gnl(const int fd, char *str)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (ret == -1)
			return (NULL);
		if (!(str = str_realloc(str, buf)))
			return (NULL);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret == -1)
		return (NULL);
	return (str);
}

char	*ft_check(const int fd, char **line)
{
	char	*str;

	if (fd < 0 || !line)
		return (NULL);
	if (!(str = ft_strnew(1)))
		return (NULL);
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	char			*str;
	static char		over[BUFF_SIZE + 1];

	if (!(str = ft_check(fd, line)))
		return (-1);
	if (ft_strlen(over) > 0)
	{
		if (!(str = str_realloc(str, over)))
			return (-1);
		over[0] = '\0';
		if (ft_strchr(str, '\n'))
		{
			if (ft_getline(line, str, over) == -1)
				return (-1);
			return (1);
		}
	}
	if (!(str = read_gnl(fd, str)))
		return (-1);
	if (ft_strlen(str) <= 0)
	{
		free(str);
		line[0] = NULL;
		return (0);
	}
	return (ft_getline(line, str, over));
}
