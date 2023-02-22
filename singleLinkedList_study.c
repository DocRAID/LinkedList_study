#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct NODE {
	struct NODE* next;
	char data[64];
} NODE;

NODE g_head = { 0 };
//find
NODE* IsExist(char* pszData) { //개션 필요?? 모르겠다
	NODE* cur = g_head.next;
	NODE* temp = &g_head;
	while (cur != NULL) {
		if (strcmp(cur->data, pszData) == 0) {
			return temp;
		}
		temp = temp->next;
		cur = cur->next;
	}
	return 0;
}
//exist
int IsEmpty() {
	if (g_head.next == NULL) {
		return 1;
	}
	return 0;
}
//length
int Length() {
	NODE* temp = g_head.next;
	int count = 0;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}
//add at head
void PushAtHead(char* pszData) {
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->data, sizeof(pNode->data), pszData);
	if (IsEmpty()) {
		g_head.next = pNode;
	}
	else {
		pNode->next = g_head.next;
		g_head.next = pNode;
	}
}
//add at next
void PushAtTail(char* pszData) {
	NODE* temp = &g_head;
	NODE* cur = g_head.next;
	while (cur != NULL) {
		temp = temp->next;
		cur = cur->next;
	}
	NODE* pNode = malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE));
	strcpy_s(pNode->data, sizeof(pNode->data), pszData);
	temp->next = pNode;
	return;
}
//find -> delete
int Delete(char* pszData) {
	NODE* temp = IsExist(pszData);
	if (temp != 0) {
		NODE* dummy = temp->next;
		temp->next = dummy->next;
		free(dummy);
		return 1;
	}
	else {
		return 0;
	}
}
//print all
void ExtractAll() {
	NODE* temp = g_head.next;
	while (temp != NULL) {
		printf("[%p] value is: %s, next [%p]\n", temp, temp->data, temp->next);
		temp = temp->next;
	}
	return;
}
int main() {
	//note : 컴퓨터는 잘못 없다.
	printf("empty : %d\n", IsEmpty());
	printf("length : %d\n", Length());
	ExtractAll();

	PushAtHead("hello1");
	PushAtHead("hello2");
	PushAtHead("hello3");
	PushAtTail("hello4");

	printf("empty : %d\n", IsEmpty());
	printf("length : %d\n", Length());
	ExtractAll();

	//if exist value in list
	if (IsExist("hello3") != 0) {
		printf("find!\n");
	}
	else {
		printf("not find!\n");
	}

	//if not extis value in list
	if (IsExist("hello0") != 0) {
		printf("find!\n");
	}
	else {
		printf("not find!\n");
	}

	Delete("hello4");
	printf("empty : %d\n", IsEmpty());
	printf("length : %d\n", Length());
	ExtractAll();
	Delete("hello2");
	printf("empty : %d\n", IsEmpty());
	printf("length : %d\n", Length());
	ExtractAll();
	Delete("hello1");
	printf("empty : %d\n", IsEmpty());
	printf("length : %d\n", Length());
	ExtractAll();
	Delete("hello3");
	printf("empty : %d\n", IsEmpty());
	printf("length : %d\n", Length());
	ExtractAll();
	return 0;
}