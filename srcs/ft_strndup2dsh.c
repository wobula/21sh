#include "../includes/libft.h"

char	**ft_strndup2d(char	**str2d, int start, int end)
{
	char	**new;
	int		x;

	new = (char**)ft_memalloc(sizeof(char*) * ((end - start + 1) + 1));
	new[end - start + 1] = 0;
	x = 0;
	while (end >= start)
	{
		new[x] = ft_strdup(str2d[start]);
		x++;
		start++;
	}
	return (new);
}
