
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include "../libft/Get_next_line/get_next_line_bonus.h"
# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"

#include <sys/time.h>
#include <pthread.h>


#define true  0
#define fasle  -1

typedef struct t_times 
{
	int philosophers;
	int death;
	int food;
	int sleep;
	int food_x;
} 				s_times;

typedef struct t_ThreadData{ 
    int name;
	int stay_or_life;
	int time_start;
	int start_second_time;
	s_times times;
} s_ThreadData;

typedef struct t_loco {
	
	int livfe;
	int *eu;
	//s_ThreadData *norm;
	int thead_start;
	pthread_mutex_t death;
	pthread_mutex_t *mutex;
}	s_loco;

typedef struct t_new {
	int start;
	s_times times;
	pthread_mutex_t death;
} s_new;


typedef struct t_new_fuck {
	s_new * fuck;
	int end;
	int pq;
}	s_new_fuck;

pthread_mutex_t  *ft_alloc_mutex(int philosop);
void filof(s_times times);
void ft_free_mutex(pthread_mutex_t *data,int philo);
void *thead(void *infs);


#endif