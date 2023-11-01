/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcsoma <dcsoma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:21:12 by dcsoma            #+#    #+#             */
/*   Updated: 2023/11/01 19:47:16 by dcsoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_end(char *str, size_t i)
{
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*read_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	i = line_end(str, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*remaining(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str[i] == '\0')
		return (free(str), NULL);
	i = line_end(str, i);
	new_str = (char *)malloc((ft_strlen(str) - i + 1));
	if (!new_str)
		return (free(new_str), free(str), NULL);
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	if (!new_str[0])
		return (free(str), free(new_str), NULL);
	free(str);
	return (new_str);
}

char	*clean_up(char *buff1, char *buff2)
{
	free(buff1);
	free(buff2);
	buff1 = NULL;
	buff2 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*content;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	content = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!content)
		return (NULL);
	bytes = 1;
	while (!(ft_strchr(buffer, '\n')) && bytes > 0)
	{
		bytes = read(fd, content, BUFFER_SIZE);
		if (bytes == -1)
		{
			buffer = clean_up(content, buffer);
			return (NULL);
		}
		content[bytes] = '\0';
		buffer = ft_strjoin(buffer, content);
		if (!buffer)
			return (free(content), NULL);
		
	}
	free(content);
	content = read_line(buffer);
	buffer = remaining(buffer);
	return (content);
}

int main(int argc, char **argv)
{
	while (argc)
		break ;
    int fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        perror("Failed to open file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line); // Free the memory allocated by get_next_line
    }

    close(fd);
    return 0;
}
