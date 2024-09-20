/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:23:05 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/20 10:26:01 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


void bar_start(s_new_fuck env)
{
	pthread_t bar_men;
	pthread_create(&bar_men,NULL,bar_men_thead,&env);
	env.set =fasle;
	pthread_join(bar_men,NULL);
	
	
}

s_ThreadData copy_data(s_ThreadData data,int i) 
{
	s_ThreadData copy_data;
	copy_data.times = data.times;
	copy_data.name = i;
	return(copy_data);
		
}

pthread_t *trhed_criate(s_times times)
{
	pthread_t *therds;
	therds = (pthread_t *)malloc(times.philosophers * sizeof(pthread_t));
	if(therds == NULL)
		return(NULL);
	return(therds);
}
void trhed_sleep(int cont,pthread_t* therds)
{
	int i;
	i = -1;
	while (++i < cont)
	{
		pthread_join(therds[i],NULL);
	}
	
}

void  trhed_start(pthread_t* therds,s_loco infos,s_times times)
{
	s_new *env;

	s_new_fuck fuck;
	int i;
	
	pthread_mutex_init(&(fuck.death),NULL);
	pthread_mutex_init(&(fuck.mens),NULL);
	i = -1;
	(void)infos;
	env = (s_new *)malloc( times.philosophers * sizeof(s_new));
	if(env == NULL)
		return;

	fuck.end = 1;

	while(++i < times.philosophers)
	{
		env[i].start = i;
		env[i].im = i;
		env[i].times = times;
 		fuck.pq = i;
		fuck.set = true;
		fuck.end = 1;
		fuck.fuck= &env[i];
		fuck.fork = infos.mutex;
		fuck.philo = times.philosophers-1;
		env[i].i_end = &fuck.end;
	}
	i = -1;
	while(++i < times.philosophers)
	{
		usleep(15000);
		pthread_mutex_lock(&fuck.mens);
		fuck.fuck= &env[i];
		pthread_mutex_unlock(&fuck.mens);

		pthread_create(&therds[i],NULL,thead,&fuck);
	//	printf("oi\n");
	}
	pthread_t bar_men;	
	pthread_mutex_lock(&fuck.mens);
	pthread_mutex_unlock(&fuck.mens);
	
	
	pthread_create(&bar_men,NULL,bar_men_thead,&fuck);
	fuck.set =fasle;
	pthread_join(bar_men,NULL);




	//printf("merda\n");
	trhed_sleep(times.philosophers,therds);
	pthread_mutex_destroy(&fuck.death);
	pthread_mutex_destroy(&(fuck.mens));
	free(env);
	return;
}




void filof(s_times  times)
{
	s_loco infos;
	pthread_t *therds;		
	pthread_mutex_init(&infos.death,NULL);
	infos.mutex = ft_alloc_mutex(times.philosophers);
	if(infos.mutex == NULL)
		return ;
	therds = trhed_criate(times);
	if(therds == NULL )
	{
		free(infos.mutex);
		return;
	}
	trhed_start(therds,infos,times);

	free(therds);
	ft_free_mutex(infos.mutex,times.philosophers);
	//pthread_mutex_destroy(&dead);
}
