/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:18:02 by atang             #+#    #+#             */
/*   Updated: 2024/02/11 09:04:14 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_stack_node **stack_a, int *operation_count)
{
	t_stack_node	*last_element;
	t_stack_node	*temp;

	if (*stack_a != NULL && (*stack_a)->next != NULL)
	{
		last_element = *stack_a;
		while (last_element->next != NULL)
			last_element = last_element->next;
		temp = *stack_a;
		*stack_a = (*stack_a)->next;
		temp->next = NULL;
		last_element->next = temp;
	}
	ft_printf("ra\n");
	(*operation_count)++;
}

void	rb(t_stack_node **stack_b, int *operation_count)
{
	t_stack_node	*last_element;
	t_stack_node	*temp;

	if (*stack_b != NULL && (*stack_b)->next != NULL)
	{
		last_element = *stack_b;
		while (last_element->next != NULL)
			last_element = last_element->next;
		temp = *stack_b;
		*stack_b = (*stack_b)->next;
		temp->next = NULL;
		last_element->next = temp;
	}
	ft_printf("rb\n");
	(*operation_count)++;
}

void	rr(t_stack_node **stack_a, t_stack_node **stack_b, int *operation_count)
{
	ra(stack_a, operation_count);
	rb(stack_b, operation_count);
	ft_printf("rr\n");
	(*operation_count)++;
}
