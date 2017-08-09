/*
** malloc.h for malloc in /home/margue_m/rendu/test/malloc
**
 ** Made by Mattéo Margueritte
** Login   <margue_m@epitech.net>
**
** Started on  Wed Jan 25 14:00:33 2017 Mattéo Margueritte
** Last update Thu Feb  9 15:31:01 2017 Vidalu
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <stdio.h>
# include <stddef.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAILURE 1

# ifndef __X86_64__
#  define ALIGNMENT (16)
# else
#  define ALIGNMENT (8)
# endif

# define ALIGN(x) __ALIGN_MASK(x,(ALIGNMENT) - 1)
# define __ALIGN_MASK(x, mask) (((x) + (mask)) &~ (mask))
# define DEFAULT_MAP_SIZE (ALIGN(sysconf(_SC_PAGESIZE)))

typedef struct		s_ctrl
{
  size_t		is_free;
  size_t		size;
  struct s_ctrl		*next;
  struct s_ctrl		*prev;
}			t_ctrl;

typedef struct		s_mem_map
{
  size_t		map_size;
  size_t		free_space;
  t_ctrl		*head;
}			t_mem_map;

extern t_mem_map	g_map;
extern int		g_empty_map;

void			free(void *);
void			*malloc(size_t);
void			*realloc(void *, size_t);
void			*calloc(size_t, size_t);
void			show_alloc_mem(void);
void			lock_thread(void);
void			unlock_thread(void);
t_ctrl			*split(t_ctrl *, int);

#endif /* !MALLOC_H_ */
