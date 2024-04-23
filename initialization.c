#ifndef __INITIALIZATION
#define __INITIALIZATION

void Initialization()
{
    stulih=(stunode*)malloc(sizeof(stunode));
    stulih->pre=stulih->next=NULL;
    stulit=stulih;
    clslih=(clsnode*)malloc(sizeof(clsnode));
    clslih->pre=clslih->next=NULL;
    clslit=clslih;
	tealih=(teanode*)malloc(sizeof(teanode));
	tealih->pre=tealih->next=NULL;
	tealit=tealih;
	rootlih=(rootnode*)malloc(sizeof(rootnode));
	rootlih->pre=rootlih->next=NULL;
	rootlit=rootlih;

	InitializationOfSTU();
	InitializationOfCLS();
	InitializationOfSCORE();
	InitializationOfROOT();
	InitializationOfTEA();
	InitializationOfORDER();
	InitializationOfEA();

	stunode* p=stulih;
    while(p!=NULL)
    {
        cptsg(p);
        p=p->next;
    }
	return;
}

void InitializationOfEA()
{
	FILE *fp;
	if((fp=fopen(EA,"r"))!=NULL)
    {
        aptlih=NULL;
        apt* p=aptlih;
        while(fgets(str,MAXINPUT,fp))
        {
            if(str[0]=='\0'||str[0]=='\r'||str[0]=='\n')continue;
            if(aptlih==NULL)
            {
                p=(apt*)malloc(sizeof(apt));
                aptlih=p;
                strcpy(p->str,str);
                p->status=0;
                p->next=p->pre=NULL;
            }
            else
            {
                apt* newapt=(apt*)malloc(sizeof(apt));
                newapt->status=0;
                strcpy(newapt->str,str);
                newapt->next=NULL;
                newapt->pre=p;
                p->next=newapt;
                p=p->next;
            }
        }
    }
	fclose(fp);
	return;
}

void InitializationOfSTU()
{
	FILE *fp;
	if((fp=fopen(STU,"r"))!=NULL)
    {
        while(fgets(str,MAXINPUT,fp))
        {
            if(str[0]=='\n'||str[0]=='\r')continue;
            Tstu++;
            student astu;
            int j,p=0;
            for(j=0;str[p]!=';';j++)
            {
                astu.name[j]=str[p];
                p++;
            }
            astu.name[j]='\0';
            p++;
            for(j=0;str[p]!=';';j++)
            {
                astu.id[j]=str[p];
                p++;
            }
            astu.id[j]='\0';
            p++;
            astu.gender=0;
            for(j=0;str[p]!=';';j++)
            {
                if(str[p]>='0'&&str[p]<='9')
                    astu.gender=str[p]-'0';
                p++;
            }
            p++;
            for(j=0;str[p]!=';';j++)
            {
                astu.major[j]=str[p];
                p++;
            }
            astu.major[j]='\0';
            p++;
            astu.year=0;
            while(str[p]!=';')
            {
                if(str[p]>='0'&&str[p]<='9')
                    astu.year=astu.year*10+(str[p]-'0');
                p++;
            }
            p++;
            astu.Class=0;
            while(str[p]!=';')
            {
                if(str[p]>='0'&&str[p]<='9')
                    astu.Class=astu.Class*10+(str[p]-'0');
                p++;
            }
            p++;
            for(j=0;str[p]!=';';j++)
            {
                astu.pwd[j]=str[p];
                p++;
            }
            astu.pwd[j]='\0';
            p++;
            for(j=0;str[p]!='\n'&&str[p]!='\r';j++)
            {
                astu.home[j]=str[p];
                p++;
            }
            astu.home[j]='\0';
            astu.scoreh=(cosnode*)malloc(sizeof(cosnode));
            astu.scoreh->pre=astu.scoreh->next=NULL;
            astu.scoret=astu.scoreh;

            astu.honorh=(strnode*)malloc(sizeof(strnode));
            astu.honorh->pre=astu.honorh->next=NULL;
            astu.honorh->inf=0;
            astu.honort=astu.honorh;

            astu.punishh=(strnode*)malloc(sizeof(strnode));
            astu.punishh->pre=astu.punishh->next=NULL;
            astu.punishh->inf=0;
            astu.punisht=astu.punishh;

            stunode* anewnode=(stunode*)malloc(sizeof(stunode));
            anewnode->pre=stulit;
            anewnode->next=NULL;
            anewnode->stu=astu;
            stulit->next=anewnode;
            stulit=stulit->next;
        }
        stulih=stulih->next;
    }
	fclose(fp);
	return;
}

