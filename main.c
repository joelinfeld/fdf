#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	//void *mlx;
	//void *win;
	int		fd;
	char	*thestuff;

	fd = open("42.fdf", O_RDONLY);
	while (get_next_line(fd, &thestuff))
	{
		printf("%s\n", thestuff);
	}
	//mlx = mlx_init();
	//win = mlx_new_window(mlx, 400, 400, "mlx 42");
	//mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
	//mlx_loop(mlx);
}
