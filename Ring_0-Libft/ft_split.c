/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:57:02 by atang             #+#    #+#             */
/*   Updated: 2023/07/26 16:10:13 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Function name
	ft_split

Prototype
	char **ft_split(char const *s, char c);

Parameters
	s: The string to be split.
	c: The delimiter character.

Return value
	The array of new strings resulting from the split.
	NULL if the allocation fails.

External functs.
	malloc, free

Description
	Allocates (with malloc(3)) and returns an array of strings obtained by 
	splitting ’s’ using the character ’c’ as a delimiter. The array must end 
	with a NULL pointer.
*/
/* 
	- count the number of words in the input string separated by the delimiter, 
	iterating through the string and keeping track of whether it's inside a 
	word or not (in_word_flag). For a delimiter, it sets the flag to 0, 
	and when it encounters a character while in_word_flag is 0, it increments 
	the count and sets the in_word_flag to 1 to indicate that inside a word.
	
	- extract a single word - passed a pointer to a pointer s, so it can 
	update the original pointer to move past the extracted word. It first skips 
	leading delimiters by incrementing *s (the pointer to the input string) 
	until it reaches a non-delimiter character. Then, it calculates the length
	of the word by counting characters until it encounters the next delimiter
	or the end of the string. After determining the word's length, it 
	dynamically allocates memory for the word using malloc, copies the 
	characters from *s into the new memory, and terminates the word with a 
	null-terminator. Finally, it increments the pointer *s to move past the 
	extracted word.

	- free the memory allocated for each word in the array, words, iterating 
	through the array and freeing each word's memory.

	- main function returns an array of words as output, calling count_words 
	first. Then, memory is dynamically allocated for the result array to 
	store pointers to the words. Then, the function iterates through the words
	and calls extract_word to extract each word and store its pointer in the 
	result array. If extract_word returns NULL, (extract word failure), memory 
	allocated for the words processed so far in freed and then the result array
	itself is freed before returning NULL to indicate failure. Otherwise,
	continuation of word extraction before NULL termination of the array, 
	and return of the array of words.
 */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word_flag;

	count = 0;
	in_word_flag = 0;
	while (*s)
	{
		if (*s == c)
			in_word_flag = 0;
		else if (in_word_flag == 0)
		{
			in_word_flag = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*extract_word(char const **s, char c)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	while (**s && **s == c)
		(*s)++;
	while ((*s)[word_len] && (*s)[word_len] != c)
		word_len++;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = (*s)[i];
		i++;
	}
	word[word_len] = '\0';
	*s += word_len;
	return (word);
}

static void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = extract_word(&s, c);
		if (!result[i])
		{
			free_words(result);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
/* 
int	main(void)
{
	char	input_string[] = "Hello,World,this,is,me!,";
	char	delimiter = ',';
	int		i;
	char	**words;

	words = ft_split(input_string, delimiter);
	if (words == NULL)
	{
		printf("Memory allocation failed OR input string NULL.\n");
		return (1);
	}
	i = 0;
	while (words[i])
	{
		printf("%s\n", words[i]);
		i++;
	}
	free_words(words);
	free(words);
	return (0);
}
 */