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

static char	*ft_write_line(char *str, int i)
{
    char    *res;

    res = (char *)malloc(sizeof(char) * ft_str_len_tonl(str) + 1);
	while (str[i] != '\n')
	{
        res[i] = str[i];
		i++;
	}
    res[i] = '\0';
    return (res);
}

static char *ft_first_line(const int fd, char **line, char *str)
{
	int 	ret;
	char	buff[BUFF_SIZE + 1];

	if (fd < 0)
		return (0);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!str)
			str = ft_strdup(buff);
		else
			str = ft_strjoin(str, buff);
		if (ft_strrchr(str, '\n'))
        {
			*line = ft_write_line(str, 0);
            break ;
        }
	}
    return (str);
}

int 	get_next_line(const int fd, char **line)
{
	static char	*str;
	char		buff[BUFF_SIZE + 1];
	int			res;

	if (!str)
		str = ft_first_line(fd, line, str);
	if (fd < 0)
		return (-1);
	if (!str)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	while ((get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		break ;
	}
	return 0;
}