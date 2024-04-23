#ifndef SHOWTOADM
#define SHOWTOADM
 
//向管理员展示学生基本信息 
LRESULT CALLBACK ShowStutoAdmProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int i=0;
    int NUMLINES=120;
    if(msg==WM_COMMAND)
    {
        if((LOWORD(wParam))==ID_BUTTON_ROOT_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("ShowStutoAdmWin", GetModuleHandle(NULL));
        }
        return 0;
    }
    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("ShowStutoAdmWin", GetModuleHandle(NULL));
        }
        else return 0;
    }
    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    if(msg==WM_CREATE) 
    {	
        hdc=GetDC(hwnd);
        GetTextMetrics(hdc,&tm);
        cxChar=tm.tmAveCharWidth;
        cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2;
        cyChar=tm.tmHeight+tm.tmExternalLeading;
        ReleaseDC(hwnd,hdc);
        SetScrollRange(hwnd,SB_VERT,0,NUMLINES-1,FALSE);
        SetScrollPos(hwnd,SB_VERT,0,TRUE);
        return 0;
    }
    if(msg==WM_PAINT)
    {
        hdc = BeginPaint(hwnd, &ps); 
        stunode *pnow;
        pnow=stulih;
        wsprintf(szBuffer,TEXT("--------------------------------------------------------------------------------------"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
        
		while(pnow!=NULL)
		{
			student st=pnow->stu; 
            wsprintf(szBuffer,TEXT("学生姓名：%s"),st.name);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            char gendernow[3];
            if(st.gender==1)strcpy(gendernow,"男");
            else  strcpy(gendernow,"女");
            wsprintf(szBuffer,TEXT("学号：%s 性别：%s 专业：%s"),st.id,gendernow,st.major);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            wsprintf(szBuffer,TEXT("生源地：%s 班级号：%d"),st.home,st.Class);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            wsprintf(szBuffer,TEXT("--------------------------------------------------------------------------------------"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            pnow=pnow->next;
        }
        i=0;
		EndPaint(hwnd, &ps);
		return 0;
	}
	if(msg==WM_SIZE)
	{
        cxCliect=LOWORD(lParam);
        cyClient=HIWORD(lParam);
	}
	if(msg==WM_VSCROLL)
	{
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
	}
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//管理员展示教师基本信息
LRESULT CALLBACK ShowTeatoAdmProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int i=0;
    int NUMLINES=50;
    if(msg==WM_COMMAND)
    {
   		if((LOWORD(wParam))==ID_BUTTON_ROOT_EXIT_SYSTEM)
        {
			DestroyWindow(hwnd);
        	UnregisterClass("ShowTeatoAdmWin", GetModuleHandle(NULL));
        }
        return 0;
    }
    if(msg==WM_CLOSE)
	{
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
	    {
	        DestroyWindow(hwnd);
	        UnregisterClass("ShowTeatoAdmWin", GetModuleHandle(NULL));
	    }
	    else return 0;
	}
    if(msg==WM_DESTROY)
    {
    	PostQuitMessage(0);
        return 0;
	}
    if(msg==WM_CREATE) 
	{	
	    hdc=GetDC(hwnd);
	    GetTextMetrics(hdc,&tm);
	    cxChar=tm.tmAveCharWidth;
	    cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2;
	    cyChar=tm.tmHeight+tm.tmExternalLeading;
	    ReleaseDC(hwnd,hdc);
        SetScrollRange(hwnd,SB_VERT,0,NUMLINES-1,FALSE);
        SetScrollPos(hwnd,SB_VERT,0,TRUE);
	    return 0;
	}
    if(msg==WM_PAINT)
    {
    	hdc = BeginPaint(hwnd, &ps); 
        teanode *pnow;
		pnow=tealih;
        wsprintf(szBuffer,TEXT("--------------------------------------------------------------------------------------"));
    	iTarget=lstrlen(szBuffer);
    	TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
    	
		while(pnow!=NULL)
		{
	        wsprintf(szBuffer,TEXT("教师姓名：%s"),pnow->tea.name);
	        iTarget=lstrlen(szBuffer);
	        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
	        wsprintf(szBuffer,TEXT("教师账户：%s"),pnow->tea.account);
	        iTarget=lstrlen(szBuffer);
	        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
	        wsprintf(szBuffer,TEXT("教师密码：%s"),pnow->tea.pwd);
	        iTarget=lstrlen(szBuffer);
	        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
	        wsprintf(szBuffer,TEXT("--------------------------------------------------------------------------------------"));
    		iTarget=lstrlen(szBuffer);
    		TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
	        pnow=pnow->next;
		}
    	i=0;
		EndPaint(hwnd, &ps);
		return 0;
	}
	if(msg==WM_SIZE)
	{
        cxCliect=LOWORD(lParam);
        cyClient=HIWORD(lParam);
	}
	if(msg==WM_VSCROLL)
	{
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
	}
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//管理员展示课程基本信息
LRESULT CALLBACK ShowCostoAdmProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int i=0;
    int NUMLINES=120;
    if(msg==WM_COMMAND)
    {
        if((LOWORD(wParam))==ID_BUTTON_ROOT_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("ShowCostoAdmWin", GetModuleHandle(NULL));
        }
        return 0;
    }
    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("ShowCostoAdmWin", GetModuleHandle(NULL));
        }
        else return 0;
    }
    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    if(msg==WM_CREATE) 
    {	
        hdc=GetDC(hwnd);
        GetTextMetrics(hdc,&tm);
        cxChar=tm.tmAveCharWidth;
        cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2;
        cyChar=tm.tmHeight+tm.tmExternalLeading;
        ReleaseDC(hwnd,hdc);
        SetScrollRange(hwnd,SB_VERT,0,NUMLINES-1,FALSE);
        SetScrollPos(hwnd,SB_VERT,0,TRUE);
        return 0;
    }
    if(msg==WM_PAINT)
    {
        hdc = BeginPaint(hwnd, &ps); 
        clsnode *p=clslih;
        wsprintf(szBuffer,TEXT("--------------------------------------------------------------------------------------"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);

        while(p!=NULL)
        {
            cls st=p->clsif;
            wsprintf(szBuffer,TEXT("课程名称：%s  老师：%s"),st.name,st.teacher);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            char naturenow[6];
            if(st.nature==0)strcpy(naturenow,"必修");
            else  if(st.nature==1)strcpy(naturenow,"选修");
            else  strcpy(naturenow,"限选");
            wsprintf(szBuffer,TEXT("课程性质：%s 课程编号：%s"),naturenow,st.id);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            sprintf(szBuffer,TEXT("学分：%.1lf"),st.cdt);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            wsprintf(szBuffer,TEXT("--------------------------------------------------------------------------------------"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
            p=p->next;
        }
        i=0;
        EndPaint(hwnd, &ps);
        return 0;
    }
    if(msg==WM_SIZE)
    {
        cxCliect=LOWORD(lParam);
        cyClient=HIWORD(lParam);
    }
    if(msg==WM_VSCROLL)
    {
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
	}
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void ShowTeatoAdmWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ShowTeatoAdmProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"ShowTeatoAdmWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("ShowTeatoAdmWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    200, 200, 700, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    400, 200, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void ShowCostoAdmWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ShowCostoAdmProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"ShowCostoAdmWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("ShowCostoAdmWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    200, 200, 700, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    400, 200, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void ShowStutoAdmWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ShowStutoAdmProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"ShowStutoAdmWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("ShowStutoAdmWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    200, 200, 700, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    400, 200, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif
