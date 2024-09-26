/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:23:05 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/26 11:58:48 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

pthread_t	*trhed_criate(t_times times)
{
	pthread_t	*therds;

	therds = (pthread_t *)malloc(times.philosophers * sizeof(pthread_t));
	if (therds == NULL)
		return (NULL);
	return (therds);
}

void	trhed_sleep(int cont, pthread_t *therds)
{
	int	i;

	i = -1;
	while (++i < cont)
	{
		pthread_join(therds[i], NULL);
	}
}

t_new	*set_philo_data(t_times times, t_new_philo *fuck,
pthread_mutex_t *mutex)
{
	int		i;
	t_new	*env;

	pthread_mutex_init(&(fuck->death), NULL);
	pthread_mutex_init(&(fuck->mens), NULL);
	i = -1;
	env = (t_new *)malloc(times.philosophers * sizeof(t_new));
	if (env == NULL)
		return (NULL);
	while (++i < times.philosophers)
	{
		env[i].start = i;
		env[i].im = i;
		env[i].times = times;
		fuck->pq = i;
		fuck->set = TRUE;
		fuck->end = 1;
		fuck->time = 0;
		fuck->fuck = &env[i];
		fuck->fork = mutex;
		fuck->philo = times.philosophers - 1;
		env[i].i_end = &fuck->end;
		env[i].i_time = &fuck->time;
	}
	return (env);
}

void	trhed_start(pthread_t *therds, pthread_mutex_t *mutex, t_times times)
{
	t_new		*env;
	t_new_philo	fuck;
	int			i;
	pthread_t	bar_men;

	i = -1;
	env = set_philo_data(times, &fuck, mutex);
	while (++i < times.philosophers)
	{
		usleep(25000);
		pthread_mutex_lock(&fuck.mens);
		fuck.fuck = &env[i];
		pthread_mutex_unlock(&fuck.mens);
		pthread_create(&therds[i], NULL, thead, &fuck);
	}
	pthread_mutex_lock(&fuck.mens);
	pthread_mutex_unlock(&fuck.mens);
	pthread_create(&bar_men, NULL, bar_men_thead, &fuck);
	fuck.set = FASLE;
	pthread_join(bar_men, NULL);
	trhed_sleep(times.philosophers, therds);
	pthread_mutex_destroy(&fuck.death);
	pthread_mutex_destroy(&(fuck.mens));
	free(env);
	return ;
}

void	filof(t_times times)
{
	pthread_t		*therds;
	pthread_mutex_t	*mutex;

	mutex = ft_alloc_mutex(times.philosophers);
	if (mutex == NULL)
		return ;
	therds = trhed_criate(times);
	if (therds == NULL)
	{
		free(mutex);
		return ;
	}
	trhed_start(therds, mutex, times);
	free(therds);
	ft_free_mutex(mutex, times.philosophers);
}
