/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:23:05 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/12 14:44:06 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


void bar_start(s_new_fuck env)
{
	pthread_t bar_men;
	pthread_create(&bar_men,NULL,bar_men_thead,&env);
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
	pthread_mutex_t death;
	s_new_fuck fuck;
	int i;
	
	pthread_mutex_init(&death,NULL);
	pthread_mutex_init(&(fuck.mens),NULL);
	i = -1;
	(void)infos;
	env = (s_new *)malloc( times.philosophers * sizeof(s_new));
	if(env == NULL)
		return;
	fuck.fork = infos.mutex;
	while(++i < times.philosophers)
	{
		env[i].start = i;
		env[i].im = i;
		env[i].death = death;
		env[i].times = times;
 		fuck.pq = i;
		fuck.end = 1;
		fuck.fuck= &env[i];
		env[i].i_end = &fuck.end;
		usleep(9000);
		pthread_create(&therds[i],NULL,thead,&fuck);
		
	}
	fuck.fuck= &env[0];
	bar_start(fuck);
	fuck.end = 0;
	trhed_sleep(times.philosophers,therds);
	pthread_mutex_destroy(&death);
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
