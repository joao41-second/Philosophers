/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/26 12:01:41 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_food(t_new *infot_new, t_new_philo *infos, int time)
{
	int				start_time;
	int				time_temp;
	t_forks			forkss;

	forkss = set_forks(infot_new->start, infot_new->times.philosophers - 1);
	start_time = get_time(infos) - infot_new->start_time;
	infot_new->time_reste = start_time;
	if (forks(infot_new, infos, forkss) == FASLE)
		return (time - (get_time(infos) - infot_new->start_time - start_time));
	time_temp = get_time(infos) - infot_new->start_time;
	if (time - (time_temp - start_time) < 0)
	{
		pthread_mutex_unlock(&infos->fork[forkss.fork[1]]);
		pthread_mutex_unlock(&infos->fork[forkss.fork[0]]);
		return (time - (time_temp - start_time));
	}
	if (chek_end(infos) == FASLE)
		return (-1);
	print(infos, "is eating", infot_new, infot_new->start_time);
	time = infot_new->times.death;
	usleep(infot_new->times.food * 1000);
	pthread_mutex_unlock(&infos->fork[forkss.fork[1]]);
	pthread_mutex_unlock(&infos->fork[forkss.fork[0]]);
	time_temp = get_time(infos) - infot_new->start_time;
	return (time - ((time_temp - start_time) - infot_new->times.food));
}

int	ft_sleep(t_new *infot_new, int time, t_new_philo *infos)
{
	int	start_time;

	start_time = get_time(infos) - infot_new->start_time;
	if (infot_new->i_end == 0)
		return (-1);
	print(infos, "is sleeping", infot_new, infot_new->start_time);
	if (infot_new->times.sleep <= time)
		usleep(infot_new->times.sleep * 1000);
	else
	{
		usleep(( infot_new->times.sleep-time ) * 1000);
		return (-1);
	}
	if (chek_end(infos) == FASLE || time
		-(get_time(infos) - infot_new->start_time
			- start_time) < 0)
	{
		return (FASLE);
	}
	print(infos, "is thinking", infot_new, infot_new->start_time);
	return (time - (get_time(infos) - infot_new->start_time - start_time));
}

int	thead_run(t_new infot_new, t_new_philo *infos, int time, int x)
{
	int	temp;

	while (1)
	{
		if (x == infot_new.times.food_x && infot_new.times.food_x != 0)
			return (end(infot_new, infos, time));
		pthread_mutex_lock(&infos->mens);
		temp = *infos->fuck->i_end;
		pthread_mutex_unlock(&infos->mens);
		if (temp <= 0)
			return (end(infot_new, infos, time));
		infot_new.dead_time = time;
		time = ft_food(&infot_new, infos, time);
		if (chek_end(infos) == FASLE)
			return (FASLE);
		if (time < 0)
			return (end(infot_new, infos, time));
		usleep(1000);
		time = ft_sleep(&infot_new, time, infos);
		if (chek_end(infos) == FASLE)
			return (FASLE);
		x++;
	}
	return (TRUE);
}

void	thead_sleep(t_new_philo *infos)
{
	int	temp;

	while (1)
	{
		usleep(50);
		pthread_mutex_lock(&infos->mens);
		temp = *infos->fuck->i_end;
		pthread_mutex_unlock(&infos->mens);
		if (temp == 2)
		{
			break ;
		}
	}
}

void	*thead(void *infs)
{
	t_new_philo		*infos;
	t_new			*infos_news;
	t_new			infos_new;
	t_ints			ints;

	infos = (t_new_philo *)infs;
	ints.fil_n = infos->fuck->start;
	ints.x = 0;
	thead_sleep(infos);
	pthread_mutex_lock(&infos->mens);
	infos_news = (t_new *)infos->fuck;
	infos_new = copy_struct(infos_news, ints.fil_n);
	ints.time = infos->fuck->times.death;
	pthread_mutex_unlock(&infos->mens);
	infos_new.start_time = get_time(infos);
	if (infos->fuck->start == 0)
	{
		return (not_philos(infos, infos_new));
	}
	thead_run(infos_new, infos, ints.time, ints.x);
	return ("oi");
}
