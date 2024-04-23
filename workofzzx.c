#ifndef __WORKOFZZX
#define __WORKOFZZX

inline cosnode *sort_bycls(stunode *stunow)
{
	cosnode *cosnow=stunow->stu.scoreh;
	cosnode *coslist=NULL,*cosr=NULL,*ctmp=NULL,*coslast=NULL;
	while(cosnow!=NULL)
	{
		if(cosnow->cos.c==NULL)
		{
			cosnow=cosnow->next;
			continue;
		}
		
		if(cosnow->cos.score==-1)
		{
			cosnow=cosnow->next;
			continue;
		}
		
		
		ctmp=(cosnode*)malloc(sizeof(cosnode));
        ctmp->cos=cosnow->cos;
		if(coslist==NULL)
        {
            coslist=(cosnode*)malloc(sizeof(cosnode));
            coslist=ctmp;
            coslist->next=NULL;
            coslist->pre=NULL;
        }
        else
        {
            int flag=0;
            cosr=coslist;
            while(strcmp(cosr->cos.c->id,ctmp->cos.c->id)!=-1)
            {
                if(cosr->next!=NULL)
                cosr=cosr->next;
                else
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                if(cosr==coslist)
                {
                    ctmp->next=cosr;
                    cosr->pre=ctmp;
                    coslist=ctmp;
                }
                else
                {
                    coslast=cosr->pre;
                    coslast->next=ctmp;
                    ctmp->pre=coslast;
                    cosr->pre=ctmp;
                    ctmp->next=cosr;
                }
            }
            else
            {
                cosr->next=ctmp;
                ctmp->pre=cosr;
                ctmp->next=NULL;
            }
		}
		cosnow=cosnow->next;
	}
	return ctmp;
}
double maxdouble(double x,double y)
{
	if(x<y)return y;
	return x;
}

void cptsg(stunode *Stu)
{
    stunode *studentnow=Stu;
	if(Stu->stu.scoreh->pre==NULL&&Stu->stu.scoreh->next!=NULL)Stu->stu.scoreh=Stu->stu.scoreh->next;
	cosnode *coursenow=sort_bycls(studentnow);
	cosnode *courselit=coursenow;
	double callcdt=0.0000,tallcdt=0.0000,sallcdt=0.0000,oallcdt=0.0000;
	double callscore=0.0000,tallscore=0.0000,sallscore=0.0000,oallscore=0.0000;
	double callgp=0.0000,tallgp=0.0000,sallgp=0.0000,oallgp=0.0000;
	double cdtnow,scorenow,hscore=-1.0000,gpnow,hgp=-1.0000;
	double scoreweid,gpweid;

	course cosnow;
	int naturenow;
	while(coursenow!=NULL)
	{
		cosnow=coursenow->cos;
		naturenow=cosnow.c->nature;
		cdtnow=cosnow.c->cdt;
		scorenow=cosnow.score;
		gpnow=cosnow.gp;
		hscore=maxdouble(hscore,scorenow);
		hgp=maxdouble(hgp,gpnow);
		
		if(coursenow->pre!=NULL)
		{
			if(strcmp(coursenow->pre->cos.c->id,coursenow->cos.c->id)==0)
			{
				coursenow=coursenow->pre;
				continue;
			}
		}
		
		scoreweid=scorenow*cdtnow;
		gpweid=gpnow*cdtnow;
		
		tallcdt+=cdtnow;
		tallscore+=scoreweid;
		tallgp+=gpweid;
		if(naturenow==0)
		{
			callcdt+=cdtnow;
			callscore+=scoreweid;
			callgp+=gpweid;

			sallcdt+=cdtnow;
			sallscore+=scoreweid;
			sallgp+=gpweid;
		}
		if(naturenow==2)
		{
			sallcdt+=cdtnow;
			sallscore+=scoreweid;
			sallgp+=gpweid;
		}
		
		oallcdt+=cdtnow;
		oallscore+=hscore*cdtnow;
		oallgp+=hgp*cdtnow;
		hscore=-1.0000;
		hgp=-1.0000;
		
		coursenow=coursenow->pre;
	}
	strnode* p;
	if(Stu->stu.honorh->pre==NULL&&Stu->stu.honorh->next!=NULL)Stu->stu.honorh=Stu->stu.honorh->next;
	p=Stu->stu.honorh;
	double addscore=0.0;
	while(p!=NULL)
	{
		addscore+=p->inf;
		p=p->next;
	}
	if(fabs(callcdt)<1e-5)
		studentnow->stu.cgpa=0;
	else	
		studentnow->stu.cgpa=callgp/callcdt;
	if(fabs(callcdt)<1e-5)
		studentnow->stu.csco=0;
	else	
		studentnow->stu.csco=callscore/callcdt;
	if(fabs(tallcdt)<1e-5) 
		studentnow->stu.tgpa=0;
	else	
		studentnow->stu.tgpa=tallgp/tallcdt;
	if(fabs(tallcdt)<1e-5)
		studentnow->stu.tsco=0;
	else	
		studentnow->stu.tsco=tallscore/tallcdt;
	if(fabs(sallcdt)<1e-5)
		studentnow->stu.sgpa=addscore;
	else    
		studentnow->stu.sgpa=sallgp/sallcdt+addscore;
	if(fabs(sallcdt)<1e-5)
		studentnow->stu.ssco=0;
	else
		studentnow->stu.ssco=sallscore/sallcdt;
	if(fabs(oallcdt)<1e-5)
		studentnow->stu.ogpa=addscore;
	else    
		studentnow->stu.ogpa=oallgp/oallcdt;
	if(fabs(oallcdt)<1e-5)
		studentnow->stu.osco=0;
	else
		studentnow->stu.osco=oallscore/oallcdt;
	
	while(courselit!=NULL)
	{
		cosnode *p=courselit;
		courselit=courselit->pre;
		free(p);
	}
    return;
}

