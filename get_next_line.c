/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:47:06 by mgessa            #+#    #+#             */
/*   Updated: 2018/11/17 00:18:10 by mgessa           ###   ########.fr       */
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
	if (!(new = (char*)malloc(sizeof(char*) * (i + j + 1))))
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

int		fill_next_line(char *flow, char **line)
{
	int		i;
	int		size_flow;

	printf("Flow char: %s\n", flow);
	i = 0;
	size_flow = ft_strlen(flow);
	while (flow[i] != '\n' && flow[i] != '\0')
		i++;
	if (!(line[0] = ft_strnew(i)))
		return (-42);
	ft_strncpy(line[0], flow, i);
	ft_strncpy(flow, flow + i + 1, size_flow);
	flow[size_flow] = '\0';
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int     		ret;
	static char    	over[BUF_SIZE + 1] = "salut\nhello\napl\nuhuhu";
	char			buf[BUF_SIZE + 1];
	int				passFirst;

	passFirst = 0;
	if (ft_strlen(over) > 0)
		passFirst = fill_next_line(over, line);
	if (passFirst == -42)
		return (-1);
	ret = 0;
	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		buf[ret] = '\0';
		if (passFirst == 1)
		{
			if (!(line[0] = ft_realloc(line[0], buf)))
				return (-1);
			passFirst = 0;
		}
	}
	return (0);
}
