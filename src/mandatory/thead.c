/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/02 15:04:20 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int random_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

void *thead(void *infs)
{
	if(infs){}
	s_new_fuck * infos;
	s_new * infos_new;
	
	infos = (s_new_fuck*)infs;
	
	infos_new = (s_new*)infos->fuck;
	while (infos->pq < infos_new->times.philosophers-1)
	{
	}


	usleep(10000);

	printf("eu sou %d \n",infos_new->start);
//m	printf("pthread_mutex_lock(&infos_new->death);oi pauunsa\n");
	
	
	while (1)
	{
		if(infos->end == 0)
		{
			printf("dead\n");
			return("oi");
		}
		usleep(random_in_range(1, 100000));
		if(random_in_range(1, 100) == 99)
		{
			printf("eu matie\n");
			pthread_mutex_lock(&infos_new->death);
			infos_new->start = -1;	
			pthread_mutex_unlock(&infos_new->death);
		}
	
	}
	
	//printf("eu sou %d \n",*(infos->eu));
	

	return("oi");
}

void *bar_men_thead(void *infs)
{
	s_new_fuck * infus;
	s_new *infus2;

	infus = (s_new_fuck *)infs;
	infus2 = (s_new *)infus->fuck;

	printf("ola %d\n",infus2[1].start);
	int nb ;
	pthread_mutex_lock(&infus2->death);
	nb = infus2->times.philosophers;
	pthread_mutex_unlock(&infus2->death);
	while (1)
	{
		int i;
		i = 0;
		while (++i < nb-1)
		{
			pthread_mutex_lock(&infus2[i].death);
			if(infus2[i].start == -1)
			{
				return("ola");
			}
			pthread_mutex_unlock(&infus2[i].death);
		
		}
		
	}
	
	
	return("oi");

}