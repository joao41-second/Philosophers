/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:43:30 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/24 10:57:54 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_times	set_philosophert_times(char **time)
{
	t_times	times;

	times.philosophers = ft_atol(time[0]);
	times.death = ft_atol(time[1]);
	times.food = ft_atol(time[2]);
	times.sleep = ft_atol(time[3]);
	return (times);
}

int	cheke_philosophrt_times(char **time, int max)
{
	int	i;

	i = -1;
	while (++i < max - 1)
	{
		if (ft_atol(time[i]) <= 0)
		{
			return (FASLE);
		}
	}
	i = 0;
	while (++i < max - 1)
	{
		if (ft_atol(time[i]) < 60)
		{
			return (FASLE);
		}
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_times			times;
	struct timeval	tv;

	if (ac == 5)
		times.food_x = 0;
	else if (ac == 6)
	{
		times.food_x = ft_atol(av[4]);
		ac--;
	}
	if (ac == 5)
	{
		if (cheke_philosophrt_times(++av, ac) == FASLE)
		{
			printf("erro\n");
			return (0);
		}
		gettimeofday(&tv, NULL);
		times = set_philosophert_times(av);
		times.food_x = 0;
		gettimeofday(&tv, NULL);
		filof(times);
		return (0);
	}
	printf("erro\n");
}
