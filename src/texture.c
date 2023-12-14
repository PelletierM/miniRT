/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:00:56 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/14 16:35:06 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector		get_hit_coord(t_hit *hit, t_ray ray);
mlx_texture_t	*get_texture_img(t_data *data, t_hit *hit);

t_vector	get_color_sphere_texture(t_data *data, t_hit *hit)
{
	t_vector		color;
	mlx_texture_t	*texture;
	int				u;
	int				v;

	texture = get_texture_img(data, hit);
	if (!texture)
		return (data->spheres[hit->i].color);
	u = hit->u * texture->width;
	v = hit->v * texture->height;
	u = texture->width - u - 1;
	v = texture->height - v - 1;
	color = get_img_pixel(texture, u, v);
	return (color);
}

void	set_sphere_uv(t_data *data, t_hit *hit, t_ray ray)
{
	float		theta;
	float		phi;

	get_normal_hit(data, ray, hit);
	theta = acosf(-hit->normal.y);
	phi = atan2f(-hit->normal.z, hit->normal.x) + M_PI;
	hit->u = phi / (2 * M_PI);
	hit->v = theta / M_PI;
}

t_vector	get_hit_coord(t_hit *hit, t_ray ray)
{
	t_vector	coord;
	
	coord = vadd(ray.position, vsmul(ray.orientation, hit->t));
	return (coord);
}

mlx_texture_t	*get_texture_img(t_data *data, t_hit *hit)
{
	int	i;
	int	id;

	i = 0;
	id = get_material_id(data, *hit);
	if (id < 0)
		return (0);
	while (i < data->num_materials)
	{
		if (data->materials[i].id == id)
			return (data->materials[i].img);
		i++;
	}
	return (0);
}

int	has_texture(t_data *data, t_hit *hit)
{
	int	id;

	id = get_material_id(data, *hit);
	if (data->materials[id].texture_flag == 1)
		return (1);
	return (0);
}
