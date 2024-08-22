
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
	int n_thread;
	int time_start;
	int start_second_time;
	s_times times;
	
    pthread_mutex_t *mutex;
	struct t_ThreadData *temp;
	
} s_ThreadData;

typedef struct t_loco {
	int livfe;
	s_ThreadData *norm;
	s_ThreadData *loco;
}	s_loco;

s_ThreadData ft_alloc_mutex(int philosop);
void filof(s_times times);
void ft_free_mutex(s_ThreadData data,int philo);



#endif