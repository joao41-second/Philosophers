/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:29:35 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/25 14:32:43 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
	if (save(infos, infot_new) == FASLE
		|| print_forks(infos, infot_new, fork, forks.fork[1]) == FASLE)
	{
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		return (FASLE);
	}
	if (save(infos, infot_new) == FASLE
		|| print_forks(infos, infot_new, fork, forks.fork[0]) == FASLE)
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
	if (save(infos, infot_new) == FASLE
		|| print_forks(infos, infot_new, fork, forks.fork[0]) == FASLE)
	{
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		return (FASLE);
	}
	if (save(infos, infot_new) == FASLE
		||print_forks(infos, infot_new, fork, forks.fork[1]) == FASLE)
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

int	end(t_new infot_new, t_new_philo *infos, int neg)
{
	if (neg)
	{
	}
	pthread_mutex_lock(&infos->mens);
	infos->fuck->im = FASLE;
	pthread_mutex_unlock(&infos->mens);
	print(infos, "died", &infot_new, (infot_new.start_time) );
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
