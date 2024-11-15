/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:16:51 by tbarret           #+#    #+#             */
/*   Updated: 2024/03/08 12:42:27 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	exit_program(t_ctx *ctx)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&ctx->prop.m_dead);
	pthread_mutex_destroy(&ctx->prop.m_eat);
	pthread_mutex_destroy(&ctx->prop.m_write);
	while (i < ctx->prop.total)
	{
		pthread_mutex_destroy(&ctx->m_fork[i]);
		i++;
	}
}

static void	join_thread(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->prop.total)
	{
		pthread_join(ctx->philo[i].thread, 0);
		i++;
	}
}

void	init_thread(t_ctx *ctx)
{
	int	i;

	i = 0;
	ctx->prop.s_time = ft_date();
	while (i < ctx->prop.total)
	{
		pthread_create(&ctx->philo[i].thread, NULL, &action, &ctx->philo[i]);
		i++;
	}
	checker(ctx);
	join_thread(ctx);
}
