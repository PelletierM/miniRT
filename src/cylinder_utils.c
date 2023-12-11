/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:07:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/11 14:07:27 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cylinders_disk(t_cylinder	*cy)
{
	cy->cap = translate_pt(
			cy->position,
			cy->height / 2,
			vsmul(cy->orientation, -1));
	cy->bottom.position = vcopy(cy->cap);
	cy->bottom.orientation = vsmul(cy->orientation, -1);
	cy->top.orientation = vsmul(cy->orientation, 1);
	cy->top.position = translate_pt(
			cy->cap,
			cy->height,
			cy->orientation);
}
