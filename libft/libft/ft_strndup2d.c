#include "../includes/libft.h"

char	**ft_strndup2d(char	**str2d, int start, int end)
{
	char	**new;
	int		x;
	int		y;

	x = 0;
	y = start;
	while (end >= y)
	{
		if (str2d[y][0] != '>' && str2d[y][0] != '<')
			x++;		
		y++;
	}
	new = (char**)ft_memalloc(sizeof(char*) * (x + 1));
	new[x] = 0;
	x = 0;
	while (end >= start)
	{
		if (str2d[start][0] != '>' && str2d[start][0] != '<')
		{
			new[x] = ft_strdup(str2d[start]);
			x++;
		}
		start++;
	}
	return (new);
}
