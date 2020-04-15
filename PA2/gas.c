#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct Node {
	int location;
	int is_checked;
	int child_num;
	struct Node* child;
	struct Node* parent;
} Node;

int isReachable(int *gasStation, int N) {
	int goal = N-1;
	int cur_idx = 0;
	Node start;
	start.location = cur_idx;
	start.is_checked = true;
	start.parent = NULL;
	start.child_num = gasStation[cur_idx];
	start.child = (Node*)malloc(sizeof(Node) * gasStation[cur_idx]);
	Node* cur = &start;
	while(1) {
		for(int i=0; i<cur->child_num; i++) {
			cur->child[i].location = cur->location + gasStation[cur_idx];
		}
		

	}
	return true;
}

int main() {
	char *input = NULL;
	int in_tmp, N = 0;
	size_t size;
	char *ptr;
	int gasStation[2500];
	int result = true;

	getline(&input, &size, stdin);
	ptr = strtok(input, " ");
	while(ptr != NULL) {
		in_tmp = atoi(ptr);
		gasStation[N++] = in_tmp;
		ptr = strtok(NULL, " ");
	}
	result = isReachable(gasStation, N);
	printf("%s\n", (result?"true":"false"));
	return 0;
}

