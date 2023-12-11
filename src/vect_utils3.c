/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:58:17 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/11 15:59:53 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	rotate_figure(t_vector target, t_vector axe, int direction)
{
	t_vector	retval;
	float		cs;
	float		sn;

	cs = cosf((float) OBJ_ROT_ANGLE);
	sn = sinf((float) OBJ_ROT_ANGLE);
	sn *= direction;
	retval = vadd(vsadd(vsmul(target, cs),
				vdot(target, axe) * (1 - cs)),
			vsmul(vcross(axe, target), sn));
	return (retval);
}
