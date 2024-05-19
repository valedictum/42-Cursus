/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:22:25 by atang             #+#    #+#             */
/*   Updated: 2024/02/23 12:15:58 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack_node	**stack_b, t_stack_node **stack_a, int *operation_count)
{
	int				value;
	t_stack_node	*temp;

	if (*stack_a != NULL)
	{
		value = (*stack_a)->value;
		*stack_b = create_and_insert_node(*stack_b, value);
		temp = *stack_a;
		*stack_a = (*stack_a)->next;
		free(temp);
	}
	ft_printf("pa\n");
	(*operation_count)++;
}

void	pb(t_stack_node	**stack_a, t_stack_node **stack_b, int *operation_count)
{
	t_stack_node	*temp;

	if (*stack_a != NULL)
	{
		temp = *stack_a;
		*stack_a = (*stack_a)->next;
		temp->next = *stack_b;
		*stack_b = temp;
	}
	ft_printf("pb\n");
	(*operation_count)++;
}
