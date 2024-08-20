/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:45:15 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/20 14:03:05 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../philosophers.h"

s_ThreadData ft_alloc_mutex(int philosop)
{
	s_ThreadData data;
	int i;
	
	i = -1;
	data.mutex = ( pthread_mutex_t*)malloc( philosop * sizeof(pthread_mutex_t));
	while (++i < philosop)
	{
		pthread_mutex_init(&(data.mutex[i]),NULL);
	}
//	data[i].mutex = NULL;
	//printf("%d\n",i);
	
	
	return(data);
}


// s_ThreadData ft_alloc_mutex(int philosop)
// {
// 	s_ThreadData data;
// 	int i;
	
// 	i = -1;
// 	data.mutex = ( pthread_mutex_t*)malloc( philosop * sizeof(pthread_mutex_t));
// 	while (++i < philosop)
// 	{
// 		pthread_mutex_init(&(data.mutex[i]),NULL);
// 	}
	
// 	return(data);
// }

void ft_free_mutex(s_ThreadData data,int philo)
{
	
	int i;
	pthread_mutex_t *fre;
	i = -1;
	
	while (++i < philo)
	{
		fre =  &data.mutex[i];
		pthread_mutex_destroy(fre);
	
	}
		free(data.mutex);
		
}