void InitializationOfTEA()
{
	FILE *fp;
	if((fp=fopen(TEA,"r"))!=NULL)
    {
        while(fgets(str,MAXINPUT,fp))
        {
			teanode *anewtea=(teanode*)malloc(sizeof(teanode));
            if(str[0]=='\n'||str[0]=='\r')continue;
            int j,p=0;
            for(j=0;str[p]!=';';j++)
            {
                anewtea->tea.name[j]=str[p];
                p++;
            }
            anewtea->tea.name[j]='\0';
            p++;
            for(j=0;str[p]!=';';j++)
            {
                anewtea->tea.account[j]=str[p];
                p++;
            }
            anewtea->tea.account[j]='\0';
            p++;
            for(j=0;str[p]!='\n'&&str[p]!='\r';j++)
            {
                anewtea->tea.pwd[j]=str[p];
                p++;
            }
            anewtea->tea.pwd[j]='\0';
			tealit->next=anewtea;
			anewtea->pre=tealit;
			tealit=tealit->next;
        }
		if(tealih->pre==NULL&&tealih->next!=NULL)tealih=tealih->next;
    }
	fclose(fp);
	return;
}

void InitializationOfCLS()
{
	FILE *fp;
	if((fp=fopen(CLS,"r"))!=NULL)
    {
        while(fgets(str,MAXINPUT,fp))
        {
            if(str[0]=='\n'||str[0]=='\r')continue;
            cls acls;
            int j,p=0;
            for(j=0;str[p]!=';';j++)
            {
                acls.name[j]=str[p];
                p++;
            }
            acls.name[j]='\0';
            p++;
            for(j=0;str[p]!=';';j++)
            {
                acls.id[j]=str[p];
                p++;
            }
            acls.id[j]='\0';
            p++;
            acls.nature=0;
            while(str[p]!=';')
            {
                if(str[p]>='0'&&str[p]<='9')
                    acls.nature=str[p]-'0';
                p++;
            }
            p++;
            for(j=0;str[p]!=';';j++)
            {
                acls.teacher[j]=str[p];
                p++;
            }
            acls.teacher[j]='\0';
            p++;
            acls.cdt=0.0;
            int pa=0;
            double w=1.0;
            while(str[p]!='\n'&&str[p]!='\r')
            {
                if(str[p]=='.')pa=1;
                else if(pa==0&&str[p]>='0'&&str[p]<='9')
                    acls.cdt=acls.cdt*10+str[p]-'0';
                else if(pa==1&&str[p]>='0'&&str[p]<='9')
                {
                    w*=0.1;
                    acls.cdt+=w*(str[p]-'0');
                }
                p++;
            }

            clsnode* anewnode=(clsnode*)malloc(sizeof(clsnode));
            anewnode->pre=clslit;
            anewnode->next=NULL;
            anewnode->clsif=acls;
            clslit->next=anewnode;
            clslit=clslit->next;
        }
        clslih=clslih->next;
    }
	fclose(fp);
	return;
}

