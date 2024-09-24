/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar_men.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:19:48 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/24 20:23:37 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	bar_run(t_new_philo *infus, t_new *infus2, int i, int nb)
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

int	get_time(t_new_philo *infos)
{
	int	temp;

	pthread_mutex_lock(&infos->death);
	temp = *infos->fuck->i_time;
	pthread_mutex_unlock(&infos->death);
	return (temp);
}

void	*bar_men_thead(void *infs)
{
	t_new_philo	*infus;
	t_new		*infus2;
	int			nb;
	int			i;

	infus = (t_new_philo *)infs;
	nb = infus->philo;
	set_fuck_i_end(infus);
	set_time(infus, second());
	infus2 = (t_new *)infus->fuck;
	if (nb == 1 )
		nb++;
	if(nb == 0)
		nb = 2;

	while (1)
	{
		//printf("oi\n");
		usleep(100);
		set_time(infus, second());
		i = -1;
		if (bar_run(infs, infus2, i, nb) == FASLE)
		{
			break ;
		}
	}
	return ("oi");
}
