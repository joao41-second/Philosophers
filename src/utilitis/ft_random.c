/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:35:10 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/24 10:33:31 by jperpect         ###   ########.fr       */
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

char	*not_philos(t_new_philo *infos, t_new infos_new)
{
	print(infos, "has taken a fork", &infos_new,
		ft_time(infos_new.start_time_second) - infos_new.start_time);
	usleep(infos_new.times.death * 1000);
	end(infos_new, infos, -1);
	return ("end");
}
