#include "asm.h"

char		skip_blanks(char **s)
{
	if (!(s && *s && **s))
		return (-1);
	while ((**s) && ((**s) == SPACE || (**s) == TAB))
		(*s)++;
	return (**s ? 0 : -1);
}

_Bool	empty_line(t_file *file, char *s)
{
	if ((skip_blanks(&s) == -1) || ((*s == COMMENT_CHAR)\
				|| !(s)))
	{
		ft_strdel(&file->line);
		return (1);
	}
	return (0);
}

_Bool	breaking_line(char *s)
{
	while (*s && ft_isdigit(*s))
		(s)++;
	skip_blanks(&s);
	if (!(*s))
		return (1);
	return (0);
}