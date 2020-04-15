#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct Node {
	int location;
	int checked;
	int num_child;
	struct Node* child;
	struct Node* prev;
} Node;

void insert(Node* p, int location) {
	p->child = (Node*)realloc(p->child, sizeof(Node)*(p->num_child + 1));
	p->child[p->num_child].location = location;
	p->child[p->num_child].checked = false;
	p->child[p->num_child].num_child = 0;
	p->child[p->num_child].child = NULL;
	p->child[p->num_child].prev =p;
	p->num_child++;
}

int isReachable(int *gasStation, int N) {
	int goal = N-1;
	Node root;
	root.location = 0;
	root.checked = false;
	root.prev = NULL;
	root.num_child = 0;
	Node* cur = &root;

	while(cur != NULL && cur->location != goal) {
		//printf("cur->location: %d\n", cur->location);
		int jump = gasStation[cur->location];
		int tmp = cur->checked;
		cur->checked = true;
		if(jump == 0) {
			//printf("jump == 0, choose another child\n");
			// backtrack
			if(cur->prev == NULL) return false;
			int choosed = false;
			for(int i=cur->prev->num_child-1; i>=0; i--) {
				if(cur->prev->child[i].checked == false) {
					cur = &(cur->prev->child[i]);
					choosed = true;
					break;
				}
			}
			if(choosed) continue;
			else cur = cur->prev;
		}
		else {
			// not checked yet
			//printf("jump != 0\n");
			if(tmp  == false) {
				//printf("not checked, so insert child\n");
				for(int i=1; i<=jump; i++) {
					insert(cur, cur->location + i);
				}
				cur = &(cur->child[cur->num_child - 1]);
			} 
			// already checked
			else {
				// backtrack
				//printf("already checked before, backtrack\n");
				if(cur->prev == NULL) return false;
				int choosed = false;
				for(int i=cur->prev->num_child-1; i>=0; i--) {
					if(cur->prev->child[i].checked == false) {
						cur = &(cur->prev->child[i]);
						choosed = true;
						break;
					}
				}
				if(choosed) continue;
				else cur = cur->prev;
			}
		}
		//cur->checked = true;
	}
	if(cur==NULL)
		return false;
	
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

