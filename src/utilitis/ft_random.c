/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:35:10 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/24 20:13:15 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_new	copy_struct(t_new *infot_new, int im)
{
	t_new	copy;

	copy.i_end = infot_new->i_end;
	copy.times = infot_new->times;
	copy.start = im;
	copy.start_time = infot_new->start_time;
	copy.start_time_second = infot_new->start_time_second;
	copy.times = infot_new->times;
	return (copy);
}

char	*not_philos(t_new_philo *infos, t_new infos_new)
{
	print(infos, "has taken a fork", &infos_new,
	get_time(infos) - infos_new.start_time);
	usleep(infos_new.times.death * 1000);
	end(infos_new, infos, infos_new.times.death);
	return ("end");
}

void	set_time(t_new_philo *infus, int second)
{
	pthread_mutex_lock(&infus->death);
	*infus->fuck->i_time = ft_time(second);
	pthread_mutex_unlock(&infus->death);
}

int	second(void)
{
	struct timeval	tv;
	static int		second = 0;

	gettimeofday(&tv, NULL);
	if (second == 0)
		second = tv.tv_sec * 1000;
	return (second);
}

void	set_fuck_i_end(t_new_philo *infus)
{
	pthread_mutex_lock(&infus->mens);
	*infus->fuck->i_end = 2;
	pthread_mutex_unlock(&infus->mens);
}
