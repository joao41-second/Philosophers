/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/23 13:22:56 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int end(s_new infos_new,s_new_fuck *infos,int neg)
{
	pthread_mutex_lock(&infos->mens);
	infos->fuck->im = fasle;
	pthread_mutex_unlock(&infos->mens);
	print(infos,"dead",&infos_new,(ft_time(infos_new.start_time_second)-infos_new.start_time)+(neg+1));
	return(fasle);
}

int chek_end( s_new_fuck *infos)
{

		pthread_mutex_lock(&infos->mens);
		if(*infos->fuck->i_end == fasle)
		{
			pthread_mutex_unlock(&infos->mens);
			return(fasle);
		}
		pthread_mutex_unlock(&infos->mens);
	return(true);
}

void print(s_new_fuck *infos,char *mens, s_new *infos_new ,int time)
{
	//printf("muita raiva %d\n",*infos->fuck->set);
	static int  hp =0;
	pthread_mutex_lock(&infos->mens);
	if(hp == 0){
	if(*infos->fuck->i_end != 0)
	{
		ft_printf("%d %d %s\n",time,infos_new->start,mens);
	}else 
	 hp = 1;
	if(mens[0] == 'd')
	 hp =1;
	}
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
	pthread_mutex_lock(&infos->mens);
	if(*infos->fuck->i_end == fasle)
	{
		pthread_mutex_unlock(&infos->mens);
		return(fasle);
	}
	pthread_mutex_unlock(&infos->mens);
	if(infos){}
	print(infos,"has taken a fork",infos_new,ft_time(infos_new->start_time_second)-infos_new->start_time);
	return(true);
}

int pair_fork( s_new_fuck *infos,s_new *infos_new,s_forks forks,pthread_mutex_t *fork)
{
	pthread_mutex_lock(&infos->mens);
	if(*infos->fuck->i_end == fasle)
	{
		pthread_mutex_unlock(&infos->mens);
		return(fasle);
	}
	pthread_mutex_unlock(&infos->mens);

	if(print_forks(infos,infos_new,fork,forks.fork[1]) == fasle)
	{
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		return(fasle);
	}
	if(print_forks(infos,infos_new,fork,forks.fork[0]) == fasle)
	{
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		return(fasle);
	}
	return(true);
}
int odd_fork(s_new_fuck *infos,s_new *infos_new,s_forks forks,pthread_mutex_t *fork)
{
	usleep(100);
	pthread_mutex_lock(&infos->mens);
	if(*infos->fuck->i_end == fasle)
	{
		pthread_mutex_unlock(&infos->mens);
		return(fasle);
	}
	pthread_mutex_unlock(&infos->mens);
	if(print_forks(infos,infos_new,fork,forks.fork[0]) == fasle)
	{
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		return(fasle);
	}
	if(print_forks(infos,infos_new,fork,forks.fork[1]) == fasle)
	{
		pthread_mutex_unlock(&fork[forks.fork[0]]);
		pthread_mutex_unlock(&fork[forks.fork[1]]);
		return(fasle);
	}
	return(true);	
}

int forks(s_new *infos_new,s_new_fuck *infos, s_forks forks)
{
	int save = 0;
	pthread_mutex_t *fork;
	static int temp = 0;

	fork = infos->fork;
	(void)infos_new;
	save = par(infos_new->start);
	if(infos_new->times.philosophers  %2 != 0 && infos_new->start == infos_new->times.philosophers -2 && temp == 0)
	{
		usleep(1500);
	}
	if(save == 0)
	{
		if(pair_fork(infos,infos_new,forks,fork) == fasle)
			return(fasle);
	}
	else
	{
		if(odd_fork(infos,infos_new,forks,fork) == fasle)
			return(fasle);
	}
	return(true);
}

