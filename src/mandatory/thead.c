/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/05 11:27:54 by jperpect         ###   ########.fr       */
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

s_forks set_forks(int my,int max)
{
	s_forks forks;
	if(my == 0)
	{
		forks.my = 0;
		forks.steal = max;
	}
	else
	{
		forks.my = my;
		forks.steal = my -1; 
	}
	return(forks);
}

void forks(s_new *infos_new,s_new_fuck *infos )
{
	s_forks forks;
	int save = 0;
	pthread_mutex_t *fork;
	static int temp = 0;


	forks = set_forks(infos_new->start,infos_new->times.philosophers-1);
	fork = infos->fork;
	(void)infos_new;
	//printf("os filom sa x = %d\n",infos_new->times.philosophers);
	save = par(infos_new->start);
	if(infos_new->times.philosophers  %2 != 0 && infos_new->start == infos_new->times.philosophers -2 && temp == 0)
	{
		temp++;
		usleep(1000);
		save = 0;
	}

	
	if(save == 0)
	{
		pthread_mutex_lock(&infos->fork[forks.fork[1]]);
		printf("%d %d has taken a left fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
		pthread_mutex_lock(&fork[forks.fork[0]]);
		printf("%d %d has taken a right fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&fork[forks.fork[0]]);
		printf("%d %d has taken a right fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	 	pthread_mutex_lock(&infos->fork[forks.fork[1]]);
		printf("%d %d has taken a left fork\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	}
}


int ft_food( s_new *infos_new,s_new_fuck *infos,int time)
{
	(void)infos_new;
	int start_time;
	int time_temp;
	pthread_mutex_t *fork;
	s_forks forkss;


	forkss = set_forks(infos_new->start,infos_new->times.philosophers-1);

	start_time = ft_time(infos_new->start_time_second)-infos_new->start_time;
	fork = infos->fork;
	forks(infos_new,infos);
		
		
	time_temp = ft_time(infos_new->start_time_second)-infos_new->start_time;
	if(time - (time_temp-start_time) < 0)
	{
		pthread_mutex_unlock(&fork[forkss.fork[1]]);
		pthread_mutex_unlock(&fork[forkss.fork[0]]);
		return(time - (time_temp-start_time));
	}
	printf("%d %d is eating\n", ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	usleep(infos_new->times.food *1000);

	
	pthread_mutex_unlock(&fork[forkss.fork[1]]);
	pthread_mutex_unlock(&fork[forkss.fork[0]]);
	time_temp = ft_time(infos_new->start_time_second)-infos_new->start_time;
	return(time - (time_temp-start_time));
}
int ft_sleep(s_new *infos_new,int time)
{
	int start_time;
	int time_temp;
	start_time = ft_time(infos_new->start_time_second)-infos_new->start_time;
	printf("%d %d is sleeping\n",ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	usleep(infos_new->times.sleep * 1000);
	time_temp = ft_time(infos_new->start_time_second)-infos_new->start_time;
	if(time - (time_temp - start_time) < 0)
		return(time - (time_temp - start_time));
	printf("%d %d is thinking\n",ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	return(time - (time_temp - start_time));
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
	int time;
	int x;
	 
	infos = (s_new_fuck*)infs;
	infos_new = (s_new*)infos->fuck;
	time = infos_new->times.death;
	x = 0;
	while (infos->pq < infos_new->times.philosophers-1)
	{}
	
	gettimeofday(&tv, NULL);
	infos_new->start_time_second = tv.tv_sec * 1000;
	infos_new->start_time = ft_time(infos_new->start_time_second);
	while (1)
	{
		if(x == infos_new->times.food_x && infos_new->times.food_x != 0)
		{
			end(infos_new);
			usleep(1000);
			return("ola mudn");
		}
		if(*(infos_new->i_end) == 0)
		{
			printf("dead\n");
			return("oi");
		}
		time = ft_food(infos_new,infos,time);
		if(time < 0)
		{
			printf("dead\n");
			end(infos_new);
			return("oi");
		}else
			time = infos_new->times.death;
		if(*(infos_new->i_end)== 0)
		{
			printf("dead\n");
			return("oi");
		}
		time = ft_sleep(infos_new,time);
		if(time < 0)
		{
			printf("dead\n");
			end(infos_new);
			return("oi");
		}
		x++;
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
				infus->end = 0;
				return("ola");
			}
			pthread_mutex_unlock(&infus2[i].death);
		}	
	}
	return("oi");
}
