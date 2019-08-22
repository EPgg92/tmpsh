#include "char_concatenation.h"
#include "libft.h"
#include "char_utils.h"
#include "screen_size.h"

/*
** get_repr_len:
**
** Calculate the total length for a single t_char string, increase the size of
** one if the cursor is at the end of the line, and leave enough place to
** add all reverse video character inside the string.
*/

static int		get_repr_len(t_char *char_lst, t_cursor *cursor, int line)
{
	int		line_len;

	line_len = 0;
	line_len += char_lst_len(char_lst);
	if (cursor->row == line)
	{
		if (cursor->column == line_len)
			line_len += 1;
		line_len += ft_strlen(g_caps->video) + ft_strlen(g_caps->reset_video);
	}
	line_len += 1;
	return (line_len);
}

/*
** add_cursor_repr:
**
** Insert into a string the representation of the char, setting up and resetting
** the reverse video mode.
*/

static void	add_cursor_repr(char *line, int *str_index, char cursor_letter)
{
	ft_strcpy(line + *str_index, g_caps->video);
	*str_index += ft_strlen(g_caps->video);
	line[*str_index] = cursor_letter;
	*str_index += 1;
	ft_strcpy(line + *str_index, g_caps->reset_video);
	*str_index += ft_strlen(g_caps->reset_video);
}

/*
** format_char_lst:
**
** Concat in the string each char of a t_char chained list.
** Concet the string with the locked part of the t_char.
*/

char		*format_char_lst(t_char *char_lst, t_cursor *cursor, int line)
{
	char	*line_repr;
	int		line_len;
	int		index;
	int		cursor_displayed;

	line_len = get_repr_len(char_lst, cursor, line);
	if (!(line_repr = (char *)MALLOC(sizeof(char) * (line_len+ 5))))
		exit(-1);
	index = 0;
	cursor_displayed = FALSE;
	while (char_lst)
	{
			if (line == cursor->row && cursor->column == char_lst->position)
			{
				add_cursor_repr(line_repr, &index, char_lst->letter);
				cursor_displayed = TRUE;
			}
			else
				line_repr[index++] = char_lst->letter;
			char_lst = char_lst->next;
	}
	if (cursor_displayed == FALSE && line == cursor->row)
		add_cursor_repr(line_repr, &index, ' ');
	line_repr[index] = '\0';
	return (line_repr);
}

/*
** concat_shell:
**
** Concat an entire shell representation into a single string.
** Count also the number of line in the terminal who will be occuped
** by the shell.
*/

char			*concat_shell(t_line *prompt_lines, t_cursor *cursor, \
		int *total_lines)
{
	char	*shell_str;
	char	*new_line;
	int		line_len;
	t_win	window;
	char	*newline_tmp;

	shell_str = ft_strnew(0);
	*total_lines = 0;
	screen_size(&window);
	while (prompt_lines)
	{
		new_line = format_char_lst(prompt_lines->chars, cursor, \
						prompt_lines->position);
		if (!(shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1)))
			exit(-1);
		line_len = char_lst_len(prompt_lines->chars);
		if (cursor->row == prompt_lines->position && cursor->column == line_len)
			line_len++;
		*total_lines += line_len / window.ws_col;
		*total_lines += line_len % window.ws_col > 0;
		prompt_lines = prompt_lines->next;
		newline_tmp = "\n";
		if (prompt_lines)
		{
			if (!(shell_str = ft_fstrjoin(&shell_str, &newline_tmp, 1, 0)))
				exit(-1);
		}
	}
	return (shell_str);
}

/*
** history_formatter:
**
** Format a single line of shell_repr
*/

static void		history_formatter(t_line **shell_repr, char **format)
{
	int line_len;
	int	index;
	t_char	*char_lst;

	char_lst = get_unlocked_char((*shell_repr)->chars);
	line_len = char_lst_len(char_lst);
	*format = (char *)ft_memalloc(sizeof(char) * line_len + 1);
	index = 0;
	while (char_lst)
	{
		(*format)[index++] = char_lst->letter;
		char_lst = char_lst->next;
	}
	(*format)[index] = '\0';
}

/*
** render_shell_content:
**
** Concat in the single string all input given by the user, removing the
** unlocked part of the t_char.
*/

char			*render_shell_content(t_line *prompt_lines)
{
	char	*shell_str;
	char	*new_line;
	char	*newline_tmp;

	shell_str = ft_strnew(0);
	while (prompt_lines)
	{
		history_formatter(&prompt_lines, &new_line);
		shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1);
		prompt_lines = prompt_lines->next;
		newline_tmp = "\n";
		shell_str = ft_fstrjoin(&shell_str, &newline_tmp, 1, 0);
	}
	return (shell_str);
}
