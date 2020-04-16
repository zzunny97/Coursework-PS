#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0


int isReachable(int *gasStation, int N) {
	int goal = N-1;
	int cur = 0;
	int history[2500] = {-1};
	int back[2500] = {0};
	int hidx = 0;
	while(cur < goal) {
		//printf("cur: %d ", cur);
		history[hidx++] = cur;
		int max_jump = gasStation[cur] - back[cur];
		//printf("max_jump: %d\n", max_jump);
		if(max_jump == 0) {
			hidx-=2;
			if(hidx < 0) return false;
			back[history[hidx]]++;
			cur = history[hidx];
		} else {
			cur += max_jump;
		}
	}
	//printf("\n");
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

