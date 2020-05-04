#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define n1_max 15000000
#define n2_max 150000000

int n1[n1_max];
int n2[n2_max];

int input[3];
int n1_num;
int n2_num;

int answer = 0; //final common

int binary_search(int target, int *arr, int start, int end);

// Find common part of two array and reserve at global variable 'answer' You can change function to int function if you want to return value.
void find_common(){
	int *first1 = n1;
	int *last1= n1 + n1_num;
	int *first2 = n2;
	int *last2 = n2 + n2_num;

	while(first1 != last1 && first2 != last2) {
		if(*first1 < *first2) {
			++first1;
		}
		else if(*first1 > *first2) {
			++first2;
		}
		else {
			++answer;
			++first1;
			++first2;
		}
	}
	
}

int binary_search2(int target, int *arr, int start, int end) {
	int mid;
	while(start<=end) {
		mid	= (start+end) / 2;
		if(arr[mid] < target) {
			start = mid+1;
		}
		else if(arr[mid] > target) {
			end = mid-1;
		}
		else {
			return mid;
		}
	}
	return -1;
}


int binary_search(int target, int *arr, int start, int end) {
	int mid;
	while(start<=end) {
		mid	= (start+end) / 2;
		if(arr[mid] < target) {
			start = mid+1;
		}
		else if(arr[mid] > target) {
			end = mid-1;
		}
		else {
			break;
		}
	}
	//printf("start: %d, end: %d\n", start, end);
	return mid; 
}

void intersect(int *d, int* q, int mind, int maxd, int minq, int maxq) {
	//printf("mind: %d ", mind);
	//printf("maxd: %d ", maxd);
	//printf("minq: %d ", minq);
	//printf("maxq: %d\n", maxq);
	//printf("%d %d %d %d\n", d[mind], d[maxd], q[minq], q[maxq]);
	
	
	//int midq, midqval, midd;
	
	if(mind > maxd || minq > maxq) return;
	if(d[maxd] < q[minq] || q[maxq] < d[mind]) return;
	int midq = (minq+maxq) / 2;
	int midqval = q[midq];
	int midd = binary_search(midqval, d, mind, maxd);
	//printf("midd: %d\n", midd);
	if(midd-mind > midq-minq) {
		intersect(d, q, mind, midd, minq, midq-1);
	}
	else {
		intersect(q, d, minq, midq-1, mind, midd);
	}
	if(d[midd] == midqval) {
		++answer;
	}
	if(maxd-midd > maxq-midq) {
		intersect(d, q, midd, maxd, midq+1, maxq);
	}
	else {
		intersect(q, d, midq+1, maxq, midd, maxd);
	}
}

void find_common2() {
	
	if(n2_num / n1_num > 2) {
		int *n1_cur = n1;
		int *n1_end = n1 + n1_num;
		int *n2_cur = n2;
		int *n2_end = n2 + n2_num;

		while(n1_cur!=n1_end && n2_cur!=n2_end) {
			if(*n1_cur < *n2_cur) {
				++n1_cur;
			}
			else if(*n1_cur > *n2_cur) {
				++n2_cur;
			}
			else {
				++answer;
				++n1_cur;
				++n2_cur;
			}
		}
	}
	else {
		intersect(n2, n1, 0, n2_num-1, 0, n1_num-1);
	}
}

void find_common3() {
	int *first1 = n1;
	int *last1= n1 + n1_num;
	int *first2 = n2;
	int *last2 = n2 + n2_num;
	
	int ratio = n2_num / n1_num;
	int h = 1;
	printf("ratio: %d\n", ratio);
	if(ratio > 2) {
		while(first1 < last1 && first2 < last2) {
			if(*first2 < *first1) {
				first2 += ratio;
			} else if(*first2 > *first1) {
				/*
				while(*first2 > *first1) {
					--first2;
				}
				if(*first2 < *first1) {
					++first1;
					++first2;
				}
				*/
				first2 -= ratio;
				while(*first2 < *first1) {
					++first2;
				}
				if(*first2 > *first1) {
					++first1;
				}
			} else {
				++answer;
				++first1;
				++first2;
			}
		}
		first2 -= ratio;
		while(first2 < last2) {
			if(*first2 == *first1) ++answer;
			++first2;
		}
	}
	else {
		while(first1 != last1 && first2 != last2) {
			if(*first1 < *first2) ++first1;
			else if(*first1 > *first2) ++first2;
			else {
				++answer;
				++first1;
				++first2;
			}
		}
	}


}


int main()
{

FILE *fp =  fopen("sample5_answer.txt", "r");
FILE *fp2 = fopen("sample5_n2.txt", "r");
FILE *fp3 = fopen("sample5_n1.txt", "r");
//FILE *fp =  fopen("answer.txt", "r");
//FILE *fp2 = fopen("input2.txt", "r");
//FILE *fp3 = fopen("input1.txt", "r");


for(int i=0; i<3; i++){
        fscanf(fp, "%d", &input[i]);
}

fclose(fp);

n2_num = input[0];
n1_num = input[1];
int common = input[2]; //Correct Answer!

for(int i =0; i<n2_num; i++){
        fscanf(fp2, "%d", &n2[i]);
}

for(int i =0; i<n1_num; i++){
        fscanf(fp3, "%d", &n1[i]);
}
printf("n2_num: %d\n", n2_num);
printf("n1_num: %d\n", n1_num);


fclose(fp2);
fclose(fp3);
struct timeval start, end;
double diff;


printf("common3\n");
gettimeofday(&start, NULL);
find_common3();
gettimeofday(&end, NULL);
diff = (end.tv_sec - start.tv_sec) + ((double)(end.tv_usec - start.tv_usec) / 1000000);
printf("elapsed: %f\n", diff);
printf("Real_Common : %d\n",common ); //Real answer
printf("Calculated_Common : %d\n",answer ); //Your guess

/*

answer = 0;
printf("original\n");
gettimeofday(&start, NULL);
find_common();
gettimeofday(&end, NULL);
diff = (end.tv_sec - start.tv_sec) + ((double)(end.tv_usec - start.tv_usec) / 1000000);
printf("elapsed: %f\n", diff);
printf("Real_Common : %d\n",common ); //Real answer
printf("Calculated_Common : %d\n",answer ); //Your guess
*/

return 0;

}
