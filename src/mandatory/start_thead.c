/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:23:05 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/30 17:36:19 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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

s_ThreadData *alloc_dat(s_times times)
{
	s_ThreadData data;
	s_ThreadData *dat_thead;
	
	int i;

	dat_thead = (s_ThreadData *)malloc(times.philosophers *sizeof(s_ThreadData));
	if(dat_thead == NULL)
		return(NULL);
	i = -1;
	data.times = times;
	while(++i < times.philosophers)
	{
		dat_thead[i].times = times;
		dat_thead[i].name = i;
		dat_thead[i] = copy_data(data,i);
	}
	return(dat_thead);
}

void trhed_start(pthread_t* therds,s_loco infos,s_times times)
{
	s_new *env;
	pthread_mutex_t death;
	s_new_fuck fuck;
	int i;
	int tem;
	
	pthread_mutex_init(&death,NULL);
	i = -1;
	(void)infos;
	env = (s_new *)malloc( times.philosophers * sizeof(s_new));
	if(env == NULL)
		return;
	tem = true;
	while(++i < times.philosophers)
	{
		
		env[i].start = i;
		env[i].death = death;
		env[i].times = times;
 		fuck.pq = i;
		fuck.end = 0;
		fuck.fuck= &env[i];
		pthread_create(&therds[i],NULL,thead,&fuck);
	}
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

void filof(s_times  times)
{
	s_loco infos;
	pthread_t *therds;
	
	
	pthread_mutex_init(&infos.death,NULL);
	infos.mutex = ft_alloc_mutex(times.philosophers-1);
	if(infos.mutex == NULL)
		return ;
	therds = trhed_criate(times);
	if(therds == NULL )
	{
		free(infos.mutex);
		return;
	}
	trhed_start(therds,infos,times);
	// int i;

	// i = -1;
	// while (++i < times.philosophers)
	// {
	// 	pthread_join(therds[i],NULL);
	// }
	trhed_sleep(times.philosophers,therds);
	free(therds);
	//ft_free_mutex(infos.mutex,times.philosophers);
}
