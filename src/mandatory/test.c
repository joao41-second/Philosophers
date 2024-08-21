/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:11 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/21 16:17:35 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../philosophers.h"


// int comer( s_ThreadData *mute)
// {
// 	struct timeval tv;
// 	pthread_mutex_t *garfo =mute->mutex;
// 	int time;
// 	int start;
// 	int end;
// 	pthread_mutex_lock(&garfo[mute->name]);
// 	gettimeofday(&tv, NULL);	
// 	time = tv.tv_usec /1000;
// 	if(mute->name != 0)
// 		pthread_mutex_lock(&garfo[mute->name-1]);
// 	else
// 		pthread_mutex_lock(&garfo[mute->times.philosophers ]);

// 	gettimeofday(&tv, NULL);	
// 	start = tv.tv_usec /1000;
// 	//printf("eu  %d comesei a comer as %d\n",mute->name,start);
// 	usleep((mute->times.food)*1000);
// 	 pthread_mutex_unlock(&garfo[mute->name]);
// 	if(mute->name != 0)
// 	  pthread_mutex_unlock(&garfo[mute->name-1]);
// 	 else
// 	 	pthread_mutex_unlock(&garfo[mute->times.philosophers ]);
// 	gettimeofday(&tv, NULL);	
// 	end = tv.tv_usec /1000;
// 	//printf("eu %d acabei de comer as %d\n",mute->name,end);
// 	return(  start- time);
// }

int par (int n)
{
	if(n %2 == 0)
		return(true);
	return(fasle);	
}

 int comer( s_ThreadData *mute)
 {
	pthread_mutex_t *garfo =mute->mutex;
	struct timeval tv;
	int save;
	save = par(mute->name);
	if(save == 0)
	{
			pthread_mutex_lock(&garfo[mute->name]);
 		if(mute->name != 0)
	 		pthread_mutex_lock(&garfo[mute->name-1]);
 		else
	 		pthread_mutex_lock(&garfo[mute->times.philosophers ]);
	}
	else
	{
		usleep(1000);
			pthread_mutex_lock(&garfo[mute->name]);
 		if(mute->name != 0)
	 		pthread_mutex_lock(&garfo[mute->name-1]);
 		else
	 		pthread_mutex_lock(&garfo[mute->times.philosophers ]);
	}
	
	
	usleep((mute->times.food)*1000);
	gettimeofday(&tv, NULL);	
 	save = tv.tv_usec /1000;
	 pthread_mutex_unlock(&garfo[mute->name]);
	if(mute->name != 0)
	  pthread_mutex_unlock(&garfo[mute->name-1]);
	 else
	 	pthread_mutex_unlock(&garfo[mute->times.philosophers ]);
	return(save);
 }
 

int ft_sleep(s_ThreadData *mute)
{
	struct timeval tv;
	int time;
	gettimeofday(&tv, NULL);	
	time = tv.tv_usec /1000;
	printf("\n eu %d vou dromir\n",mute->name);
 	usleep(mute->times.sleep*1000);
	gettimeofday(&tv, NULL);	
	time =   tv.tv_usec /1000 - time;
	return(0);
}

void *therd(void * struc)
{
	s_ThreadData *mute;
	s_loco *mutes;
	s_ThreadData* loco;
	struct timeval tv;
	int neg_temp;
	int start;
	mutes = (s_loco *)struc;
	loco = (s_ThreadData *)mutes->loco;
	mute = (s_ThreadData* )mutes->norm;
	
	
	while(loco->name != mute->times.philosophers-1)
	 ;
	
	gettimeofday(&tv, NULL);	
	start = tv.tv_usec /1000;
	
	
	
	neg_temp = comer(mute);
	
	printf("\n eu %d demorei %d\n",mute->name, mute->times.death -( neg_temp - start));
	if(mute->times.death-( neg_temp - start) < 0)
	{
		printf("eu %d mori",mute->name);
		return("mori");
	}
	ft_sleep(mute);
	//printf("\n eu %d quero comer %d\n",mute->name, mute->times.death-neg_temp);
	 
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

	i = -1;

	 s_loco test;
	 
	while (++i < times.philosophers)
	{	
			data.name = i;
			temp[i] = copy_data(data,i);
			test.norm = &temp[i];
			test.loco = &data;
			pthread_create(&therds[i],NULL,therd,&test);
	}

	i = -1;
	while (++i < times.philosophers)
	{
		
		pthread_join(therds[i],NULL);
	}
	free(therds);
	ft_free_mutex(data,times.philosophers);
	
}
