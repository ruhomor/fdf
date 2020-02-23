/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:25:55 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_length(t_file *files)
{
	char	*tmp;
	int		i;

	if (!(tmp = ft_strchr(files->rest, '\n')))
		i = ft_strlen(files->rest);
	else
		i = tmp - files->rest;
	return (i);
}

int		ft_readline(const int fd, char **line, t_file *files)
{
	int		check;
	char	*str;

	str = files->rest;
	files->rest = ft_strsub(files->rest, ft_length(files) + 1,
			ft_strlen(files->rest));
	ft_strclr(str);
	free(str);
	while ((check = read(fd, *line, BUFF_SIZE)) && (check != -1))
	{
		(*line)[check] = '\0';
		str = files->rest;
		files->rest = ft_strjoin(files->rest, *line);
		ft_strclr(str);
		free(str);
		if (ft_strchr(*line, '\n'))
			break ;
	}
	return (check);
}

t_file	*ft_newfile(t_file *files, const int fd)
{
	t_file *newfile;

	newfile = (t_file *)malloc(sizeof(t_file));
	newfile->fd = fd;
	newfile->rest = ft_strnew(0);
	newfile->next = NULL;
	newfile->prev = files;
	newfile->base = (files->base + 1);
	files = newfile;
	return (files);
}

t_file	*ft_filebase(t_file *files)
{
	t_file	*filebase;

	if (!files)
	{
		filebase = (t_file *)malloc(sizeof(t_file));
		filebase->next = NULL;
		filebase->prev = NULL;
		filebase->base = 0;
		filebase->rest = ft_strnew(0);
		filebase->fd = -1;
		files = filebase;
	}
	else
	{
		while (files->base != 0)
			files = files->prev;
	}
	return (files);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*files;
	int				check;
	char			*str;

	files = ft_filebase(files);
	if (!line || !(*line = ft_strnew(BUFF_SIZE)) ||
		(fd < 0) || (fd > FD_MAX) || (BUFF_SIZE < 1))
		return (-1);
	while (files->next)
	{
		if (files->next->fd == fd)
			break ;
		files = files->next;
	}
	if (!files->next)
		files->next = ft_newfile(files, fd);
	files = files->next;
	if ((check = ft_readline(fd, line, files)) == -1)
		return (-1);
	str = *line;
	*line = ft_strsub(files->rest, 0, ft_length(files));
	ft_strclr(str);
	if (!((files->rest)[0]) && !(check))
		return (0);
	return (1);
}
