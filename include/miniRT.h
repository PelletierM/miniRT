/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:42:04 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 17:07:49 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42.h"

# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define BG_COLOR 0x000000FF

# define MAX_LINES 1024
# define MAX_FIGURE 256

# define VALID_CHARS "+-., 0123456789\n"
# define ERR_ARGC 0
# define ERR_FILE_FORMAT 1
# define ERR_NO_FILE 2
# define ERR_LINE_FORMAT 3
# define ERR_MLX_INIT 4

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
	char		flag;
	t_sphere	spheres[MAX_FIGURE];
	int			num_spheres;
	t_plane		planes[MAX_FIGURE];
	int			num_planes;
	t_cylinder	cylinders[MAX_FIGURE];
	int			num_cylinders;
	mlx_image_t	*img;
	mlx_t		*mlx;
}				t_data;

int				mrt_parser(char *file, t_data *data);
int				mrt_check_argv(int argc, char **argv);
void			mrt_init_data(t_data *data);
int				set_values(char *line, t_data *data);
int				check_line(char *line);
char			*skip_spaces(char *line);
char			*skip_double(char *line);
char			*skip_digits(char *line);
char			*skip_coord(char *line);

int				check_data(t_data data);
int				check_cylinders(t_data data);
int				check_color(t_vector color);
int				check_normalized_vector(t_vector vector);

int				set_ambient(char *line, t_data *data);
int				set_camera(char *line, t_data *data);
int				set_light(char *line, t_data *data);
int				set_sphere(char *line, t_data *data);
int				set_plane(char *line, t_data *data);
int				set_cylinder(char *line, t_data *data);

int				get_ratio(char *line, double *ratio);
int				get_coord(char *line, t_vector *vector);
double			get_double(char *line);

unsigned int	get_rgba(int r, int g, int b, int a);
int				get_alpha(unsigned int color);
int				get_red(unsigned int color);
int				get_green(unsigned int color);
int				get_blue(unsigned int color);

int				mrt_error_message(int error, int line);

void			ft_fill_bg(t_data *data);
void			ft_put_pixel(t_data *data, double x,
					double y, unsigned int color);

#endif
