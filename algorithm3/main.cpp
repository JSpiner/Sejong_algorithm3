#include <stdio.h>
#include <stdlib.h>

struct Node{ //리스트와 큐에서 쓸 노드 
	int value; 
	struct Node* next;
};

struct Queue{ //큐가 필요한 부분이 있어 큐 선언 
	int count; //큐안에 들어있는 값들의 갯수 
	Node* head; //큐의 앞부분 
	Node* tail; //큐의 뒷부분 
};

struct Node* iList[1100]; //인접리스트 


/*
인접리스트 구조

iList[0] -> node -> node -> node
iList[1] -> node -> node -> node -> node
iList[2] -> node -> node -> node
iList[3] -> node -> node -> node -> node
iList[4] -> node -> node -> node
.
.
.
iList[n-1] -> node -> node -> node -> node

#배열이 아닌 리스트도 링크드 리스트로 해야하는지 잘 몰라 배열로 했는데, 논리적인 구조는 같습니다!

*/

int dList[1100]; //모든 노드의 시작노드로부터의 거리 
int rList[1100]; //결과값이 순차적으로 들어가는 배열 
int n,m,s; //입력받는 n,m,s값들 
int c; // 결과값이 들어가는 index

Queue* initQueue(){ //큐 생성 함수 
	Queue* nQueue;
	nQueue = (Queue*)malloc(sizeof(Queue));
	nQueue->count = 0; //초기화 
	nQueue->head = NULL;
	nQueue->tail = NULL;

	return nQueue;
}

void push(Queue* nQueue, Node* node){ //큐에 노드를 넣는다.
	Node* tmp = (Node*)malloc(sizeof(Node*));
	if(nQueue->tail == NULL){ //큐가 비어있을경우 
		tmp->value = node->value; //값을 넣고 
		tmp->next = NULL;
		nQueue->head = tmp; //머리이자 꼬리를 해당값으로 설정 
		nQueue->tail = tmp;
	}
	else{
		tmp->value = node->value; //값을 넣고 
		tmp->next = NULL;
		nQueue->tail->next = tmp; //제일 뒤에 노드 추가 
		nQueue->tail = tmp;
	}

	nQueue->count++; //갯수 하나 추가 
}

Node* pop(Queue* nQueue){ //큐에서 노드를 빼온다.
	Node* tmp;
	if(nQueue->head==NULL){ //비어있을경우 
		return NULL; //아무것도 안줌 
	}
	else{
		tmp = nQueue->head; //제일 앞 노드를 가져옴  
		nQueue->head = nQueue->head->next; //제일 앞 노드를 삭제 
		nQueue->count--; //갯수 하나 지움 
		return tmp; //노드 리턴 
	}

	return NULL;
}

void insertNode(int a, int b){ //인접리스트에서 노드 삽입 

	Node* visit = iList[a]; //a번째 노드 배열에 삽입 
	while(visit->next !=NULL){ //제일 뒤까지 이동 
		if(visit->value == b) return; //이미 삽입되 있으면 스킵 
		visit = visit->next;
	}
	if(visit->value==b) return; //이미 삽입되 있으면 스킵 
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = b; //새롭게 노드를 생성하여 값을 넣음 
	tmp->next = NULL;
	visit->next = tmp; //인접리스트에 값 추가 

}

void calcDistance(int s){ //s란 값의 노드의 거리를 계싼 
	
	Queue* nQueue = initQueue(); //큐를 생성 

	Node* visit = iList[s]->next; //s번째 노드를 불러옴 
	while(visit !=NULL){ //해당 값의 링크드리스트 탐색 

		if(dList[visit->value]==0 || dList[visit->value]>dList[s]+1){ //거리 계산이 안되있거나 작은값이 들어가있으면 삽입 
			dList[visit->value] = dList[s] + 1; //현재 값보다 한칸 더 움직인 값으로 대입 
			push(nQueue, visit); //모두 대입후 재귀호출을 위해 큐에 삽입 
		}

		visit=visit->next; //다음 노드로 이동 
	}

	while(true){ //큐에 넣었던 노드들로 재귀호출 
		Node* node = pop(nQueue);
		if(node==NULL) break;
		calcDistance(node->value);
	}

}

