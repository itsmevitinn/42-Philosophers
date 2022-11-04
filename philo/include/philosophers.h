/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/04 00:38:57 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_global
{
	pthread_mutex_t		finish;
	pthread_mutex_t		*meal_access;
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		print;
	int					*forks;
	long int			guests;
	long int			*lst_meal;
	int					all_eaten;
	int					end;
}				t_global;

typedef struct s_data
{
	t_global			*global;
	pthread_t			*ph_thread;
	struct s_data		*ph_data;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			times_must_eat;
	int					*meals;
	int					all_eaten;
	int					id;
}						t_data;

long int	get_current_time(void);
long int	ft_atoi(char *str);
long int	exit_atoi(void);
void		print_status(t_data *data, char type, int pos);
int			create_data(t_data *data, char **argv, int argc, t_global *global);
void		create_philo_threads(t_data *data);
void		*lifetime(void *philo);
void		death_time(t_data *data, int i);
void		monitor(t_data *data, int i);
void		start_global(t_global *global, char **argv);
void		join_philos(t_data *data);
void		*dinner(void *data);
int			take_forks(t_data *data);
int			eat(t_data *data);
void		return_forks(t_data *data);
int			sleep_time(t_data *data);
int			smart_check(long int timer, t_data *data);
void		free_all(t_data *data);
void		init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);
int			invalid_args(void);
int			invalid_values(void);
int			check_values(t_data *data);
int			check_atoi_numbers(char *string);

#endif
