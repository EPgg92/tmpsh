#include "t_char_utils.h"

/*
** create_char:
**
** Allocate a single t_char element.
*/

static int	create_char(t_char	**char_node, char letter, int position, \
		t_char *previous)
{
	if (!(*char_node = (t_char *)malloc(sizeof(t_char))))
		return (MALLOC_ERROR);
	(*char_node)->letter = letter;
	(*char_node)->position = position;
	(*char_node)->next = NULL;
	(*char_node)->prev = previous;
	return (MALLOC_SUCCESS);
}

/*
** push_end_char:
**
** Create at the end of the t_char * chained list a new t_char element.
*/

int			push_end_char(t_char **char_node, char letter, int lock)
{
	t_char	*tmp_char;

	if (!*char_node)
		 return (create_char(char_node, letter, 0, NULL));
	tmp_char = *char_node;
	while (tmp_char->next)
		tmp_char = tmp_char->next;
	if (create_char(&tmp_char->next, letter, tmp_char->position + 1, \
				tmp_char) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	tmp_char->lock = lock;
	return (MALLOC_SUCCESS);
}


/*
** update_position:
**
** Go from a t_char * to the end of the list to update
** each char position.
*/

void		update_position(t_char *char_lst)
{
	int		index;

	index = char_lst && char_lst->prev ? char_lst->prev->position + 1 : 0;
	while (char_lst)
	{
		char_lst->position = index++;
		char_lst = char_lst->next;
	}
}
/*
** free_t_char:
**
** Deallocate a single t_char element, set his pointer to NULL.
*/

void static		free_t_char(t_char **char_node)
{
	free(*char_node);
	*char_node = NULL;
}

/*
** free_t_char_lst:
**
** Free an entire chained list of t_char, and set his pointer to NULL.
** Return the given status value.
*/

int			free_t_char_lst(t_char **char_lst, int status)
{
	t_char	*tmp_char;
	t_char	*next_char;

	tmp_char = *char_lst;
	while (tmp_char)
	{
		next_char = tmp_char->next;
		free_t_char(&tmp_char);
		tmp_char = next_char;
	}
	*char_lst = NULL;
	return (status);
}



/*
** display_chars:
**
** Print on stdout each char of a t_char list.
*/

void		display_chars(t_char *char_lst, t_cursor *cursor, int line, \
		int *printed_cursor)
{
	while (char_lst)
	{
		if (line == cursor->row && cursor->column == char_lst->position)
		{
			*printed_cursor = TRUE;
			show_cursor(char_lst->letter);
		}
		else
			write(1, &char_lst->letter, 1);
		char_lst = char_lst->next;
	}
}

int			char_lst_len(t_char *char_lst)
{
	int		index;

	index = 0;
	while (char_lst)
	{
		index++;
		char_lst = char_lst->next;
	}
	return (index);
}

