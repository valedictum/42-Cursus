/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:20:53 by atang             #+#    #+#             */
/*   Updated: 2024/02/25 12:14:51 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_if_sorted_descending(t_stack_node *stack_a)
{
	int	prev_value;

	prev_value = INT_MAX;
	while (stack_a)
	{
		if (prev_value < stack_a->value)
			return (0);
		prev_value = stack_a->value;
		stack_a = stack_a->next;
	}
	return (1);
}

int	is_in_range(int rank, int i, int max_rank)
{
	if (i == 2)
		return (rank >= i * (max_rank / 3) + 1 && rank <= max_rank);
	else
		return (rank >= i * (max_rank / 3) + 1 && rank
			<= (i + 1) * (max_rank / 3));
}

int	is_in_chunk_range(t_stack_node *current, t_stack_node **stack_a, int i,
		int total_chunks)
{
	return (current->rank >= (i * (max_rank(*stack_a) / total_chunks) + 1)
		&& current->rank <= ((i + 1) * (max_rank(*stack_a) / total_chunks)));
}

void	process_chunk_500(t_stack_node **stack_a, t_stack_node **stack_b,
			int	*operation_count, int i)
{
	t_stack_node	*current;
	t_chunk_node	*chunk_head;
	t_chunk_node	*chunk_tail;

	current = *stack_a;
	set_chunk_null(&chunk_head, &chunk_tail);
	while (current != NULL && !check_if_sorted_descending(*stack_a))
	{
		if (is_in_chunk_range(current, stack_a, i, 10))
			add_to_chunk(&chunk_head, &chunk_tail, current);
		current = current->next;
	}
	if (chunk_head != NULL)
		push_chunk_to_b(stack_a, stack_b, &chunk_head, operation_count);
}
