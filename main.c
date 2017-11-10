#include "get_next_line.h"

static int  ft_str_len_tonl(char *str)
{
    int     len;

    len = 0;
    if (!str)
        return (0);
    while (str[len])
    {
        if (str[len] == '\n' || str[len] == '\0')
            break ;
        len++;
    }
    return (len);
}

static char	*ft_write_line(char **str, int i, int j)
{
    char	*res;
	char	*dst;
	int		len;
	char	*test;

	test = *str;
    res = (char *)malloc(sizeof(char) * (ft_str_len_tonl(*str) + 1));
	while (test[i] != '\n')
	{
        res[i] = test[i];
		i++;
	}
	res[i] = '\0';
	len = ft_strlen(*str) - ft_str_len_tonl(*str);
	dst = (char *)malloc(sizeof(char) * len);
	i++;
	while (test[i++])
		dst[j++] = test[i];
	dst[j] = '\0';
	free(str);
	*str = dst;
    return (res);
}

int 	get_next_line(const int fd, char **line)
{
	static char	*str;
	char		buff[BUFF_SIZE + 1];
	int			ret;

//	if (!str)
//		str = ft_first_line(fd, line, str);
	if (fd < 0)
		return (-1);
	if (line)
		free(line);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!str)
			str = ft_strdup(buff);
		else
			str = ft_strjoin(str, buff);
		if (ft_strrchr(str, '\n'))
		{
			*line = ft_write_line(&str, 0, 0);
			break ;
		}
	}
	if (!str)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	printf("wdfgwrgf\n");
	while ((get_next_line(fd, &line)) > 0)
		printf("%s\n", line);
	return 0;
}