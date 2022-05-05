#pragma once

#include "resource.h"
struct node {
	//Data could be anything.
	int Value;
	//Pointer to the next Node in "List".
	struct node* next;

};
enum enumButtons
{
    AddNode = 1,
    InsertHead,
    Delete,
    Reverse
};
static struct {
    enumButtons Type;
    const wchar_t* txt;    // pointer to text to display on button face     // count of number of times button clicked
    HWND     hwnd;         // button window handle which identifies the button
} GUIButtons[] = {
    {AddNode, L"Add Node", 0},
    {InsertHead,L"Insert Head", 0},
    {Delete,L"Delete", 0},
    {Reverse,L"Reverse", 0}
};
node* myLList;
void initList(struct node* head, int Value);
void addNode(struct node* head, int Value);
void insertHead(struct node** head, int Value);

//Delete by Pointer
int deleteNode(struct node** head, node* pDelete);
//Delete by Node Number
int deleteNode(struct node** head, UINT32 uNode);
struct node* reverse(struct node** head);
void PrintList(HDC hdc,struct node* FirstNode);

int btnProcess(HWND hwnd, HWND hwndBtn );
