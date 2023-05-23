/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:48:01 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 16:42:30 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

#define	WINDOW_NAME "FdF"
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

#define INTERSPACE 20

#define	ESCAPE_KEY 53

#define	UP_KEY 126
#define	DOWN_KEY 125
#define	LEFT_KEY 123
#define	RIGHT_KEY 124

#define	UP_SCROLL 4
#define	DOWN_SCROLL 5
#define	LEFT_CLICK 1

#define H_KEY 4
#define M_KEY 46
#define N_KEY 45
#define R_KEY 15
#define X_KEY 7
#define Z_KEY 6

#define WHITE 0xFFFFFF
#define GREEN 0x00FF00
#define DEFAULT_COLOUR GREEN

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

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	int		colour;
}				t_point;

typedef struct	s_line {
	t_point	start;
	t_point	end;
}				t_line;

typedef struct	s_isometric_data {
	int		origin_x;
	int		origin_y;
	double	angle;
	double		interspace;
	double		height;
	int		move_x;
	int		move_y;
}				t_isometric_data;

typedef struct	s_map_data {
	t_point		*s_map;
	int			total_row;
	int			total_column;
	ssize_t		total_size;
}				t_map_data;

typedef struct	s_file_data {
	int		fd;
	char	*path;
}				t_file_data;

typedef struct s_drag_drop_data {
	int	click_pos_x;
	int	click_pos_y;
	int	previous_pos_x;
	int	previous_pos_y;
}				t_drag_drop_data;

typedef struct	s_fdf {
	t_mlx_data			s_mlx_data;
	t_map_data			s_map_data;
	t_file_data			s_file_data;
	t_isometric_data	s_isometric_data;
	t_drag_drop_data	s_drag_drop_data;
	int					mode;
	bool				toggle_menu;
	bool				drag_drop_status;
	bool				exit_status;
}				t_fdf;

/*	MAIN FUNCTIONS	*/
void	ft_set_fdf_data(t_fdf *s_fdf, char *path);

/*	ISOMETRICS FUNCTIONS	*/
void	ft_print_map(t_fdf *s_fdf);
double	ft_rad(int degree);

/*	BRESENHAM FUNCTIONS	*/
void	ft_draw_line(t_img_data *s_img, t_line *s_line);

/*	INTERFACE FUNCTIONS	*/
void	ft_print_help_menu(t_fdf *s_fdf);
void	ft_print_actual_mode(t_fdf *s_fdf);

/*	ACTIONS FUNCTIONS	*/
void	ft_move(t_fdf *s_fdf, int keycode);
void	ft_height(t_fdf *s_fdf, int keycode);
void	ft_zoom(t_fdf *s_fdf, int keycode);
void	ft_rotate(t_fdf *s_fdf, int keycode);





/*	EVENTS FUNCTIONS	*/
int	ft_key_pressed(int keycode, t_fdf *s_fdf);
int	ft_click(int button, int x, int y, t_fdf *s_fdf);
int	ft_close(t_fdf *s_fdf);
int	ft_hold_key(int keycode, t_fdf *s_fdf);
int	ft_unclick(int button, int x, int y, t_fdf *s_fdf);
int	ft_move_mouse(int x, int y, t_fdf *s_fdf);

/*	PARSE FUNCTIONS	*/
void	ft_parse_map(t_fdf *s_fdf);

void	ft_refresh_interface(t_fdf *s_fdf);

void	ft_reprint_image(t_fdf *s_fdf);

#endif
