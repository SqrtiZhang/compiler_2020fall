#include <stdio.h>
int main()
{
	int a;int b;int c;int d;
	int e;
	c = 5;
	d = 9;
	e = (a = b = c + d);
	printf("%d",e);
	return 0;
}
