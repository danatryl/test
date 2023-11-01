#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*replica;

	len = ft_strlen((char *)s) + 1;
	replica = (char *) malloc(len);
	i = 0;
	if (replica != NULL)
	{
		while (s[i] != '\0')
		{
			replica[i] = s[i];
			i++;
		}
		replica[i] = '\0';
	}
	return (replica);
}

char	*ft_strjoin(char *buffer, char *content)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!buffer)
		return (ft_strdup(content));
	if (!content)
		return (ft_strdup(buffer));
	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(buffer)
				+ ft_strlen(content)) + 1);
	if (!result)
		return (NULL);
	while (buffer && buffer[i] != '\0')
	{
		result[i] = buffer[i];
		i++;
	}
	while (content && content[j] != '\0')
		result[i++] = content[j++];
	result[i] = '\0';
	free(buffer);
	return (result);
}