//下面是一个250行的函数，略微超标
void InitializationOfORDER()
{
	FILE *fp;
	if((fp=fopen(ORDER,"r"))!=NULL)
    {
        while(fgets(str,MAXINPUT,fp))
        {
            int j,p=0;
            if(str[0]=='\n'||str[0]=='\r')continue;
            char ordername[100];
            for(j=0;str[p]!=';';j++)
            {
                ordername[j]=str[p];
                p++;
            }
            ordername[j]='\0';p++;
            if(strcmp(ordername,"deletestu")==0)
            {
                char astuname[100];
                for(j=0;str[p]!=';';j++)
                {
                    astuname[j]=str[p];
                    p++;
                }
                astuname[j]='\0';p++;
                deletestudent(searchstu(astuname));
            }
            else if(strcmp(ordername,"changescoreofastu")==0)
            {
                char astr[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                stunode* astu=searchstu(astr);
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                
                clsnode* acls=searchcls(astr);
                int anum=0;
                while(str[p]!=';')
                {
                    if(str[p]>='0'&&str[p]<='9')
                        anum=anum*10+str[p]-'0';
                    p++;
                }
                p++;
                int newscore=anum;
                anum=0;
                while(str[p]!=';')
                {
                    if(str[p]>='0'&&str[p]<='9')
                        anum=anum*10+str[p]-'0';
                    p++;
                }
                int isfirst=anum;
                changescoreofastu(astu,acls,newscore,isfirst);
            }
            else if(strcmp(ordername,"enterhonor")==0)
            {
                char astr[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                stunode* astu=searchstu(astr);
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                int flag=0;
                double zs=0.0,xs=0.0,adouble,m1=0.1;
                for(j=0;str[p]!=';';j++)
                {
                    if(str[p]=='.')
                    {
                        flag=1;p++;
                        continue;
                    }
                    if(flag==0)
                    {
                        zs=zs*10+str[p]-'0';
                    }
                    else
                    {
                        xs+=m1*(str[p]-'0');
                        m1*=0.1;
                    }
                    p++;
                }
                adouble=zs+xs;
                enterhonor(astu,astr,adouble);
            }
            else if(strcmp(ordername,"enterpunish")==0)
            {
                char astr[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                stunode* astu=searchstu(astr);
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                int flag=0;
                double zs=0.0,xs=0.0,adouble,m1=0.1;
                for(j=0;str[p]!=';';j++)
                {
                    if(str[p]=='.')
                    {
                        flag=1;p++;
                        continue;
                    }
                    if(flag==0)
                    {
                        zs=zs*10+str[p]-'0';
                    }
                    else
                    {
                        xs+=m1*(str[p]-'0');
                        m1*=0.1;
                    }
                    p++;
                }
                adouble=zs+xs;
                enterpunish(astu,astr,adouble);
            }
            else if(strcmp(ordername,"inputcourse")==0)
            {
                char astr1[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr1[j]=str[p];
                    p++;
                }
                astr1[j]='\0';p++;
                char astr2[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr2[j]=str[p];
                    p++;
                }
                astr2[j]='\0';p++;
                int anum=0;
                while(str[p]!=';')
                {
                    if(str[p]>='0'&&str[p]<='9')
                        anum=anum*10+str[p]-'0';
                    p++;
                }
                p++;
                char astr3[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr3[j]=str[p];
                    p++;
                }
                astr3[j]='\0';p++;
                int flag=0;
                double zs=0.0,xs=0.0,adouble,m1=0.1;
                for(j=0;str[p]!=';';j++)
                {
                    if(str[p]=='.')
                    {
                        flag=1;p++;
                        continue;
                    }
                    if(flag==0)
                    {
                        zs=zs*10+str[p]-'0';
                    }
                    else
                    {
                        xs+=m1*(str[p]-'0');
                        m1*=0.1;
                    }
                    p++;
                }
                adouble=zs+xs;
                inputcourse(astr1,astr2,anum,astr3,adouble);
            }
            else if(strcmp(ordername,"changepwdofstu")==0)
			{
				char astr1[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr1[j]=str[p];
                    p++;
                }
                astr1[j]='\0';p++;
                char astr2[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr2[j]=str[p];
                    p++;
                }
                astr2[j]='\0';p++;
				changepwdofstu(searchstu(astr1),astr2);
			}
			else if(strcmp(ordername,"changemajorofstu")==0)
			{
				char astr1[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr1[j]=str[p];
                    p++;
                }
                astr1[j]='\0';p++;
                char astr2[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr2[j]=str[p];
                    p++;
                }
                astr2[j]='\0';p++;
				changemajorofstu(searchstu(astr1),astr2);
			}
			else if(strcmp(ordername,"changepwdoftea")==0)
			{
				char astr1[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr1[j]=str[p];
                    p++;
                }
                astr1[j]='\0';p++;
                char astr2[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr2[j]=str[p];
                    p++;
                }
                astr2[j]='\0';p++;
				changepwdoftea(searchtea(astr1),astr2);
			}
			else if(strcmp(ordername,"changepwdofroot")==0)
			{
				char astr1[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr1[j]=str[p];
                    p++;
                }
                astr1[j]='\0';p++;
                char astr2[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr2[j]=str[p];
                    p++;
                }
                astr2[j]='\0';p++;
				changepwdofroot(searchroot(astr1),astr2);
			}
			else if(strcmp(ordername,"inputscore")==0)
            {
                char astr[100];
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                stunode* astu=searchstu(astr);
                for(j=0;str[p]!=';';j++)
                {
                    astr[j]=str[p];
                    p++;
                }
                astr[j]='\0';p++;
                
                clsnode* acls=searchcls(astr);
                int anum=0,iffu=1;
                while(str[p]!=';')
                {
                    if(str[p]=='-')iffu=-1;
                    if(str[p]>='0'&&str[p]<='9')
                        anum=anum*10+str[p]-'0';
                    p++;
                }
                p++;
                int newscore=anum*iffu;
                anum=0;
                int flag=0;
                double zs=0.0,xs=0.0,adouble,m1=0.1,iffuf=1.0;
                for(j=0;str[p]!=';';j++)
                {
                    if(str[p]=='-')
					{
						iffuf=-1.0;p++;continue;
					}
                    if(str[p]=='.')
                    {
                        flag=1;p++;
                        continue;
                    }
                    if(flag==0)
                    {
                        zs=zs*10+str[p]-'0';
                    }
                    else
                    {
                        xs+=m1*(str[p]-'0');
                        m1*=0.1;
                    }
                    p++;
                }
                adouble=(zs+xs)*iffuf;p++;
                while(str[p]!=';')
                {
                    if(str[p]>='0'&&str[p]<='9')
                        anum=anum*10+str[p]-'0';
                    p++;
                }
                int isfirst=anum;
                inputscore(astu,acls,newscore,adouble,isfirst);
            }
			else
            {
                printf("ERROR:%s\n",ordername);
            }
        }
    }
	fclose(fp);
}

void InitializationOfROOT()
{
	FILE *fp;
	if((fp=fopen(ROOT,"r"))!=NULL)
    {
        while(fgets(str,MAXINPUT,fp))
        {
			rootnode *anewroot=(rootnode*)malloc(sizeof(rootnode));
            if(str[0]=='\n'||str[0]=='\r')continue;
            int j,p=0;
            for(j=0;str[p]!=';';j++)
            {
                anewroot->rt.name[j]=str[p];
                p++;
            }
            anewroot->rt.name[j]='\0';
            p++;
            for(j=0;str[p]!=';';j++)
            {
                anewroot->rt.account[j]=str[p];
                p++;
            }
            anewroot->rt.account[j]='\0';
            p++;
            for(j=0;str[p]!='\n'&&str[p]!='\r';j++)
            {
                anewroot->rt.pwd[j]=str[p];
                p++;
            }
            anewroot->rt.pwd[j]='\0';
			rootlit->next=anewroot;
			anewroot->pre=rootlit;
			rootlit=rootlit->next;
        }
		if(rootlih->pre==NULL&&rootlih->next!=NULL)rootlih=rootlih->next;
    }
	fclose(fp);
	return;
}

void InitializationOfSCORE()
{
	FILE *fp;
	if((fp=fopen(SCORE,"r"))!=NULL)
    {
        while(fgets(str,MAXINPUT,fp))
        {
            if(str[0]=='\n'||str[0]=='\r')continue;
            char stuname[100],clsname[100],fi,sco;
            int j,p=0;
            for(j=0;str[p]!=';';j++)
            {
                stuname[j]=str[p];
                p++;
            }
            stuname[j]='\0';
            p++;
            for(j=0;str[p]!=';';j++)
            {
                clsname[j]=str[p];
                p++;
            }
            clsname[j]='\0';
            p++;
            fi=0;
            while(str[p]!=';')
            {
                if(str[p]>='0'&&str[p]<='9')
                    fi=str[p]-'0';
                p++;
            }
            p++;
            sco=0;
            while(str[p]!='\n'&&str[p]!='\r')
            {
                if(str[p]>='0'&&str[p]<='9')
                    sco=sco*10+str[p]-'0';
                p++;
            }
            stunode* stup=searchstu(stuname);
            if(stup==NULL)printf("error");
            clsnode* clsp=searchcls(clsname);
			if(clsp==NULL)printf("error");
            double agp=cptgp(sco);
            inputscore(stup,clsp,sco,agp,fi);
            if(stup->stu.scoreh!=NULL&&stup->stu.scoreh->pre==NULL&&stup->stu.scoreh->next!=NULL)
				stup->stu.scoreh=stup->stu.scoreh->next;
        }
    }
	fclose(fp);
	return;
}

#endif
