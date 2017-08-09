#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

int	main()
{
	void *mlx;
	void *win;
	int		fd;
	int		height;
	int		width;
	int		len;
	char	*thestuff;
	char	**otherstuff;
	int		**matrix;
	int		i;
	int		j;
	int		k;
	int		first;
	
	first = 0;
	height = 11;
	width = 19;
	i = -1;
//	fd = open("42.fdf", O_RDONLY);
//	while (get_next_line(fd, &thestuff))
//		height++;
//	otherstuff = ft_strsplit(thestuff, ' ');
//	while (otherstuff[++i])
//		width++;
//  close(fd);
	fd = open("42.fdf", O_RDONLY);
	matrix = (int**)malloc(sizeof(int*) * height);
	i = -1;
	while (get_next_line(fd, &thestuff) > 0 && ++i < height)
	{
		write(1, "eatme\n", 6);
		len = ft_strlen(thestuff);
		matrix[i] = (int*)malloc(sizeof(int) * width);
		j = 0;
		k = -1;
		while(thestuff[++k])
		{
			if (!first)
			{
				matrix[i][j++] = ft_atoi(&thestuff[k]);
				first = 1;
			}
			if (thestuff[k] == ' ')
				matrix[i][j++] = ft_atoi(&thestuff[k]);
		}
	//	ft_strdel(&thestuff);
	}
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			printf("(%d, %d) = %d\n", j, i, matrix[i][j]); 
	}
	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
	mlx_loop(mlx);
}
