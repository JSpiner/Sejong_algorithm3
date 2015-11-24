#include <stdio.h>
#include <stdlib.h>

struct Node{ //����Ʈ�� ť���� �� ��� 
	int value; 
	struct Node* next;
};

struct Queue{ //ť�� �ʿ��� �κ��� �־� ť ���� 
	int count; //ť�ȿ� ����ִ� ������ ���� 
	Node* head; //ť�� �պκ� 
	Node* tail; //ť�� �޺κ� 
};

struct Node* iList[1100]; //��������Ʈ 


/*
��������Ʈ ����

iList[0] -> node -> node -> node
iList[1] -> node -> node -> node -> node
iList[2] -> node -> node -> node
iList[3] -> node -> node -> node -> node
iList[4] -> node -> node -> node
.
.
.
iList[n-1] -> node -> node -> node -> node

#�迭�� �ƴ� ����Ʈ�� ��ũ�� ����Ʈ�� �ؾ��ϴ��� �� ���� �迭�� �ߴµ�, ������ ������ �����ϴ�!

*/

int dList[1100]; //��� ����� ���۳��κ����� �Ÿ� 
int rList[1100]; //������� ���������� ���� �迭 
int n,m,s; //�Է¹޴� n,m,s���� 
int c; // ������� ���� index

Queue* initQueue(){ //ť ���� �Լ� 
	Queue* nQueue;
	nQueue = (Queue*)malloc(sizeof(Queue));
	nQueue->count = 0; //�ʱ�ȭ 
	nQueue->head = NULL;
	nQueue->tail = NULL;

	return nQueue;
}

void push(Queue* nQueue, Node* node){ //ť�� ��带 �ִ´�.
	Node* tmp = (Node*)malloc(sizeof(Node*));
	if(nQueue->tail == NULL){ //ť�� ���������� 
		tmp->value = node->value; //���� �ְ� 
		tmp->next = NULL;
		nQueue->head = tmp; //�Ӹ����� ������ �ش簪���� ���� 
		nQueue->tail = tmp;
	}
	else{
		tmp->value = node->value; //���� �ְ� 
		tmp->next = NULL;
		nQueue->tail->next = tmp; //���� �ڿ� ��� �߰� 
		nQueue->tail = tmp;
	}

	nQueue->count++; //���� �ϳ� �߰� 
}

Node* pop(Queue* nQueue){ //ť���� ��带 ���´�.
	Node* tmp;
	if(nQueue->head==NULL){ //���������� 
		return NULL; //�ƹ��͵� ���� 
	}
	else{
		tmp = nQueue->head; //���� �� ��带 ������  
		nQueue->head = nQueue->head->next; //���� �� ��带 ���� 
		nQueue->count--; //���� �ϳ� ���� 
		return tmp; //��� ���� 
	}

	return NULL;
}

void insertNode(int a, int b){ //��������Ʈ���� ��� ���� 

	Node* visit = iList[a]; //a��° ��� �迭�� ���� 
	while(visit->next !=NULL){ //���� �ڱ��� �̵� 
		if(visit->value == b) return; //�̹� ���Ե� ������ ��ŵ 
		visit = visit->next;
	}
	if(visit->value==b) return; //�̹� ���Ե� ������ ��ŵ 
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = b; //���Ӱ� ��带 �����Ͽ� ���� ���� 
	tmp->next = NULL;
	visit->next = tmp; //��������Ʈ�� �� �߰� 

}

void calcDistance(int s){ //s�� ���� ����� �Ÿ��� ��� 
	
	Queue* nQueue = initQueue(); //ť�� ���� 

	Node* visit = iList[s]->next; //s��° ��带 �ҷ��� 
	while(visit !=NULL){ //�ش� ���� ��ũ�帮��Ʈ Ž�� 

		if(dList[visit->value]==0 || dList[visit->value]>dList[s]+1){ //�Ÿ� ����� �ȵ��ְų� �������� �������� ���� 
			dList[visit->value] = dList[s] + 1; //���� ������ ��ĭ �� ������ ������ ���� 
			push(nQueue, visit); //��� ������ ���ȣ���� ���� ť�� ���� 
		}

		visit=visit->next; //���� ���� �̵� 
	}

	while(true){ //ť�� �־��� ����� ���ȣ�� 
		Node* node = pop(nQueue);
		if(node==NULL) break;
		calcDistance(node->value);
	}

}

