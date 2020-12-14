#include <stdio.h>
int x[25];
void main(void){
	int i;
	int j;
	i = (j = 0);
	while (i < 5){
		j = 0;
		while (j < 5){
		scanf("%d",&x[i * 5 + j]);
			
			j = j + 1;
		}
		i = 1 + i;
	}
	j = (i = 1);
	while (i < 5){
		while (j < 5){
			printf("-1");
			return;
		}
	}
}