int ft_food( s_new *infos_new,s_new_fuck *infos,int time)
{
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
	if(chek_end(infos) == fasle)
		return(-1);
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
	if(chek_end(infos) == fasle || time - (ft_time(infos_new->start_time_second)-infos_new->start_time - start_time) < 0)
	{
		return(fasle);
	}
	print(infos,"is thinking",infos_new,(ft_time(infos_new->start_time_second)-infos_new->start_time));
	return(time - (ft_time(infos_new->start_time_second)-infos_new->start_time - start_time));
}

s_new copy_struct(s_new *infos_new,int im)
{
	s_new copy;
	copy.i_end = infos_new->i_end;
	copy.start = im;
	copy.start_time = infos_new->start_time;
	copy.start_time_second = infos_new->start_time_second;
	copy.times = infos_new->times;
	return(copy);
}

int thead_run(s_new infos_new, s_new_fuck *infos, int time , int x)
{
	while (1)
	{
	if(x == infos_new.times.food_x && infos_new.times.food_x != 0)
		end(infos_new,infos,time);
	pthread_mutex_lock(&infos->mens);
	int temp = *infos->fuck->i_end;
	pthread_mutex_unlock(&infos->mens);
	if( temp == 0)
		return(fasle);
	time = ft_food(&infos_new,infos,time);
	if(chek_end(infos) == fasle)
		return(fasle);
	if(time < 0)
		return(end(infos_new,infos,time));
	else
		time = infos_new.times.death;
	usleep(1000);
	time = ft_sleep(&infos_new,time,infos);
	if(chek_end(infos) == fasle)
		return(fasle);
	if(time < 0)
		return(end(infos_new,infos,time));
	x++;
	}
	return(true);
}
void thead_sleep(s_new_fuck *infos)
{
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(&infos->mens);
		int temp = *infos->fuck->i_end;
		pthread_mutex_unlock(&infos->mens);
		if( temp == 2)
		{
			break;
		}
	}
	
}

void *thead(void *infs)
{
	s_new_fuck * infos;
	s_new * infos_news;
	s_new infos_new;
	struct timeval tv;
	s_ints ints;
	
	infos = (s_new_fuck*)infs;
	ints.fil_n = infos->fuck->start;
	ints.x = 0;
	thead_sleep(infos);
	pthread_mutex_lock(&infos->mens);
	infos_news = (s_new*)infos->fuck;
	infos_new = copy_struct(infos_news,ints.fil_n); 
	ints.time = infos->fuck->times.death;
	pthread_mutex_unlock(&infos->mens);
	gettimeofday(&tv, NULL);
	infos_new.start_time_second = tv.tv_sec * 1000;
	infos_new.start_time = ft_time(infos_new.start_time_second);
	thead_run(infos_new,infos, ints.time,ints.x);
	return("oi");
}

int bar_run(s_new_fuck *infus,s_new *infus2,int i , int nb)
{
		while (++i < nb-1)
		{	
			usleep(25);
			
			pthread_mutex_lock(&infus->mens);
			if(infus2->im == fasle)
			{
				i = -5;
			}
		    pthread_mutex_unlock(&infus->mens);
			if( i == -5)
			{
				pthread_mutex_lock(&infus->mens);
				*infus->fuck->i_end = 0;
				pthread_mutex_unlock(&infus->mens);
				return(fasle);
			}
				pthread_mutex_lock(&infus->mens);
			infus2--;
				pthread_mutex_unlock(&infus->mens);
		}
		pthread_mutex_lock(&infus->mens);
		infus2 += nb-1;
		pthread_mutex_unlock(&infus->mens);
		return(true);
}

void *bar_men_thead(void *infs)
{
	s_new_fuck * infus;
	s_new *infus2;
	int nb ;
	int i;

	infus = (s_new_fuck *)infs;
	nb =infus->philo;
	pthread_mutex_lock(&infus->mens);
	*infus->fuck->i_end = 2;
	pthread_mutex_unlock(&infus->mens);
	infus2 = (s_new *)infus->fuck;
	if(nb == 1)
	{
		nb++;
	}
	while (1)
	{
		i = -1;
		if(bar_run(infs,infus2,i,nb) == fasle)
		{
			break;
		}	
	}
	return("oi");
}
