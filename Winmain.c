#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "project.h"

char ORDER[100]="./order.txt";
char EA[100]="./ea.txt";
char SCORE[100]="./scorelist.txt";
char CLS[100]="./clslist.txt";
char ROOT[100]="./rootlist.txt";
char TEA[100]="./teacherlist.txt";
char STU[100]="./stulist.txt";

HWND g_hComboBoxLoginType;
HWND g_hComboBoxpaiming0Type;
HWND g_hComboBoxpaiming1Type;
HWND g_hComboBoxpaiming2Type;
HWND g_hComboBoxpaiming3Type;
HWND g_hEditUsername;
HWND g_hEditUsername1;
HWND g_hEditPassword;
HWND g_hEditPassword0;
HWND g_hEditPassword1;
HWND g_hEditUseryear;
HWND g_hEditUsermajor;
HWND g_hEditUserclass;
HWND g_hEditUserid;
HWND g_hEditUserid1;
HWND g_hEditUsergender;
HWND g_hEditUserpwd;
HWND g_hEditUserpwd1;
HWND g_hEditUserhome;
HWND g_hEditUserypwd;
HWND g_hEditStuname;
HWND g_hEditevent;
HWND g_hEditpoint;
HWND g_hComboBoxPunishType;
HWND g_hEditCourse;
HWND g_hEditGrade;
TCHAR szBuffer[128];
size_t iTarget;
HDC hdc;
PAINTSTRUCT ps;
TEXTMETRIC tm;

char majornow[100],Bclass[100],str1,ch,str[10000];
int ordern,tos=1,req_1,req_2,Ayear,Aclass,cntx,cnty,flag;
int aid,Tstu,i,j,emptynum=0,flaginson2=0;//account id; teacher or student
stunode *stulih,*stulit,*stunowinall,*stuuser,*astu;
cosnode *coslih,*coslit,*cosnowinall;
clsnode *clslih,*clslit,*clstobe;
teanode *tealih,*tealit,*teauser;
rootnode *rootlih,*rootlit,*rootuser;
apt *aptlih=NULL,*Q,*P;
nstunode *nstulihh,*nstuinall;
static int cxChar,cxCaps,cyChar,cxCliect,cyClient,iVscrollPos;

//主窗口
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch(msg) {
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case ID_BUTTON_LOGIN:
                    {
                        // 获取选择的登录类型
                        int loginTypeIndex = SendMessage(g_hComboBoxLoginType, CB_GETCURSEL, 0, 0);

                        char username[100], password[100];
                        GetWindowTextA(g_hEditUsername, username, sizeof(username));
                        GetWindowTextA(g_hEditPassword, password, sizeof(password));

                        // 根据选择的登录类型进行不同的登录验证
                        if(loginTypeIndex==-1){
                        	MessageBox(hwnd,TEXT("请选择登录身份"), TEXT("提示"), MB_OK);
                        	return 0;
						}
                        switch (loginTypeIndex) {
                            case 0: // 学生
                                stuuser=searchstuid(username);
                                if (stuuser!=NULL&&strcmp(password,stuuser->stu.pwd)==0) {
                                    MessageBoxA(hwnd,TEXT("登录成功！"), TEXT("提示"), MB_OK);
                                    tos=1;StudentWindow();
                                } else {
                                    MessageBoxA(hwnd, TEXT("账号或密码错误，请重新输入！"), TEXT("错误"), MB_OK | MB_ICONERROR);
                                }
                                break;
                            case 1: // 教师
                                teauser=searchtea(username);
                                if (teauser!=NULL&&strcmp(password,teauser->tea.pwd)==0) {
                                    MessageBoxA(hwnd,TEXT("登录成功！"), TEXT("提示"), MB_OK);
                                    tos=0;TeacherWindow();
                                } else {
                                    MessageBoxA(hwnd, TEXT("账号或密码错误，请重新输入！"), TEXT("错误"), MB_OK | MB_ICONERROR);
                                }
                                break;
                            case 2: // 管理员
                                rootuser=searchroot(username);
                                if(rootuser!=NULL&&strcmp(password,rootuser->rt.pwd)==0) {
                                    MessageBoxA(hwnd,TEXT("登录成功！"), TEXT("提示"), MB_OK);
                                    tos=1;AdminWindow();
                                } else {
                                    MessageBoxA(hwnd, TEXT("账号或密码错误，请重新输入！"), TEXT("错误"), MB_OK | MB_ICONERROR);
                                }
                                break;
                        }
                    }
                    break;
            }
            break;

        case WM_CLOSE: //关闭确认
        if(MessageBox(NULL,TEXT("是否关闭该程序"),TEXT("请确认"),MB_YESNO)==IDYES)
                DestroyWindow(hwnd);
        else   
                return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG Msg;

    // 注册窗口类
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = TEXT("WindowClass");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("窗口注册失败！"), TEXT("错误"), MB_ICONERROR);
        return 0;
    }

    // 创建窗口
    Initialization();
    hwnd = CreateWindowEx(
        0,
        TEXT("WindowClass"),
        TEXT("登录窗口"),
        WS_OVERLAPPEDWINDOW,
        650, 300, 450, 300,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("窗口创建失败！"), TEXT("错误"), MB_ICONERROR);
        return 0;
    }

    // 创建欢迎文字
    CreateWindow(
        TEXT("STATIC"), TEXT("欢迎使用教务管理系统。先选择身份，再输入账号密码登录。"),
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        0, 30, 450, 30,
        hwnd, NULL, NULL, NULL);
    CreateWindow(
        TEXT("STATIC"), TEXT("类型："),
        WS_VISIBLE | WS_CHILD | SS_LEFT,
        50, 75, 50, 20,
        hwnd, NULL, NULL, NULL);
    CreateWindow(
        TEXT("STATIC"), TEXT("账号："),
        WS_VISIBLE | WS_CHILD | SS_LEFT,
        50, 120, 50, 20,
        hwnd, NULL, NULL, NULL);
    CreateWindow(
        TEXT("STATIC"), TEXT("密码："),
        WS_VISIBLE | WS_CHILD | SS_LEFT,
        50, 165, 50, 20,
        hwnd, NULL, NULL, NULL);

    // 创建登录方式选择下拉框
    g_hComboBoxLoginType = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        130, 75, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

    SendMessage(g_hComboBoxLoginType, CB_ADDSTRING, 0, (LPARAM)TEXT("学生"));
    SendMessage(g_hComboBoxLoginType, CB_ADDSTRING, 0, (LPARAM)TEXT("教师"));
    SendMessage(g_hComboBoxLoginType, CB_ADDSTRING, 0, (LPARAM)TEXT("管理员"));

    // 创建账号输入框
    g_hEditUsername = CreateWindow(
        TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        130, 120, 200, 20,
        hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

    // 创建密码输入框
    g_hEditPassword = CreateWindow(
        TEXT("EDIT"), TEXT(""),
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
        130, 165, 200, 20,
        hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

    // 创建登录按钮
    CreateWindow(
        TEXT("BUTTON"), TEXT("登录"),
        WS_VISIBLE | WS_CHILD,
        150, 200, 150, 45,
        hwnd, (HMENU)ID_BUTTON_LOGIN, NULL, NULL);

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
