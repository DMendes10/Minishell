
int	quote_checker(char c, int quotes)
{
	if (c == '\'')
	{
		if (quotes == 1)
			quotes = 0;
		else if (quotes == 0)
			quotes = 1;
	}
	if (c == '\"')
	{
		if (quotes == 2)
			quotes = 0;
		else if (quotes == 0)
			quotes = 2;
	}
	return (quotes);
}
