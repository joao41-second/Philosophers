/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:45:15 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/04 10:23:41 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../philosophers.h"

pthread_mutex_t  *ft_alloc_mutex(int philosop)
{
	pthread_mutex_t  *data;
	int i;
	
	i = -1;
	data = ( pthread_mutex_t*)malloc( philosop * sizeof(pthread_mutex_t));
	if(data == NULL)
		return(NULL);
	while (++i < philosop)
	{
		pthread_mutex_init(&(data[i]),NULL);
	}
	printf("tenho x motex %d \n",i);
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

void ft_free_mutex(pthread_mutex_t *data,int philo)
{
	
	int i;
	pthread_mutex_t *fre;
	i = -1;
	
	while (++i < philo)
	{
		fre =  &data[i];
		pthread_mutex_destroy(fre);
	
	}
		free(data);
		
}