void DFS(Node* u){ //u노드를 기준으로 DFS 탐색 
	rList[c] = u->value; //노드를 결과값에 삽입 
	c++;

	Node* visit = u->next; //방문한 노드부터 주위 탐색 
	Node* iHeader = NULL; //이동 가능한 방문하지 않은 정점들의 리스트, 여기에 방문가능한 우선순위 기준으로 리스트를 만든다. 
	
	int i;
	int sw;


	while(visit !=NULL){ //노드 탐색 
	
		sw=0;
		for(i=0;i<c;i++){ //이미 방문한 노드인지 탐색 
			if(rList[i]==visit->value){
				sw=1;
				break;
			}
		}

		if(sw==0){ //방문한 기록이 없을 경우
			if(iHeader==NULL){ //방문리스트가 비었을경우 
				iHeader = (Node*)malloc(sizeof(Node)); //첫번째 노드로 삽입 
				iHeader->value = visit->value;
				iHeader->next = NULL;
			}
			else{//방문 리스트가 비지 않았을 경우 
				Node* visit2 = iHeader;  //처음부터 탐색 
				while(visit2!=NULL){
					if(dList[visit2->value]>dList[visit->value]){ //거리가 짧을경우가 우선 
						Node *tmp = (Node*) malloc(sizeof(Node)); //우선순위대로 리스트 중간에 노드 삽입 
						tmp->value = visit2->value;
						tmp->next = visit2->next;
						visit2->value = visit->value;
						visit2->next = tmp;
						break; //노드 삽입을 마쳤으므로 해당 루프 탈출 
					}
					else if(dList[visit2->value]==dList[visit->value]){ //거리가 같을 경우 
						if(visit2->value>visit->value){ //노드의 값으로 비교 
							Node *tmp = (Node*) malloc(sizeof(Node)); //우선순위대로 리스트 중간에 노드 삽입 
							tmp->value = visit2->value;
							tmp->next = visit2->next;
							visit2->value = visit->value;
							visit2->next = tmp;
							break; //노드 삽입을 마쳤으므로 해당 루프 탈출 
						}
					}
					else{ //거리가 길 경우 순차적으로 계속 탐색 

					}
					if(visit2->next ==NULL){ //제일 끝까지없을경우 
						Node *tmp = (Node*) malloc(sizeof(Node)); //제일 뒤에 노드 삽입 
						tmp->value = visit->value;
						tmp->next = NULL;
						visit2->next = tmp;
						break; //노드 삽입을 마쳤으므로 해당 루프 탈출 
					}
					visit2 = visit2->next; //다음 노드 탐색 
				}
			}
		}

		visit = visit->next; //다음 노드 탐색 
	}


	//iHeader엔 방문 가능한 노드들이 우선순위대로 들어있음 

	visit = iHeader;  //방문 가능한 노드들을 처음부터 호출 
	while(visit!=NULL){
		
		sw=0;
		for(i=0;i<c;i++){ //혹시 방문한 값일 경우 생략 
			if(rList[i]==visit->value){
				sw=1;
				break;
			}
		}
		if(sw==0){ //방문하지 않았을경우 재귀호출 
			DFS(iList[visit->value]);
		}
		visit = visit->next; //다음 노드로 이동 
	}


}

int main(){

	int i;
	int a,b;
	scanf("%d %d %d",&n,&m,&s); //값들 입력 
	s--; //배열은 0부터 시작하므로 1 감소 

	for(i=0;i<n;i++){ //인접리스트 초기화 
		iList[i] = (Node*)malloc(sizeof(Node));
		iList[i]->next = NULL;
		iList[i]->value  = (i);
	}

	for(i=0;i<m;i++){
		scanf("%d %d",&a,&b);
		a--; //배열은 0부터 시작하므로 1 감소 
		b--;

		insertNode(a,b); //쌍방 연결이므로 
		insertNode(b,a);//양방향으로 두번 호출한다. 

		
	}
	dList[s] = 1; //시작노드의 거리를 1로 초기화 
	calcDistance(s); //시작노드를 기준으로 거리 계산 
	DFS(iList[s]); //DFS호출 

	for(i=0;i<n;i++){ //출력
		printf("%d",rList[i]+1);
		if(i!=n-1){
			printf(" ");
		}
	}

}