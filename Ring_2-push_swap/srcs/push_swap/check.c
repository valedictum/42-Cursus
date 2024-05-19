/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:46:44 by sentry            #+#    #+#             */
/*   Updated: 2024/02/16 11:14:29 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

bool	valid_integer(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!is_digit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	check_dupe(t_stack_node *stack_a)
{
	t_stack_node	*temp;

	while (stack_a)
	{
		temp = stack_a->next;
		while (temp)
		{
			if (stack_a->value == temp->value)
				return (1);
			temp = temp->next;
		}
		stack_a = stack_a->next;
	}
	return (0);
}

void	check_stack_and_display_error(t_stack_node *stack_a)
{
	if (!stack_a || check_dupe(stack_a))
	{
		free_stack(&stack_a);
		error_message();
		exit (1);
	}
}

bool	is_sorted(t_stack_node *stack)
{
	while (stack != NULL && stack->next != NULL)
	{
		if (stack->rank > stack->next->rank)
			return (false);
		stack = stack->next;
	}
	return (true);
}
