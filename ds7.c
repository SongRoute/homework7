/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    printf("[----- [송동선] [2023078041] -----]\n");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
    node->key = key; // 새로운 노드에 key값 저장

    listNode* p = h->first; // p는 headnode의 첫번째 노드
    listNode* prev = NULL; // prev는 p의 이전 노드

	// headnode가 비어있을 경우
    if (p == NULL) {
        node->link = NULL;
        h->first = node;
        return 0;
    }

	// key값이 가장 작을 경우
    while (p != NULL) {
        if (p->key >= key) {
            break;
        }
        prev = p;
        p = p->link;
    }

	// key값이 가장 클 경우
    if (prev == NULL) {
        node->link = h->first;
        h->first = node;
    }

	// key값이 중간에 있을 경우
    else {
        node->link = p;
        prev->link = node;
    }

    return 0;

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
    node->key = key; // 새로운 노드에 key값 저장
    node->link = NULL;	// 새로운 노드의 link는 NULL

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

    listNode* node = h->first; // headnode의 첫번째 노드

	// headnode가 비어있을 경우
    if (node == NULL) {
        printf("headnode가 비었습니다.\n");
        return 0;
    }

    h->first = node->link; // headnode의 첫번째 노드를 두번째 노드로 변경
    free(node);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

    listNode* p = h->first; // headnode의 첫번째 노드
    listNode* prev = NULL; // p의 이전 노드

	// headnode가 비어있을 경우
    while (p != NULL) {
        if (p->key == key) {
            break;
        }
        prev = p;
        p = p->link;
    }

	// key값이 없을 경우
    if (p == NULL) {
        printf("key값이 없습니다.\n");
        return 0;
    }

	// key값이 가장 작을 경우
    if (prev == NULL) {
        h->first = p->link;
    }
	
	// key값이 중간에 있을 경우
    else {
        prev->link = p->link;
    }

    free(p);

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

    listNode* p = h->first; // headnode의 첫번째 노드
    listNode* prev = NULL; // p의 이전 노드

	// headnode가 비어있을 경우
    if (p == NULL) {
        printf("There is no node to delete.\n");
        return 0;
    }

	// headnode에 노드가 하나만 있을 경우
    while (p->link != NULL) {
        prev = p;
        p = p->link;
    }

	// headnode에 노드가 하나만 있을 경우
    if (prev == NULL) {
        h->first = NULL;
    }
	
	// headnode에 노드가 여러개 있을 경우
    else {
        prev->link = NULL;
    }

    free(p);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

    listNode* p = h->first;// headnode의 첫번째 노드
    listNode* prev = NULL;// p의 이전 노드
    listNode* next = NULL;// p의 다음 노드

	// headnode가 비어있을 경우
    while (p != NULL) {
        next = p->link;
        p->link = prev;
        prev = p;
        p = next;
    }

    h->first = prev; // headnode의 첫번째 노드를 prev로 변경

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

