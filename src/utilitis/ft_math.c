/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:30:44 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/25 14:42:37 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_time(int second)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + (tv.tv_sec - second) * 1000);
}

int	par(int n)
{
	if (n % 2 == 0)
		return (TRUE);
	return (FASLE);
}

void	print(t_new_philo *infos, char *mens, t_new *infot_new, int time)
{
	static int	hp = 0;
	if(time)
	{}
	pthread_mutex_lock(&infos->mens);
	if (hp == 0)
	{
		if (*infos->fuck->i_end != 0)
		{
			printf("%d %d %s\n", get_time(infos) - time, infot_new->start, mens);
		}
		else
			hp = 1;
		if (mens[0] == 'd')
			hp = 1;
	}
	pthread_mutex_unlock(&infos->mens);
}

t_forks	set_forks(int my, int max)
{
	t_forks	forks;

	if (my == 0)
	{
		forks.my = 0;
		forks.steal = max;
	}
	else
	{
		forks.my = my;
		forks.steal = my - 1;
	}
	return (forks);
}

int	print_forks(t_new_philo *infos, t_new *infot_new, pthread_mutex_t *fork,
		int mut)
{
	pthread_mutex_lock(&fork[mut]);
	pthread_mutex_lock(&infos->mens);
	if (*infos->fuck->i_end == FASLE)
	{
		pthread_mutex_unlock(&infos->mens);
		return (FASLE);
	}
	pthread_mutex_unlock(&infos->mens);
	print(infos, "has taken a fork", infot_new, infot_new->start_time);
	return (TRUE);
}
