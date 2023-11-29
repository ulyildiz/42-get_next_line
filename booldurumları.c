#include <stdio.h>
#include <stdbool.h>
int main()
{
	char	*a = "merhaba";
	char	*b = "\0";
	char	*c = "";
	char	*d = NULL;
	if(!d)
		printf("bu d = %s\n", d);
	if(!b)
		printf("bu b = %s\n", b);
	if (!c)
		printf("bu c = %s\n", c);
	if (a)
		printf("bu a = %s\n", a);
	printf("a = %d, b = %d, c = %d, d = %d", (bool)a, (bool)b, (bool)c, (bool)d);

	int f = 0;
	int g;
	int h = 5;

	printf("f = %d, g = %d, h = %d", (bool)f, (bool)g, (bool)h);
}