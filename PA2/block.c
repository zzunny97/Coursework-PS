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

void calculator() {
	int level=0, cnt=0;
	char* expect = (char*)malloc(sizeof(wall));
	memset(expect, 0, sizeof(expect));
	for(int i=0; i<wall_length; i++) {
		if(!strcmp(expect, wall)) {
			break;
		}
		//printf("%s\tlevel: %d\tcnt: %d\n", expect, level, cnt);
		if(expect[i] == 0) {
			if(wall[i] == block[0]) {
				for(int j=0; j<block_length; j++)
					expect[i+j] = block[j];
				cnt++; level++;
			} else {
				int find_idx;
				for(int j=0; j<block_length; j++) {
					if(wall[i] == block[j])
						find_idx = j;
				}
				int tmp = i;
				for(int j=find_idx; j<block_length; j++) {
					expect[tmp++] = block[j];
				}
				cnt++; level--;
			}
		} else {
			int ret = compare(expect[i], wall[i]);
			//printf("ret: %d\n", ret);
			if(ret) {
				if(ret == 2) {
					for(int j=0; j<block_length; j++)
						expect[i+j] = block[j];
					cnt++; level++;
				} else {
					for(int j=0; j<block_length; j++) {
						if(compare(expect[i+j], wall[i+j])==2)
							continue;
						else 
							expect[i+j] = block[j];
					}
					level--; cnt++;
				}
			} else {
				continue;
			}
		}
	}
	answer_num = cnt;
	answer_height = level;
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
