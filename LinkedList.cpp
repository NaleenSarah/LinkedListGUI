// LinkedList.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "LinkedList.h"

#define MAX_LOADSTRING 100

#define xstr(s) str(s)
#define str(s) #s

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LINKEDLIST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LINKEDLIST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LINKEDLIST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LINKEDLIST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 500, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   myLList = new node;
   initList(myLList, 0);
   POINT ButtonLoc = { 4,4 };

   for (auto &a : GUIButtons) {
           a.hwnd = CreateWindow(
           L"BUTTON",  
           a.txt,
           WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
           ButtonLoc.x,  // x position 
           ButtonLoc.y,  // y position 
           100,        // Button width
           30,         // Button height
           hWnd,       // Parent window
           NULL,       // No menu.
           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
           NULL // Pointer not needed.
       );      
       ButtonLoc.y += 50;
   }
   

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int wmCode = HIWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                if (wmCode == BN_CLICKED) {
                    // if we are managing this button then we skip
                    // the DefWindowProc() otherwise it is called.
                    if (btnProcess(hWnd, (HWND)lParam)) {
                        break;
                    }
                }
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            
            PrintList(hdc,myLList);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void initList(struct node* head, int Value) {
    head->Value = Value;
    head->next = NULL;
}
void addNode(struct node* head, int Value) {
    node* current = head;
    node* newNode = new node;
    newNode->Value = Value;
    newNode->next = NULL;
    
    while (current) {
        if (current->next == NULL) {
            current->next = newNode;
            return;
        }
        current = current->next;
    }
}
void insertHead(struct node** head, int Value) {
    node* newNode = new node;
    newNode->Value = Value;
    newNode->next = *head;
    //Make the passed node address = the new new head.
    *head = newNode;
}

//Delete by Pointer
int deleteNode(struct node** head, node* pDelete) { 
    node* current = *head;
    if (pDelete == *head) {
        *head = current->next;
        delete pDelete;
        pDelete = NULL;
        return 1;
    }

    while (current) {
        if (current->next == pDelete) {
            current->next = pDelete->next;
            delete pDelete;
            pDelete = NULL;
            return 1;
        }
        current = current->next;
    }
    return 0;
}
//Delete by Node Number
int deleteNode(struct node** head, UINT32 uNode) { 
    node* current = *head;
    if (uNode < sizeof(myLList)) {
        for (UINT32 counter = 0; counter < sizeof(myLList); counter += 1) {
            if (counter == uNode) {
                deleteNode(head, current);
                return 1;
            }
            current = current->next;
        }
    }
    return 0;
}
struct node* reverse(struct node** head) { 
    node* parent = *head;
    node* me = parent->next;
    node* child = me->next;

    /* make parent as tail */
    parent->next = NULL;
    while (child) {
        me->next = parent;
        parent = me;
        me = child;
        child = child->next;
    }
    me->next = parent;
    *head = me;
    return *head;
}

void PrintList(HDC hdc, struct node* FirstNode)
{
    TCHAR curPointer[32];
    TCHAR nxtPointer[32];
    TCHAR curValue[32]; 
    node* current = FirstNode;
    int iTotal = 1, iPadding = 4, iHeight = 16;
    //While Current is Valid (not Null).
    while (current) {
        
        swprintf_s(curPointer, 32, L"0x%p", current);
        swprintf_s(nxtPointer, 32, L"0x%p", current->next);
        swprintf_s(curValue, 32, L"%d", current->Value);
        TextOut(hdc, 200, iTotal*iPadding + ((iTotal-1)  * (iPadding+iHeight)), curPointer, wcslen(curPointer));
        TextOut(hdc, 300, iTotal*iPadding + ((iTotal-1)  * (iPadding+iHeight)), nxtPointer, wcslen(nxtPointer));
        TextOut(hdc, 400, iTotal*iPadding + ((iTotal-1)  * (iPadding+iHeight)), curValue, wcslen(curValue));

        current = current->next;
        iTotal++;
    }
    
    
}

int btnProcess(HWND hwnd, HWND hwndBtn) {
    for (auto& a : GUIButtons) {
        if (a.hwnd == hwndBtn) {
            // this is one of our buttons so we increment button click count.
            // then invalidate the window area and update to trigger WM_PAINT message.
            switch (a.Type)
            {
            case AddNode: {
                //Insert at the end of the list or bottom
                addNode(myLList, rand() % 100 + 1);
                }break;
            case InsertHead: {
                //Insert at the head/beginning/top of list
                insertHead(&myLList, rand() % 100 + 1);
                }break;
            case Delete: {
                //Delete node, using 0 (head) for testing.
                deleteNode(&myLList, (UINT32)0);
                }break;
            case Reverse: {
                reverse(&myLList);
                }break;

            }
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
            return 1;    // indicate we processed this event.
        }
    }
    return 0;

}
