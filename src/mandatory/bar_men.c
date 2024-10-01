/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar_men.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:19:48 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/26 11:59:45 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int dead_off_static(t_new_philo *infus,int i)
{
	int time_save;
	pthread_mutex_lock(&infus->mens);
	//printf("ola mundo minha vida e de %d %d\n",infus->fuck->dead_time,get_time(infus)-infus->fuck->start_time);
	time_save =  (get_time(infus)-infus->fuck->start_time) - infus->fuck->dead_time  ;
	if(infus->fuck->dead_time == 0)
		time_save -= infus->fuck->times.food;
	//printf("ola time %d\n", (infus->fuck->times.death - infus->fuck->times.food)-time_save );
	if(infus->fuck->dead_time > 0){
		if(((  (infus->fuck->times.death - infus->fuck->times.food)-time_save ) <= 0 ))
			{
				*infus->fuck->i_end = 0;
				printf("%d %d died\n",get_time(infus)-infus->fuck->start_time,i);
				pthread_mutex_unlock(&infus->mens);
				return(FASLE);
			}
	}
	pthread_mutex_unlock(&infus->mens);
	return(TRUE);
}


static int	bar_run(t_new_philo *infus, t_new *infus2, int i, int nb)
{
	while (++i < nb +1)
	{

		usleep(25);
		pthread_mutex_lock(&infus->mens);
		if (infus2->im == FASLE)
		{
			i = -5;
		}
		pthread_mutex_unlock(&infus->mens);
		if (dead_off_static(infus,i)== FASLE)
			return (FASLE);
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
	if (nb == 1)
		nb++;
	if (nb == 0)
		nb = 2;
	while (1)
	{
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
