/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:48:14 by atang             #+#    #+#             */
/*   Updated: 2023/09/08 10:34:33 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_append_lines(int fd, char	*stash)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(stash, '\n') && (bytes_read != 0))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		if (!stash)
			stash = gnl_initialise_str();
		stash = gnl_strjoin(stash, temp_buffer);
		if (!stash)
			break ;
	}
	free(temp_buffer);
	return (stash);
}
/* 

- read_and_append_lines reads and appends lines from a 'fd' to the 'stash' 
buffer until it finds a newline character or reaches the end of the file.
- fn dynamically allocates memory for 'temp_buffer' to read chunks of data, 
and 'bytes_read' is initialised to 1 so we enter the while loop to read data
- Inside the loop, as long as there is no newline character in the stash AND 
'bytes_read' is not 0 (i.e. end of file has been reached so no more to read):
	- data is read from the 'fd' into the 'temp_buffer' up to 'buffer_size' 
	of data
	- if an error occurs during read (i.e. return of -1), memory is freed and 
	NULL is returned
	- null-terminator is added at the end of the data read to turn it into 
	a null-terminated string
	- if the 'stash' buffer is empty (NULL), it is initialised using 
	gnl_initialise_str to allocate memory for an empty string
	- data read from 'temp_buffer' is appended to the 'stash' buffer using
	gnl_strjoin, accumulating data into the 'stash' buffer
	- if memory allocation for 'stash' during gnl_strjoin failed, error has 
	occured so break to exit loop
- 'temp_buffer' is freed and the updated 'stash' buffer with accumulated data
read from the 'fd' is returned

 */

char	*extract_line_from_stash(char	*stash)
{
	char	*extracted_line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	extracted_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		extracted_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		extracted_line[i] = stash[i];
		i++;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}
/* 

- extract_line_from_stash extracts a line from the 'stash' buffer until a 
newline character is found
- fn checks if the 'stash' buffer is empty, if it is then there is no line 
to extract so NULL is returned
- length needed to be extracted is calculated by iterating i through 'stash' 
buffer while not '\0' OR '\n'
- after determining length of the line, memory is dynamically allocated 
for the 'extracted_line' (+2 to accommodate '\n' AND '\0'). If memory 
allocation failed, NULL is returned to indicate an error has occurred
- once memory has been allocated successfullly, a while loop is entered where
characters are copied FROM the 'stash' buffer INTO the 'extracted_line' until
the '\n' is found or the end of the the 'stash' buffer is reached
- after copying, the fn checks if the character at the current position 
in the 'stash' buffer is '\n', and if it is, the '\n' is also copied into 
'extracted_line' so that '\n' is also in 'extracted_line'
- 'extracted_line' is null-terminated as a str should be and then returned 
containing the extracted line from the 'stash' buffer 

 */

char	*remaining_stash_after_extraction(char *stash)
{
	int		s_index;
	int		r_index;
	char	*remaining;

	s_index = 0;
	r_index = 0;
	while (stash[s_index] && stash[s_index] != '\n')
		s_index++;
	if (!stash[s_index])
	{
		free(stash);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * ((gnl_strlen(stash)
					- s_index + 1)));
	if (!remaining)
		return (NULL);
	s_index++;
	while (stash[s_index])
		remaining[r_index++] = stash[s_index++];
	remaining[r_index] = '\0';
	free(stash);
	return (remaining);
}
/* 

- remaining_stash returns the remaining contents of the 'stash' buffer 
after extracting a line
- fn uses a while loop to iterate through the 'stash' buffer until either
'\0' or '\n' (to find the end of the 'stash' buffer or the position of 
the newline character)
- fn then checks if it is at the end of the 'stash' buffer (i.e. no more 
characters in the buffer), and if it is, the 'stash' buffer has been 
processed completely so there is no more data to extract. In that case, 
'stash' is freed and NULL is returned to denote no remaining data
- if the 'stash' buffer isn't fully processed, the fn then calculates the 
length of the remaining data in the 'stash' (from newline character position
to the end) and allocates memory for the 'remaining' buffer to store the 
data. If memory allocation fails for 'remaining', NULL is returned
- s_index is incremented to move PAST '\n' in the 'stash' and another while
loop is entered to copy the remaining data FROM the 'stash' buffer INTO the
'remaining' buffer until the end of the 'stash' buffer
- '\0' is added to the end of 'remaining' buffer, 'stash' is freed, and the
'remaining' buffer is returned which has the remaining data from 'stash' 
after line extraction

 */

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*completed_line_or_null;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		return (NULL);
	}
	stash = read_and_append_lines(fd, stash);
	if (!stash)
		return (NULL);
	completed_line_or_null = extract_line_from_stash(stash);
	stash = remaining_stash_after_extraction(stash);
	return (completed_line_or_null);
}
/* 

- get_next_line is the main function which reads and returns 
the next line from the given file descriptor using static storage 
(stash) to keep track of the data read so far
- fn checks if 'fd' < 0 (invalid fd) OR 'buffer_size' <= 0 (invalid buffer
size), and if EITHER are true, the fn frees memory allocated for the 'stash' 
buffer and returns NULL to indicate error
- read_and_append_lines is called to read and append data from 'fd' into the
'stash' buffer, updating the 'stash' variable with the accumulated data. 
If 'stash' is NULL, an error occurred during reading OR memory allocation, 
NULL is returned to indicate error
- extract_line_from_stash is called to extract line from the 'stash' buffer
and assigns the result to the 'completed_line_or_null' variable
- after extraction, remaining_stash_after_extraction is called to update 
the 'stash' buffer with the remaining data
- fn returns completed_line_or_null which contains the line extracted from the 
'stash' buffer; this will be a complete line from the file or 'NULL' if 
there are no more lines or an error occurred during the process   

 */

/* int	main(void)
{
	int		fd = open("example.txt", O_RDONLY);
	char	*line;


	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
} */

/* 
gcc -o GNL get_next_line_utils.c get_next_line.c
&
Contents for example.txt:

Line 1 with a normal length.
Short line.
Long line that spans multiple buffer reads, exceeding the BUFFER_SIZE
defined in your code.
Line with a tab character:              tabbed content.
Line with spaces at the end.         
Empty line below this.

This line has no newline character at the end.
Unicode line: 🌟✨🌍
A line with special characters: !@#$%^&*()_+{}|:"<>?[];',./\-
 */
