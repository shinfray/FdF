/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:38:56 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/28 22:33:34 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		ft_isometric(t_point s_point, t_isometric *s_isometric);
static void	ft_matrix_vector_mult(t_point *s_point, const double matrix[3][3]);

t_point	ft_isometric(t_point s_point, t_isometric *s_isometric)
{
	const double	alpha = s_isometric->angle_x;
	const double	beta = s_isometric->angle_y;
	const double	gamma = s_isometric->angle_z;
	const double	rotation_matrix[3][3] = \
		{{cos(beta) * cos(gamma), \
		sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma), \
		cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma)}, \
		{cos(beta) * sin(gamma), \
		sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma), \
		cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma)}, \
		{-sin(beta), sin(alpha) * cos(beta), cos(alpha) * cos(beta)}};

	s_point.x *= s_isometric->interspace;
	s_point.y *= s_isometric->interspace;
	s_point.z *= s_isometric->height;
	ft_matrix_vector_mult(&s_point, rotation_matrix);
	s_point.x += s_isometric->move_x;
	s_point.y += s_isometric->move_y;
	return (s_point);
}

static void	ft_matrix_vector_mult(t_point *s_point, const double matrix[3][3])
{
	const double	vector[3] = {s_point->x, s_point->y, s_point->z};
	double			result[3];
	int				i;
	int				j;

	i = -1;
	while (++i < 3)
	{
		result[i] = 0.0;
		j = -1;
		while (++j < 3)
			result[i] += matrix[i][j] * vector[j];
	}
	s_point->x = result[0] + 0.5;
	s_point->y = result[1] + 0.5;
	s_point->z = result[2] + 0.5;
}
