#include "parser.h"


static char	*seperator(char *input, int pos)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(ft_strlen(input) + 3);
	if (!ret)
		return(NULL);
	while (i < pos)
		ret[j++] = input[i++];
	ret[j++] = SEP;
	ret[j++] = input[i++];
	if (input[i] == input[i - 1] && input[i] != '|')
		ret[j++] = input[i++];
	ret[j++] = SEP;
	while (input[i])
		ret[j++] = input[i++];
	ret[j] = '\0';
	free(input);
	return (ret);
}

char	*lexer(char *input)
{
	int		i;
	int		quotes;
	char	*temp;
	char	*cmdtable;
	
	i = 0;
	quotes = 0;
	temp = ft_strdup(input);
	while (temp && temp[i])
	{
		if (temp[i] == '|' || temp[i] == '<' || temp[i] == '>')
		{
			temp = seperator(temp, i);
			i = i + 2;
		}
		else if (temp[i] == '\'' || temp[i] == '\"')
			quotes_check(temp[i], quotes);
		i++;
	}
	if (quotes)
		free(temp);
	cmdtable = ft_strdup(temp);
	free(temp);
	return (cmdtable);
}