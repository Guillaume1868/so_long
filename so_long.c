#include "so_long.h"

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(&mlx_ptr, 1920, 1080, "okau");
	int i = 1;
	while (++i< 100)
		mlx_pixel_put(mlx_ptr,win_ptr,i,10,0x00ff0000);
	mlx_loop(mlx_ptr);
}
