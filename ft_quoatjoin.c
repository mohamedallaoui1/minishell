#include "minishell.h"

char	*ft_specequaot(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*s3;

	i = 0;
	j = 0;
	k = 0;
	if (!s1)
		s1=ft_strdup("");
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	s3 = (char *)malloc(sizeof(char) * (i + j + 2));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s3[k++] = s1[i++];
    s3[k++] = ' ' ;
    s3[k++] = '\'';
	while (s2[j])
		s3[k++] = s2[j++];
        s3[k++] = '\'';
	s3[k] = '\0';
	return (free(s1),s3);
}