int searchyear(int wheyear)
{
    stunode *p=stulih;
    while(p!=NULL)
    {
        if(p->stu.year==wheyear)return 1;
        p=p->next;
    }
    return 0;
}

inline int sort_three_cmp(int require,stunode *x,stunode *y,int ord)
{
	if(ord==2||ord==3)
	if(x->stu.Class!=y->stu.Class)
	return x->stu.Class<y->stu.Class;
    if(require<=4)return x->stu.cgpa>=y->stu.cgpa;
    return x->stu.csco>=y->stu.csco;
}

void sort_free(stunode *xxx,nstunode *yyy,nstunode *zzz)
{
	while(xxx!=NULL)
    {
        stunode *p=xxx;
        xxx=xxx->next;free(p);
    }
    while(yyy!=NULL)
    {
        nstunode *pp=yyy;
        yyy=yyy->next;free(pp);
        nstunode *ppp=zzz;
        zzz=zzz->next;free(ppp);
	}
	return;
}


void sort_print1(int req1,int req2)
{
    wsprintf(szBuffer,TEXT("-------------------------------------------------------------------------------------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370,50+cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("排名    学生姓名    学生性别     生源地             平均成绩          平均绩点"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370,50+cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    return;
}

void sort_print2(stunode *stow,int studnum)
{
    wsprintf(szBuffer,TEXT("%d"),studnum);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370 , 50+cyChar*(cnty-iVscrollPos) ,szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("%s"),stow->stu.name);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370+cxChar*7 , 50+cyChar*(cnty-iVscrollPos) ,szBuffer,iTarget);
    if(stow->stu.gender==1)
    {
    wsprintf(szBuffer,TEXT("男"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370+cxChar*21,50+cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
    else 
    {
    wsprintf(szBuffer,TEXT("女"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370+cxChar*21,50+cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    }
    wsprintf(szBuffer,TEXT("%s"),stow->stu.home);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370+cxChar*29,50+cyChar*(cnty-iVscrollPos),szBuffer,iTarget);
    //printf("%.4lf\t\t%.4lf\n",stow->stu.csco,stow->stu.cgpa);
    sprintf(szBuffer,TEXT("%.4lf            %.4lf"),stow->stu.csco,stow->stu.cgpa);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,370+cxChar*43,50+cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    return;
}

void sort_three(int year,char majornow[],int ordern,int req_1,int req_2,int classre)
{
    
    int stunum=0,flag=0,wheright=0; 
    
    stunode *stur=NULL,*tmp=NULL,*stutail=NULL,*stulist=NULL;//这两行要放到窗口化的最开头
    nstunode *nstulih=NULL,*nstulit=NULL;
    // 以及在退出系统的时候要最后一次free掉新建的链表
	//sort_free(stulist,nstulih,nstulit); 就把这句放到退出系统那里一起执行 
    
    nstunode *nstunow1=NULL,*nstunow2=NULL,*ntmp=NULL;
    if(1)//这里放入判断条件 就是年份或者专业有没有改变 
    {
        sort_free(stulist,nstulih,nstulit);
        
	    //初始记分
	    stunode *stunow=stulih,*p=stulih,*stulast=NULL;
		while(p!=NULL)
		{
			cptsg(p);
			p=p->next;
		}
		
        while(stunow!=NULL)
        {
            if(stunow->stu.year==year&&(strcmp(stunow->stu.major,majornow))==0)
            {
                stunum+=1;
                tmp=(stunode*)malloc(sizeof(stunode));
                tmp->stu=stunow->stu;
                if(req_2==2||req_2==6)
                {
                    tmp->stu.cgpa=tmp->stu.sgpa;
                    tmp->stu.csco=tmp->stu.ssco;
                }
                else if(req_2==3||req_2==7)
                    {
                        tmp->stu.cgpa=tmp->stu.tgpa;
                        tmp->stu.csco=tmp->stu.tsco;
                    }
                    else if(req_2==4||req_2==8)
                        {
                            tmp->stu.cgpa=tmp->stu.ogpa;
                            tmp->stu.csco=tmp->stu.osco;
                        }
                
                if(stulist==NULL)
                {
                    stulist=(stunode*)malloc(sizeof(stunode));
                    stulist=tmp;
                    stulist->next=NULL;
                    stulist->pre=NULL;
                    stutail=stulist;
                }
                else
                {
                    flag=0;
                    stur=stulist;
                    while(sort_three_cmp(req_2,stur,tmp,ordern)==1)
                    {
                        if(stur->next!=NULL)
                        stur=stur->next;
                        else
                        {
                            flag=1;
                            break;
                        }
                    }
                                
                    if(flag==0)
                    {
                        if(stur==stulist)
                        {
                            tmp->next=stur;
                            stur->pre=tmp;
                            stulist=tmp;
                        }
                        else
                        {
                            stulast=stur->pre;
                            stulast->next=tmp;
                            tmp->pre=stulast;
                            stur->pre=tmp;
                            tmp->next=stur;
                        }
                    }
                    else
                    {
                        stur->next=tmp;
                        tmp->pre=stur;
                        tmp->next=NULL;
                        stutail=tmp;
                    }
                }
            }
            stunow=stunow->next;
        }
        
        if(stulist==NULL)
        {
            MessageBox(NULL,TEXT("未查到该学年入学的学习该专业的学生，请重新输入"),TEXT("提示"),MB_OK);
			return;
		}
		
        int classn=0,numn=0;
		stunow=stulist;
		while(stunow!=NULL)
		{
			if(classn!=stunow->stu.Class)
			{
				classn=stunow->stu.Class;
				ntmp=(struct nstunode*)malloc(sizeof(struct nstunode));
				ntmp->Stu=stunow;ntmp->freenum=classn;ntmp->next=NULL;
				if(nstulih==NULL)
				{
					nstulih=(struct nstunode*)malloc(sizeof(struct nstunode));
					ntmp->pre=NULL;nstulih=ntmp;nstunow1=nstulih;
				}
				else
				{
					ntmp->pre=nstunow1;nstunow1->next=ntmp;nstunow1=ntmp;
					ntmp=(struct nstunode*)malloc(sizeof(struct nstunode));
					ntmp->Stu=stunow->pre;ntmp->next=NULL;ntmp->freenum=numn;
					if(nstulit==NULL)
					{
						nstulit=(struct nstunode*)malloc(sizeof(struct nstunode));
						ntmp->pre=NULL;nstulit=ntmp;nstunow2=nstulit;
					}
					else{ntmp->pre=nstunow2;nstunow2->next=ntmp;nstunow2=ntmp;}
				}
				numn=0;
			}
			numn+=1;
			stunow=stunow->next;
		}
		ntmp=(struct nstunode*)malloc(sizeof(struct nstunode));
		ntmp->Stu=stutail;ntmp->next=NULL;ntmp->freenum=numn;
		if(nstulit==NULL)
		{
			nstulit=(struct nstunode*)malloc(sizeof(struct nstunode));
			ntmp->pre=NULL;nstulit=ntmp;nstunow2=nstulit;
		}
		else{ntmp->pre=nstunow2;nstunow2->next=ntmp;nstunow2=ntmp;}
	}

	if(ordern==3)
	{
        wsprintf(szBuffer,TEXT("当前班级有:"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,0,0,szBuffer,iTarget);
		nstunow1=nstulih;
		while(nstunow1!=NULL)
		{
            wsprintf(szBuffer,TEXT("%d班  "),nstunow1->freenum);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,cxChar*(cntx++)*5,cyChar,szBuffer,iTarget);
			nstunow1=nstunow1->next;
		}
		cntx=0;
		do
		{
			nstunow1=nstulih;
			nstunow2=nstulit;
			while(nstunow1!=NULL)
			{
				if(nstunow1->freenum==classre)
				{
					sort_print1(req_1,req_2);
					if(req_1==0)
					stunum=1,stur=nstunow1->Stu;
					else stunum=nstunow2->freenum,stur=nstunow2->Stu;
	
					while(stur!=NULL)
					{
						if(stur->stu.Class!=classre)break;
						sort_print2(stur,stunum);
						if(req_1==0)
						{
							stur=stur->next;
							stunum+=1;
						}
						else
						{
							stur=stur->pre;
							stunum-=1;
						}
					}
							
					//注明：不允许出现班级号为-1的情况 否则会出错
					wheright=1;
					break;
				}
				nstunow1=nstunow1->next;
				nstunow2=nstunow2->next;
			}
			if(wheright==0)
            {
                MessageBox(NULL,TEXT("无该班级，请重新输入"),TEXT("提示"),MB_OK);
                return;
            }
		}while(wheright==0);
	}
	else if(ordern==1)
	{
		sort_print1(req_1,req_2);
		if(req_1==0)
		stunum=1,stur=stulist;
		else stur=stutail;
		while(stur!=NULL)
		{
            sort_print2(stur,stunum);
            if(req_1==0)
            {stur=stur->next;stunum+=1;}
            else{stur=stur->pre;stunum-=1;}
        }
	}
	else
	{
		sort_print1(req_1,req_2);
		int classnow=0;
		nstunode *nstur=NULL;
        if(req_1==0)nstur=nstulih;
        else nstur=nstulit;
        while(nstur!=NULL)
        {
            stur=nstur->Stu;
            classnow=stur->stu.Class;
            wsprintf(szBuffer,TEXT("%d班："),classnow);
            iTarget=lstrlen(szBuffer);
            TextOut(hdc,370,50+cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
            if(req_1==0)stunum=1;
            else stunum=nstur->freenum;
            while(stur!=NULL)
            {
                if(stur->stu.Class!=classnow)break;
                sort_print2(stur,stunum);
                if(req_1==0)
                {stur=stur->next;stunum+=1;}
                else{stur=stur->pre;stunum-=1;}
            }
			nstur=nstur->next;
		}
	}
    
    return;
}

void survey_subject(clsnode *Cls) //Cos:指向当前课程的指针 Stu:学生头指针
{
    stunode *studentnow=stulih;
    cls *classnow=&(Cls->clsif);
    int studentnum=0;
    double allscore=0.0000,allgp=0.0000;
    double    failnum=0.0000,goodnum=0.0000,ecltnum=0.0000,fulgpnum=0.0000;
    double failrate,goodrate,ecltrate,fulgprate;
    double avgescore,avgegp;
    
    // allx 总x
    //xrate x率
    //xnum x人数

    wsprintf(szBuffer,TEXT("提示：若学生未完成该课程的学习，即未录入分数，则成绩为-1"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,0,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
    
    wsprintf(szBuffer,TEXT("------------------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("关于你查询的课程: %s"),classnow->id);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("------------------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("基本信息:"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("学科性质:"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
    if(classnow->nature==0)
    {
    wsprintf(szBuffer,TEXT("必修"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450+cxChar*10,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
    }
    else if(classnow->nature==0)
    {
    wsprintf(szBuffer,TEXT("选修"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450+cxChar*10,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
    }
    else
    {
    wsprintf(szBuffer,TEXT("限选"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450+cxChar*10,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
    }
    sprintf(szBuffer,TEXT("学分:%.1lf"),classnow->cdt);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450+cxChar*16,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("任课老师:%s"),classnow->teacher);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450+cxChar*26,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("---------------------------------------------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    wsprintf(szBuffer,TEXT("学生学习情况:"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    
    studentnow=stulih;
    
    nstunode *newstulist=NULL,*newstunow=NULL,*tmp=NULL;
    //新建链表，节点为选择了 该课程的学生：newstulist 和 学生该课程的信息；thecoslist
    
    while(studentnow!=NULL)             //寻找相关学生
    {
        student stunow=studentnow->stu;
        if(stunow.scoreh->pre==NULL&&stunow.scoreh->next!=NULL)stunow.scoreh=stunow.scoreh->next;
        if(stunow.scoret->pre!=NULL)
		{
			cosnode *coursenow=stunow.scoret;
			while(coursenow!=NULL&&coursenow->pre!=NULL)
			{
				if(strcmp(coursenow->cos.c->id,Cls->clsif.id)==0)
				{
					tmp=(struct nstunode*)malloc(sizeof(struct nstunode));
					tmp->Stu=studentnow;
					tmp->Cos=coursenow;
					tmp->next=NULL;
					
					if(newstulist==NULL)
					{
						newstulist=(struct nstunode*)malloc(sizeof(struct nstunode));
						newstulist=tmp;
						newstulist->pre=NULL;
						newstunow=newstulist;
					}
					else
					{
						newstunow->next=tmp;
						tmp->pre=newstunow;
						newstunow=tmp;
					}
					double scorenow=coursenow->cos.score;
					double gpnow=coursenow->cos.gp;
					if(scorenow>=0)
					{
						studentnum+=1;
						allscore+=scorenow;
						allgp+=gpnow;
					}
					if(gpnow>=3.0000)
					{
						goodnum+=1;
						if(gpnow>=3.7000)
						{
							ecltnum+=1;
							if(gpnow==4.0000)
							fulgpnum+=1;
						}
					}
					else if(scorenow<60.0000&&scorenow>=0)
					failnum+=1;
					break;
				}
				coursenow=coursenow->pre;
			}
			studentnow=studentnow->next;
		}
	}
        
    
    if(newstulist==NULL)
    {
        wsprintf(szBuffer,TEXT("未查到选择该课程的学生，故无法显示学生排名！"));
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        return;
    }
    
    //计分 计率
    if(studentnum!=0)
    {
    	avgescore=allscore/studentnum;
	    avgegp=allgp/studentnum;
	    failrate=failnum/studentnum;
	    goodrate=goodnum/studentnum;
	    ecltrate=ecltnum/studentnum;
	    fulgprate=fulgpnum/studentnum;
	}
	else
	{
		avgescore=0.0000;
	    avgegp=0.0000;
	    failrate=0.0000;
	    goodrate=0.0000;
	    ecltrate=0.0000;
	    fulgprate=0.0000;
	}
	
    newstunow=newstulist;
    nstunode *newstulast=NULL,*newstux=NULL,*newstuy=NULL,*newstut=NULL;
    
    while(newstunow!=NULL)
    {
        newstux=newstulist;
        
        while(newstux->Cos->cos.score>=newstunow->Cos->cos.score&&newstux!=newstunow)
        {
            newstuy=newstux;
            newstux=newstux->next;
        }
        if(newstux!=newstunow)
        {
            newstut=newstunow;
            newstulast->next=newstunow->next;
            newstunow=newstulast;
            
            if(newstux==newstulist)
            {
                newstut->next=newstulist;
                newstulist=newstut;
            }
            else
            {
                newstuy->next=newstut;
                newstut->next=newstux;
            }
        }
        
        newstulast=newstunow;
        newstunow=newstunow->next;
    }
    
    sprintf(szBuffer,TEXT("均分:%10.4lf  均绩:%10.4lf"),avgescore,avgegp);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("挂科率:%.4lf%%   良好率:%.4lf%%"),failrate*100.0000,goodrate*100.0000);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("优秀率:%.4lf%%   满绩率:%.4lf%%"),ecltrate*100.0000,fulgprate*100.0000);
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("---------------------------------------------------------------------------"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    sprintf(szBuffer,TEXT("学生姓名              该课成绩         该课绩点"));
    iTarget=lstrlen(szBuffer);
    TextOut(hdc,450,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
    while(newstulist!=NULL)
    {
        sprintf(szBuffer,TEXT("%-20s"),newstulist->Stu->stu.name);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,450,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
        sprintf(szBuffer,TEXT("%-10d"),newstulist->Cos->cos.score);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,450+cxChar*20,cyChar*((cnty)-iVscrollPos),szBuffer,iTarget);
        sprintf(szBuffer,TEXT("%-10.4lf"),newstulist->Cos->cos.gp);
        iTarget=lstrlen(szBuffer);
        TextOut(hdc,450+cxChar*30,cyChar*((cnty++)-iVscrollPos),szBuffer,iTarget);
        newstulist=newstulist->next;
    }
    while(newstulist!=NULL)
    {
        nstunode *p=newstulist;
        free(p);
        newstulist=newstulist->next;
    }
    return;
}

void inputstuascr(int choose)
{
    if(choose==0)
        AESorSSon1Window();
    if(choose==1)
    {
        char str[1000];
        stunode *stunow=stulih;
        nstulihh=NULL;
        emptynum=0;
        nstunode *tmp=NULL,*nstunow=NULL;
        strcpy(str,clstobe->clsif.name);
        while(stunow!=NULL)
        {
            if(stunow->stu.scoreh->pre==NULL&&stunow->stu.scoreh->next!=NULL)stunow->stu.scoreh=stunow->stu.scoreh->next;
            cosnode *cosn=stunow->stu.scoret;
            while(cosn!=NULL&&cosn->pre!=NULL)
            {
                if(strcmp(cosn->cos.c->name,str)==0)
                {
                    if(cosn->cos.score==-1)
                    {
                        emptynum+=1;
                        tmp=(struct nstunode*)malloc(sizeof(struct nstunode));
                        tmp->Stu=stunow;tmp->Cos=cosn;tmp->next=NULL;tmp->pre=NULL;
                        if(nstulihh==NULL)
                        {
                            nstulihh=(struct nstunode*)malloc(sizeof(struct nstunode));
                            nstulihh=tmp;nstunow=nstulihh;
                        }
                        else
                        {
                            nstunow->next=tmp;
                            tmp->pre=nstunow;
                            nstunow=tmp;
                        }
                    }
                break;
                }
                cosn=cosn->pre;
            }
            stunow=stunow->next;
        }
        
        if(nstulihh==NULL)
        {
            MessageBox(NULL,TEXT("当前课程未查到学生需要录入成绩"),TEXT("提示"),MB_OK);
            return;
        }
        
        nstuinall=nstulihh;
        AESorSSon2Window();
        while(nstulihh!=NULL)
        {
            nstunode *p=nstulihh;
            nstulihh=nstulihh->next;
            free(p);
        }
    }
    return;
}
#endif
