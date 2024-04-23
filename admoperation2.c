#ifndef ADMOPERATION2
#define ADMOPERATION2

//管理员录入学生
LRESULT CALLBACK AdmInStuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            int gender=SendMessage(g_hEditUsergender,CB_GETCURSEL, 0, 0);
            char year[20],classnow[20],name[20],id[20],major[50],pwd[20],home[20];
            int Ayear=0,Aclass=0;
            GetWindowTextA(g_hEditUseryear, year, sizeof(year));
            GetWindowTextA(g_hEditUserclass, classnow, sizeof(classnow));
            GetWindowTextA(g_hEditUsername1, name, sizeof(name));
            GetWindowTextA(g_hEditUserid1, id, sizeof(id));
            GetWindowTextA(g_hEditUsermajor, major, sizeof(major));
            GetWindowTextA(g_hEditUserpwd1, pwd, sizeof(pwd));
            GetWindowTextA(g_hEditUserhome, home, sizeof(home));
            
            if(strlen(year)==0||strlen(classnow)==0||strlen(name)==0||strlen(id)==0||strlen(major)==0||strlen(pwd)==0||strlen(home)==0||gender==-1)
            {
            	MessageBox(NULL,TEXT("输入数据不完整"),TEXT("警告"),MB_OK);
                return 0;
			}
            int len=strlen(year);
            int i; 
            for(i=0;i<len;++i)
    		{
    			
    			if(year[i]<'0'||year[i]>'9')
    			{
    				MessageBox(NULL,TEXT("入学年份异常"),TEXT("警告"),MB_OK);
					return 0; 
				}
				Ayear=Ayear*10+(year[i]-'0');
			}
			if(Ayear<1900||Ayear>2300)
    		{
    			MessageBox(NULL,TEXT("入学年份异常，请输入适当年份"),TEXT("提示"),MB_OK);
				return 0; 
			}
			len=strlen(classnow);
			for(i=0;i<len;++i)
    		{
    			
    			if(classnow[i]<'0'||classnow[i]>'9')
    			{
    				MessageBox(NULL,TEXT("班级异常"),TEXT("警告"),MB_OK);
					return 0; 
				}
				Aclass=Aclass*10+(classnow[i]-'0');
			}
			stunode *stunow1=stulih;
			while(stunow1!=NULL)
			{
				if(strcmp(stunow1->stu.id,id)==0)
				{
					MessageBox(NULL,TEXT("已有相同学号的同学，请确认学号"),TEXT("警告"),MB_OK);
					return 0;
				}
				stunow1=stunow1->next;
			}
			if(MessageBox(NULL,TEXT("是否录入该学生"),TEXT("提示"),MB_YESNO)==IDYES)
			{
				addstudentofroot(name,id,gender,major,Ayear,Aclass,pwd,home);
	            MessageBox(NULL,TEXT("学生录入成功"),TEXT("通过"),MB_OK);
			}
        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmInStuWin", GetModuleHandle(NULL));
            return 0;
        }
    }

    if(msg==WM_CREATE)
    {
        CreateWindow(TEXT("STATIC"), TEXT("姓名："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 75, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("学号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 120, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("性别："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 165, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("专业："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 210, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("入学年份："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            380, 75, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("班级："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            380, 120, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("密码："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            380, 165, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("生源地："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            380, 210, 80, 20,hwnd, NULL, NULL, NULL);

        g_hEditUsername1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            150, 75, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        g_hEditUserid1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 120, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUsermajor = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 210, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUseryear = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            480, 75, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUserclass = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            480, 120, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUserpwd1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            480, 165, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUserhome = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            480, 210, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("执行操作"),WS_VISIBLE | WS_CHILD,
            300, 250, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

        g_hEditUsergender = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 165, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hEditUsergender, CB_ADDSTRING, 0, (LPARAM)TEXT("女"));
        SendMessage(g_hEditUsergender, CB_ADDSTRING, 0, (LPARAM)TEXT("男"));

    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmInStuWin", GetModuleHandle(NULL));
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

//管理员转出学生
LRESULT CALLBACK AdmOutStuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            char name[20];
            GetWindowTextA(g_hEditUsername1, name, sizeof(name));
            deletestuofroot(name);
        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmOutStuWin", GetModuleHandle(NULL));
            return 0;
        }
    }

    if(msg==WM_CREATE)
    {
        CreateWindow(TEXT("STATIC"), TEXT("姓名："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 75, 80, 20,hwnd, NULL, NULL, NULL);

        g_hEditUsername1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            150, 75, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("执行操作"),WS_VISIBLE | WS_CHILD,
            120, 130, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmOutStuWin", GetModuleHandle(NULL));
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

//管理员录入课程
LRESULT CALLBACK AdmInCouProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            int nature=SendMessage(g_hEditUsergender,CB_GETCURSEL, 0, 0);
            char tea[20],name[50],id[20],credit[20];
            GetWindowTextA(g_hEditUseryear, credit, sizeof(credit));
            GetWindowTextA(g_hEditUsermajor, tea, sizeof(tea));
            GetWindowTextA(g_hEditUsername1, name, sizeof(name));
            GetWindowTextA(g_hEditUserid1, id, sizeof(id));
            if(strlen(credit)==0||strlen(tea)==0||strlen(name)==0||strlen(id)==0||nature==-1)
            {
            	MessageBox(NULL,TEXT("输入数据不完整"),TEXT("警告"),MB_OK);
                return 0;
			}
			teanode *teanow1=tealih;
			while(teanow1!=NULL)
			{
				if(strcmp(teanow1->tea.name,tea)==0){break;}
				teanow1=teanow1->next;
			}
			if(teanow1==NULL)
			{
				MessageBox(NULL,TEXT("未查到该教师，请重新输入"),TEXT("警告"),MB_OK);
				return 0;
			}
			clsnode *clsnow1=clslih;
			while(clsnow1!=NULL)
			{
				if(strcmp(clsnow1->clsif.id,id)==0)
				{
					MessageBox(NULL,TEXT("已有相同编号的课程，请重新输入编号"),TEXT("警告"),MB_OK);
					return 0;
				}
				clsnow1=clsnow1->next;
			}
			int flagnow1=0,flagnow2=0,i=0,len=strlen(credit);
            double Acredit=0,xs=0,zs=0.1;
            for(i=0;i<len;i++)
            {
                if(credit[i]!='.'&&(credit[i]<'0'||credit[i]>'9'))
                {flagnow1=1;break;}
                if(credit[i]=='.')
                {
                    if(i==0||i==len-1||flagnow2==1)
                    {flagnow1=1;break;}
                    flagnow2=1;
                }
                else
                {
                    if(flagnow2==0)
                        Acredit=Acredit*10+credit[i]-'0';
                    else xs+=zs*(credit[i]-'0'),zs*=0.1;
                }
            }
            Acredit+=xs;
            if(flagnow1==1||Acredit>10)
            {
            	MessageBox(NULL,TEXT("学分异常，请重新输入"),TEXT("警告"),MB_OK);
				return 0;
			}
            
            if(MessageBox(NULL,TEXT("是否录入该课程"),TEXT("提示"),MB_YESNO)==IDYES)
			{
                inputcourse(name,id,nature,tea,Acredit);
                FILE* fp=fopen(ORDER,"a+");
                fprintf(fp,"inputcourse;%s;%s;%d;%s;%lf;\n",name,id,nature,tea,Acredit);
                fclose(fp);
            	MessageBox(NULL,TEXT("课程录入成功"),TEXT("通过"),MB_OK);
			}
        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmInCouWin", GetModuleHandle(NULL));
            return 0;
        }
    }

    if(msg==WM_CREATE)
    {
        CreateWindow(TEXT("STATIC"), TEXT("课程名："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 75, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("课程编号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 120, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("授课教师："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 165, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("课程性质："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 210, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("课程学分："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 255, 80, 20,hwnd, NULL, NULL, NULL);

        g_hEditUsername1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            150, 75, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        g_hEditUserid1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 120, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUsermajor = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 165, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUseryear = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 255, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("执行"),WS_VISIBLE | WS_CHILD,
            120, 300, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

        g_hEditUsergender = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 210, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hEditUsergender, CB_ADDSTRING, 0, (LPARAM)TEXT("必修"));
        SendMessage(g_hEditUsergender, CB_ADDSTRING, 0, (LPARAM)TEXT("选修"));
        SendMessage(g_hEditUsergender, CB_ADDSTRING, 0, (LPARAM)TEXT("限选"));
    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmInCouWin", GetModuleHandle(NULL));
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

//管理员录入老师
LRESULT CALLBACK AdmInTeaProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            char name[20],id[50],pwd[20];
            GetWindowTextA(g_hEditUsername1, name, sizeof(name));
            GetWindowTextA(g_hEditUserid1, id, sizeof(id));
            GetWindowTextA(g_hEditUserpwd1, pwd, sizeof(pwd));
            if(strlen(name)==0||strlen(id)==0||strlen(pwd)==0)
            {
            	MessageBox(NULL,TEXT("输入数据不完整"),TEXT("警告"),MB_OK);
                return 0;
			}
            teanode *teanow1=tealih;
			while(teanow1!=NULL)
			{
				if(strcmp(teanow1->tea.account,id)==0)
				{
					MessageBox(NULL,TEXT("已有相同账号的教师，请重新输入账号"),TEXT("警告"),MB_OK);
					return 0;
				}
				teanow1=teanow1->next;
			}
            if(MessageBox(NULL,TEXT("是否录入该老师"),TEXT("提示"),MB_YESNO)==IDYES)
		    {
				inputnewteacher(name,id,pwd);
            	MessageBox(NULL,TEXT("录入老师成功"),TEXT("通过"),MB_OK);
            	return 0;
        	}
        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmInTeaWin", GetModuleHandle(NULL));
            return 0;
        }
    }

    if(msg==WM_CREATE)
    {
        CreateWindow(TEXT("STATIC"), TEXT("姓名："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 75, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("账号："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 120, 80, 20,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("密码："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 165, 80, 20,hwnd, NULL, NULL, NULL);

        g_hEditUsername1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            150, 75, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

        g_hEditUserid1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 120, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        g_hEditUserpwd1 = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 165, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("执行操作"),WS_VISIBLE | WS_CHILD,
            120, 210, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AdmInTeaWin", GetModuleHandle(NULL));
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

void AdmOutStuWindow()
{
    HWND hwnd;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmOutStuProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmOutStuWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmOutStuWin"), TEXT("学生"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    600, 400, 400, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 200, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdmInTeaWindow()
{
    HWND hwnd;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmInTeaProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmInTeaWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmInTeaWin"), TEXT("学生"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    600, 400, 400, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 270, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdmInCouWindow()
{
    HWND hwnd;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmInCouProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmInCouWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmInCouWin"), TEXT("学生"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    600, 300, 450, 500, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 350, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdmInStuWindow()
{
    HWND hwnd;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmInStuProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmInStuWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmInStuWin"), TEXT("学生"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    200, 200, 750, 450, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        270, 320, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

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
