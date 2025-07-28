#include "ft_printf_bonus.h"

int	put_padding(int width, char c)
{
	int	i;

	i = 0;
	while (i < width)
	{
		write(1, &c, 1);
		i++;
	}
	return (width);
}
