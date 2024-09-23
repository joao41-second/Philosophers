/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:43:30 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/23 13:25:39 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"




s_times set_philosophers_times(char **time)
{
	s_times times;
	times.philosophers = ft_atol(time[0]);
	times.death = ft_atol(time[1]);
	times.food = ft_atol(time[2]);
	times.sleep = ft_atol(time[3]);
	return(times);
}
int cheke_philosophrs_times(char **time,int max)
{
	int i;
	
	i = -1;
	while (++i < max-1)
	{
		if(ft_atol(time[i]) <= 0)
		{
			return(fasle);
		}
	}
	return(true);
}

int	main(int ac, char **av)
{
	s_times times;
	struct timeval tv;
	
	 if (ac == 5)
	 {
		
		if(cheke_philosophrs_times(++av,ac) == fasle)
		{
			 printf("erro\n");
			 return(0);
		}
		gettimeofday(&tv, NULL);
		 times = set_philosophers_times(av);
		 times.food_x = 0 ;
		gettimeofday(&tv, NULL);
		filof(times);
		
	 }else  if (ac == 6)
	 {
		
		if(cheke_philosophrs_times(++av,ac) == fasle)
		{
			 printf("erro\n");
			 return(0);
		}
		gettimeofday(&tv, NULL);
		times = set_philosophers_times(av);
		times.food_x = ft_atol(av[4]) ;
		gettimeofday(&tv, NULL);
		filof(times);
		
	 }
	 else
	 printf("erro\n");
}
