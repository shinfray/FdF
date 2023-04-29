#include "fdf.h"

int	ft_mouse_click(int button, int x, int y, t_data *param)
{
	(void)param;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_key_pressed(int keycode, t_data *param)
{
	if (keycode == ESCAPE_KEY)
		return (ft_close(param));
	ft_printf("=====KEY PRESSED=====\nkeycode: %d\n", keycode);
	return (0);
}

int	ft_close(t_data *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	free(param->mlx_ptr);
	exit(EXIT_SUCCESS);
}
