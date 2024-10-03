/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:35:46 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/26 11:58:23 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TRUE 0
# define FASLE -1

typedef struct s_times
{
	int				philosophers;
	int				death;
	int				food;
	int				sleep;
	int				food_x;
}					t_times;

typedef struct s_new
{
	int				start;
	int				im;
	int				start_time_second;
	int				start_time;
	int				dead_time;
	int				time_reste;
	t_times			times;
	int				*i_end;
	int				*i_time;
	int				*set;
}					t_new;

typedef struct s_new_philo
{
	t_new			*fuck;
	pthread_mutex_t	mens;
	pthread_mutex_t	death;
	pthread_mutex_t	*fork;
	int				time;
	int				end;
	int				set;
	int				pq;
	int				philo;
}					t_new_philo;

typedef union s_forks
{
	struct
	{
		int			my;
		int			steal;
	};
	int				fork[2];

}					t_forks;

typedef struct s_ints
{
	int				time;
	int				x;
	int				fil_n;
}					t_ints;

int					save(t_new_philo *infos, t_new *infot_new);
pthread_mutex_t		*ft_alloc_mutex(int philosop);
long int			ft_atol(const char *nptr);
void				filof(t_times times);
void				ft_free_mutex(pthread_mutex_t *data, int philo);
void				*thead(void *infs);
void				*bar_men_thead(void *infs);

void				print(t_new_philo *infos, char *mens, t_new *infos_new,
						int time);
int					ft_time(int second);

int					par(int n);

t_forks				set_forks(int my, int max);

t_forks				set_forks(int my, int max);

int					print_forks(t_new_philo *infos, t_new *infot_new,
						pthread_mutex_t *fork, int mut);

int					forks(t_new *infot_new, t_new_philo *infos, t_forks forks);

int					end(t_new infot_new, t_new_philo *infos, int neg);

int					chek_end(t_new_philo *infos);

t_new				copy_struct(t_new *infot_new, int im);

char				*not_philos(t_new_philo *infos, t_new infos_new);

int					get_time(t_new_philo *infos);

void				set_time(t_new_philo *infus, int second);

int					second(void);

void				set_fuck_i_end(t_new_philo *infus);

#endif