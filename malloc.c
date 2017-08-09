/*
** malloc.c for malloc in /home/margue_m/rendu/test/malloc
**
** Made by Mattéo Margueritte
** Login   <margue_m@epitech.net>
**
** Started on  Wed Jan 25 14:00:29 2017 Mattéo Margueritte
** Last update Sat Feb 11 15:03:02 2017 Mattéo Margueritte
*/

#include <pthread.h>
#include "malloc.h"

t_mem_map		g_map;
int			g_empty_map = TRUE;

static t_ctrl		*get_free_block(size_t size)
{
  t_ctrl		*tmp;

  tmp = g_map.head;
  while (tmp != NULL)
    {
      if (tmp->is_free == TRUE && tmp->size >= size)
	{
	  tmp->is_free = FALSE;
	  return (tmp);
	}
      tmp = tmp->next;
    }
  return (NULL);
}

static void		*init_map(size_t size)
{
  t_ctrl		*tmp;

  g_map.map_size = DEFAULT_MAP_SIZE;
  while (g_map.map_size < size + sizeof(t_ctrl))
    g_map.map_size += DEFAULT_MAP_SIZE;
  if ((g_map.head = (t_ctrl *)sbrk(g_map.map_size)) == (void *)-1)
    {
      unlock_thread();
      return (NULL);
    }
  tmp = g_map.head;
  tmp->next = NULL;
  tmp->prev = NULL;
  tmp->size = size;
  tmp->is_free = FALSE;
  g_map.free_space = g_map.map_size - size - sizeof(t_ctrl);
  g_empty_map = FALSE;
  unlock_thread();
  return ((void *)((char *)tmp + sizeof(t_ctrl)));
}

static void		*add_block(size_t size)
{
  t_ctrl		*tmp;
  t_ctrl		*new;

  tmp = split(get_free_block(size), size);
  if (tmp != NULL)
    {
      unlock_thread();
      return ((void *)((char *)tmp + sizeof(t_ctrl)));
    }
  tmp = g_map.head;
  while (tmp->next != NULL)
    tmp = tmp->next;
  new = (t_ctrl *)((char *)tmp + sizeof(t_ctrl) + tmp->size);
  new->prev = tmp;
  new->next = NULL;
  tmp->next = new;
  new->size = size;
  new->is_free = FALSE;
  g_map.free_space -= (new->size + sizeof(t_ctrl));
  unlock_thread();
  return ((void *)((char *)new + sizeof(t_ctrl)));
}

static void		*resize_map(size_t size)
{
  size_t		size_shift;

  size_shift = 0;
  while (g_map.free_space < size + sizeof(t_ctrl))
    {
      g_map.map_size += DEFAULT_MAP_SIZE;
      g_map.free_space += DEFAULT_MAP_SIZE;
      size_shift += DEFAULT_MAP_SIZE;
    }
  if (sbrk(size_shift) == (void *)-1)
    return (NULL);
  return (add_block(size));
}

#include <stdint.h>

void			*malloc(size_t size)
{
  size_t		a_size;

  if ((int64_t)size < 0)
    return (NULL);
  lock_thread();
  a_size = ALIGN(size);
  if (g_empty_map == TRUE)
    return (init_map(a_size));
  else
    {
      if ((a_size + sizeof(t_ctrl)) <= g_map.free_space)
      	return (add_block(a_size));
      else
	return (resize_map(a_size));
    }
  return (NULL);
}
