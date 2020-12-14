#include <stdio.h>
int test(float a[])
{
	return a[0];
}
int main()
{
	int b[10];
	int c;
	b[0] = 1;
	printf("%d", test(b));
	return 0;
}
