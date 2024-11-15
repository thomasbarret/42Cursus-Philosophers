/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:40:43 by tbarret           #+#    #+#             */
/*   Updated: 2024/02/29 12:42:31 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# ifndef PHILO_MAX
#  define PHILO_MAX 1000
# endif

typedef struct s_prop
{
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_write;
	size_t			s_time;
	size_t			t_dead;
	size_t			t_sleep;
	size_t			t_eat;
	int				total;
	int				dead;
	int				max_eat;
}	t_prop;

typedef struct s_philo
{
	int				id;		
	int				eating;
	int				eaten;
	size_t			l_eat;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_prop			*prop;
}	t_philo;

typedef struct s_ctx
{
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	m_fork[PHILO_MAX];
	t_prop			prop;
	pthread_t		thread;
}	t_ctx;

size_t	ft_date(void);
int		ft_atoi(const char *str);
int		dead_exit(t_philo *p);
void	ft_print(t_philo *p, char *str);
void	init_mutex(t_ctx *ctx);
void	init_philo(t_ctx *ctx);
void	init_thread(t_ctx *ctx);
void	*action(void *ptr);
void	eating(t_philo *p);
void	sleeping(t_philo *p);
void	thinking(t_philo *p);
void	*checker(t_ctx *ctx);
void	exit_program(t_ctx *ctx);
int		only_one(t_ctx *ctx);
int		ft_usleep(size_t milliseconds);

#endif