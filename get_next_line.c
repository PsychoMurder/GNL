#include "get_next_line.h"

static char
*ft_read_file(int fd, char **fdb)
{
	char	*buffer;
	char	*temp;
	int		rbyte;

	buffer = (char *)malloc(sizeof(buffer) * (BUFF_SIZE + 1));
	if (fd < 0 || BUFF_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (*fdb == NULL)
		*fdb = ft_strdup("");
	while (!(ft_strchr(*fdb, '\n')))
	{
		if ((rbyte = read(fd, buffer, BUFF_SIZE)) < 0)
			return (0);
		buffer[rbyte] = '\0';
		temp = ft_strjoin(*fdb, buffer);
		free(*fdb);
		*fdb = temp;
		if (rbyte == 0)
			break ;
	}
	free(buffer);
	return (*fdb);
}

int
get_next_line(int fd, char **line)
{
	static char		*fdbuf[256];
	char			*eos;
	char			*leakfd;
	char			*leakline;

	if (!(fdbuf[fd] = ft_read_file(fd, &fdbuf[fd])) || !line)
		return (-1);
	if ((eos = ft_strchr(fdbuf[fd], '\n')))
	{
		leakfd = fdbuf[fd];
		leakline = *line;
		*line = ft_substr(fdbuf[fd], 0, eos - fdbuf[fd]);
		free(leakline);
		fdbuf[fd] = ft_strdup(fdbuf[fd] + (eos - fdbuf[fd]) + 1);
		free(leakfd);
		return (1);
	}
	else
	{
		leakline = *line;
		*line = ft_strdup(fdbuf[fd]);
		free(leakline);
		free(fdbuf[fd]);
		fdbuf[fd] = NULL;
		return (0);
	}
}