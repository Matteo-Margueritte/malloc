/*
** split.c for malloc in /home/margue_m/rendu/PSU_2016_malloc
**
** Made by Mattéo Margueritte
** Login   <margue_m@epitech.net>
**
** Started on  Thu Feb  2 12:26:18 2017 Mattéo Margueritte
** Last update Thu Feb  2 12:47:09 2017 Mattéo Margueritte
*/

#include "malloc.h"

t_ctrl			*split(t_ctrl *block, int size)
{
  t_ctrl		*new;
  t_ctrl		*next;

  if (block != NULL && block->size > (size + sizeof(t_ctrl) + 1))
    {
      next = block->next;
      new = (t_ctrl *)((char *)block + size + sizeof(t_ctrl));
      new->size = block->size - sizeof(t_ctrl) - size;
      new->is_free = TRUE;
      block->size = size;
      block->next = new;
      if (next != NULL)
	next->prev = new;
      new->next = next;
      new->prev = block;
    }
  return (block);
}
