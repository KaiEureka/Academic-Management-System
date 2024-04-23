#ifndef ADMAPPLY
#define ADMAPPLY
//管理员审批
LRESULT CALLBACK AmdAppProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg==WM_COMMAND){
        if (LOWORD(wParam)==ID_BUTTON_LOGIN)
        {
            int tmp=SendMessage(g_hComboBoxpaiming0Type, CB_GETCURSEL, 0, 0);
            if(tmp==-1)
            {
                MessageBox(NULL,TEXT("请选择操作类型"),TEXT("提示"),MB_OK);
                return 0;
            }
            if(tmp==0) 
            {
                str1='a';
                flag=1;
            }
            else if(tmp==1) 
            {
                str1='r';
                flag=1;
            }
            else if(tmp==2) 
            {
                str1='w';
                flag=1;
            }
            InvalidateRect(hwnd,NULL,TRUE);
            UpdateWindow(hwnd);
        }
        if(LOWORD(wParam)==ID_BUTTON_EXIT_SYSTEM)
        {
            //删除已经审批的信息，并保存审批结果
            FILE* fp=fopen(EA,"w");
            apt* Q=aptlih;
            apt* lQ;
            if(aptlih!=NULL)
            {
                while(Q!=NULL)
                {
                    if(Q->status!=0)
                    {
                        if(Q->pre!=NULL)Q->pre->next=Q->next;
                        if(Q->next!=NULL)Q->next->pre=Q->pre;
                        lQ=Q;
                        if(Q==aptlih)aptlih=aptlih->next;
                        Q=Q->next;
                        free(lQ);  //有玄学小概率bug
                    }
                    else
                    {
                        fprintf(fp,"%s",Q->str);
                        //fgets读进来的破烂本身自带\n
                        Q=Q->next;
                    }
                    
                }
            }
            fclose(fp);
            DestroyWindow(hwnd);
            UnregisterClass("AmdAppWin", GetModuleHandle(NULL));
            return 0;
        }
    }

	if(msg==WM_PAINT)
	{
        if(flag==0)
        {
            hdc = BeginPaint(hwnd, &ps);
			examineofroot();
			cnty=0;
			EndPaint(hwnd, &ps);
        }
		if(flag==1)
		{
            if(P!=NULL)
            {
            dealwithch(P,str1);
            P=P->next;
			hdc = BeginPaint(hwnd, &ps);
			examineofroot();
			cnty=0;
			EndPaint(hwnd, &ps);
            }
            else{
            hdc = BeginPaint(hwnd, &ps);
            wsprintf(szBuffer,TEXT("当前没有审核信息!"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,0,szBuffer,iTarget);
			cnty=0;
			EndPaint(hwnd, &ps);
            }
		}
	}

    if(msg==WM_CREATE)
    {
        //获取字符间距
        hdc=GetDC(hwnd);
        GetTextMetrics(hdc,&tm);
        cxChar=tm.tmAveCharWidth;
        cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2; //获取字符平均间距
        cyChar=tm.tmHeight+tm.tmExternalLeading;
        ReleaseDC(hwnd,hdc);

        CreateWindow(TEXT("STATIC"), TEXT("操作类型："),WS_VISIBLE | WS_CHILD | SS_LEFT,
            50, 220, 80, 20,hwnd, NULL, NULL, NULL);

        // 创建查询按钮
        CreateWindow(TEXT("BUTTON"), TEXT("下一条"),WS_VISIBLE | WS_CHILD,
            120, 300, 150, 45,hwnd, (HMENU)ID_BUTTON_LOGIN  , NULL, NULL);

        //创造选择条
        g_hComboBoxpaiming0Type = CreateWindow(
        TEXT("COMBOBOX"), TEXT(""),
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        150, 220, 200, 200,
        hwnd, (HMENU)ID_COMBOBOX_LOGIN_TYPE, NULL, NULL);

        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("批准"));
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("否决"));
        SendMessage(g_hComboBoxpaiming0Type, CB_ADDSTRING, 0, (LPARAM)TEXT("跳过"));
    }

    if(msg==WM_CLOSE)
    {
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            //删除已经审批的信息，并保存审批结果
            FILE* fp=fopen(EA,"w");
            apt* Q=aptlih;
            apt* lQ;
            if(aptlih!=NULL)
            {
                while(Q!=NULL)
                {
                    if(Q->status!=0)
                    {
                        if(Q->pre!=NULL)Q->pre->next=Q->next;
                        if(Q->next!=NULL)Q->next->pre=Q->pre;
                        lQ=Q;
                        if(Q==aptlih)aptlih=aptlih->next;
                        Q=Q->next;
                        free(lQ);  //有玄学小概率bug
                    }
                    else
                    {
                        fprintf(fp,"%s",Q->str);
                        //fgets读进来的破烂本身自带\n
                        Q=Q->next;
                    }
                }
            }
            fclose(fp);
            DestroyWindow(hwnd);
            UnregisterClass("AmdAppWin", GetModuleHandle(NULL));
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

void AmdAppWindow()
{
    HWND hwnd;
    P=aptlih;

	cntx=0,cnty=0,flag=0;
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AmdAppProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AmdAppWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AmdAppWin"), TEXT("管理员"), 
	(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 
    200, 200, 900, 700, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        100, 380, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void examineofroot()
{
	if(P==NULL)
	{
    wsprintf(szBuffer,TEXT("当前没有待审核信息!"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
		return;
	}
	if(P!=NULL)
	{
		if(P->status==0)
		{
            wsprintf(szBuffer,TEXT("当前待审批项目信息如下:"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
			char* S=P->str;
			int j,p=0;
			if(S[0]=='\n'||S[0]=='\r') return;
			char ordername[300];
			for(j=0;S[p]!=';';j++)
			{
				ordername[j]=S[p];
				p++;
			}
			ordername[j]='\0';p++;
			char teachername[100];
			if(strcmp(ordername,"deletestu")==0)
			{
				char astuname[100];
				for(j=0;S[p]!=';';j++)
				{
					astuname[j]=S[p];
					p++;
				}
				astuname[j]='\0';p++;
				for(j=0;S[p]!=';';j++)
				{
					teachername[j]=S[p];
					p++;
				}
				teachername[j]='\0';p++;
                wsprintf(szBuffer,TEXT("审批类型：申请开除学生"));
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                wsprintf(szBuffer,TEXT("审批来源：%s老师"),teachername);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                wsprintf(szBuffer,TEXT("申请内容：请求开除%s"),astuname);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
			}
			else if(strcmp(ordername,"changescoreofastu")==0)
			{
				char astr[100];
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				stunode* astu=searchstu(astr);
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				clsnode* acls=searchcls(astr);
				int anum=0;
				while(S[p]!=';')
				{
					if(S[p]>='0'&&S[p]<='9')
						anum=anum*10+S[p]-'0';
					p++;
				}
				p++;
				int newscore=anum;
				anum=0;
				while(S[p]!=';')
				{
					if(S[p]>='0'&&S[p]<='9')
						anum=anum*10+S[p]-'0';
					p++;
				}
				p++;
				int isfirst=anum;
				for(j=0;S[p]!=';';j++)
				{
					teachername[j]=S[p];
					p++;
				}
				teachername[j]='\0';p++;
                wsprintf(szBuffer,TEXT("审批类型：请求修改学生成绩"));
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                wsprintf(szBuffer,TEXT("审批来源：%s老师"),teachername);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
				if(isfirst==1)
                {
                    wsprintf(szBuffer,TEXT("申请内容：请求将%s同学的%s成绩修改为%d分，且标记为初修"),astu->stu.name,acls->clsif.name,newscore);
                    iTarget=lstrlen(szBuffer);
                    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else
                {
                    wsprintf(szBuffer,TEXT("申请内容：请求将%s同学的%s成绩修改为%d分，且标记为重修"),astu->stu.name,acls->clsif.name,newscore);
                    iTarget=lstrlen(szBuffer);
                    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
			}
			else if(strcmp(ordername,"enterhonor")==0)
			{
				char astr[100];
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				stunode* astu=searchstu(astr);
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				int flag=0;
				double zs=0.0,xs=0.0,adouble,m1=0.1;
				for(j=0;S[p]!=';';j++)
				{
					if(S[p]=='.')
					{
						flag=1;p++;
						continue;
					}
					if(flag==0)
					{
						zs=zs*10+S[p]-'0';
					}
					else
					{
						xs+=m1*(S[p]-'0');
						m1*=0.1;
					}
					p++;
				}
				adouble=zs+xs;p++;
				for(j=0;S[p]!=';';j++)
				{
					teachername[j]=S[p];
					p++;
				}
				teachername[j]='\0';p++;
                wsprintf(szBuffer,TEXT("审批类型：申请录入学生素质类加分项目"));
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                wsprintf(szBuffer,TEXT("审批来源：%s老师"),teachername);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                sprintf(szBuffer,TEXT("申请内容：请求为%s同学录入素质类加分项目，内容为%s，保研加分分值为%lf"),astu->stu.name,astr,adouble);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
			}
			else if(strcmp(ordername,"enterpunish")==0)
			{
				char astr[100];
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				stunode* astu=searchstu(astr);
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				int flag=0;
				double zs=0.0,xs=0.0,adouble,m1=0.1;
				for(j=0;S[p]!=';';j++)
				{
					if(S[p]=='.')
					{
						flag=1;p++;
						continue;
					}
					if(flag==0)
					{
						zs=zs*10+S[p]-'0';
					}
					else
					{
						xs+=m1*(S[p]-'0');
						m1*=0.1;
					}
					p++;
				}
				adouble=zs+xs;p++;
				for(j=0;S[p]!=';';j++)
				{
					teachername[j]=S[p];
					p++;
				}
				teachername[j]='\0';p++;
                wsprintf(szBuffer,TEXT("审批类型：申请录入学生处分信息"));
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                wsprintf(szBuffer,TEXT("审批来源：%s老师"),teachername);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
				if(fabs(adouble-1)<1e-5)
                {
                wsprintf(szBuffer,TEXT("申请内容：请求为%s同学录入处分信息，内容为%s，处分类型为警告"),astu->stu.name,astr);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(fabs(adouble-2)<1e-5)
                {
                wsprintf(szBuffer,TEXT("申请内容：请求为%s同学录入处分信息，内容为%s，处分类型为严重警告"),astu->stu.name,astr);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(fabs(adouble-3)<1e-5)
                {
                wsprintf(szBuffer,TEXT("申请内容：请求为%s同学录入处分信息，内容为%s，处分类型为处分"),astu->stu.name,astr);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(fabs(adouble-4)<1e-5)
                {
                wsprintf(szBuffer,TEXT("申请内容：请求为%s同学录入处分信息，内容为%s，处分类型为严重处分"),astu->stu.name,astr);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(fabs(adouble-5)<1e-5)
                {
                wsprintf(szBuffer,TEXT("申请内容：请求为%s同学录入处分信息，内容为%s，处分类型为留校查看"),astu->stu.name,astr);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(fabs(adouble-6)<1e-5)
                {
                wsprintf(szBuffer,TEXT("申请内容：请求为%s同学录入处分信息，内容为%s，处分类型为劝退"),astu->stu.name,astr);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
			}
			else if(strcmp(ordername,"inputcourse")==0)
			{
				char astr1[100];
				for(j=0;S[p]!=';';j++)
				{
					astr1[j]=S[p];
					p++;
				}
				astr1[j]='\0';p++;
				char astr2[100];
				for(j=0;S[p]!=';';j++)
				{
					astr2[j]=S[p];
					p++;
				}
				astr2[j]='\0';p++;
				int anum=0;
				while(S[p]!=';')
				{
					if(S[p]>='0'&&S[p]<='9')
						anum=anum*10+S[p]-'0';
					p++;
				}
				p++;
				char astr3[100];
				for(j=0;S[p]!=';';j++)
				{
					astr3[j]=S[p];
					p++;
				}
				astr3[j]='\0';p++;
				int flag=0;
				double zs=0.0,xs=0.0,adouble,m1=0.1;
				for(j=0;S[p]!=';';j++)
				{
					if(S[p]=='.')
					{
						flag=1;p++;
						continue;
					}
					if(flag==0)
					{
						zs=zs*10+S[p]-'0';
					}
					else
					{
						xs+=m1*(S[p]-'0');
						m1*=0.1;
					}
					p++;
				}
				adouble=zs+xs;
				p++;
				for(j=0;S[p]!=';';j++)
				{
					teachername[j]=S[p];
					p++;
				}
				teachername[j]='\0';p++;
                wsprintf(szBuffer,TEXT("审批类型：申请录入新课程信息"));
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                wsprintf(szBuffer,TEXT("审批来源：%s老师"),teachername);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
				if(anum==0)
                {
                    wsprintf(szBuffer,TEXT("申请内容：请求录入新课程，课程名称为%s,课程序号为%s,课程性质为必修"),astr1,astr2);
                    iTarget=lstrlen(szBuffer);
                    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(anum==1)
                {
                    wsprintf(szBuffer,TEXT("申请内容：请求录入新课程，课程名称为%s,课程序号为%s,课程性质为选修"),astr1,astr2);
                    iTarget=lstrlen(szBuffer);
                    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
				else if(anum==2)
                {
                    wsprintf(szBuffer,TEXT("申请内容：请求录入新课程，课程名称为%s,课程序号为%s,课程性质为限选"),astr1,astr2);
                    iTarget=lstrlen(szBuffer);
                    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
                }
                sprintf(szBuffer,TEXT("授课教师为%s,课程所占学分为%lf"),astr3,adouble);
                iTarget=lstrlen(szBuffer);
                TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
			}
			else
			{
				printf("ERROR:%s\n",ordername);
			}
		}
	}
	return;
}

void dealwithch(apt* P,char ch)
{
	int hereflag;
		hereflag=1;
		char* S=P->str;
		int j,p=0;
		if(S[0]=='\n'||S[0]=='\r')return;
		char ordername[300];
		for(j=0;S[p]!=';';j++)
		{
			ordername[j]=S[p];
			p++;
		}
		ordername[j]='\0';p++;
		if(ch=='w'){P->status=0;}
		else if(ch=='a')
		{
			P->status=1;
			if(strcmp(ordername,"deletestu")==0)
			{
				char astuname[100];
				for(j=0;S[p]!=';';j++)
				{
					astuname[j]=S[p];
					p++;
				}
				astuname[j]='\0';p++;
				deletestudent(searchstu(astuname));
				FILE* fp=fopen(ORDER,"a+");
				fprintf(fp,"deletestu;%s;\n",astuname);
				fclose(fp);
			}
			else if(strcmp(ordername,"changescoreofastu")==0)
			{
				char astr[100];
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				stunode* astu=searchstu(astr);
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				clsnode* acls=searchcls(astr);
				int anum=0;
				while(S[p]!=';')
				{
					if(S[p]>='0'&&S[p]<='9')
						anum=anum*10+S[p]-'0';
					p++;
				}
				p++;
				int newscore=anum;
				anum=0;
				while(S[p]!=';')
				{
					if(S[p]>='0'&&S[p]<='9')
						anum=anum*10+S[p]-'0';
					p++;
				}
				p++;
				int isfirst=anum;
				changescoreofastu(astu,acls,newscore,isfirst);
				FILE* fp=fopen(ORDER,"a+");
				fprintf(fp,"changescoreofastu;%s;%s;%d;%d;\n",astu->stu.name,acls->clsif.name,newscore,isfirst);
				fclose(fp);
			}
			else if(strcmp(ordername,"enterhonor")==0)
			{
				char astr[100];
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				stunode* astu=searchstu(astr);
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				int flag=0;
				double zs=0.0,xs=0.0,adouble,m1=0.1;
				for(j=0;S[p]!=';';j++)
				{
					if(S[p]=='.')
					{
						flag=1;p++;
						continue;
					}
					if(flag==0)
					{
						zs=zs*10+S[p]-'0';
					}
					else
					{
						xs+=m1*(S[p]-'0');
						m1*=0.1;
					}
					p++;
				}
				adouble=zs+xs;p++;
				enterhonor(astu,astr,adouble);
				FILE* fp=fopen(ORDER,"a+");
				fprintf(fp,"enterhonor;%s;%s;%.2lf;\n",astu->stu.name,astr,adouble);
				fclose(fp);
			}
			else if(strcmp(ordername,"enterpunish")==0)
			{
				char astr[100];
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				stunode* astu=searchstu(astr);
				for(j=0;S[p]!=';';j++)
				{
					astr[j]=S[p];
					p++;
				}
				astr[j]='\0';p++;
				int flag=0;
				double zs=0.0,xs=0.0,adouble,m1=0.1;
				for(j=0;S[p]!=';';j++)
				{
					if(S[p]=='.')
					{
						flag=1;p++;
						continue;
					}
					if(flag==0)
					{
						zs=zs*10+S[p]-'0';
					}
					else
					{
						xs+=m1*(S[p]-'0');
						m1*=0.1;
					}
					p++;
				}
				adouble=zs+xs;p++;
				enterpunish(astu,astr,adouble);
				FILE* fp=fopen(ORDER,"a+");
				fprintf(fp,"enterpunish;%s;%s;%d;\n",astu->stu.name,astr,(int)(adouble));
				fclose(fp);
			}
			else if(strcmp(ordername,"inputcourse")==0)
			{
				char astr1[100];
				for(j=0;S[p]!=';';j++)
				{
					astr1[j]=S[p];
					p++;
				}
				astr1[j]='\0';p++;
				char astr2[100];
				for(j=0;S[p]!=';';j++)
				{
					astr2[j]=S[p];
					p++;
				}
				astr2[j]='\0';p++;
				int anum=0;
				while(S[p]!=';')
				{
					if(S[p]>='0'&&S[p]<='9')
						anum=anum*10+S[p]-'0';
					p++;
				}
				p++;
				char astr3[100];
				for(j=0;S[p]!=';';j++)
				{
					astr3[j]=S[p];
					p++;
				}
				astr3[j]='\0';p++;
				int flag=0;
				double zs=0.0,xs=0.0,adouble,m1=0.1;
				for(j=0;S[p]!=';';j++)
				{
					if(S[p]=='.')
					{
						flag=1;p++;
						continue;
					}
					if(flag==0)
					{
						zs=zs*10+S[p]-'0';
					}
					else
					{
						xs+=m1*(S[p]-'0');
						m1*=0.1;
					}
					p++;
				}
				adouble=zs+xs;
				inputcourse(astr1,astr2,anum,astr3,adouble);
				FILE* fp=fopen(ORDER,"a+");
				fprintf(fp,"inputcourse;%s;%s;%d;%s;%lf;\n",astr1,astr2,anum,astr3,adouble);
				fclose(fp);
			}
			else
			{
				;//ERROR
			}
		}
		else if(ch=='r')
		{
			P->status=2;
		}
}

#endif
