#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;
	if(num1 < num2)
		return -1;
	else if(num1 > num2)
		return 1;
	else
		return 0;
}

void print(int* weights, int num) {
	for(int i=0; i<num; i++) {
		printf("%d ", weights[i]);
	}
	printf("\n");

}

int numShoppingBag(int* weights, int num, int limit){	
	int cnt = 0;
	for(int i=0; i<num; i++) {
		if(weights[i] > limit) {
			return -1;
		}
	}
	qsort(weights, num, sizeof(int), compare);
	/*
	for(int i=0; i<num; i++) {
		printf("%d ", *(weights + i));
	}
	printf("\n");
	*/

	while(num) {
		printf("num: %d, cnt: %d\n", num, cnt);
		print(weights, num);
		if(num == 1) {
			cnt++;
			num--;
		}
		else {
			if(weights[0] + weights[num-1] <= limit) {
				for(int i=0; i<num-1; i++) {
					weights[i] = weights[i+1];
				}
				cnt++;
				num -= 2;
			} else {
				num--;
				cnt++;
			}
		}
	}

	return cnt;
}


int main() {
	int num;
	int limit;
	scanf("%d", &limit);
	scanf("%d", &num);
	int* weights = (int*)malloc(sizeof(int) * num);
	for(int i=0; i<num; i++) {
		scanf("%d", &weights[i]);
	}
	printf("%d\n", numShoppingBag(weights, num, limit));
	return 0;
}
