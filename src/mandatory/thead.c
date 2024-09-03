/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/03 15:05:46 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void end(s_new *infos_new)
{
	pthread_mutex_lock(&infos_new->death);
	infos_new->start = -1;	
	pthread_mutex_unlock(&infos_new->death);
}

int ft_time(int second)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);	
	return( tv.tv_usec /1000 + (tv.tv_sec-second)*1000);
}

int par (int n)
{
	if(n %2 == 0)
		return(true);
	return(fasle);	

}

void forks(s_new *infos_new,s_new_fuck *infos )
{
	int save = 0;
	pthread_mutex_t *fork;
	fork = infos->fork;
	(void)infos_new;	
	//save = par(infos_new->start);
	if(save == 0)
	{	
		pthread_mutex_lock(&fork[infos_new->start]);
		printf("%d %d has taken a right fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
 		if(infos_new->start != 0)
	 		pthread_mutex_lock(&infos->fork[infos_new->start-1]);
 		else
	 		pthread_mutex_lock(&infos->fork[infos_new->times.philosophers ]);
		printf("%d %d has taken a left fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	}
	else
	{
		usleep(100);
 		if(infos_new->start != 0)
	 		pthread_mutex_lock(&infos->fork[infos_new->start-1]);
 		else
	 		pthread_mutex_lock(&infos->fork[infos_new->times.philosophers-1 ]);
		printf("%d %d has taken a left fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
		pthread_mutex_lock(&infos->fork[infos_new->start]);
		printf("%d %d has taken a right fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	}
}


int ft_food( s_new *infos_new,s_new_fuck *infos)
{
	(void)infos_new;
	forks(infos_new,infos);
	return(0);
}

int random_in_range(int min, int max) 
{
	return min + rand() % (max - min + 1);
}



void *thead(void *infs)
{
	s_new_fuck * infos;
	s_new * infos_new;
	struct timeval tv;

	infos = (s_new_fuck*)infs;
	infos_new = (s_new*)infos->fuck;
	while (infos->pq < infos_new->times.philosophers-1)
	{}
	
	gettimeofday(&tv, NULL);
	infos_new->start_time_second = tv.tv_sec * 1000;
	infos_new->start_time = ft_time(infos_new->start_time_second);
	while (1)
	{
		if(infos->end == 0)
		{
			printf("dead\n");
			return("oi");
		}
		ft_food(infos_new,infos);
		if(random_in_range(1, 100) == 99)
 		{
 			printf("eu matie\n");
 			end(infos_new);
			return("oi");
 		}
	}
	return("oi");
}




void *bar_men_thead(void *infs)
{
	s_new_fuck * infus;
	s_new *infus2;
	int nb ;

	infus = (s_new_fuck *)infs;
	infus2 = (s_new *)infus->fuck;

	pthread_mutex_lock(&infus2->death);
	nb = infus2->times.philosophers;
	pthread_mutex_unlock(&infus2->death);
	while (1)
	{
		int i;
		i = 0;
		while (++i < nb)
		{
			pthread_mutex_lock(&infus2[i].death);
			if(infus2[i].start == -1)
			{
				return("ola");
			}
			pthread_mutex_unlock(&infus2[i].death);
		}	
	}
	return("oi");
}
