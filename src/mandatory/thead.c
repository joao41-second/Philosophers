/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thead.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:08 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/30 17:35:50 by jperpect         ###   ########.fr       */
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
	printf("oi pausa\n");
	while (1)
	{
		printf("vou durmir\n");
		usleep(random_in_range(1, 100000));
		printf("vou acurdar\n");
		if(infos->end == 0)
		{
			printf("dead\n");
			return("oi");
		}
	}
	
	//printf("eu sou %d \n",*(infos->eu));
	

	return("oi");
}