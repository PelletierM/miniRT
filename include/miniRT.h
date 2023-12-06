/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:42:04 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/06 15:22:19 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42.h"
# include <math.h>
# include <stdio.h>
# include <float.h>

# define VP_DIAG 0.04327
# define WIN_HEIGHT 768
# define WIN_WIDTH	1024 
# define RES_MAX_HEIGHT 1440
# define RES_MAX_WIDTH 2560
# define BG_COLOR 0x000000FF

# define MAX_LINES	128
# define MAX_FIGURE 24

# define VALID_CHARS "+-., 0123456789\n"
# define ERR_ARGC 0
# define ERR_FILE_FORMAT 1
# define ERR_NO_FILE 2
# define ERR_LINE_FORMAT 3
# define ERR_MLX_INIT 4
# define ERR_DIV_ZERO 5

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

typedef struct s_ambient
{
	float			ratio;
	t_vector		color;
}			t_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	z_axis;
	t_vector	y_axis;
	t_vector	x_axis;
	float		focal_len;
	float		vp_horiz_len;
	float		vp_vert_len;
	float		fov;
}				t_camera;

typedef struct s_light
{
	t_vector		position;
	float			ratio;
	t_vector		color;
}				t_light;

typedef struct s_sphere
{
	t_vector		position;
	float			diameter;
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
	float			diameter;
	float			height;
	t_vector		color;
}				t_cylinder;

typedef struct s_ray
{
	t_vector	position;
	t_vector	orientation;
	float		t;
}	t_ray;

typedef struct s_hit
{
	int		shape;
	int 	i;
	float	t;
}	t_hit;

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
	int32_t		width;
	int32_t		height;
	float		ratio;
}				t_data;

int				mrt_parser(char *file, t_data *data);
int				mrt_check_argv(int argc, char **argv);
void			mrt_init_data(t_data *data);
int				ft_mlx_init(t_data *data);
void			ft_keyhook(mlx_key_data_t keydata, void *param);
void			ft_resize_hook(int32_t width, int32_t height, void *param);
int				set_values(char *line, t_data *data);
int				check_line(char *line);
char			*skip_spaces(char *line);
char			*skip_float(char *line);
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

int				get_ratio(char *line, float *ratio);
int				get_coord(char *line, t_vector *vector);
float			get_float(char *line);

unsigned int	get_rgba(int r, int g, int b, int a);
unsigned int	get_vect_rgba(t_vector c);
int				get_alpha(unsigned int color);
int				get_red(unsigned int color);
int				get_green(unsigned int color);
int				get_blue(unsigned int color);

int				mrt_error_message(int error, int line);

float			check_hit_cylinder(t_cylinder sp, t_ray ray);
float			check_hit_sphere(t_sphere sp, t_ray ray);
float			check_hit_cylinders(t_cylinder cy, t_ray ray);

void			render(void *param);
void			mrt_create_camera(t_data *data);

// Vector operations
float			vdot(t_vector v1, t_vector v2);
t_vector		vcross(t_vector v1, t_vector v2);
t_vector		vnormalize(t_vector v1);
t_vector		vadd(t_vector v1, t_vector v2);
t_vector		vsub(t_vector v1, t_vector v2);
t_vector		vmul(t_vector v1, t_vector v2);
t_vector		vsmul(t_vector v1, float factor);
t_vector		vsdiv(t_vector v1, float factor);
t_vector		vsadd(t_vector v1, float factor);

#endif
