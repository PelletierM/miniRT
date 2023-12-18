/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:13:41 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 11:20:52 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_object_color(t_data *data, t_hit *hit, t_ray ray)
{
	if (has_texture(data, hit) == 1)
	{
		if (hit->shape == OBJ_SPHERE)
		{
			set_sphere_uv(data, hit, ray);
			hit->color = get_color_sphere_texture(data, hit);
		}
		else if (hit->shape == OBJ_PLANE)
		{
			set_plane_uv(data, hit, ray);
			hit->color = get_color_plane_texture(data, hit);
		}
	}
	else
		hit->color = get_material_color(data, *hit);
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

mlx_texture_t	*get_norm_texture_img(t_data *data, t_hit hit)
{
	int	i;
	int	id;

	i = 0;
	id = get_material_id(data, hit);
	printf("%d\n", id);
	if (id < 0)
		return (0);
	while (i < data->num_materials)
	{
		if (data->materials[i].id == id)
			return (data->materials[i].norm_img);
		i++;
	}
	return (0);
}

int	has_texture(t_data *data, t_hit *hit)
{
	int	id;

	id = get_material_id(data, *hit);
	if (id < 0 || id >= data->num_materials)
		return (0);
	if (data->materials[id].texture_flag == 1)
		return (1);
	return (0);
}
