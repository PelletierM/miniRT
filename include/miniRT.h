/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:42:04 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 15:39:25 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_DIST 1000000
# define THREAD_MAX 12
# define MAX_BOUNCE 10
// Camera and viewport settings 
# define VP_DIAG 0.04327
# define CAM_APERTURE 5.4
# define CAM_FOCUS_DIST 3
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define RES_MAX_HEIGHT 1440
# define RES_MAX_WIDTH 2560
# define BG_COLOR 0x000000FF

// Transformation flags
# define OBJ_MV_RATIO 0.5
# define OBJ_MV_LEFT 1
# define OBJ_MV_RIGHT 2
# define OBJ_MV_FORWARD 4
# define OBJ_MV_BACK 8
# define OBJ_MV_DOWN 16
# define OBJ_MV_UP 32
# define OBJ_ROT_ANGLE 0.0872665
# define OBJ_ROT_LEFT 64
# define OBJ_ROT_RIGHT 128
# define OBJ_ROT_UP 256
# define OBJ_ROT_DOWN 512
# define OBJ_SCALE_UP 1024
# define OBJ_SCALE_DOWN 2048
# define OBJ_SCALE_UP_B 4096
# define OBJ_SCALE_DOWN_B 8192
# define OBJ_ZOOM_RATIO 0.0872665
# define OBJ_SCALE_RATIO 1.05
# define LIGHT_RATIO 0.01

# define MAX_LINES	128
# define MAX_FIGURE 24
# define MAX_CHAR_PATH 100

# define VALID_CHARS "+-., 0123456789\n"
# define ERR_ARGC 0
# define ERR_FILE_FORMAT 1
# define ERR_NO_FILE 2
# define ERR_LINE_FORMAT 3
# define ERR_MLX_INIT 4
# define ERR_DIV_ZERO 5

# define OBJ_CAM 0
# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_CYL 3
# define OBJ_LIGHT 4


typedef struct s_quadratic
{
	float	dis;
	float	t1;
	float	t2;
}	t_quadratic;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

typedef struct s_material
{
	int				id;
	float			roughness;
	float			metallic;
	float			emissive_ratio;
	int				texture_flag;
	t_vector		color;
	mlx_texture_t	*img;
	mlx_texture_t	*norm_img;
}	t_material;

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
	float		vp_horiz_len;
	float		vp_vert_len;
	float		fov;
	float		focal_len;
	float		focus_dist;
	float		aperture;
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
	int				material_id;
}				t_sphere;

typedef struct s_plane
{
	t_vector		position;
	t_vector		orientation;
	t_vector		color;
	int				material_id;
}				t_plane;

typedef struct s_cylinder
{
	t_vector		position;
	t_vector		cap;
	t_vector		orientation;
	float			diameter;
	float			height;
	t_vector		color;
	t_plane			bottom;
	t_plane			top;
	int				material_id;
}				t_cylinder;

typedef struct s_ray
{
	t_vector	position;
	t_vector	orientation;
	float		t;
}	t_ray;

typedef struct s_hit
{
	int			shape;
	int			i;
	int			flag;
	float		t;
	int			pos_hit_number;
	t_vector	position;
	t_vector	normal;
	t_vector	color;
	float		u;
	float		v;
}	t_hit;

typedef struct s_nav_mode
{
	int	obj;
	int	i;	
}	t_nav_mode;

typedef struct s_data
{
	t_vector	*accumulator;
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
	t_material	materials[MAX_FIGURE];
	int			num_materials;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_nav_mode	nav_mode;
	int			nav_flag;
	int32_t		width;
	int32_t		height;
	float		ratio;
	int			samples;
}				t_data;

typedef struct s_thread
{
	int			id;
	t_data		*data;
	pthread_t	thread;

}	t_thread;

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
int				set_material(char *line, t_data *data);

int				get_ratio(char *line, float *ratio);
int				get_coord(char *line, t_vector *vector);
int				get_color(char *line, t_vector *vector);
float			get_float(char *line);

unsigned int	get_rgba(int r, int g, int b, int a);
unsigned int	get_vect_rgba(t_vector c);
t_vector		get_rgb_vect(unsigned int color);
t_vector		get_img_pixel(mlx_texture_t *texture, int x, int y);
int				get_alpha(unsigned int color);
int				get_red(unsigned int color);
int				get_green(unsigned int color);
int				get_blue(unsigned int color);
t_vector		update_color(t_data *data, t_vector color, int x, int y);
t_vector		clamp_color(t_vector color);
void			update_image(t_data *data);

