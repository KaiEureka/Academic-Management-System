#ifndef __SEARCH
#define __SEARCH

teanode* searchtea(char* str)
{
	teanode* p=tealih;

    while(p!=NULL)
    {
        if(strcmp(p->tea.account,str)==0)
            return p;
		p=p->next;
    }
    return NULL;
}

rootnode* searchroot(char* str)
{
	rootnode* p=rootlih;
    while(p!=NULL)
    {
        if(strcmp(p->rt.account,str)==0)
            return p;
		p=p->next;
    }
    return NULL;
}

stunode* searchstuid(char* str)
{
    stunode* p=stulih;
    while(p!=NULL)
    {
        if(strcmp(p->stu.id,str)==0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

stunode* searchstu(char* str)
{
    stunode* p=stulih;
    while(p!=NULL)
    {
        if(strcmp(p->stu.name,str)==0)
        {
            return p;
        }
        p=p->next;
    }
	p=stulih;
	while(p!=NULL)
    {
        if(strcmp(p->stu.id,str)==0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

clsnode* searchcls(char* str)
{
    clsnode* p=clslih;
    while(p!=NULL)
    {
        if(strcmp(p->clsif.name,str)==0)
        {
            return p;
        }
        p=p->next;
    }
	p=clslih;
    while(p!=NULL)
    {
        if(strcmp(p->clsif.id,str)==0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

int searchmajor(char* str)
{
    stunode* p=stulih;
    while(p!=NULL)
    {
        if(strcmp(p->stu.major,str)==0)return 1;
        p=p->next;
    }
    return 0;
}

#endif
