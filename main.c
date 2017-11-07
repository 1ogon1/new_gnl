#include "get_next_line.h"

static void	ft_write_line(char *str, char **line, int i)
{
	while (str[i] != '\n' || str[i] != '\0')
	{
		*line[i] = str[i];
		i++;
	}
}

static void	ft_first_line(const int fd, char **line, char **str)
{
	int 	ret;
	char	buff[BUFF_SIZE + 1];

	if (fd < 0)
		return ;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		*str = ft_strdup(buff);
		if (ft_strrchr(*str, '\n'))
			ft_write_line(*str, line, 0);
		free(buff);
	}
}

int 	get_next_line(const int fd, char **line)
{
	static char	*str;
	char		buff[BUFF_SIZE + 1];
	int			res;

	if (!str)
		ft_first_line(fd, line, &str);
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