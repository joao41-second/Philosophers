/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/23 15:57:59 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	end(t_new infot_new, t_new_philo *infos, int neg)
{
	pthread_mutex_lock(&infos->mens);
	infos->fuck->im = FASLE;
	pthread_mutex_unlock(&infos->mens);
	print(infos, "dead", &infot_new, (ft_time(infot_new.start_time_second)
			- infot_new.start_time) + (neg + 1));
	return (FASLE);
}

int	chek_end(t_new_philo *infos)
{
	pthread_mutex_lock(&infos->mens);
	if (*infos->fuck->i_end == FASLE)
	{
		pthread_mutex_unlock(&infos->mens);
		return (FASLE);
	}
	pthread_mutex_unlock(&infos->mens);
	return (TRUE);
}

void	print(t_new_philo *infos, char *mens, t_new *infot_new, int time)
{
	static int	hp = 0;

	pthread_mutex_lock(&infos->mens);
	if (hp == 0)
	{
		if (*infos->fuck->i_end != 0)
		{
			printf("%d %d %s\n", time, infot_new->start, mens);
		}
		else
			hp = 1;
		if (mens[0] == 'd')
			hp = 1;
	}
	pthread_mutex_unlock(&infos->mens);
}

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
	print(infos, "has taken a fork", infot_new,
		ft_time(infot_new->start_time_second) - infot_new->start_time);
	return (TRUE);
}

int	pair_fork(t_new_philo *infos, t_new *infot_new, t_forks forks,
		pthread_mutex_t *fork)
{
	pthread_mutex_lock(&infos->mens);
	if (*infos->fuck->i_end == FASLE)
	{
		pthread_mutex_unlock(&infos->mens);
		return (FASLE);
	}
	pthread_mutex_unlock(&infos->mens);
	if (print_forks(infos, infot_new, fork, forks.fork[1]) == FASLE)
	{
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		return (FASLE);
	}
	if (print_forks(infos, infot_new, fork, forks.fork[0]) == FASLE)
	{
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		return (FASLE);
	}
	return (TRUE);
}

int	odd_fork(t_new_philo *infos, t_new *infot_new, t_forks forks,
		pthread_mutex_t *fork)
{
	usleep(100);
	pthread_mutex_lock(&infos->mens);
	if (*infos->fuck->i_end == FASLE)
	{
		pthread_mutex_unlock(&infos->mens);
		return (FASLE);
	}
	pthread_mutex_unlock(&infos->mens);
	if (print_forks(infos, infot_new, fork, forks.fork[0]) == FASLE)
	{
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		return (FASLE);
	}
	if (print_forks(infos, infot_new, fork, forks.fork[1]) == FASLE)
	{
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		return (FASLE);
	}
	return (TRUE);
}

int	forks(t_new *infot_new, t_new_philo *infos, t_forks forks)
{
	int				save;
	pthread_mutex_t	*fork;
	static int		temp = 0;

	save = 0;
	fork = infos->fork;
	(void)infot_new;
	save = par(infot_new->start);
	if (infot_new->times.philosophers % 2 != 0
		&& infot_new->start == infot_new->times.philosophers - 2 && temp == 0)
	{
		usleep(1500);
	}
	if (save == 0)
	{
		if (pair_fork(infos, infot_new, forks, fork) == FASLE)
			return (FASLE);
	}
	else
	{
		if (odd_fork(infos, infot_new, forks, fork) == FASLE)
			return (FASLE);
	}
	return (TRUE);
}

int	ft_food(t_new *infot_new, t_new_philo *infos, int time)
{
	int				start_time;
	int				time_temp;
	t_forks			forkss;

	forkss = set_forks(infot_new->start, infot_new->times.philosophers - 1);
	start_time = ft_time(infot_new->start_time_second) - infot_new->start_time;
	if (forks(infot_new, infos, forkss) == FASLE)
		return (FASLE);
	time_temp = ft_time(infot_new->start_time_second) - infot_new->start_time;
	if (time - (time_temp - start_time) < 0)
	{
		pthread_mutex_unlock(&infos->fork[forkss.fork[1]]);
		pthread_mutex_unlock(&infos->fork[forkss.fork[0]]);
		return (time - (time_temp - start_time));
	}
	if (chek_end(infos) == FASLE)
		return (-1);
	print(infos, "is eating", infot_new, ft_time(infot_new->start_time_second)
		- infot_new->start_time);
	usleep(infot_new->times.food * 1000);
	pthread_mutex_unlock(&infos->fork[forkss.fork[1]]);
	pthread_mutex_unlock(&infos->fork[forkss.fork[0]]);
	time_temp = ft_time(infot_new->start_time_second) - infot_new->start_time;
	return (time - (time_temp - start_time));
}

