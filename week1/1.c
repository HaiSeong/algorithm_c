#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char elem;			//	저장할 값
	struct node *prev;	//	이전 노드
	struct node *next;	//	다음 노드
}Node;


typedef struct doubleLinkedList	//	이중연결리스트
{
	Node *header;
	Node *trailer;
}DoubleLinkedList;

Node *initNode(char elem)	//	노드 초기화
{
	Node *node;
	node = (Node *)malloc(sizeof(Node));
	node->elem = elem;
	
	return node;
}

DoubleLinkedList *initList()	//	리스트 초기화
{
	DoubleLinkedList *list;
	list = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
	
	list->header = initNode(0);		// 헤더에 더미노드 생성
	list->trailer = initNode(0);	// 트레일러에 더미노드 생성

 	list->header->next = list->trailer;	//	연결
	list->trailer->prev = list->header;

	return list;
}

void add(DoubleLinkedList *list, int r, char e)	//	list의 r번째 순위에 e를 배치시킴
{
	int cnt = 1;
	Node *temp;
	temp = list->header;

	while (cnt < r && temp != list->trailer)	//	r번째 순위까지 temp를 전진시킴
	{
		temp = temp->next;
		cnt++;
	}
	
	if (cnt < r && temp == list->trailer)	//	잘못된 명령 (r번째 인덱스에 아직 도착 못했는데 temp가 trailer일 때)
	{
		printf("invalid position\n");
		return ;
	}

	Node *new = initNode(e);	//	(temp)=(temp->next)
	new->prev = temp;			//	(temp)<-(new) (temp->next)
	new->next = temp->next;		//	(temp)<-(new)->(temp->next)
	temp->next->prev = new;		//	(temp)<-(new)=(temp->next)
	temp->next = new;			//	(temp)=(new)=(temp->next)
}

void delete(DoubleLinkedList *list, int r)
{
	int cnt = 0;
	Node *temp;
	temp = list->header;

	while (cnt < r && temp != list->trailer)	//	r번째 순위까지 temp를 전진시킴
	{
		temp = temp->next;
		cnt++;
	}

	if (temp == list->trailer)	//	잘못된 명령 (r번째 인덱스에 아직 도착 못했는데 temp가 trailer일 때)
	{
		printf("invalid position\n");
		return ;
	}
									//	(temp) : 삭제할 노드
									//	(temp->prev) (temp->next)
	temp->prev->next = temp->next;	//	(temp->prev)->(temp->next)
	temp->next->prev = temp->prev;	//	(temp->prev)=(temp->next)
	free(temp);
}

char get(DoubleLinkedList *list, int r)
{
	int cnt = 0;
	Node *temp;
	temp = list->header;

	while (cnt < r && temp != list->trailer)	//	r번째 순위까지 temp를 전진시킴
	{
		temp = temp->next;
		cnt++;
	}

	if (temp == list->trailer)	//	잘못된 명령 (r번째 인덱스에 아직 도착 못했는데 temp가 trailer일 때)
	{
		printf("invalid position\n");
		return 0;
	}

	return temp->elem;
}


char print(DoubleLinkedList *list)
{
	Node *temp;
	temp = list->header;

	while (temp->next != list->trailer)	//	하나씩 증가하며 출력
	{
		temp = temp->next;
		printf("%c",temp->elem);
	}

	printf("\n");
	return temp->elem;
}

int main()
{
	DoubleLinkedList *list;
	list = initList();
	int N, r;
	char command, e, c;
	scanf("%d",&N);
	fflush(stdin);

	for (int i=0; i<N; i++)
	{
		getchar();
		scanf("%c",&command);
		
		switch (command)
		{
			case 'A':
				scanf("%d %c",&r, &e);
				add(list, r, e);
				break;
			case 'D':
				scanf("%d",&r);
				delete(list, r);
				break;
			case 'G':
				scanf("%d",&r);
				c = get(list, r);
				if (c != 0)
					printf("%c\n",c);
				break;
			case 'P':
				print(list);
				break;
		}
		fflush(stdin);
	}
	
	printf("\n");
}

