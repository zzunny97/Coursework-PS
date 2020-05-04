#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <map>
#include <utility>
#include <time.h>

#define n1_max 15000000
#define n2_max 150000000

using namespace std;

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

	map<int, bool> m;
	for(int i=0; i<n1_num; i++) {
		m.insert(make_pair(n1[i], true));
	}
	for(int i=0; i<n2_num; i++) {
		if(m.find(n2[i]) != m.end()) {
			++answer;
		}
	}
	
	/*
	if(n2_num / n1_num >= 5) {
		int start_idx = binary_search(n1[0], n2, 0, n2_num-1);
		int end_idx = binary_search(n1[n1_num-1], n2, 0, n2_num-1);
		printf("%d %d\n", start_idx, end_idx);
	}

	while(first1 != last1 && first2 != last2) {
		if(*first1 < *first2) ++first1;
		else if(*first1 > *first2) ++first2;
		else {
			++answer;
			++first1;
			++first2;
		}
	}
	*/
}


int main()
{

FILE *fp =  fopen("sample5_answer.txt", "r");
FILE *fp2 = fopen("sample5_n2.txt", "r");
FILE *fp3 = fopen("sample5_n1.txt", "r");


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

find_common();

printf("Real_Common : %d\n",common ); //Real answer
printf("Calculated_Common : %d\n",answer ); //Your guess


return 0;

}
