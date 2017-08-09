/*
** free.c for malloc in /home/margue_m/rendu/test/malloc
**
** Made by Mattéo Margueritte
** Login   <margue_m@epitech.net>
**
** Started on  Sat Jan 28 14:52:07 2017 Mattéo Margueritte
** Last update Thu Feb  9 13:19:35 2017 Mattéo Margueritte
*/

#include <stdlib.h>
#include "malloc.h"

static int		is_all_free(void)
{
  t_ctrl		*tmp;

  tmp = g_map.head;
  while (tmp != NULL)
    {
      if (tmp->is_free == FALSE)
	return (FALSE);
      tmp = tmp->next;
    }
  return (TRUE);
}

void			merge_nearby_blocks(void)
{
  t_ctrl		*tmp;
  t_ctrl		*next;

  tmp = g_map.head;
  while (tmp->next != NULL)
    {
      next = tmp->next;
      if (tmp->is_free == TRUE && next->is_free == TRUE)
	{
	  tmp->size += (next->size + sizeof(t_ctrl));
	  if (next->next != NULL)
	    next->next->prev = tmp;
	  tmp->next = next->next;
	}
      if (tmp->next == NULL)
	return ;
      tmp = tmp->next;
    }
}

void			free(void *ptr)
{
  t_ctrl		*tmp;

  if (ptr != NULL && g_map.head != NULL)
    {
      lock_thread();
      tmp = (t_ctrl *)((char *)ptr - sizeof(t_ctrl));
      tmp->is_free = TRUE;
      merge_nearby_blocks();
      if (is_all_free() == TRUE)
	if (brk((void *)g_map.head) != -1)
	  {
	    g_map.free_space = 0;
	    g_map.map_size = 0;
	    g_map.head = NULL;
	    g_empty_map = TRUE;
	  }
      unlock_thread();
    }
}
