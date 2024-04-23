#ifndef __STRUCTOFPJ
#define __STRUCTOFPJ

typedef struct applyment
{
    char str[1000];
    int status;//0 代表未处理 1代表批准 2代表否决
    struct applyment *next;
    struct applyment *pre;
}apt;
typedef struct strnode
{
    char s[200];
    double inf;//influnce of gpa
    struct strnode * next;
    struct strnode * pre;
}strnode;
typedef struct classitself
{
    char name[100];
    char id[20];//the id of class
    int nature;//0 is Compulsory course while 1 is optional course of study while 2 is optional compulsory courses
    char teacher[100];//teacher's name
    double cdt;
}cls;
typedef struct course
{
    cls* c;
    int first;//1 is first while 0 is re-study
    int score;
    double gp;
}course;
typedef struct cosnode
{
    course cos;
    struct cosnode* next;
    struct cosnode* pre;
}cosnode;
typedef struct clsnode
{
    cls clsif;
    struct clsnode* next;
    struct clsnode* pre;
}clsnode;
typedef struct student
{
    char name[20];
    char id[30];//student number
    int gender;//1 is male while 0 is female
    int year;//Year of enrollment
    int Class;
    double cgpa;
    double csco;
    double tgpa;
    double tsco;
    double sgpa;
    double ssco;
	double ogpa;
    double osco;
    char pwd[30];
    char home[20];//province of stu
    char major[100];
    cosnode *scoreh,*scoret;
    strnode *honorh,*honort;
    strnode *punishh,*punisht;
}student;
typedef struct stunode
{
    student stu;
    struct stunode* next;
    struct stunode* pre;
}stunode;
typedef struct nstunode                //Stu指向学生 Cos指向学生学习的这门课程
{
	int freenum;						//定义一个自由量 方便操作，不然太难受了QwQ 
    stunode *Stu;
    cosnode *Cos;
    struct nstunode *next;
    struct nstunode *pre;
}nstunode;
typedef struct teacher
{
	char name[50];
	char account[50];
	char pwd[50];
}teacher;
typedef struct teanode
{
	teacher tea;
	struct teanode* next;
	struct teanode* pre;
}teanode;
typedef struct root
{
	char name[50];
	char account[50];
	char pwd[50];
}root;
typedef struct rootnode
{
	root rt;
	struct rootnode* next;
	struct rootnode* pre;
}rootnode;

#endif
