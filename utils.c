/*
** utils.c for malloc in /home/margue_m/rendu/PSU_2016_malloc
** 
** Made by Mattéo Margueritte
** Login   <margue_m@epitech.net>
** 
** Started on  Mon Jan 30 11:02:35 2017 Mattéo Margueritte
** Last update Mon Jan 30 16:39:06 2017 Mattéo Margueritte
*/

#include <pthread.h>
#include "malloc.h"

static pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		lock_thread(void)
{
  pthread_mutex_lock(&g_mutex);
}

void		unlock_thread(void)
{
  pthread_mutex_unlock(&g_mutex);
}

void		show_alloc_mem(void)
{
  t_ctrl	*tmp;

  tmp = g_map.head;
  printf("break : %p\n", (void *)tmp);
  while (tmp != NULL)
    {
      printf("%p - %p : %lu bytes\n", (void *)tmp,
	     (void *)tmp + sizeof(t_ctrl) + tmp->size,
	     tmp->size);
      tmp = tmp->next;
    }
}
