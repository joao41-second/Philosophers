/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:11 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/28 15:54:52 by jperpect         ###   ########.fr       */
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
// 	usleep((mute->times. (time()-mute->time_start))*1000);
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

int ft_time(int second)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);	
	return( tv.tv_usec /1000 + (tv.tv_sec-second)*1000);
}


 int comer( s_ThreadData *mute  )
 {
	pthread_mutex_t *garfo =mute->mutex;
	int save;
	int start;
	int temp;

 	start = ft_time(mute->start_second_time);

	save = par(mute->name);
	if(save == 0)
	{
		pthread_mutex_lock(&garfo[mute->name]);
		temp = ft_time(mute->start_second_time)-mute->time_start ;
		printf("%d %d has taken a right fork\n", temp,mute->name);
 		if(mute->name != 0)
	 		pthread_mutex_lock(&garfo[mute->name-1]);
 		else
	 		pthread_mutex_lock(&garfo[mute->times.philosophers ]);
		temp = ft_time(mute->start_second_time)-mute->time_start ;
		printf("%d %d has taken a left fork\n", temp,mute->name);
	}
	else
	{
		usleep(100);
 		if(mute->name != 0)
	 		pthread_mutex_lock(&garfo[mute->name-1]);
 		else
	 		pthread_mutex_lock(&garfo[mute->times.philosophers ]);
		temp = ft_time(mute->start_second_time)-mute->time_start ;
		printf("%d %d has taken a left fork\n", temp,mute->name);
		pthread_mutex_lock(&garfo[mute->name]);
		temp = ft_time(mute->start_second_time)-mute->time_start ;
		printf("%d %d has taken a right fork\n", temp,mute->name);
	}

	
	save = ft_time(mute->start_second_time);
		 temp = ft_time(mute->start_second_time)-mute->time_start;
		printf("%d %d is eating\n", temp,mute->name);
		usleep((mute->times.food)*1000);
		
	save =ft_time(mute->start_second_time);
	printf("%d %d is sleeping\n",save - mute->time_start,mute->name);

	if(save == 0)
	{
		pthread_mutex_unlock(&garfo[mute->name]);
		if(mute->name != 0)
		pthread_mutex_unlock(&garfo[mute->name-1]);
		else
		pthread_mutex_unlock(&garfo[mute->times.philosophers ]);
	}
	else
		if(mute->name != 0)
		pthread_mutex_unlock(&garfo[mute->name-1]);
		else
		pthread_mutex_unlock(&garfo[mute->times.philosophers ]);
		pthread_mutex_unlock(&garfo[mute->name]);
	
	return(save);
 }
 
 

int ft_sleep(s_ThreadData *mute)
{
 	usleep(mute->times.sleep*1000);
	return(0);
}

void *therd(void * struc)
{
	s_ThreadData *mute;
	s_loco *mutes;
	s_ThreadData* loco;
	
	
	int n_food;
	int max;
	int neg_temp;
	int start;
	
	n_food = 0;
	
	mutes = (s_loco *)struc;
	loco = (s_ThreadData *)mutes->loco;
	mute = (s_ThreadData* )mutes->norm;
	mute->stay_or_life = true;
	max = mute->times.food_x;
	
	while(loco->name != mute->times.philosophers-1)
	 ;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	mute->start_second_time = tv.tv_sec *1000;
	start = ft_time(mute->start_second_time);	
	mute->time_start = start;
	
	while(1)
	{
	if(max < n_food && n_food != 0)
	{
		mute->stay_or_life = fasle;
		return("mori");
	}
	pthread_mutex_lock(&mutes->death);  

	if(mutes->livfe == fasle)
	{
		printf("%d %d died\n ",(ft_time(mute->start_second_time)-mute->time_start),mute->name);
		return("mori");
	}
	pthread_mutex_unlock(&mutes->death);  

	start = ft_time(mute->start_second_time);
	neg_temp = comer(mute);
	n_food++;
	if(mute->times.death-( neg_temp - start) < 0)
	{
		printf("%d %d died\n",(ft_time(mute->start_second_time)-mute->time_start),mute->name);
		return("mori");
	}

	ft_sleep(mute);
	if(mute->times.death-  mute->times.sleep< 0)
	{
		printf("%d %d died\n ",(ft_time(mute->start_second_time)-mute->time_start),mute->name);
		return("mori");
	}
	printf("%d %d is thinking\n", (ft_time(mute->start_second_time)-mute->time_start),mute->name);
	usleep(1000);
	}
	 
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



void* bar_men(void * struc)
{
	
	s_ThreadData *mute;
	s_loco *mutes;
	int i;
	i = -1;
	mutes = (s_loco *)struc;
	mute = (s_ThreadData* )mutes->norm;
	pthread_mutex_lock(&mutes->death);
	mutes->livfe = true;
	
	while(++i < mute->times.philosophers)
	{
		if(mute[i].stay_or_life == fasle)
		{
			
			mutes->livfe = fasle;
		
		}
	}
		pthread_mutex_unlock(&mutes->death);
	return("ola");
}



void filof(s_times  times)
{
	s_ThreadData data;
	s_ThreadData *temp;
	
	pthread_t *therds;
	pthread_t bar;
	int i;

	i = -1;
	data =ft_alloc_mutex(times.philosophers);
	therds = (pthread_t *)malloc(times.philosophers * sizeof(pthread_t));
	temp = (s_ThreadData *)malloc(times.philosophers *sizeof(s_ThreadData));
	data.times = times;

	i = -1;

	 s_loco test;
		
	pthread_mutex_init(&(test.death),NULL);

	while (++i < times.philosophers)
	{	
			data.name = i;
			temp[i] = copy_data(data,i);
			test.norm = &temp[i];
			test.loco = &data;
			pthread_create(&therds[i],NULL,therd,&test);
	}
	i++;
	//printf("eu sou %d\n",i);
	data.name = i;
			temp[i] = copy_data(data,i);
			test.norm = &temp[i];
			test.loco = &data;
	pthread_create(&bar,NULL,bar_men,&test);

	i = -1;
	while (++i < times.philosophers)
	{	
		pthread_join(therds[i],NULL);
	}
	pthread_join(bar,NULL);
	free(therds);
	ft_free_mutex(data,times.philosophers);
	
}
