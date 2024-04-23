#ifndef __DIRECTSHOW
#define __DIRECTSHOW

void showstudent()
{
    stunode* p=stulih;
    while(p!=NULL)
    {
        student st=p->stu;
        wsprintf(szBuffer,TEXT("学生姓名：%s"),st.name);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("学号：%s"),st.id);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("性别：%d"),st.gender);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("专业：%s"),st.major);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("生源地：%s"),st.home);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("班级号:%d"),st.Class);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        showgcofastu(p);
        cnty++;
        p=p->next;
    }
	return;
}

void showstudentscores()
{
    stunode* p=stulih;
    if(p->pre==NULL)p=p->next;
    wsprintf(szBuffer,TEXT("-----------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    while(p!=NULL)
    {
        student st=p->stu;
        wsprintf(szBuffer,TEXT("学生姓名：%s"),st.name);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("学号：%s"),st.id);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("专业:%s"),st.major);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        showhpofastu(p);
        showgcofastu(p);
        cnty+=2;
        showscoresofastu(p);
        cnty++;
        p=p->next;
    }
    wsprintf(szBuffer,TEXT("-----------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
	return;
}

void showcls()
{
    clsnode *p=clslih;
    wsprintf(szBuffer,TEXT("---------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    while(p!=NULL)
    {
        cls st=p->clsif;
        wsprintf(szBuffer,TEXT("课程名称：%s"),st.name);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("课程编号：%s"),st.id);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("课程性质：%d"),st.nature);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        sprintf(szBuffer,TEXT("学分：%.1lf"),st.cdt);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("老师：%s"),st.teacher);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        cnty++;
        p=p->next;
    }
    wsprintf(szBuffer,TEXT("---------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
	return;
}

void showgcofastu(stunode* stuuser)
{
	cptsg(stuuser);
    wsprintf(szBuffer,TEXT("成绩概述"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("（必修课成绩）均分:%.4lf     均绩:%.4lf"),stuuser->stu.csco,stuuser->stu.cgpa);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("（保研成绩）  均分:%.4lf     均绩:%.4lf"),stuuser->stu.ssco,stuuser->stu.sgpa);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("（总成绩）    均分:%.4lf     均绩:%.4lf"),stuuser->stu.tsco,stuuser->stu.tgpa);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("（用于留学的总成绩）    均分:%.4lf     均绩:%.4lf"),stuuser->stu.osco,stuuser->stu.ogpa);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
	return;
}

void showhpofastu(stunode* stuuser)
{
    wsprintf(szBuffer,TEXT("学生所获荣誉"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    strnode* h=stuuser->stu.honorh;
    if(h->pre==NULL)h=h->next;
    if(h==NULL)printf("无\n");
    while(h!=NULL)
    {
        wsprintf(szBuffer,TEXT("加分项目名称：%s"),h->s);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        sprintf(szBuffer,TEXT("加分分值：%lf"),h->inf);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        h=h->next;
    }
    cnty++;
    wsprintf(szBuffer,TEXT("学生所获处分"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    h=stuuser->stu.punishh;
    if(h->pre==NULL)h=h->next;
    if(h==NULL)
    {
        wsprintf(szBuffer,TEXT("无"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    }
    while(h!=NULL)
    {
        wsprintf(szBuffer,TEXT("处分缘由：%s"),h->s);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        sprintf(szBuffer,TEXT("加分等级：%lf"),h->inf);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        h=h->next;
    }
    cnty++;
	return;
}

void showscoresofastu(stunode* astu)
{
    cosnode* h=astu->stu.scoreh;
    if(astu->stu.scoreh->pre==NULL&&astu->stu.scoreh->next!=NULL)astu->stu.scoreh=astu->stu.scoreh->next;
    if(h==NULL||h!=NULL&&astu->stu.scoreh->pre==NULL)
    {
        wsprintf(szBuffer,TEXT("该学学生未录入任何一门成绩，暂无成绩显示！"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        return;
    }
    while(h!=NULL)
    {
        wsprintf(szBuffer,TEXT("课程名称：%s"),h->cos.c->name);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        wsprintf(szBuffer,TEXT("课程编号：%s"),h->cos.c->id);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
		if(h->cos.c->nature==0)
        {
            wsprintf(szBuffer,TEXT("课程性质：必修"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        }
		else if(h->cos.c->nature==1)
        {
            wsprintf(szBuffer,TEXT("课程性质：选修"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        }
		else if(h->cos.c->nature==2)
        {
            wsprintf(szBuffer,TEXT("课程性质：限选"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        }
            wsprintf(szBuffer,TEXT("授课教师：%s"),h->cos.c->teacher);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
            sprintf(szBuffer,TEXT("学分：%.1lf"),h->cos.c->cdt);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
		if(h->cos.first==1)
        {
            wsprintf(szBuffer,TEXT("是否为重修：是"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        }
		else
        {
            wsprintf(szBuffer,TEXT("是否为重修：否"));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        }
            sprintf(szBuffer,TEXT("绩点：%.1lf"),h->cos.gp);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
		if(h->cos.c->nature!=1)
        {
            wsprintf(szBuffer,TEXT("成绩：%d"),h->cos.score);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        }
		else
		{
            wsprintf(szBuffer,TEXT("成绩："));
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,0,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
			showoptionalscore(h->cos.score);
            cnty++;
		}
        cnty++;
        h=h->next;
    }
	return;
}

#endif
