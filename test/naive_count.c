#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int n;
	scanf("%d", &n);

	int *arr = (int*)malloc(sizeof(int) * n);
	for(int i=0; i<n; i++) 
		scanf("%d", &arr[i]);
	int max = arr[0];
	for(int i=0; i<n; i++) {
		if(max < arr[i])
			max = arr[i];
	}
	max += 1;
	int *count = (int*)malloc(sizeof(int) * max);
	memset(count, 0, max);
	for(int i=0; i<n; i++)
		count[arr[i]]++;

	for(int i=0; i<max; i++) {
		if(count[i] % 2 != 0)
			printf("%d\n", i);
	}
	return 0;
	
}
