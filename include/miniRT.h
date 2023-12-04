/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:42:04 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 11:27:41 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42.h"
# define VALID_CHARS "+-., 0123456789\n"
# define MAX_LINES 1024
# define MAX_FIGURE 256
# define ERR_ARGC 0
# define ERR_FILE_FORMAT 1
# define ERR_NO_FILE 2
# define ERR_LINE_FORMAT 3

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_ambient
{
	double			ratio;
	t_vector		color;
}			t_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct s_light
{
	t_vector		position;
	double			ratio;
	t_vector		color;
}				t_light;

typedef struct s_sphere
{
	t_vector		position;
	double			diameter;
	t_vector		color;
}				t_sphere;

typedef struct s_plane
{
	t_vector		position;
	t_vector		orientation;
	t_vector		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector		position;
	t_vector		orientation;
	double			diameter;
	double			height;
	t_vector		color;
}				t_cylinder;

typedef struct s_data
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	spheres[MAX_FIGURE];
	t_plane		planes[MAX_FIGURE];
	t_cylinder	cylinders[MAX_FIGURE];
}				t_data;

int				mrt_parser(char *file, t_data *data);
int				mrt_check_argv(int argc, char **argv);
int				set_values(char *line, t_data *data);
int				check_line(char *line);
char			*skip_spaces(char *line);
char			*skip_double(char *line);
char			*skip_digits(char *line);
char			*skip_coord(char *line);
int				set_ambient(char *line, t_data *data);
int				set_camera(char *line, t_data *data);
int				get_ratio(char *line, double *ratio);
int				get_coord(char *line, t_vector *vector);
double			get_double(char *line);

unsigned int	get_rgba(int r, int g, int b, int a);
int				get_alpha(unsigned int color);
int				get_red(unsigned int color);
int				get_green(unsigned int color);
int				get_blue(unsigned int color);

int 			mrt_error_message(int error, int line);

#endif
