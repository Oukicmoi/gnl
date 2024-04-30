/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:00:15 by gtraiman          #+#    #+#             */
/*   Updated: 2024/04/30 20:30:49 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include "get_next_line.h"

char	*ft_read(int fd, char *stash)
{
	int		n;
	char	*buff;

	n = 1;
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(stash), NULL);
	while (n != 0 && !ft_strchr(stash, '\n'))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
			return (free(buff), NULL);
		buff[n] = 0;
		stash = ft_strjoin(stash, buff);
		if (!stash)
			return (free(buff), NULL);
	}
	free(buff);
	return (stash);
}

char	*ft_stline(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*ft_new_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	new_stash = (char *)malloc(sizeof(char) * ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = 0;
	if (new_stash[0] == 0)
		return (free(stash), free(new_stash), NULL);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	stash[fd] = ft_read(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_stline(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	stash[fd] = ft_new_stash(stash[fd]);
	if (line[0] == 0)
		return (free(stash[fd]), free(line), NULL);
	return (line);
}
// int main(void)
// {
//     int fd[2];
//     char *line;
//     const char *filename = "text.txt";
//     const char *filename2 = "text2.txt";

//     fd[0] = open(filename, O_RDONLY);
//     fd[1] = open(filename2, O_RDONLY);
//     while (1)
//     {
// 	line = get_next_line(fd[0]);
// 	if (line != NULL)
// 	{ 
//         	printf("%s", line);
//         	free(line);
// 	}
// 	line = get_next_line(fd[1]);
// 	if (line == NULL)
// 		break;
// 	printf("%s", line);
// 	free(line);
//     }
// }