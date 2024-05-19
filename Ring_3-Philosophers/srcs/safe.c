/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:47:44 by atang             #+#    #+#             */
/*   Updated: 2024/05/12 11:14:00 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Contains thread and mutex functions with embedded chekcs for errors
	on return. 2 clean wrappers (safe_mutex and safe_thread) 
	are used with OPCODE (enum) for safer, cleaner, more readbale code.
*/

/*
	safe_malloc() makes sure that the malloc call was successful. If the 
	malloc function fails, the program will exit with an error message.
	The function first calls the standard malloc function to allocate the
	requested number of bytes. If the malloc function fails (i.e., it
	returns a NULL pointer), the function will print an error message and
	exit the program.
	If the malloc function is successful, the function will return a
	pointer to the allocated memory. This pointer is the return value of
	the function.
*/

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with malloc");
	return (ret);
}

/*
	mutex_error() handles errors related to mutex operations and is called 
	whenever a mutex operation is performed to check for errors. It takes an 
	integer representing the return value of the mutex operation and an 
	enumeration value indicating the type of mutex operation to perform. It 
	then calls error_exit() with the corresponding error message if there was
	an error i.e. mutex_error() checks the return value of the mutex operation 
	(status) and calls the error_exit function if there was an error.
	The mutex operation is one of the following: LOCK, UNLOCK, INIT.

	Flow:
	- if the mutex operation is successful, the function will simply return.
	- possible error messages are as follows:
		- "The value specified by mutex is invalid" - if the mutex operation	
		is either LOCK or UNLOCK and the return value is EINVAL.
		- "The value specified by attr is invalid." - if the mutex operation
		is INIT and the return value is EINVAL.
		- "A deadlock would occur if the thread blocked waiting for mutex." -
		if the return value is EDEADLK.
		- "The current thread does not hold a lock on mutex." - if the return
		value is EPERM.
		- "The process cannot allocate enough memory to create another mutex."
		- if the return value is ENOMEM.
		- "Mutex is locked" - if the return value is EBUSY.
*/

static void	mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

/*
	thread_error() handles errors related to thread operations. It is called 
	whenever a thread operation is performed to check for errors. It takes an 
	integer representing the return value of the thread operation and an 
	enumeration value indicating the type of thread operation
	to perform. It then calls the error_exit function with the corresponding
	error message if there was an error i.e. fn() checks the return value of the 
	thread operation (status) and calls the error_exit function with the 
	corresponding error message based on the value of status and the type of 
	thread operation (opcode).

	Flow: 
	- if status is 0, the function returns without doing anything (no error)
	- if status is EAGAIN, the function calls error_exit(); this 
	indicates that there are no resources to create another thread
	- if status is EPERM, the function calls error_exit(); this
	indicates that the caller does not have the necessary permissions to
	perform the thread operation
	- If status is EINVAL and opcode is CREATE, the function calls the
	error_exit(); this indicates that the value of attr is invalid
	- if status is EINVAL and opcode is JOIN or DETACH, the function calls
	error_exit(); this indicates that the value of thread is not joinable
	- if status is ESRCH, the function calls the error_exit(); this indicates 
	that no thread could be found corresponding to the given thread ID
	- if status is EDEADLK, the function calls the error_exit(); this indicates 
	that a deadlock was detected or the value of thread specifies the calling 
	thread
*/

static void	thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have apporpriate permission\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread");
}

/*
	safe_mutex() is a safe way to use mutexes in pthreads with error 
	handling inbuilt.

	With error handling:
	- if the opcode is LOCK, lock the mutex
	- if the opcode is UNLOCK, unlock the mutex
	- if the opcode is INIT, init the mutex
	- if the opcode is DESTROY, destroy the mutex
	- if the opcode is not one of the above, error
*/

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle"
			"use <LOCK> <UNLOCK> <INIT> <DESTROY>");
}

/*
	safe_thread() handles threads safely where thread is the thread to 
	work with, foo is the function to run in the thread, data is the data to 
	pass to the function and opcode is the operation to perform

	- <CREATE> to create a new thread with the given fuction and data
	- <JOIN> to wait for a thread to finish
	- <DETACH> to detach a thread (let it run in the background)
	- any other value will cause an error
*/

void	safe_thread(pthread_t *thread, void *(*foo)(void *),
	void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle:"
			" Use <CREATE> <JOIN> <DETACH>");
}
