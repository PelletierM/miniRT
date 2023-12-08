/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 09:14:33 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	check_hit_sphere(t_sphere sp, t_ray ray)
{
	t_quadratic	s;

	s = solve_quadratic_sphere(sp, ray);
	if (s.dis < 0)
		return (0);
	if (s.t1 > 0 && s.t2 > 0)
		return (s.t2);
	return (s.t1);
}
