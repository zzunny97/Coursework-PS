#include <stdio.h>
#include <stdlib.h>

int block_length = 0;
int wall_length = 0;
char* block;
char* wall;
int answer_num;
int answer_height;

void calculator() {
		
}

int main() {
	scanf("%d", &block_length);
	scanf("%d", &wall_length);

	block = malloc(sizeof(char)*block_length);
	wall =  malloc(sizeof(char)*wall_length);

	scanf("%s", block);
	scanf("%s", wall);

	calculator();

	printf("%d\n", answer_num);
	printf("%d\n", answer_height);

	return 0;
}
