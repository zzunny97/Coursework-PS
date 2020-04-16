#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int block_length = 0;
int wall_length = 0;
char* block;
char* wall;
int answer_num;
int answer_height;

int compare(char a, char b) {
	int idx1, idx2;
	for(int i=0; i<block_length; i++) {
		if(block[i] == a) idx1 = i;
		if(block[i] == b) idx2 = i;
	}
	if(idx1 == idx2) return 0;
	else if(idx1 < idx2) return 1;
	else return 2;
}

typedef struct pair{
	int x;
	int y;
} pair;

int top;
pair p[100000];
void push(int x, int y) {
	p[top].x = x;	
	p[top].y = y;
	top++;
}
void print() {
	for(int i=0; i<top; i++) {
		printf("(%d, %d)\n", p[i].x, p[i].y);
	}
}

int seek(int x, int y) {
	for(int i=0; i<top; i++) {
		if(p[i].x == x && p[i].y == y) return 1;
	}
	return 0;
}


void calculator() {
	int cur_x = 0, cur_y = 0;
	for(int i=0; i<100000; i++) {
		p[i].x = -1;
		p[i].y = -1;
	}
	
	int level_min=0, level_max=0;
	int level=0, cnt=0;
	char* expect = (char*)malloc(sizeof(char)*1000);
	memset(expect, 0, sizeof(expect));
	printf("%s\n", block);
	printf("%s\n", wall);
	printf("================\n");
	for(int i=0; i<wall_length; i++) {
		if(!strcmp(expect, wall)) {
			break;
		}
		printf("%s\ti: %d\tlevel: %d\tcnt: %d\n", expect, i, level, cnt);
		//printf("%s\n", wall);
		if(expect[i] == 0) {
			if(wall[i] == block[0]) {
				for(int j=0; j<block_length; j++) {
					//printf("copy %d\n", j);
					expect[i+j] = block[j];
					push(cur_x++, cur_y);			
				}
				cnt++; level++;
			} else {
				cur_y--;
				for(int i=0; i<top; i++) {
					if(seek(cur_x, cur_y)) {
						cur_y--;
					}
				}	
				int find_idx;
				for(int j=0; j<block_length; j++) {
					if(wall[i] == block[j]) {
						find_idx = j;
					} else {
						cur_x--;
					}
				}
				cur_x++;
				printf("cur_x: %d, cur_y: %d\n", cur_x, cur_y);
				for(int j=0; j<find_idx; j++)
					push(cur_x++, cur_y);
				int tmp = i;
				for(int j=find_idx; j<block_length; j++) {
					expect[tmp++] = block[j];
					push(cur_x++, cur_y);
				}
				cnt++; level--;
			}
		} else {
			int ret = compare(expect[i], wall[i]);
			printf("else-ret: %d expect[i]: %c, wall[i]: %c\n", ret, expect[i], wall[i]);
			if(ret) {
				if(ret == 2) {
					cur_x=i;
					cur_y++;
					for(int j=0; j<block_length; j++) {
						expect[i+j] = block[j];
						push(cur_x++, cur_y);
					}
					cnt++; level++;
				} else { 
					cur_y--;
					for(int i=0; i<top; i++) {
						if(seek(cur_x, cur_y)) {
							cur_y--;
						}
				}	
					for(int j=0; j<block_length; j++) {
						if(compare(expect[i+j], wall[i+j])==2) {
							cur_x--;
							continue;
						}
						else {
							expect[i+j] = block[j];
							push(cur_x++, cur_y);
						}
					}
					cnt++; level--;
				}
			} else {
				continue;
			}
		}
		//if(level_min > level) level_min = level;
		//if(level_max < level) level_max = level;
	}
	for(int i=0; i<top; i++) {
		if(level_min > p[i].y) level_min = p[i].y;
		if(level_max < p[i].y) level_max = p[i].y;

	}
	//printf("level_min: %d\n", level_min);
	//printf("level_max: %d\n", level_max);
	print();
	printf("%s\n", wall);
	answer_num = cnt;
	answer_height = level_max - level_min;
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
