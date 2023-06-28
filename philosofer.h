#ifndef PHILOSOFER_H
# define PHILOSOFER_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_matrix;

typedef struct s_philo
{
	int				id;
	int				life;
	int				eating;
	int				count_eat;
	int				next_fork;
	u_int64_t		time;
	u_int64_t		time_life;
	pthread_t		philo;
	pthread_t		keeper;
	pthread_mutex_t	fork;
	struct s_matrix	*mat;
	struct timeval	ts;

}					t_philo;

typedef struct s_matrix
{
	int				num_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				time_max_eat;
	u_int64_t		origin_time;
	pthread_mutex_t	lock;
	t_philo			*room;
	struct timeval	ts;
}					t_matrix;

int					check_input(int ac, char **av, t_matrix *mat);
u_int64_t			get_time(void);
int					philo_init(t_matrix *mat);
int					ft_exit(t_matrix *mat);
void				my_usleep(int ms);
void				message(t_philo *philo, char *str);
void				caseone(t_matrix *mat);

#endif