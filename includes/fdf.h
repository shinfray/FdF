/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:48:01 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/06 12:04:40 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define	ESCAPE_KEY 53

enum	e_events{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img_data;

typedef struct	s_data {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_data	s_img;
}				t_data;

typedef struct	s_rect {
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}				t_rect;

typedef struct s_coordinates {
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	color;
}				t_coordinates;

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	int		color;
	int		last_point;
}				t_point;


typedef struct	s_map_data {
	t_point	*map;
	int		total_row;
	int		total_column;
}				t_map_data;

/*	DRAWING FUNCTIONS	*/
void	ft_pixel_put_image(t_img_data *s_image, int x, int y, int color);
int		ft_draw_rectangle(t_img_data *s_img, t_rect s_rect);
int		ft_draw_bordure(t_img_data *s_img, t_rect s_rect);
void	ft_draw_circle(t_img_data *s_img, int xc, int yc, int x, int y);
void	ft_circle_bres(t_img_data *s_img, int xc, int yc, int r);

/*	EVENTS FUNCTIONS	*/
int	ft_mouse_click(int button, int x, int y, t_data *param);
int	ft_key_pressed(int keycode, t_data *param);
int	ft_close(t_data *param);


/*	BRESENHAM'S FUNCTIONS	*/
void	ft_draw_line(t_img_data *s_img, t_coordinates coordinates);

/*	PARSE FUNCTIONS	*/
void	ft_parse_map(char *file, t_map_data *map_data);

/*	ISOMETRICS FUNCTIONS	*/
void	ft_print_map(t_map_data *map_data, t_img_data *s_img);

#endif
