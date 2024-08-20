/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:11 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/20 16:58:20 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../philosophers.h"


int comer( s_ThreadData *mute)
{
	struct timeval tv;
	pthread_mutex_t *garfo =mute->mutex;
	int time;
	int start;
	int end;
	pthread_mutex_lock(&garfo[mute->name]);
	gettimeofday(&tv, NULL);	
	time = tv.tv_usec /1000;
	if(mute->name != 0)
		pthread_mutex_lock(&garfo[mute->name-1]);
	else
		pthread_mutex_lock(&garfo[mute->times.philosophers ]);

	gettimeofday(&tv, NULL);	
	start = tv.tv_usec /1000;
	ft_printf("eu  %d comesei a comer as %d\n",mute->name,start);
	usleep((mute->times.food)*1000);
	 pthread_mutex_unlock(&garfo[mute->name]);
	if(mute->name != 0)
	  pthread_mutex_unlock(&garfo[mute->name-1]);
	 else
	 	pthread_mutex_unlock(&garfo[mute->times.philosophers ]);
	gettimeofday(&tv, NULL);	
	end = tv.tv_usec /1000;
	printf("eu %d acabei de comer as %d\n",mute->name,end);
	return( end- start);
}



void *therd(void * struc)
{
	s_ThreadData *mute;
	struct timeval tv;
	int neg_temp;
	int start;
	gettimeofday(&tv, NULL);	
	start = tv.tv_usec /1000;
	mute = (s_ThreadData *)struc;
	printf("a espera para comer %d\n",mute->name);
	
	neg_temp = comer(mute);
	printf("\ndemorei %d\n", mute->times.death-neg_temp);
	//-printf("eu tanho um grafo %d\n",mute->name);
	 
	return("ola");
}

s_ThreadData copy_data(s_ThreadData data,int i) 
{
	s_ThreadData copy_data;
	copy_data.mutex = data.mutex;
	copy_data.times = data.times;
	copy_data.name = i;
	return(copy_data);
		
}


void filof(s_times  times)
{

	s_ThreadData data;
	s_ThreadData *temp;
	pthread_t *therds;
	int i;

	i = -1;
	data =ft_alloc_mutex(times.philosophers);
	therds = (pthread_t *)malloc(times.philosophers * sizeof(pthread_t));
	temp = (s_ThreadData *)malloc(times.philosophers *sizeof(s_ThreadData));
	data.times = times;
	while (++i < times.philosophers)
	{
		
		
		temp[i] = copy_data(data,i);
	//	pthread_create(&therds[i],NULL,therd,&temp);
	}
	i = -1;
	while (++i < times.philosophers)
	{
		pthread_create(&therds[i],NULL,therd,&temp[i]);
	}
	i = -1;
	while (++i < times.philosophers)
	{
		pthread_join(therds[i],NULL);
	}
	free(therds);
	ft_free_mutex(data,times.philosophers);
	
}
