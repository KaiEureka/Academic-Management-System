#ifndef __WORKOFXZL
#define __WORKOFXZL

void inputcourse(char Name[],char Id[],int Nature,char Teacher[],double Credit)
{
    clsnode *cnew=(clsnode*)malloc(sizeof(clsnode));
    strcpy(cnew->clsif.name,Name);
    strcpy(cnew->clsif.id,Id);
    strcpy(cnew->clsif.teacher,Teacher);
    cnew->clsif.nature=Nature;
    cnew->clsif.cdt=Credit;
    cnew->next=NULL;
    cnew->pre=clslit;
    clslit->next=cnew;
    clslit=clslit->next; 
}

void deletestudent(stunode* Stu)
{
    if(Stu->next!=NULL) Stu->next->pre=Stu->pre;
    Stu->pre->next=Stu->next;
	if(Stu==stulih)stulih=stulih->next;
    free(Stu);
}

void enterhonor(stunode *Stu,char S[],double Inf)
{
    strnode *cnew=(strnode*)malloc(sizeof(strnode));
    cnew->inf=Inf;
    strcpy(cnew->s,S);
    cnew->next=NULL;
    cnew->pre=Stu->stu.honort;
    Stu->stu.honort->next=cnew;
    Stu->stu.honort=Stu->stu.honort->next;
}

void enterpunish(stunode *Stu,char S[],double Inf)
{
    strnode *cnew=(strnode*)malloc(sizeof(strnode));
    cnew->inf=Inf;
    strcpy(cnew->s,S);
    cnew->next=NULL;
    cnew->pre=Stu->stu.punisht;
    Stu->stu.punisht->next=cnew;
    Stu->stu.punisht=Stu->stu.punisht->next;
}

#endif
