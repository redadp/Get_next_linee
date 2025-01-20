/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboukhra <rboukhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:23:58 by rboukhra          #+#    #+#             */
/*   Updated: 2025/01/03 21:35:45 by rboukhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

char	*get_backup(int fd, char *backup)
{
	char	*mini_buff;
	ssize_t	l;

	l = 1;
	mini_buff = (char *)malloc((size_t)BUFFER_SIZE + 1 * sizeof(char));
	if (!mini_buff)
		return (NULL);
	while (l > 0 && !ft_strchr(backup, '\n'))
	{
		l = read(fd, mini_buff, BUFFER_SIZE);
		if (l == -1)
		{
			free(mini_buff);
			free(backup);
			return (NULL);
		}
		mini_buff[l] = '\0';
		backup = ft_strjoin(backup, mini_buff);
	}
	free(mini_buff);
	return (backup);
}

char	*get_line_lina(char *backup)
{
	int		i;
	int		j;
	char	*res_line;

	i = 0;
	j = 0;
	if (!*backup)
		return (NULL);
	while (backup[i] != '\n' && backup[i])
		i++;
	if (backup[i] == '\n')
		i++;
	res_line = (char *)malloc(i + 1 * sizeof(char));
	if (!res_line)
		return (NULL);
	while (j < i)
	{
		res_line[j] = backup[j];
		j++;
	}
	res_line[j] = '\0';
	return (res_line);
}

char	*update_backup(char *backup)
{
	char	*new_backup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (backup[i] != '\n' && backup[i])
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = (char *)malloc(((ft_strlen(backup) - i) + 1) * sizeof(char));
	if (!new_backup)
		return (NULL);
	i++;
	while (backup[i] != '\0')
		new_backup[j++] = backup[i++];
	new_backup[j] = '\0';
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	backup = get_backup(fd, backup);
	if (!backup)
		return (NULL);
	line = get_line_lina(backup);
	if (!backup)
		return (NULL);
	backup = update_backup(backup);
	return (line);
}