int				mrt_error_message(int error, int line);

float			check_hit_sphere(t_sphere sp, t_ray ray, t_hit *hit);
float			check_hit_cylinders(t_cylinder cy, t_ray ray, int *flag);
float			check_hit_planes(t_plane plane, t_ray ray);

t_vector		trace_pixel(t_data *data, t_ray ray, int depth);
t_ray			get_current_ray(t_data *data, int x, int y);
void			render(t_data *data);
void			*render_thread(void *param);
void			perpixel(int x, int y, t_data *data);

// Camera functions
void			mrt_create_cam(t_data *data);
void			move_cam(t_data *data, int direction);
void			rot_cam(t_data *data, int direction);
void			zoom_cam(t_data *data, int direction);
t_ray			apply_dof(t_data *data, t_ray ray);

// Obj move functions
void			move_obj(t_data *data, int i);
void			rot_obj(t_data *data, int i);
void			scale_obj(t_data *data, int i);

// MLX hooks
void			ft_gen_hook(void *ptr);
void			ft_keyhook(mlx_key_data_t keydata, void *param);
void			ft_mouse_hook(enum mouse_key mouse_key, enum action action,
					enum modifier_key modifier_key, void *param);
void			ft_resize_hook(int32_t width, int32_t height, void *param);
void			ft_keyhook_move_obj(mlx_key_data_t keydata, t_data *data);
void			ft_keyhook_rotate_obj(mlx_key_data_t keydata, t_data *data);
void			ft_keyhook_scale_obj(mlx_key_data_t keydata, t_data *data);
void			ft_keyhook_mode(mlx_key_data_t keydata, t_data *data);
int				check_cam_hook(t_data *data, int i);
int				check_obj_hook(t_data *data, int i);
void			ft_get_click_target(t_data *data);

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
t_vector		vssub(t_vector v1, float factor);
t_vector		vcopy(t_vector v);
t_vector		translate_pt(t_vector position,
					float t,
					t_vector orientation);
t_vector		rotate_figure(t_vector target, t_vector axe, int direction);
float			vlength_squared(t_vector v);
int				is_vect_negative(t_vector vector);
float			vlength(t_vector v1);
t_vector		create_vector_from_points(t_vector p1, t_vector p2);
t_vector		vreflect(t_vector v, t_vector normal);
t_vector		black_color(void);

float			vdistance(t_vector v1, t_vector v2);
t_quadratic		solve_quadratic_cylinder(t_cylinder cy, t_ray ray);
t_quadratic		solve_quadratic_sphere(t_sphere sp, t_ray ray);

void			set_cylinders_disk(t_cylinder	*cy);
t_hit			get_closest_hit(t_data *data, t_ray ray);
void			get_normal_hit(t_data *data, t_ray, t_hit *hit);
t_vector		get_light(t_hit hit, t_data *data);
t_vector		get_material_normal(t_data *data, t_hit hit, t_ray ray);

// Random functions
t_vector	vrandom_range(float min, float max);
t_vector	vrandom();
float		random_float_range(float min, float max);
float		random_float();
t_vector	random_unit_vector();
t_vector	random_in_unit_sphere();

// Material
float	get_roughness_factor(t_data *data, t_hit hit);
float	get_metallic_factor(t_data *data, t_hit hit);
float	get_emissive_ratio(t_data *data, t_hit hit);
int		get_material_id(t_data *data, t_hit hit);
void	get_object_color(t_data *data, t_hit *hit, t_ray ray);

// Texture
mlx_texture_t	*get_texture_img(t_data *data, t_hit *hit);
mlx_texture_t	*get_norm_texture_img(t_data *data, t_hit hit);
t_vector		get_color_sphere_texture(t_data *data, t_hit *hit);
void			set_sphere_uv(t_data *data, t_hit *hit, t_ray ray);
int				has_texture(t_data *data, t_hit *hit);
t_vector		get_texture_normal(t_data *data, t_hit hit, t_ray ray);
void			set_plane_uv(t_data *data, t_hit *hit, t_ray ray);
t_vector		get_color_plane_texture(t_data *data, t_hit *hit);
t_vector		get_material_color(t_data *data, t_hit hit);
#endif
