/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/17 16:23:34 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void end(s_new *infos_new,s_new_fuck *infos)
{
	 pthread_mutex_lock(&infos_new->death);
	 if(infos){};
	 infos_new->im = -1;
	 pthread_mutex_unlock(&infos_new->death);
}

void print(s_new_fuck *infos,char *mens, s_new *infos_new ,int time)
{
	//printf("muita raiva %d\n",*infos->fuck->set);
	pthread_mutex_lock(&infos->mens);
	pthread_mutex_lock(&infos->fuck->death);
	if(infos->fuck->im != -1 )
	printf("%d %d %s\n",time,infos_new->start,mens);
	pthread_mutex_unlock(&infos->fuck->death);
	pthread_mutex_unlock(&infos->mens);
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

int print_forks(s_new_fuck *infos,s_new *infos_new,pthread_mutex_t *fork,int mut)
{
	pthread_mutex_lock(&fork[mut]); 
	if(*infos_new->i_end == fasle)
	{
		return(fasle);
	};
	if(infos){}
	print(infos,"has taken a fork",infos_new,ft_time(infos_new->start_time_second)-infos_new->start_time);
	return(true);
}

int forks(s_new *infos_new,s_new_fuck *infos, s_forks forks)
{
	int save = 0;
	pthread_mutex_t *fork;
	static int temp = 0;
	int i;

	i = 2;
	fork = infos->fork;
	(void)infos_new;
	save = par(infos_new->start);
	if(infos_new->times.philosophers  %2 != 0 && infos_new->start == infos_new->times.philosophers -2 && temp == 0)
	{
		//temp++;
		usleep(1000);
		//save = 0;
	}
	if(save == 0)
	{
		if(*infos_new->i_end == fasle)
		{
			return(fasle);
		}
		if(print_forks(infos,infos_new,fork,forks.fork[1]) == fasle)
		{
			pthread_mutex_unlock(&fork[forks.fork[1]]);
			return(fasle);
		}
		if(print_forks(infos,infos_new,fork,forks.fork[0]) == fasle)
		{
			pthread_mutex_unlock(&fork[forks.fork[1]]);
			pthread_mutex_unlock(&fork[forks.fork[0]]);
			printf("end\n");
			return(fasle);
		}
	}
	else
	{
		usleep(200);
		if(*infos_new->i_end == fasle)
		{
			return(fasle);
		}
		
		if(print_forks(infos,infos_new,fork,forks.fork[0]) == fasle)
		{
			pthread_mutex_unlock(&fork[forks.fork[0]]);
			printf("end\n");
			return(fasle);
		}
	
		if(print_forks(infos,infos_new,fork,forks.fork[1]) == fasle)
		{
			pthread_mutex_unlock(&fork[forks.fork[0]]);
			pthread_mutex_unlock(&fork[forks.fork[1]]);
			printf("end\n");
			return(fasle);
		}
		
	}
	return(true);
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
	if (forks(infos_new,infos,forkss) == fasle)
		return(fasle);
	time_temp = ft_time(infos_new->start_time_second)-infos_new->start_time;
	if(time - (time_temp-start_time) < 0)
	{
		pthread_mutex_unlock(&fork[forkss.fork[1]]);
		pthread_mutex_unlock(&fork[forkss.fork[0]]);
		return(time - (time_temp-start_time));
	}
	print(infos,"is eating",infos_new,ft_time(infos_new->start_time_second)-infos_new->start_time);
	usleep(infos_new->times.food *1000);
	pthread_mutex_unlock(&fork[forkss.fork[1]]);
	pthread_mutex_unlock(&fork[forkss.fork[0]]);
	time_temp = ft_time(infos_new->start_time_second)-infos_new->start_time;
	return(time - (time_temp-start_time));
}

int ft_sleep(s_new *infos_new,int time,s_new_fuck *infos)
{
	int start_time;
	start_time = ft_time(infos_new->start_time_second)-infos_new->start_time;
	if(infos_new->i_end == 0)
		return(-1);
	print(infos,"is sleeping",infos_new,ft_time(infos_new->start_time_second)-infos_new->start_time);
	// printf("%d %d is sleeping\n",ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);
	
	if(infos_new->times.food < infos_new->times.death)
		usleep(infos_new->times.food *1000);
	else
	{
		usleep((infos_new->times.food - infos_new->times.death)*1000);
		return(-1);
	}

	print(infos,"is thinking",infos_new,ft_time(infos_new->start_time_second)-infos_new->start_time);
	//printf("%d %d is thinking\n",ft_time(infos_new->start_time_second)-infos_new->start_time,infos_new->start);a
	return(time - (ft_time(infos_new->start_time_second)-infos_new->start_time - start_time));
}

s_new copy_struct(s_new *infos_new)
{
s_new copy;
	//copy.death = infos_new->death;
	copy.i_end = infos_new->i_end;
	//copy.im = infos_new->im;
	copy.start = infos_new->start;
	copy.start_time = infos_new->start_time;
	copy.start_time_second = infos_new->start_time_second;
	copy.times = infos_new->times;
	return(copy);
}


void *thead(void *infs)
{
	usleep(1000);
	s_new_fuck * infos;
	s_new * infos_news;
	s_new infos_new;
	struct timeval tv;
	int time;
	int x;
	int fil_n;
	 
	
	infos = (s_new_fuck*)infs;
	pthread_mutex_lock(&infos->mens);
	infos_news = (s_new*)infos->fuck;
	infos_new = copy_struct(infos_news); 
	time = infos_news->times.death;
	pthread_mutex_unlock(&infos->mens);
	
	x = 0;

	fil_n = infos_new.times.philosophers-1;

	
	while (infos->pq <fil_n)
	{}
	
	gettimeofday(&tv, NULL);
	infos_new.start_time_second = tv.tv_sec * 1000;
	infos_new.start_time = ft_time(infos_new.start_time_second);
	while (1)
	{
		if(x == infos_new.times.food_x && infos_new.times.food_x != 0)
		{
			end(infos_news,infos);
			return("ola mudn");
		}
		
		if(infos_news->i_end == 0 )
		{
			end(infos_news,infos);
			return("oi");
			
		}
		time = ft_food(&infos_new,infos,time);
		usleep(1000);
		if(time < 0)
		{
			end(infos_news,infos);
			return("oi");
		}else
			time = infos_new.times.death;
		if(infos_news->i_end == 0 )
		{
			end(infos_news,infos);
			return("oi");
		}
		time = infos_new.times.death;
		time = ft_sleep(&infos_new,time,infos);
		
		if(time < 0)
		{
			end(infos_news,infos);
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
		i = -1;
		while (++i < nb)
		{
			//usleep(50);
			
			pthread_mutex_lock(&infus2->death);
			if(infus2[i].im == fasle)
			{
				infus->end = fasle;
				printf("dead\n");
				i = -1;
				infus->set = fasle;
				while (++i < nb)
				{
					infus2[i].im = fasle;
					infus2[i].i_end = 0;
				}
				return("ola");
			}
			pthread_mutex_unlock(&infus2->death);
			
		}
		return("ola");
	}
	return("oi");
}