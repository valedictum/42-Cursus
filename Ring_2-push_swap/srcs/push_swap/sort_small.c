/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:16:37 by sentry            #+#    #+#             */
/*   Updated: 2024/02/21 12:41:03 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_2(t_stack_node **stack_a, int *operation_count)
{
	if (*stack_a != NULL && (*stack_a)->next != NULL)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
		{
			sa(stack_a, operation_count);
		}
	}
}

void	sort_3(t_stack_node **stack_a, int *operation_count)
{
	t_stack_node	*a;
	t_stack_node	*b;
	t_stack_node	*c;

	a = *stack_a;
	b = (*stack_a)->next;
	c = (*stack_a)->next->next;
	if (a->value > b->value && b->value < c->value && a->value < c->value)
		sa(stack_a, operation_count);
	else if (a->value > b->value && b->value > c->value && a->value > c->value)
		sa(stack_a, operation_count);
	if (b->value > a->value && b->value > c->value && a->value > c->value)
		rra(stack_a, operation_count);
	else if (a->value < b->value && b->value > c->value && a->value < c->value)
		sa(stack_a, operation_count);
	if (a->value > b->value && b->value < c->value && a->value > c->value)
		ra(stack_a, operation_count);
}

static void	move_element_back(t_stack_node **stack_a, t_stack_node **stack_b,
			int *operation_count, int *i)
{
	pa(stack_a, stack_b, operation_count);
	(*i)--;
}

void	sort_5(t_stack_node **stack_a, t_stack_node **stack_b,
			int *operation_count)
{
	int				target_rank;
	int				i;
	t_stack_node	*target_element;

	i = 0;
	target_rank = 1;
	while (!is_sorted(*stack_a))
	{
		while (*stack_a != NULL && target_rank <= 2)
		{
			target_element = find_rank(stack_a, target_rank);
			rotate_to_top_of_a(stack_a, target_element, operation_count);
			pb(stack_a, stack_b, operation_count);
			target_rank++;
			i++;
		}
		if (stack_size(*stack_a) == 3)
			sort_3(stack_a, operation_count);
		if (i > 0)
		{
			move_element_back(stack_a, stack_b, operation_count, &i);
		}
		else
			break ;
	}
}
