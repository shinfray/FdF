/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/30 16:18:40 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_check_mouse_click(int button, int x, int y, void *param)
{
	(void)param;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_check_key_pressed(int keycode, void *param)
{
	(void)param;
	ft_printf("=====KEY PRESSED=====\nkeycode: %d\n", keycode);
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "FdF");
	mlx_mouse_hook(win_ptr, &ft_check_mouse_click, NULL);
	mlx_key_hook(win_ptr, &ft_check_key_pressed, NULL);
	mlx_loop(mlx_ptr);

	return (0);
}