void DFS(Node* u){ //u��带 �������� DFS Ž�� 
	rList[c] = u->value; //��带 ������� ���� 
	c++;

	Node* visit = u->next; //�湮�� ������ ���� Ž�� 
	Node* iHeader = NULL; //�̵� ������ �湮���� ���� �������� ����Ʈ, ���⿡ �湮������ �켱���� �������� ����Ʈ�� �����. 
	
	int i;
	int sw;


	while(visit !=NULL){ //��� Ž�� 
	
		sw=0;
		for(i=0;i<c;i++){ //�̹� �湮�� ������� Ž�� 
			if(rList[i]==visit->value){
				sw=1;
				break;
			}
		}

		if(sw==0){ //�湮�� ����� ���� ���
			if(iHeader==NULL){ //�湮����Ʈ�� �������� 
				iHeader = (Node*)malloc(sizeof(Node)); //ù��° ���� ���� 
				iHeader->value = visit->value;
				iHeader->next = NULL;
			}
			else{//�湮 ����Ʈ�� ���� �ʾ��� ��� 
				Node* visit2 = iHeader;  //ó������ Ž�� 
				while(visit2!=NULL){
					if(dList[visit2->value]>dList[visit->value]){ //�Ÿ��� ª����찡 �켱 
						Node *tmp = (Node*) malloc(sizeof(Node)); //�켱������� ����Ʈ �߰��� ��� ���� 
						tmp->value = visit2->value;
						tmp->next = visit2->next;
						visit2->value = visit->value;
						visit2->next = tmp;
						break; //��� ������ �������Ƿ� �ش� ���� Ż�� 
					}
					else if(dList[visit2->value]==dList[visit->value]){ //�Ÿ��� ���� ��� 
						if(visit2->value>visit->value){ //����� ������ �� 
							Node *tmp = (Node*) malloc(sizeof(Node)); //�켱������� ����Ʈ �߰��� ��� ���� 
							tmp->value = visit2->value;
							tmp->next = visit2->next;
							visit2->value = visit->value;
							visit2->next = tmp;
							break; //��� ������ �������Ƿ� �ش� ���� Ż�� 
						}
					}
					else{ //�Ÿ��� �� ��� ���������� ��� Ž�� 

					}
					if(visit2->next ==NULL){ //���� ������������� 
						Node *tmp = (Node*) malloc(sizeof(Node)); //���� �ڿ� ��� ���� 
						tmp->value = visit->value;
						tmp->next = NULL;
						visit2->next = tmp;
						break; //��� ������ �������Ƿ� �ش� ���� Ż�� 
					}
					visit2 = visit2->next; //���� ��� Ž�� 
				}
			}
		}

		visit = visit->next; //���� ��� Ž�� 
	}


	//iHeader�� �湮 ������ ������ �켱������� ������� 

	visit = iHeader;  //�湮 ������ ������ ó������ ȣ�� 
	while(visit!=NULL){
		
		sw=0;
		for(i=0;i<c;i++){ //Ȥ�� �湮�� ���� ��� ���� 
			if(rList[i]==visit->value){
				sw=1;
				break;
			}
		}
		if(sw==0){ //�湮���� �ʾ������ ���ȣ�� 
			DFS(iList[visit->value]);
		}
		visit = visit->next; //���� ���� �̵� 
	}


}

int main(){

	int i;
	int a,b;
	scanf("%d %d %d",&n,&m,&s); //���� �Է� 
	s--; //�迭�� 0���� �����ϹǷ� 1 ���� 

	for(i=0;i<n;i++){ //��������Ʈ �ʱ�ȭ 
		iList[i] = (Node*)malloc(sizeof(Node));
		iList[i]->next = NULL;
		iList[i]->value  = (i);
	}

	for(i=0;i<m;i++){
		scanf("%d %d",&a,&b);
		a--; //�迭�� 0���� �����ϹǷ� 1 ���� 
		b--;

		insertNode(a,b); //�ֹ� �����̹Ƿ� 
		insertNode(b,a);//��������� �ι� ȣ���Ѵ�. 

		
	}
	dList[s] = 1; //���۳���� �Ÿ��� 1�� �ʱ�ȭ 
	calcDistance(s); //���۳�带 �������� �Ÿ� ��� 
	DFS(iList[s]); //DFSȣ�� 

	for(i=0;i<n;i++){ //���
		printf("%d",rList[i]+1);
		if(i!=n-1){
			printf(" ");
		}
	}

}