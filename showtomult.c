#ifndef SHOWTOMULT
#define SHOWTOMULT

//学生(教师)显示自己所有课程
LRESULT CALLBACK StuClassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int NUMLINES=200;
    switch (msg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case ID_BUTTON_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("StuClassWin", GetModuleHandle(NULL));
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
                UnregisterClass("StuClassWin", GetModuleHandle(NULL));
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
        showcls();
        cnty=0;
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//(学生，教师，管理员)查专业成绩
LRESULT CALLBACK SearchGradeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
    int i=0;
    int NUMLINES=100;
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            ordern=SendMessage(g_hComboBoxpaiming0Type, CB_GETCURSEL, 0, 0)+1;
            req_1=SendMessage(g_hComboBoxpaiming1Type, CB_GETCURSEL, 0, 0);
            req_2=SendMessage(g_hComboBoxpaiming2Type, CB_GETCURSEL, 0, 0)+1;

            char year[100],classnow[100];
            int p=0;
            GetWindowTextA(g_hEditUseryear, year, sizeof(year));
            GetWindowTextA(g_hEditUsermajor, majornow, sizeof(majornow));
            GetWindowTextA(g_hEditUserclass, classnow, sizeof(classnow));
            if(ordern==0)
            {
				MessageBox(NULL,TEXT("请选择排名类型"),TEXT("警告"),MB_OK);
				return 0;
			}
			if(req_1==-1)
            {
				MessageBox(NULL,TEXT("请选择排序顺序"),TEXT("警告"),MB_OK);
				return 0;
			}
			if(req_2==0)
            {
				MessageBox(NULL,TEXT("请选择排序依据"),TEXT("警告"),MB_OK);
				return 0;
			}
            Ayear=0;
            while(year[p]>='0'&&year[p]<='9')
            {
                Ayear=Ayear*10+(year[p]-'0');
                p++;
            }
            Aclass=p=0;
            while(classnow[p]>='0'&&classnow[p]<='9')
            {
                Aclass=Aclass*10+(classnow[p]-'0');
                p++;
            }
            if(searchyear(Ayear)==0)
                MessageBox(NULL,TEXT("未查到在该年入学的学生，请重新输入"),TEXT("警告"),MB_OK);
            else{
                if(searchmajor(majornow)==0)
                    MessageBox(NULL,TEXT("未查到该专业的学生，请重新输入"),TEXT("警告"),MB_OK);
                else{
                    flag=1;
                    InvalidateRect(hwnd,NULL,TRUE);
                    UpdateWindow(hwnd);
                }
            }

        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("SearchGradeWin", GetModuleHandle(NULL));
            return 0;
        }
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

	if(msg==WM_PAINT)
	{
		if(flag==1)
		{
			hdc = BeginPaint(hwnd, &ps);
			sort_three(Ayear,majornow,ordern,req_1,req_2,Aclass);
			cnty=0;
			EndPaint(hwnd, &ps);
		}
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

        CreateWindow(TEXT("STATIC"), TEXT("排名类型："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 75, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("排序顺序："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 120, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("排序依据："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 165, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("入学年份："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 210, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("专业："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 255, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("班级(选填)："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 300, 80, 20,hwnd, NULL, NULL, NULL);

        g_hEditUseryear = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            150, 210, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        g_hEditUsermajor = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 255, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUserclass = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 300, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("查询"),WS_VISIBLE | WS_CHILD,
            120, 335, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

        g_hComboBoxpaiming0Type = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 75, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("综合排名"));
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("分班排名"));
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("班级学生排名"));

        g_hComboBoxpaiming1Type = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 120, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hComboBoxpaiming1Type, CB_ADDSTRING, 0, (LPARAM)TEXT("从高到低"));
        SendMessage(g_hComboBoxpaiming1Type, CB_ADDSTRING, 0, (LPARAM)TEXT("从低到高"));

        g_hComboBoxpaiming2Type = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 165, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("总绩点排名"));
        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("必修课绩点排名"));
        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("保研绩点排名"));
        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("出国绩点排名"));
		SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("总成绩排名"));
        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("必修课成绩排名"));
        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("保研成绩排名"));
        SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("出国成绩排名"));
    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("SearchGradeWin", GetModuleHandle(NULL));
        }
        else   
                return 0;
    }

    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//管理员(教师)查看学生总成绩
LRESULT CALLBACK AdmStuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int NUMLINES=8000;
    if(msg==WM_COMMAND){
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmStuWin", GetModuleHandle(NULL));
            return 0;
        }
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

	if(msg==WM_PAINT)
	{
			hdc = BeginPaint(hwnd, &ps);
            showstudentscores();
			cnty=0;
			EndPaint(hwnd, &ps);
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
    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmStuWin", GetModuleHandle(NULL));
        }
        else   
                return 0;
        }

    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//管理员(教师)查看课程分析
LRESULT CALLBACK ClassAnalyProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int NUMLINES=100;
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            GetWindowTextA(g_hEditUseryear, Bclass, sizeof(Bclass));
            if(searchcls(Bclass)==NULL)
                MessageBox(NULL,TEXT("未查询到该课程，请重新输入"),TEXT("警告"),MB_OK);
            else{
                    flag=1;
                    InvalidateRect(hwnd,NULL,TRUE);
                    UpdateWindow(hwnd);
                }

        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("ClassAnalyWin", GetModuleHandle(NULL));
            return 0;
        }
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

	if(msg==WM_PAINT)
	{
		if(flag==1)
		{
			hdc = BeginPaint(hwnd, &ps);
			survey_subject(searchcls(Bclass));
			cnty=0;
			EndPaint(hwnd, &ps);
		}
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

        CreateWindow(TEXT("STATIC"), TEXT("查询课程："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 120, 80, 20,hwnd, NULL, NULL, NULL);

        g_hEditUseryear = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            150, 120, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("查询"),WS_VISIBLE | WS_CHILD,
            120, 250, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("ClassAnalyWin", GetModuleHandle(NULL));
        }
        else   
            return 0;
        }

    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void StuClassWindow()
{
    cntx=0,cnty=0;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = StuClassProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"StuClassWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("StuClassWin"), TEXT("学生"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
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

void SearchGradeWindow()
{
    HWND hwnd;
	cntx=0,cnty=0,flag=0;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = SearchGradeProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"SearchGradeWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("SearchGradeWin"), TEXT("学生"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    400, 200, 900, 700, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 400, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdmStuWindow()
{
    HWND hwnd;
	cntx=0,cnty=0,flag=0;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmStuProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmStuWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmStuWin"), TEXT("管理员"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    450, 200, 900, 700, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        500, 400, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void ClassAnalyWindow()
{
    HWND hwnd;
	cntx=0,cnty=0,flag=0;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ClassAnalyProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"ClassAnalyWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("ClassAnalyWin"), TEXT("管理员"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    400, 200, 900, 700, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 400, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif
