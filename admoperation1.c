#ifndef ADMOPERATION1
#define ADMOPERATION1

//管理员修改学生成绩
LRESULT CALLBACK AdmChangeScoreProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
    int i=0;
    int NUMLINES=100;
    if(msg==WM_COMMAND)
	{
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            char stuname[100],coursenow[100],gradenow[100];
            GetWindowTextA(g_hEditStuname, stuname, sizeof(stuname));
            GetWindowTextA(g_hEditCourse, coursenow, sizeof(coursenow));
            GetWindowTextA(g_hEditGrade, gradenow, sizeof(gradenow));
			int naturenow=SendMessage(g_hComboBoxpaiming0Type, CB_GETCURSEL, 0, 0);
			
			stunode *Astu;
			Astu=searchstu(stuname);
			if(Astu==NULL)
			{
				MessageBox(NULL,TEXT("学生不存在，请重新输入"),TEXT("警告"),MB_OK);
				return 0;
			}
			clsnode *Acls;
			Acls=searchcls(coursenow);
			if(Acls==NULL)
			{
				MessageBox(NULL,TEXT("课程不存在，请重新输入"),TEXT("警告"),MB_OK);
				return 0;
			}
			
			if(strlen(gradenow)==0)
			{
				MessageBox(NULL,TEXT("成绩输入错误"),TEXT("警告"),MB_OK);
				return 0;
			}
			int cfind=0;
			if(Astu->stu.scoreh->pre==NULL&&Astu->stu.scoreh->next!=NULL)Astu->stu.scoreh=Astu->stu.scoreh->next;
			cosnode* pnow=Astu->stu.scoreh;
			while(pnow!=NULL&&pnow->pre!=NULL)
			{
				if(pnow->cos.c==&(Acls->clsif))cfind=1;
				pnow=pnow->next;
			}
			if(cfind==0)
			{
				MessageBox(NULL,TEXT("该学生并未完成该课程的学习，请重新输入"),TEXT("警告"),MB_OK);
				return 0;
			}
			
			int i=0,flagnow=0,len=strlen(gradenow),gradere;
			for(i=0;i<len;i++)
			{
				if(gradenow[i]<'0'||gradenow[i]>'9')
				{
					flagnow=1;
					break;
				}
				gradere=gradere*10+gradenow[i]-'0';
			}
			if(flagnow==1||gradere>100)
			{
				MessageBox(NULL,TEXT("输入异常，请重新输入"),TEXT("警告"),MB_OK);
				return 0;
			}
			if(naturenow==-1)
			{
				MessageBox(NULL,TEXT("请选择学习性质"),TEXT("警告"),MB_OK);
				return 0;
			}
			MessageBox(NULL,TEXT("成绩修改成功"),TEXT("提示"),MB_OK);
			FILE* fp=fopen(ORDER,"a+");
			fprintf(fp,"changescoreofastu;%s;%s;%d;%d;\n",Astu->stu.name,Acls->clsif.name,gradere,naturenow);
			fclose(fp);
			changescoreofastu(Astu,Acls,gradere,naturenow);
        }
        if(LOWORD(wParam)==ID_BUTTON_ROOT_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmChangeScoreWin", GetModuleHandle(NULL));
            return 0;
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

        CreateWindow(TEXT("STATIC"), TEXT("学生姓名或学号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            10, 75, 160, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("课程名称或课程编号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            10, 120, 160, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("新成绩："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            10, 165, 160, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("学习性质："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            10, 210, 160, 20,hwnd, NULL, NULL, NULL);

        g_hEditStuname = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            200, 75, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        g_hEditCourse = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            200, 120, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditGrade = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            200, 165, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);
            
            
        g_hComboBoxpaiming0Type = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        200, 210, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("初修"));
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("重修"));

        CreateWindow(TEXT("BUTTON"), TEXT("确认修改"),WS_VISIBLE | WS_CHILD,
            120, 260, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

    }

	  if(msg==WM_CLOSE)
	    if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
	    {
	        DestroyWindow(hwnd);
	        UnregisterClass("AdmChangeScoreWin", GetModuleHandle(NULL));
	    }
		else return 0;

    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//管理员录入惩罚
LRESULT CALLBACK AdmEntpunProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            if(LOWORD(wParam)==ID_BUTTON_LOGIN) 
            {
                char stuname[100], eventnow[100];
                GetWindowTextA(g_hEditStuname, stuname, sizeof(stuname));
                GetWindowTextA(g_hEditevent, eventnow, sizeof(eventnow));
				int PunishTypeIndex = SendMessage(g_hComboBoxPunishType, CB_GETCURSEL, 0, 0);

                stunode *Astu;
				Astu=searchstu(stuname);
				if(Astu!=NULL)
                {
                	if(strlen(eventnow)==0)
					{
						MessageBox(NULL,TEXT("请输入处分理由"),TEXT("警告"),MB_OK);
						return 0;
					}
                	if(PunishTypeIndex==-1)
					{
						MessageBox(NULL,TEXT("请选择处分性质"),TEXT("警告"),MB_OK);
						return 0;
					}
                	if(MessageBox(NULL,TEXT("是否为该学生录入该处分"),TEXT("提示"),MB_YESNO)==IDYES)
                    {
                		MessageBox(NULL,TEXT("处分录入成功"),TEXT("提示"),MB_OK);
                    	FILE* fp=fopen(ORDER,"a+");
						fprintf(fp,"enterpunish;%s;%s;%d;\n",Astu->stu.name,eventnow,PunishTypeIndex+1);
						fclose(fp);
						enterpunish(Astu,stuname,PunishTypeIndex+1);
					}
                }
                else MessageBox(NULL,TEXT("学生不存在，请重新输入"),TEXT("警告"),MB_ICONERROR);
                break;
			}
            else if(LOWORD(wParam)==ID_BUTTON_ROOT_EXIT_SYSTEM)
            {
                DestroyWindow(hwnd);
                UnregisterClass("AdmEntpunWin", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_CREATE:
            CreateWindow(TEXT("STATIC"), TEXT("学生的姓名或学号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 70, 135, 20,hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("处分理由："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 115, 135, 20,hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("处分性质"),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 160, 135, 20,hwnd, NULL, NULL, NULL);

            // 创建密码输入框
            g_hEditStuname = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                200, 70, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

            // 创建新密码输入框
            g_hEditevent = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                200, 115, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

		    g_hComboBoxPunishType = CreateWindow(
		        TEXT("COMBOBOX"), TEXT(""),
		        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
		        200, 160, 200, 200,
		        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);
		
		    SendMessage(g_hComboBoxPunishType, CB_ADDSTRING, 0, (LPARAM)TEXT("警告"));
		    SendMessage(g_hComboBoxPunishType, CB_ADDSTRING, 0, (LPARAM)TEXT("严重警告"));
		    SendMessage(g_hComboBoxPunishType, CB_ADDSTRING, 0, (LPARAM)TEXT("处分"));
		    SendMessage(g_hComboBoxPunishType, CB_ADDSTRING, 0, (LPARAM)TEXT("严重处分"));
		    SendMessage(g_hComboBoxPunishType, CB_ADDSTRING, 0, (LPARAM)TEXT("留校察看"));
		    SendMessage(g_hComboBoxPunishType, CB_ADDSTRING, 0, (LPARAM)TEXT("开除"));

            // 创建修改按钮
            CreateWindow(TEXT("BUTTON"), TEXT("确认添加"),WS_VISIBLE | WS_CHILD,
                130, 225, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN, NULL, NULL);

            break;

        case  WM_CLOSE: 
	        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
		    {
		        DestroyWindow(hwnd);
		        UnregisterClass("AdmEntpunWin", GetModuleHandle(NULL));
		    }
	    	else return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//管理员录入加分项 
LRESULT CALLBACK AdmEnthorProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    	char stuname[100], eventnow[100],pointnow[100];
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case ID_BUTTON_LOGIN:
                
                GetWindowTextA(g_hEditStuname, stuname, sizeof(stuname));
                GetWindowTextA(g_hEditevent, eventnow, sizeof(eventnow));
                GetWindowTextA(g_hEditpoint, pointnow, sizeof(pointnow));
                stunode *Astu;
				Astu=searchstu(stuname);
				if(Astu!=NULL)
                {
                	if(strlen(eventnow)==0)
					{
						MessageBox(NULL,TEXT("请输入加分项"),TEXT("警告"),MB_OK);
						return 0;
					}
                	if(strlen(pointnow)==0)
					{
						MessageBox(NULL,TEXT("请输入加分值"),TEXT("警告"),MB_OK);
						return 0;
					}
                	int flagnow1=0,flagnow2=0,i=0,len=strlen(pointnow);
                	double sc=0,xs=0,zs=0.1;
					for(i=0;i<len;i++)
                	{
                		if(pointnow[i]!='.'&&(pointnow[i]<'0'||pointnow[i]>'9'))
                		{flagnow1=1;break;}
						if(pointnow[i]=='.')
						{
							if(i==0||i==len-1||flagnow2==1)
							{flagnow1=1;break;}
							flagnow2=1;
						}
						else
						{
							if(flagnow2==0)
								sc=sc*10+pointnow[i]-'0';
							else xs+=zs*(pointnow[i]-'0'),zs*=0.1;
						}
					}
					sc+=xs;
                    if(sc>=0&&sc<=1&&flagnow1==0)
                    {
                    	if(MessageBox(NULL,TEXT("是否为该学生录入该加分项"),TEXT("提示"),MB_YESNO)==IDYES)
                    	{
                    		MessageBox(NULL,TEXT("新综合素质加分项录入成功"),TEXT("提示"),MB_OK);
	                        FILE* fp=fopen(ORDER,"a+");
							fprintf(fp,"enterhonor;%s;%s;%.2lf;\n",Astu->stu.name,eventnow,sc);
							fclose(fp);
							enterhonor(Astu,eventnow,sc);
						}
                    }
                    else MessageBox(NULL,TEXT("录入错误，请重新输入正确的数值！"),TEXT("警告"),MB_ICONERROR);
                }
                else MessageBox(NULL,TEXT("学生不存在，请重新输入"),TEXT("警告"),MB_ICONERROR);
                break;

            case ID_BUTTON_ROOT_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("AdmEnthorWin", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_CREATE:
            CreateWindow(TEXT("STATIC"), TEXT("学生的姓名或学号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 70, 135, 20,hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("新综合素质加分项："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 115, 135, 20,hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("录入项目在计算综测分时所加的分值："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 160, 135, 40,hwnd, NULL, NULL, NULL);

            g_hEditStuname = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                200, 70, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

            g_hEditevent = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                200, 115, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

            g_hEditpoint = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                200, 160, 200, 40,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("确认添加"),WS_VISIBLE | WS_CHILD,
                130, 225, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN, NULL, NULL);

            break;

        case  WM_CLOSE:
	        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
		    {
		        DestroyWindow(hwnd);
		        UnregisterClass("AdmEnthorWin", GetModuleHandle(NULL));
		    }
	    	else return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void AdmEntpunWindow()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmEntpunProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmEntpunWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmEntpunWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 500, 450, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 300, 230, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdmEnthorWindow()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmEnthorProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmEnthorWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmEnthorWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 500, 450, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 300, 230, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdmChangeScoreWindow()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmChangeScoreProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmChangeScoreWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmChangeScoreWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 450, 450, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 330, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

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
