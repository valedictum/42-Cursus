/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:18:27 by atang             #+#    #+#             */
/*   Updated: 2024/02/11 09:04:17 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack_node **stack_a, int *operation_count)
{
	t_stack_node	*last_element;
	t_stack_node	*second_last_element;

	if (*stack_a != NULL && (*stack_a)->next != NULL)
	{
		last_element = *stack_a;
		second_last_element = NULL;
		while (last_element->next != NULL)
		{
			second_last_element = last_element;
			last_element = last_element->next;
		}
		last_element->next = *stack_a;
		second_last_element->next = NULL;
		*stack_a = last_element;
	}
	ft_printf("rra\n");
	(*operation_count)++;
}

void	rrb(t_stack_node **stack_b, int *operation_count)
{
	t_stack_node	*last_element;
	t_stack_node	*second_last_element;

	if (*stack_b != NULL && (*stack_b)->next != NULL)
	{
		last_element = *stack_b;
		second_last_element = NULL;
		while (last_element->next != NULL)
		{
			second_last_element = last_element;
			last_element = last_element->next;
		}
		last_element->next = *stack_b;
		second_last_element->next = NULL;
		*stack_b = last_element;
	}
	ft_printf("rrb\n");
	(*operation_count)++;
}

void	rrr(t_stack_node **stack_a, t_stack_node **stack_b,
	int *operation_count)
{
	rra(stack_a, operation_count);
	rrb(stack_b, operation_count);
	ft_printf("rrr\n");
	(*operation_count)++;
}
