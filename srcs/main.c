/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/31 13:09:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_check_mouse_click(int button, int x, int y, void *param)
{
	(void)param;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_check_key_pressed(int keycode, t_data *param)
{
	(void)param;
	ft_printf("=====KEY PRESSED=====\nkeycode: %d\n", keycode);
	return (0);
}

int	ft_close(t_data *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	free(param->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(void)
{
	t_window_data	window;

	window.mlx_ptr = mlx_init();
	if (window.mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	window.win_ptr = mlx_new_window(window.mlx_ptr, 1920, 1080, "FdF");
	if (window.win_ptr == NULL)
	{
		free(window.win_ptr);
		exit(EXIT_FAILURE);
	}
	mlx_mouse_hook(window.win_ptr, &ft_check_mouse_click, NULL);
	mlx_key_hook(window.win_ptr, &ft_check_key_pressed, &window);
	mlx_hook(window.win_ptr, ON_DESTROY, 0, &ft_close, &window);
	mlx_loop(window.mlx_ptr);

	return (0);
}
