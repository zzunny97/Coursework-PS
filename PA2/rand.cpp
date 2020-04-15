#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	srand(time(NULL));
	for(int i=0; i<10; i++) {
		int n = rand() % 50 + 1;
		for(int i=0; i<n; i++) {
			if(i != n-1)
				cout << rand() % n << " ";
			else
				cout << rand() %n;
		}
		cout << endl;
	}

}


