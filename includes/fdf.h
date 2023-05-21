/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:48:01 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/21 03:44:20 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

#define	WINDOW_NAME "FdF"
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define	ESCAPE_KEY 53
#define	UP_KEY 126
#define	DOWN_KEY 125
#define	LEFT_KEY 123
#define	RIGHT_KEY 124
#define N_KEY 45
#define R_KEY 15
#define H_KEY 4
#define Z_KEY 6

enum	e_events {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum	e_modes {
	NORMAL_MODE,
	HEIGHT_MODE,
	ZOOM_MODE,
	ROTATE_MODE,
};

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img_data;

typedef struct	s_mlx_data {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_data	s_img;
}				t_mlx_data;

// typedef struct	s_rect {
// 	int	x;
// 	int	y;
// 	int	width;
// 	int	height;
// 	int	color;
// }				t_rect;

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	int		colour;
}				t_point;

typedef struct	s_map_data {
	t_point		*map;
	int			total_row;
	int			total_column;
	ssize_t		total_size;
}				t_map_data;

typedef struct	s_file_data {
	int		fd;
	char	*path;
}				t_file_data;

typedef struct	s_isometric_data {
	int		origin_x;
	int		origin_y;
	double	angle;
	int		interspace;
	int		height;
	int		move_x;
	int		move_y;
}				t_isometric_data;

typedef struct	s_fdf {
	t_mlx_data			mlx_data;
	t_map_data			map_data;
	t_file_data			s_file_data;
	t_isometric_data	s_isometric_data;
	int					mode;
}				t_fdf;


/*	DRAWING FUNCTIONS	*/
void	ft_pixel_put_image(t_img_data *s_image, int x, int y, int colour);
// int		ft_draw_rectangle(t_img_data *s_img, t_rect s_rect);
// int		ft_draw_bordure(t_img_data *s_img, t_rect s_rect);
// void	ft_draw_circle(t_img_data *s_img, int xc, int yc, int x, int y);
// void	ft_circle_bres(t_img_data *s_img, int xc, int yc, int r);

/*	EVENTS FUNCTIONS	*/
//int	ft_mouse_click(int button, int x, int y, t_fdf *s_fdf);
int	ft_key_pressed(int keycode, t_fdf *s_fdf);
int	ft_close(t_fdf *s_fdf);
int	ft_hold_key(int keycode, t_fdf *s_fdf);
void	ft_move(t_fdf *s_fdf, int keycode);
void	ft_height(t_fdf *s_fdf, int keycode);
void	ft_zoom(t_fdf *s_fdf, int keycode);
void	ft_rotate(t_fdf *s_fdf, int keycode);


/*	BRESENHAM'S FUNCTIONS	*/
void	ft_draw_line(t_img_data *s_img, t_point start, t_point end);

/*	PARSE FUNCTIONS	*/
void	ft_parse_map(t_fdf *s_fdf);

/*	ISOMETRICS FUNCTIONS	*/
void	ft_print_map(t_fdf *s_fdf);
double	ft_rad(int degree);

void	ft_print_help(t_fdf *s_fdf);

#endif
