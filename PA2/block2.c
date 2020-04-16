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

char seek(char** map, int index) {
	for(int i=300; i>=0; i--) {
		if(map[index][i] != 0) {
			return map[index][i];
		}
	}
	return 0;
}

void print_map(char** map) {
	for(int i=300; i>=0; i--) {
		int cnt=0, idx=0;
		for(int j=0; j<wall_length; j++) {
			if(map[j][i] != 0) {
				cnt++; idx = j;
			}
		}
		if(cnt) {
			printf("%d-floor\t", i);
			for(int j=0; j<=idx; j++) {
				if(map[j][i] == 0) printf(" ");
				else printf("%c", map[j][i]);
			}
			printf("\n");
		}
	}
}

int getMax(char** map) {
	for(int i=300; i>=0; i--) {
		for(int j=0; j<wall_length; j++) {
			if(map[j][i] != 0) return i;
		}
	}
	return -1;
}

int getMin(char** map) {
	for(int i=0; i<=300; i++) {
		for(int j=0; j<wall_length; j++) {
			if(map[j][i] != 0) return i;
		}
	}
	return -1;
}

void calculator() {
	//printf("block: %s\n", wall);
	//printf("wall: %s\n", wall);
	char** map = (char**)malloc(sizeof(char*)*wall_length);	
	for(int i=0; i<wall_length; i++) {
		map[i] = (char*)malloc(sizeof(char)*300);
		memset(map[i], 0, sizeof(map[i]));
	}
	int cur_y=150;
	int cnt = 0;
	for(int i=0; i<wall_length; i++) {
		//printf("==========\n"); print_map(map);
		//printf("i: %d, wall[%d]: %c\n", i,i,wall[i]);
		char t = seek(map, i);
		if(t == 0) {
			if(wall[i] == block[0]) {
				//printf("wall is first element, and top of map is empty\n");
				for(int j=0; j<block_length; j++) {
					map[i+j][cur_y] = block[j];
				}
				cnt++;
			} else {
				//printf("top is empty, but wall is not first element\n");
				int find_idx = 0;
				//printf("wall[%d]: %c\n", i, wall[i]);
				for(int j=0; j<block_length; j++) {
					if(block[j] == wall[i]) {
						find_idx = j;
						break;
					}
				}
				//printf("find_idx: %d\n", find_idx);
				i -= find_idx;
				while(map[i][cur_y] != 0) {
					cur_y--;
				}
				for(int j=0; j<block_length; j++) {
					map[i+j][cur_y] = block[j];
				}
				cnt++;
			}
		} else {
			//printf("2\n");
			int c = compare(t, wall[i]);
			//printf("compare result: %d\n", c);
			if(c==0) {
				//printf("wall == map continue...\n");
				continue;
			} else if(c==1) {
				//printf("4\n");
				// top preceed than wall	
				//printf("before cur_y: %d\n", cur_y);
				cur_y--;
				while(map[i][cur_y] != 0) {
					cur_y--;
				}
				//printf("after cur_y: %d\n", cur_y);
				for(int j=0; j<block_length; j++) {
					map[i+j][cur_y] = block[j];
				}
				cnt++;
			} else if(c==2) {
				//printf("5\n");
				// wall preceed than top
				cur_y++;
				for(int j=0; j<block_length; j++) {
					map[i+j][cur_y] = block[j];
				}
				cnt++;
			}
		}
	}
	//print_map(map);
	answer_num = cnt;
	answer_height = getMax(map) - getMin(map) + 1;
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
