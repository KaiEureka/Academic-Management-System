#ifndef ADMINPUTCS
#define ADMINPUTCS
//录入分数页面 
LRESULT CALLBACK InputScoreProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
    int i=0;
    int NUMLINES=20;
    if(msg==WM_COMMAND)
	{
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            char gradenow[100];
            GetWindowTextA(g_hEditGrade, gradenow, sizeof(gradenow));
			int naturenow=SendMessage(g_hComboBoxpaiming3Type, CB_GETCURSEL, 0, 0);
			
			int i=0,flagnow=0,len=strlen(gradenow),gradere,flagnow1=0;
			if(cosnowinall->cos.c->nature!=1)
			{
				for(i=0;i<len;i++)
				{
					flagnow1=1;
					if(gradenow[i]<'0'||gradenow[i]>'9')
					{
						flagnow=1;
						break;
					}
					gradere=gradere*10+gradenow[i]-'0';
				}
				if(naturenow!=-1)
				{
					MessageBox(NULL,TEXT("该课程不是选修课，不必选择档位"),TEXT("提示"),MB_OK);
				}
				if(flagnow==1||flagnow1==0||gradere<0||gradere>100)
				{
					MessageBox(NULL,TEXT("输入异常，请重新输入"),TEXT("警告"),MB_OK);
					return 0;
				}
				
				if(MessageBox(NULL,TEXT("请确认是否录入该成绩"),TEXT("提示"),MB_YESNO)==IDYES)
				{
					flaginson2=1;
                    cosnowinall->cos.score=gradere;
                    cosnowinall->cos.gp=cptgp(gradere);
                    MessageBox(NULL,TEXT("成绩录入修改成功"),TEXT("提示"),MB_OK);
                    FILE* fp=fopen(ORDER,"a+");
                    fprintf(fp,"changescoreofastu;%s;%s;%d;%d;\n",stunowinall->stu.name,clstobe->clsif.name,gradere,cosnowinall->cos.first);
                    fclose(fp);
                    return 0;
				}
			}
			else
			{
				if(naturenow==-1)
				{
					MessageBox(NULL,TEXT("请选择挡位"),TEXT("警告"),MB_OK);
					return 0;
				}
				if(naturenow==0)gradere=95;
				else if(naturenow==1)gradere=85;
				else if(naturenow==2)gradere=75;
				else if(naturenow==3)gradere=60;
				else if(naturenow==4)gradere=45;
				if(naturenow!=-1)
				{
					MessageBox(NULL,TEXT("该课程是选修课，不必输入成绩"),TEXT("提示"),MB_OK);
				}
				if(MessageBox(NULL,TEXT("请确认是否录入该成绩"),TEXT("提示"),MB_YESNO)==IDYES)
                {
                    cosnowinall->cos.score=gradere;
                    cosnowinall->cos.gp=cptgp(gradere);
                    MessageBox(NULL,TEXT("成绩录入修改成功"),TEXT("提示"),MB_OK);
                    FILE* fp=fopen(ORDER,"a+");
                    fprintf(fp,"changescoreofastu;%s;%s;%d;%d;\n",stunowinall->stu.name,clstobe->clsif.name,gradere,cosnowinall->cos.first);
                    fclose(fp);
                    return 0;
				}
			}
        }
        if(LOWORD(wParam)==ID_BUTTON_ROOT_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("InputScoreWin", GetModuleHandle(NULL));
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

        CreateWindow(TEXT("STATIC"), TEXT("输入成绩(若该课程为必修或限选)："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            10, 50, 110, 40,hwnd, NULL, NULL, NULL);
        CreateWindow(TEXT("STATIC"), TEXT("选择挡位(若该课程为选修)："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            10, 100, 110, 40,hwnd, NULL, NULL, NULL);

        g_hEditGrade = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL ,
            150, 50, 200, 20,hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);
            
            
        g_hComboBoxpaiming3Type = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 100, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hComboBoxpaiming3Type, CB_ADDSTRING, 0, (LPARAM)TEXT("A"));
        SendMessage(g_hComboBoxpaiming3Type, CB_ADDSTRING, 0, (LPARAM)TEXT("B"));
        SendMessage(g_hComboBoxpaiming3Type, CB_ADDSTRING, 0, (LPARAM)TEXT("C"));
        SendMessage(g_hComboBoxpaiming3Type, CB_ADDSTRING, 0, (LPARAM)TEXT("D"));
        SendMessage(g_hComboBoxpaiming3Type, CB_ADDSTRING, 0, (LPARAM)TEXT("E"));
        
        CreateWindow(TEXT("BUTTON"), TEXT("确认录入"),WS_VISIBLE | WS_CHILD,
            110, 150, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

    }
    if(msg==WM_CLOSE)
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("InputScoreWin", GetModuleHandle(NULL));
        }
        else return 0;

    if(msg==WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//批量录入子页面一 
LRESULT CALLBACK AESorSSon1Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            if(LOWORD(wParam)==ID_BUTTON_LOGIN) 
            {
                char stuname[100];
                GetWindowTextA(g_hEditStuname, stuname, sizeof(stuname));
				int choosenow = SendMessage(g_hComboBoxpaiming1Type, CB_GETCURSEL, 0, 0);
				if(choosenow==-1)
                {
                    MessageBox(NULL,TEXT("请先选择操作"),TEXT("提示"),MB_OK);
                    return 0;
                }
                stunode *Astu;
				Astu=searchstu(stuname);
				if(Astu==NULL)
                {
                    MessageBox(NULL,TEXT("未查到该学生，请重新输入"),TEXT("提示"),MB_OK);
                    return 0;
                }
                if(Astu->stu.scoreh->pre==NULL&&Astu->stu.scoreh->next!=NULL)
                Astu->stu.scoreh=Astu->stu.scoreh->next;
                cosnode *cosnow=Astu->stu.scoret;
                while(cosnow!=NULL&&cosnow->pre!=NULL)
                {
                    if(strcmp(cosnow->cos.c->name,clstobe->clsif.name)==0)
                    {
                        if(choosenow==0)
                        {
                            if(cosnow->cos.score==-1)
                            {
                                MessageBox(NULL,TEXT("该学生已录入该课程,且成绩未录入,操作非法"),TEXT("提示"),MB_OK);
                                return 0;
                            }
                            if(MessageBox(NULL,TEXT("该学生是否再次重修该课程"),TEXT("提示"),MB_YESNO)==IDYES)
                            {
                                MessageBox(NULL,TEXT("录入成功,该生已修读过该课程，学习性质设为重修"),TEXT("提示"),MB_OK);
                                cosnode *tmp1=(struct cosnode*)malloc(sizeof(struct cosnode));
                                tmp1->cos.c=&(clstobe->clsif);tmp1->pre=Astu->stu.scoret;tmp1->next=NULL;
                                tmp1->cos.first=0;tmp1->cos.score=-1;tmp1->cos.gp=-1;
                                Astu->stu.scoret->next=tmp1;
                                Astu->stu.scoret=tmp1;
                                FILE* fp=fopen(ORDER,"a+");
                                fprintf(fp,"inputscore;%s;%s;%d;%.4lf;%d;\n",Astu->stu.name,clstobe->clsif.name,-1,-1.0,0);
                                fclose(fp);
                                if(Astu->stu.scoreh->pre==NULL&&Astu->stu.scoret->next!=NULL)
                                Astu->stu.scoreh=Astu->stu.scoreh->next;
                            }
                            return 0;
                        }
                        else
                        {
                            if(cosnow->cos.score!=-1)
                            {
                                MessageBox(NULL,TEXT("该学生该科成绩已录入,操作非法"),TEXT("提示"),MB_OK);
                                return 0;
                            }
							if(MessageBox(NULL,TEXT("是否为该学生录入该课程的成绩"),TEXT("提示"),MB_YESNO)==IDYES)
							{
								stunowinall=Astu;
								cosnowinall=cosnow;
								InputScoreWindow();
							}
                            return 0;
						}
                    }
                    cosnow=cosnow->pre;
                }
                if(choosenow==1)
                {
                    MessageBox(NULL,TEXT("该学生未录入该课程或成绩已全部录入,操作非法"),TEXT("提示"),MB_OK);
                    return 0;
                }
                else
                {
                    if(MessageBox(NULL,TEXT("是否为该学生录入该课程"),TEXT("提示"),MB_YESNO)==IDYES)
                    {
                        MessageBox(NULL,TEXT("录入成功,这是该生第一次修读该课程,学习性质默认设为初修"),TEXT("提示"),MB_OK);
                        cosnode *tmp1=(struct cosnode*)malloc(sizeof(struct cosnode));
                        tmp1->cos.c=&(clstobe->clsif);tmp1->pre=Astu->stu.scoret;tmp1->next=NULL;
                        tmp1->cos.first=0;tmp1->cos.score=-1;tmp1->cos.gp=-1;
                        Astu->stu.scoret->next=tmp1;
                        Astu->stu.scoret=tmp1;
                        FILE* fp=fopen(ORDER,"a+");
                        fprintf(fp,"inputscore;%s;%s;%d;%.4lf;%d;\n",Astu->stu.name,clstobe->clsif.name,-1,-1,0);
                        fclose(fp);
                        if(Astu->stu.scoreh->pre==NULL&&Astu->stu.scoret->next!=NULL)
                        Astu->stu.scoreh=Astu->stu.scoreh->next;
                    }
                    return 0;
                }
                break;
			}
            else if(LOWORD(wParam)==ID_BUTTON_ROOT_EXIT_SYSTEM)
            {
                DestroyWindow(hwnd);
                UnregisterClass("AESorSSon1Win", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_CREATE:
            CreateWindow(TEXT("STATIC"), TEXT("学生名称："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                20, 70, 80, 20,hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("选择："),WS_VISIBLE | WS_CHILD | SS_LEFT,
				20, 110, 80, 20,hwnd, NULL, NULL, NULL);
                
            g_hEditStuname = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                120, 70, 240, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

            g_hComboBoxpaiming1Type = CreateWindow(
                TEXT("COMBOBOX"), TEXT(""),
                WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                120, 110, 240, 200,
                hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);
        
            SendMessage(g_hComboBoxpaiming1Type, CB_ADDSTRING, 0, (LPARAM)TEXT("为该学生新录入该门课程"));
            SendMessage(g_hComboBoxpaiming1Type, CB_ADDSTRING, 0, (LPARAM)TEXT("为该学生录入该课程的最新成绩"));

            CreateWindow(TEXT("BUTTON"), TEXT("确认"),WS_VISIBLE | WS_CHILD,
                100, 140, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN, NULL, NULL);

            break;

        case  WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("AESorSSon1Win", GetModuleHandle(NULL));
            }
            else return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//批量录入子页面二 
LRESULT CALLBACK AESorSSon2Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i=0;
	int NUMLINES=20;
    if(msg==WM_COMMAND)
    {
        if(LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            int choosenow=SendMessage(g_hComboBoxpaiming0Type, CB_GETCURSEL, 0, 0);
            if(choosenow==-1)
            {
                MessageBox(NULL,TEXT("请选择操作"),TEXT("提示"),MB_OK);
                return 0;
            }
            if(choosenow==0)
            {
                nstuinall=nstuinall->next;
                if(nstuinall==NULL)
                {
                    MessageBox(NULL,TEXT("已展示完所有未录入成绩的学生，自动退出"),TEXT("提示"),MB_OK);
                    DestroyWindow(hwnd);
                    UnregisterClass("AESorSSon2Win", GetModuleHandle(NULL));
                }
                InvalidateRect(hwnd,NULL,TRUE);
                UpdateWindow(hwnd);
                return 0;
            }
            else
            {
                cosnowinall=nstuinall->Cos;
                stunowinall=nstuinall->Stu;
                InputScoreWindow();
                if(flaginson2==1)
                {	
                    emptynum-=1;
                    nstuinall=nstuinall->next;
                    flaginson2=0;
                }
                if(nstuinall==NULL)
                {
                    MessageBox(NULL,TEXT("已展示完所有未录入成绩的学生，自动退出"),TEXT("提示"),MB_OK);
                    DestroyWindow(hwnd);
                    UnregisterClass("AESorSSon2Win", GetModuleHandle(NULL));
                }
				InvalidateRect(hwnd,NULL,TRUE);
                UpdateWindow(hwnd);
                
                return 0;
			}
		}
        else if(LOWORD(wParam)==ID_BUTTON_ROOT_EXIT_SYSTEM)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AESorSSon2Win", GetModuleHandle(NULL));
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

		CreateWindow(TEXT("STATIC"), TEXT("选择："),WS_VISIBLE | WS_CHILD | SS_LEFT,
			40, 110, 50, 20,hwnd, NULL, NULL, NULL);

        g_hComboBoxpaiming0Type = CreateWindow(
            TEXT("COMBOBOX"), TEXT(""),
            WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
            110, 110, 200, 200,
            hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);
    
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("跳过"));
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("进入录入界面"));

        CreateWindow(TEXT("BUTTON"), TEXT("确认选择"),WS_VISIBLE | WS_CHILD,
            100, 150, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN, NULL, NULL);
            return 0; 
	}
	if(msg==WM_PAINT)
    {
        hdc = BeginPaint(hwnd, &ps); 

        wsprintf(szBuffer,TEXT("该课程当前有 %d 名学生未录入成绩"),emptynum);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
        
        wsprintf(szBuffer,TEXT("当前正要录入成绩的学生姓名与学号："));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
        
        wsprintf(szBuffer,TEXT("%s  %s"),nstuinall->Stu->stu.name,nstuinall->Stu->stu.id);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,cxChar,cyChar*((i++)-iVscrollPos),szBuffer,iTarget);
        
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
    if(msg==WM_CLOSE)
	{
		if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("AESorSSon2Win", GetModuleHandle(NULL));
        }
        else return 0;
    }
	if(msg==WM_DESTROY)
	{
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//批量录入主页面 
LRESULT CALLBACK AdmEntStuorScoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int NUMLINES=20;
    switch (msg)
    {
        case WM_COMMAND:
            if(LOWORD(wParam)==ID_BUTTON_LOGIN) 
            {
                char coursenow[1000];
                GetWindowTextA(g_hEditCourse, coursenow, sizeof(coursenow));
				int choosenow = SendMessage(g_hComboBoxpaiming2Type, CB_GETCURSEL, 0, 0);
				
				clsnode *Acls;
				Acls=searchcls(coursenow);

                if(Acls==NULL)
                {
                    MessageBox(NULL,TEXT("未找到该门课程，请先录入该课程"),TEXT("提示"),MB_OK);
                    return 0;
                }
                if(choosenow==-1)
                {
                    MessageBox(NULL,TEXT("请选择录入方式"),TEXT("提示"),MB_OK);
                    return 0;
                }
                clstobe=Acls;
                
                if(tos==0&&strcmp(teauser->tea.name,clstobe->clsif.teacher)!=0)
                {
                    MessageBox(NULL,TEXT("该课程的授课教师不是您，您无权操作!"),TEXT("提示"),MB_OK);
                    return 0;
                }
                inputstuascr(choosenow);
                return 0; 
			}
            else if(LOWORD(wParam)==ID_BUTTON_ROOT_EXIT_SYSTEM)
            {
                DestroyWindow(hwnd);
                UnregisterClass("AdmEntStuorScoWin", GetModuleHandle(NULL));
                break;
            }
            break;

        case WM_CREATE:
            CreateWindow(TEXT("STATIC"), TEXT("课程名称："),WS_VISIBLE | WS_CHILD | SS_LEFT,
                50, 70, 80, 20,hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("选择："),WS_VISIBLE | WS_CHILD | SS_LEFT,
				50, 110, 80, 20,hwnd, NULL, NULL, NULL);
				
            g_hEditCourse = CreateWindow(TEXT("EDIT"), TEXT(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                150, 70, 200, 20,hwnd, (HMENU)IDC_EDIT_USERNAME, NULL, NULL);

            g_hComboBoxpaiming2Type = CreateWindow(
                TEXT("COMBOBOX"), TEXT(""),
                WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                150, 110, 200, 200,
                hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);
        
            SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("定向录入"));
            SendMessage(g_hComboBoxpaiming2Type, CB_ADDSTRING, 0, (LPARAM)TEXT("一键录入成绩"));

            CreateWindow(TEXT("BUTTON"), TEXT("进入"),WS_VISIBLE | WS_CHILD,
                130, 140, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN, NULL, NULL);

            break;

        case  WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("AdmEntStuorScoWin", GetModuleHandle(NULL));
            }
            else return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void AdmEntStuorScoWindow()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdmEntStuorScoProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdmEntStuorScoWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdmEntStuorScoWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 400, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 200, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AESorSSon1Window()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AESorSSon1Proc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AESorSSon1Win";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AESorSSon1Win"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 400, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        50, 200, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AESorSSon2Window()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AESorSSon2Proc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AESorSSon2Win";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AESorSSon2Win"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 400, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        80, 220, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void InputScoreWindow()
{
    HWND hwnd;

    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = InputScoreProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"InputScoreWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("InputScoreWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    650, 300, 400, 400, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        90, 220, 200, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

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
