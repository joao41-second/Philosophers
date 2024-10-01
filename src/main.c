/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:43:30 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/24 17:07:40 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_times	set_philosophert_times(char **time, int temp)
{
	t_times	times;

	times.philosophers = ft_atol(time[0]);
	times.death = ft_atol(time[1]);
	times.food = ft_atol(time[2]);
	times.sleep = ft_atol(time[3]);
	times.food_x = temp;
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
		if (ft_atol(time[0]) >= 201)
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

int	save(t_new_philo *infos, t_new *infot_new)
{
	if ((infot_new->dead_time - ((get_time(infos) - infot_new->start_time)
				- (infot_new->time_reste))) < 0)
		return (FASLE);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_times			times;
	int				temp;
	struct timeval	tv;

	if (ac == 5)
		temp = 0;
	else if (ac == 6)
	{
		temp = ft_atol(av[5]);
		if (temp > 0)
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
		times = set_philosophert_times(av, temp);
		filof(times);
		return (0);
	}
	printf("erro\n");
}
