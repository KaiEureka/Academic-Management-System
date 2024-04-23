#ifndef __ORDEROFUSER
#define __ORDEROFUSER

void addstudentofroot(char aname[],char aid[],int agender,char amajor[],int ayear,int aclass,char apwd[],char ahome[])
{
	createnewstu(aname,aid,agender,amajor,ayear,aclass,apwd,ahome);
	FILE* fp=fopen(STU,"a+");
	fprintf(fp,"%s;%s;%d;%s;%d;%d;%s;%s\n",aname,aid,agender,amajor,ayear,aclass,apwd,ahome);
	fclose(fp);
	return;
}

void deletestuofroot(char str[])
{
		if(searchstu(str)!=NULL)
		{
			deletestudent(searchstu(str));
			FILE* fp=fopen(ORDER,"a+");
			fprintf(fp,"deletestu;%s;\n",str);
			fclose(fp);
            MessageBox(NULL,TEXT("学生信息删除成功!"),TEXT("通过"),MB_OK);
		}
		else
            MessageBox(NULL,TEXT("该学生不存在，删除失败!"),TEXT("警告"),MB_ICONERROR);
	return;
}

void inputnewteacher(char tname[],char taccount[],char tpwd[])
{
	FILE* fp=fopen(TEA,"a+");
	fprintf(fp,"%s;%s;%s\n",tname,taccount,tpwd);
	fclose(fp);
	return;
}

void inputscore(stunode* pstu,clsnode* pcls,int sc,double GP,int isfirst)
{
    cosnode* newcos=(cosnode*)malloc(sizeof(cosnode));
    newcos->cos.c=&(pcls->clsif);
    newcos->cos.first=isfirst;
    newcos->cos.score=sc;
    newcos->cos.gp=GP;
    newcos->next=NULL;
    newcos->pre=pstu->stu.scoret;
    pstu->stu.scoret->next=newcos;
    pstu->stu.scoret=pstu->stu.scoret->next;
    if(pstu->stu.scoreh->pre==NULL&&pstu->stu.scoreh->next!=NULL)pstu->stu.scoreh=pstu->stu.scoreh->next;
	return;
}

//s
void changescoreofastu(stunode* astu,clsnode* acls,int newscore,int isfirst)
{
	if(astu->stu.scoreh->pre==NULL&&astu->stu.scoreh->next!=NULL)astu->stu.scoreh=astu->stu.scoreh->next;
	if(astu->stu.scoret->pre==NULL)
	{
		//printf("修改失败！");
		return;
	}
    cosnode* p=astu->stu.scoret;
    while(p!=NULL&&p->pre!=NULL)
    {
        if(p->cos.c==&(acls->clsif))
        {
            p->cos.score=newscore;
            p->cos.gp=cptgp(newscore);
            p->cos.first=isfirst;
            cptsg(astu);
            return;
        }
        p=p->pre;
    }
//	printf("修改失败！");
	return;
}

void createnewstu(char* aname,char* aid,int agender,char* amajor,int ayear,int aclass,char* apwd,char* ahome)
{
    stunode *newstunode;
    newstunode=(stunode*)malloc(sizeof(stunode));
    strcpy(newstunode->stu.name,aname);
    strcpy(newstunode->stu.id,aid);
    newstunode->stu.gender=agender;
    strcpy(newstunode->stu.major,amajor);
    newstunode->stu.year=ayear;
    newstunode->stu.Class=aclass;
    strcpy(newstunode->stu.pwd,apwd);
    strcpy(newstunode->stu.home,ahome);
	newstunode->stu.cgpa=newstunode->stu.csco=newstunode->stu.tgpa=newstunode->stu.tsco=newstunode->stu.sgpa=newstunode->stu.ssco=0;
    newstunode->stu.scoreh=(cosnode*)malloc(sizeof(cosnode));
    newstunode->stu.scoreh->next=newstunode->stu.scoreh->pre=NULL;
    newstunode->stu.scoret=newstunode->stu.scoreh;

    newstunode->stu.honorh=(strnode*)malloc(sizeof(strnode));
    newstunode->stu.honorh->inf=0;
    newstunode->stu.honorh->next=newstunode->stu.honorh->pre=NULL;
    newstunode->stu.honort=newstunode->stu.honorh;

    newstunode->stu.punishh=(strnode*)malloc(sizeof(strnode));
    newstunode->stu.punishh->inf=0;
    newstunode->stu.punishh->next=newstunode->stu.punishh->pre=NULL;
    newstunode->stu.punisht=newstunode->stu.punishh;
    stulit->next=newstunode;
    newstunode->next=NULL;
    newstunode->pre=stulit;
    stulit=stulit->next;
}

void changemajorofstu(stunode* stuuser,char* astr)
{
	if(stuuser!=NULL)
	{
		strcpy(stuuser->stu.major,astr);
	}
}

double cptgp(int sco)
{
    if(sco>=90)return 4.0;
    else if(sco>=87)return 3.7;
    else if(sco>=83)return 3.3;
    else if(sco>=80)return 3.0;
    else if(sco>=77)return 2.7;
    else if(sco>=73)return 2.3;
    else if(sco>=70)return 2.0;
    else if(sco>=67)return 1.7;
    else if(sco>=63)return 1.3;
    else if(sco>=60)return 1.0;
    else return 0.0;
}

void showoptionalscore(int sco)
{
	if(sco>=90)
    {
        wsprintf(szBuffer,TEXT("优秀"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,6*cxChar,cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
	else if(sco>=80)
    {
        wsprintf(szBuffer,TEXT("良好"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,6*cxChar,cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
	else if(sco>=70)
    {
        wsprintf(szBuffer,TEXT("中等"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,6*cxChar,cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
	else if(sco>=60)
    {
        wsprintf(szBuffer,TEXT("及格"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,6*cxChar,cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
	else
    {
        wsprintf(szBuffer,TEXT("不及格"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,6*cxChar,cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
	return;
}

void deletestuoftea(char str[])
{
		if(searchstu(str)!=NULL)
		{
            MessageBox(NULL,TEXT("审批信息已经储存并上报，请等待管理员批复！"),TEXT("通过"),MB_OK);
			FILE* fp=fopen(EA,"a+");
			fprintf(fp,"deletestu;%s;%s;\n",str,teauser->tea.name);
			fclose(fp);
		}
		else
            MessageBox(NULL,TEXT("该学生不存在，删除失败"),TEXT("失败"),MB_ICONERROR);
	return;
}

#endif