int	ft_sleep(t_new *infot_new, int time, t_new_philo *infos)
{
	int	start_time;

	start_time = ft_time(infot_new->start_time_second) - infot_new->start_time;
	if (infot_new->i_end == 0)
		return (-1);
	print(infos, "is sleeping", infot_new, ft_time(infot_new->start_time_second)
		- infot_new->start_time);
	if (infot_new->times.food < infot_new->times.death)
		usleep(infot_new->times.food * 1000);
	else
	{
		usleep((infot_new->times.food - infot_new->times.death) * 1000);
		return (-1);
	}
	if (chek_end(infos) == FASLE|| time
		- (ft_time(infot_new->start_time_second) - infot_new->start_time
			- start_time) < 0)
	{
		return (FASLE);
	}
	print(infos, "is thinking", infot_new,
		(ft_time(infot_new->start_time_second) - infot_new->start_time));
	return (time - (ft_time(infot_new->start_time_second)
			- infot_new->start_time - start_time));
}

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

int	thead_run(t_new infot_new, t_new_philo *infos, int time, int x)
{
	int	temp;

	while (1)
	{
		if (x == infot_new.times.food_x && infot_new.times.food_x != 0)
			end(infot_new, infos, time);
		pthread_mutex_lock(&infos->mens);
		temp = *infos->fuck->i_end;
		pthread_mutex_unlock(&infos->mens);
		if (temp < 0)
			return (end(infot_new, infos, time));
		time = ft_food(&infot_new, infos, time);
		if (chek_end(infos) == FASLE)
			return (FASLE);
		if (time < 0)
			return (end(infot_new, infos, time));
		else
			time = infot_new.times.death;
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
	t_new			*infot_news;
	t_new			infot_new;
	struct timeval	tv;
	t_ints			ints;

	infos = (t_new_philo *)infs;
	ints.fil_n = infos->fuck->start;
	ints.x = 0;
	thead_sleep(infos);
	pthread_mutex_lock(&infos->mens);
	infot_news = (t_new *)infos->fuck;
	infot_new = copy_struct(infot_news, ints.fil_n);
	ints.time = infos->fuck->times.death;
	pthread_mutex_unlock(&infos->mens);
	gettimeofday(&tv, NULL);
	infot_new.start_time_second = tv.tv_sec * 1000;
	infot_new.start_time = ft_time(infot_new.start_time_second);
	thead_run(infot_new, infos, ints.time, ints.x);
	return ("oi");
}

int	bar_run(t_new_philo *infus, t_new *infus2, int i, int nb)
{
	while (++i < nb - 1)
	{
		usleep(25);
		pthread_mutex_lock(&infus->mens);
		if (infus2->im == FASLE)
		{
			i = -5;
		}
		pthread_mutex_unlock(&infus->mens);
		if (i == -5)
		{
			pthread_mutex_lock(&infus->mens);
			*infus->fuck->i_end = 0;
			pthread_mutex_unlock(&infus->mens);
			return (FASLE);
		}
		pthread_mutex_lock(&infus->mens);
		infus2--;
		pthread_mutex_unlock(&infus->mens);
	}
	pthread_mutex_lock(&infus->mens);
	infus2 += nb - 1;
	pthread_mutex_unlock(&infus->mens);
	return (TRUE);
}

void	*bar_men_thead(void *infs)
{
	t_new_philo	*infus;
	t_new		*infus2;
	int			nb;
	int			i;

	infus = (t_new_philo *)infs;
	nb = infus->philo;
	pthread_mutex_lock(&infus->mens);
	*infus->fuck->i_end = 2;
	pthread_mutex_unlock(&infus->mens);
	infus2 = (t_new *)infus->fuck;
	if (nb == 1)
	{
		nb++;
	}
	while (1)
	{
		i = -1;
		if (bar_run(infs, infus2, i, nb) == FASLE)
		{
			break ;
		}
	}
	return ("oi");
}
