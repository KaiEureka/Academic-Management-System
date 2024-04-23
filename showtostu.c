#ifndef SHOWTOSTU
#define SHOWTOSTU

//学生显示自己信息
LRESULT CALLBACK ShowStuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int i=0;
    switch (msg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case ID_BUTTON_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("ShowStuWin", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("ShowStuWin", GetModuleHandle(NULL));
            }
            else   
                return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CREATE: //获取字符间距
            hdc=GetDC(hwnd);
            GetTextMetrics(hdc,&tm);
            cxChar=tm.tmAveCharWidth;
            cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2; //获取字符平均间距
            cyChar=tm.tmHeight+tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            return 0;

        case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps); 
        student st=stuuser->stu;
        wsprintf(szBuffer,TEXT("学生姓名：%s"),st.name);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*(i++),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("学号：%s"),st.id);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*(i++),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("性别：%d"),st.gender);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*(i++),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("专业：%s"),st.major);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*(i++),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("生源地：%s"),st.home);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*(i++),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("班级号:%d"),st.Class);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*(i++),szBuffer,iTarget);
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//学生显示自己总成绩
LRESULT CALLBACK StuAllScoreProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int NUMLINES=20; 
    switch (msg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case ID_BUTTON_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("StuAllScoreWin", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("StuAllScoreWin", GetModuleHandle(NULL));
            }
            else   
                return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            cxCliect=LOWORD(lParam);
            cyClient=HIWORD(lParam);

        case WM_VSCROLL:
            if(LOWORD(wParam)==SB_LINEUP)
                    iVscrollPos -=1;
            if(LOWORD(wParam)==SB_LINEDOWN)
                    iVscrollPos +=1;
            if(LOWORD(wParam)==SB_PAGEUP)
                    iVscrollPos -= cyClient / cyChar;
            if(LOWORD(wParam)==SB_PAGEDOWN)
                    iVscrollPos += cyClient / cyChar;
            if(LOWORD(wParam)==SB_THUMBTRACK)
                    iVscrollPos = HIWORD(wParam);
            if(LOWORD(wParam)==SB_THUMBPOSITION)

            iVscrollPos=max(0,min(iVscrollPos,NUMLINES-1));
            if(iVscrollPos!=GetScrollPos(hwnd,SB_VERT))
            {
                    SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);
                    InvalidateRect(hwnd,NULL,TRUE);
                    UpdateWindow(hwnd);
            }
            return 0;

        case WM_CREATE:
            hdc=GetDC(hwnd);
            GetTextMetrics(hdc,&tm);
            cxChar=tm.tmAveCharWidth;
            cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2;
            cyChar=tm.tmHeight+tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            
            SetScrollRange(hwnd,SB_VERT,0,NUMLINES-1,FALSE);
            SetScrollPos(hwnd,SB_VERT,0,TRUE);
            return 0;

        case WM_PAINT:
        cnty=0;
        hdc = BeginPaint(hwnd, &ps); 
        showhpofastu(stuuser);
        showgcofastu(stuuser);
        cnty=0;
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//学生显示所有课程分数
LRESULT CALLBACK StuClassScoreProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int NUMLINES=280;
    switch (msg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case ID_BUTTON_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("StuClassScoreWin", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_SIZE:
            cxCliect=LOWORD(lParam);
            cyClient=HIWORD(lParam);

        case WM_VSCROLL:
            if(LOWORD(wParam)==SB_LINEUP)
                    iVscrollPos -=1;
            if(LOWORD(wParam)==SB_LINEDOWN)
                    iVscrollPos +=1;
            if(LOWORD(wParam)==SB_PAGEUP)
                    iVscrollPos -= cyClient / cyChar;
            if(LOWORD(wParam)==SB_PAGEDOWN)
                    iVscrollPos += cyClient / cyChar;
            if(LOWORD(wParam)==SB_THUMBTRACK)
                    iVscrollPos = HIWORD(wParam);
            if(LOWORD(wParam)==SB_THUMBPOSITION)

            iVscrollPos=max(0,min(iVscrollPos,NUMLINES-1));
            if(iVscrollPos!=GetScrollPos(hwnd,SB_VERT))
            {
                    SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);
                    InvalidateRect(hwnd,NULL,TRUE);
                    UpdateWindow(hwnd);
            }
            return 0;

        case WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("StuClassScoreWin", GetModuleHandle(NULL));
            }
            else   
                return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            hdc=GetDC(hwnd);
            GetTextMetrics(hdc,&tm);
            cxChar=tm.tmAveCharWidth;
            cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2;
            cyChar=tm.tmHeight+tm.tmExternalLeading;
            ReleaseDC(hwnd,hdc);
            
            SetScrollRange(hwnd,SB_VERT,0,NUMLINES-1,FALSE);
            SetScrollPos(hwnd,SB_VERT,0,TRUE);

            return 0;

        case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps); 
        showscoresofastu(stuuser);
        cnty=0;
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


void ShowStuWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ShowStuProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"ShowStuWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("ShowStuWin"), TEXT("学生"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    500, 200, 700, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    50, 350, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void StuAllScoreWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = StuAllScoreProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"StuAllScoreWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("StuAllScoreWin"), TEXT("学生"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    500, 200, 700, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    50, 350, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void StuClassScoreWindow()
{
    cntx=0,cnty=0;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = StuClassScoreProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"StuClassScoreWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("StuClassScoreWin"), TEXT("学生"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    500, 200, 700, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    300, 350, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif
