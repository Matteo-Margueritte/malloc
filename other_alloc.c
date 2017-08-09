/*
** realloc.c for malloc in /home/margue_m/rendu/test/malloc
**
** Made by Mattéo Margueritte
** Login   <margue_m@epitech.net>
**
** Started on  Sat Jan 28 15:52:53 2017 Mattéo Margueritte
** Last update Wed Feb  8 15:01:40 2017 bibzor
*/

#include <string.h>
#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
  void			*new;
  t_ctrl		*old;

  old = (t_ctrl *)((char *)ptr - sizeof(t_ctrl));
  if (ptr == NULL || size == 0)
    return (malloc(size));
  free(ptr);
  if ((new = malloc(size)) == NULL)
    return (NULL);
  (old->size < size) ? memmove(new, ptr, old->size) :
    memmove(new, ptr, size);
  return (new);
}

void			*calloc(size_t nb_elem, size_t el_size)
{
  void			*ptr;

  if ((ptr = malloc(nb_elem * el_size)) == NULL)
    return (NULL);
  bzero(ptr, nb_elem * el_size);
  return (ptr);
}
