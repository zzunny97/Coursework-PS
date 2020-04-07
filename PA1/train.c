#include <stdio.h>
#include <stdlib.h>

void solve(int num_train, int power[]);
void wrap(int* num_train, int power[], int is_power_same, int idx);

int main() {
	int num_train, power[1000] = {0};
	scanf("%d", &num_train);
	for(int i=0; i<num_train; i++) {
		scanf("%d", &power[i]);
	}

	solve(num_train, power);
}

void solve(int num_train, int power[]) {
	int crash_occured = 1;
	while(crash_occured) {
		crash_occured = 0;
		for(int i=0; i<num_train-1; i++) {
			int power1 = power[i];
			int power2 = power[i+1];
			if(power1 < 0) {
				continue;
			}
			if(power1 * power2 < 0) {
				if(abs(power1) > abs(power2)) {
					wrap(&num_train, power, 0, i+1);
				} else if(abs(power1) < abs(power2)) {
					wrap(&num_train, power, 0, i);
				} else {
					wrap(&num_train, power, 1, i); 
				}
				crash_occured = 1;
				break;
			}
		}
		if(crash_occured == 0) {
			// count all trains, no any more crash
			for(int i=0; i<num_train; i++) {
				printf("%d ", power[i]);
			}
			printf("\n");
		}
	}
	
}

void wrap(int* num_train, int power[], int is_power_same, int idx) {
	// delete two
	if(is_power_same) {
		for(int i=idx+2; i<*num_train; i++) {
			power[i-2] = power[i];
		}
		*num_train -= 2;
	} else { //delete only one
		for(int i=idx+1; i<*num_train; i++) {
			power[i-1] = power[i];
		}
		*num_train -= 1;
	}
}
