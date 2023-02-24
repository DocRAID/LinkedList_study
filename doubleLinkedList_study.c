#include<stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct NODE {
	struct NODE* next;
	struct NODE* prev;
	char data[64];
} NODE;
NODE* g_Head, * g_Tail;
int g_Size = 0;

void InitList() {
	g_Head = (NODE*)malloc(sizeof(NODE));
	g_Tail = (NODE*)malloc(sizeof(NODE));
	memset(g_Head, 0, sizeof(NODE));
	memset(g_Tail, 0, sizeof(NODE));
	g_Size = 0;
	g_Head->next = g_Tail;
	g_Tail->prev = g_Head;
}

void ReleaseList() {
	printf("List Released!\n");
	if (!IsEmpty()) {
		NODE* visitor = g_Head->next;
		while (visitor!= NULL) {
			NODE* delete = visitor;
			visitor = visitor->next;
			free(delete);
		}
	}
	InitList();
}
void PrintList() {
	NODE* visitor = g_Head->next;
	printf("Head:[%p], Tail:[%p]\n", g_Head, g_Tail);
	while (visitor->next != NULL) {
		printf("prev:[%p], now:[%p], next:[%p], value: %s\n", visitor->prev, visitor, visitor->next, visitor->data);
		visitor = visitor->next;
	}
	printf("(Result) Length: %d, Empty: %d", ListLength(), IsEmpty());
	return;
}
//push front
int PushAtHead(const char* pszData) {
	NODE* temp = malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	strcpy_s(temp->data, sizeof(temp->data), pszData);
	temp->prev = g_Head;
	temp->next = g_Head->next;

	g_Head->next->prev = temp;
	g_Head->next = temp;
	g_Size++;
}
//push back
int PushAtTail(const char* pszData) {
	NODE* temp = malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	strcpy_s(temp->data, sizeof(temp->data), pszData);
	
	temp->next = g_Tail;
	temp->prev = g_Tail->prev;
	g_Tail->prev->next = temp;
	g_Tail->prev = temp;
	g_Size++;
}
//pop front
int PopHead() {
	if (!IsEmpty()) {
		NODE* temp = g_Head->next;
		printf("PopHead() :%s\n", temp->data);
		g_Head->next = temp->next;
		temp->next->prev = g_Head;
		free(temp);
		g_Size--;
	}
}
//pop back
int PopTail() {
	if (!IsEmpty()) {
		NODE* temp = g_Tail->prev;
		printf("PopTail() :%s\n", temp->data);
		g_Tail->prev = temp->prev;
		temp->prev->next = g_Tail;
		free(temp);
		g_Size--;
	}
}
//find
NODE* Search(const char* pszData) {
	NODE* visitor = g_Head->next;
	while (visitor->next != NULL) {
		if (!strcmp(visitor->data, pszData)) {
			return visitor;
		}
		visitor = visitor->next;
	}
	return NULL;
}
int IsExist(const char* pszData) {
	if (Search(pszData) != NULL)
		return 1;
	else
		return 0;
}
//find and pop
int Delete(const char* pszData) {
	NODE* delete = Search(pszData);
	if (delete != NULL) {
		delete->prev->next = delete->next;
		delete->next->prev = delete->prev;
		free(delete);
		return 1;
	}
	else {
		return 0;
	}
}

int ListLength() {
	return g_Size;
}
//empty
int IsEmpty() {
	if (g_Size == 0)
		return 1;
	else
		return 0;
}
int main(void) {
	//초기화
	InitList();
	//push test
	PushAtHead("hello world");
	PushAtHead("c lang pointer test");
	PushAtHead("Linked list");
	PushAtTail("pushed at tail");
	PushAtTail("delete");
	PrintList();

	//delete and search test
	if (Delete("delete")) {
		//if exist data delete
		printf("delete Success!\n");
	}
	else {
		printf("delete Not found(404)\n");
	}

	if (Delete("asdf")) {
		//if not exist data delete
		printf("asdf Success!\n");
	}
	else {
		printf("asdf Not found(404)\n");
	}
	//pop test
	PopHead();
	PopTail();

	PrintList();
	ReleaseList();


	PrintList();
	return 0;
}