/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:35:10 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/23 17:35:55 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_new	copy_struct(t_new *infot_new, int im)
{
	t_new	copy;

	copy.i_end = infot_new->i_end;
	copy.start = im;
	copy.start_time = infot_new->start_time;
	copy.start_time_second = infot_new->start_time_second;
	copy.times = infot_new->times;
	return (copy);
}
