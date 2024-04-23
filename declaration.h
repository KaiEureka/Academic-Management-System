#ifndef __DECLARATION
#define __DECLARATION

#ifndef MAXINPUT 
#define MAXINPUT 10000
#endif

#define ID_BUTTON_LOGIN 1
#define ID_COMBOBOX_LOGIN_TYPE 2
#define IDC_EDIT_USERNAME 3
#define IDC_EDIT_PASSWORD 4

#define ID_BUTTON_VIEW_BASIC_INFO      101
#define ID_BUTTON_VIEW_ALL_COURSES     102
#define ID_BUTTON_QUERY_SUBJECT_SCORE  103
#define ID_BUTTON_QUERY_TOTAL_SCORE    104
#define ID_BUTTON_VIEW_RANKING         105
#define ID_BUTTON_CHANGE_PASSWORD      106
#define ID_BUTTON_EXIT_SYSTEM          107
#define ID_BUTTON_SEARCH               108

#define ID_BUTTON_TEA_VIEW_BASIC_INFO        1201
#define ID_BUTTON_TEA_VIEW_ALL_COURSES       1202
#define ID_BUTTON_TEA_QUERY_DETAILED_SCORE   1203
#define ID_BUTTON_TEA_VIEW_RANKING           1204
#define ID_BUTTON_TEA_ANALISE_COURSE         1205
#define ID_BUTTON_TEA_INPUT_SCORE            1206
#define ID_BUTTON_TEA_CHANGE_SCORE           1207
#define ID_BUTTON_TEA_INPUT_NEWCOURSE        1208
#define ID_BUTTON_TEA_DELETE_STUDENT         1209
#define ID_BUTTON_TEA_INPUT_HONOR            1210
#define ID_BUTTON_TEA_INPUT_PUNISH           1211
#define ID_BUTTON_TEA_CHANGE_PASSWORD        1212
#define ID_BUTTON_TEA_EXIT_SYSTEM            1213

#define ID_BUTTON_ROOT_VIEW_STUDENT_INFO        1301
#define ID_BUTTON_ROOT_VIEW_TEACHER_INFO        1302
#define ID_BUTTON_ROOT_VIEW_COURSES_INFO        1303
#define ID_BUTTON_ROOT_VIEW_DETAILED_SCORE      1304
#define ID_BUTTON_ROOT_VIEW_RANKING             1305
#define ID_BUTTON_ROOT_CHANGE_SCORE             1306
#define ID_BUTTON_ROOT_INPUT_NEWCOURSE          1307
#define ID_BUTTON_ROOT_INPUT_NEWTEACHER         1308
#define ID_BUTTON_ROOT_INPUT_NEWSTUDENT         1309
#define ID_BUTTON_ROOT_DELETE_STUDENT           1310
#define ID_BUTTON_ROOT_INPUT_HONOR              1311
#define ID_BUTTON_ROOT_INPUT_PUNISH             1312
#define ID_BUTTON_ROOT_ANALISE_COURSE           1313
#define ID_BUTTON_ROOT_INPUT_SCORE              1314
#define ID_BUTTON_ROOT_EXAMINE_APPLY            1315
#define ID_BUTTON_ROOT_CHANGE_PASSWORD          1316
#define ID_BUTTON_ROOT_EXIT_SYSTEM              1317

extern HWND g_hComboBoxLoginType;
extern HWND g_hComboBoxpaiming0Type;
extern HWND g_hComboBoxpaiming1Type;
extern HWND g_hComboBoxpaiming2Type;
extern HWND g_hComboBoxpaiming3Type;
extern HWND g_hEditUsername;
extern HWND g_hEditUsername1;
extern HWND g_hEditPassword;
extern HWND g_hEditPassword0;
extern HWND g_hEditPassword1;
extern HWND g_hEditUseryear;
extern HWND g_hEditUsermajor;
extern HWND g_hEditUserclass;
extern HWND g_hEditUserid;
extern HWND g_hEditUserid1;
extern HWND g_hEditUsergender;
extern HWND g_hEditUserpwd;
extern HWND g_hEditUserpwd1;
extern HWND g_hEditUserhome;
extern HWND g_hEditUserypwd;
extern HWND g_hEditStuname;
extern HWND g_hEditevent;
extern HWND g_hEditpoint;
extern HWND g_hComboBoxPunishType;
extern HWND g_hEditCourse;
extern HWND g_hEditGrade;
extern TCHAR szBuffer[128];
extern size_t iTarget;
extern HDC hdc;
extern PAINTSTRUCT ps;
extern TEXTMETRIC tm;

extern char ORDER[100];
extern char EA[100];
extern char SCORE[100];
extern char CLS[100];
extern char ROOT[100];
extern char TEA[100];
extern char STU[100];
extern int aid,tos,Tstu,i,j,emptynum,flaginson2,cntx,cnty,flag,ordern,req_1,req_2,Ayear,Aclass;//account id; teacher or student
extern char ch,str[10000],majornow[100],Bclass[100],str1;
extern stunode *stulih,*stulit,*stunowinall;
extern cosnode *coslih,*coslit,*cosnowinall;
extern clsnode *clslih,*clslit,*clstobe;
extern teanode *tealih,*tealit;
extern rootnode *rootlih,*rootlit;
extern apt *aptlih,*Q,*P;
extern stunode *stuuser,*astu;
extern teanode *teauser;
extern rootnode *rootuser;
nstunode *nstulihh,*nstuinall;
static int cxChar,cxCaps,cyChar,cxCliect,cyClient,iVscrollPos;

inline cosnode *sort_bycls(stunode *stunow);
double maxdouble(double x,double y);
void showscoresofastu(stunode* astu);
void cptsg(stunode *Stu);//计算学生的必修课均分、必修课均绩、选修课均分、选修课均绩
double cptgp(int sco);
stunode* searchstu(char* str);
stunode* searchstuid(char* str);
clsnode* searchcls(char* str);
void login();
void Initialization();
void InitializationOfSTU();
void InitializationOfTEA();
void InitializationOfCLS();
void InitializationOfORDER();
void InitializationOfROOT();
void InitializationOfSCORE();
void InitializationOfEA();
void inputscore(stunode* pstu,clsnode* pcls,int sc,double gp,int isfirst);
void showstudent();
void showteacher();
void showcls();
void showfunoftea();
void showfunofstu();
void showfunofroot();
void deletestudent(stunode* Stu);
void inputcourse(char Name[],char Id[],int Nature,char Teacher[],double Credit);
void showgcofastu(stunode* stuuser);
void changescoreofastu(stunode* astu,clsnode* acls,int newscore,int isfirst);
void analysetea();
void analysestu();
void analyseroot();
void changepwd();
void showstudentscores();
void enterhonor(stunode *Stu,char S[],double Inf);
void enterpunish(stunode *Stu,char S[],double Inf);
void showhpofastu(stunode* stuuser);
void survey_subject(clsnode *Cls);
int searchmajor(char* str);
void sort_three(int year,char majornow[],int ordern,int req_1,int req_2,int classre);
int searchyear(int wheyear);
inline int sort_three_cmp(int require,stunode *x,stunode *y,int ord);
void sort_free(stunode *xxx,nstunode *yyy,nstunode *zzz);
void sort_print1(int req1,int req2);
void sort_print2(stunode *stow,int studnum);
void inputstuascr(int choose);
void inputScore(cosnode *conn);
void createnewstu(char* aname,char* aid,int agender,char* amajor,int ayear,int aclass,char* apwd,char* ahome);
void showoptionalscore(int sco);
void changepwdofstu(stunode* stuuser,char* str);
void changemajorofstu(stunode* stuuser,char* str);
void changepwdoftea(teanode* teauser,char* str);
void changepwdofroot(rootnode* rootuser,char* str);
void changescoreofroot();
void inputcourseofroot();
void addstudentofroot(char aname[],char aid[],int agender,char amajor[],int ayear,int aclass,char apwd[],char ahome[]);
void deletestuofroot(char str[]);
void enterhonorofroot();
void enterpunishofroot();
void inputnewteacher(char tname[],char taccount[],char tpwd[]);
void examineofroot();
void inputcourseoftea();
void deletestuoftea(char str[]);
void enputhonoroftea();
void enterpunishoftea();
rootnode* searchroot(char* str);
teanode* searchtea(char* str);
void StudentWindow();
void ShowStuWindow();
void ChangeStuWindow();
void SearchGradeWindow();
void TeacherWindow();
void AdminWindow(); 
void ChangeTeaWindow();
void ChangeAdmWindow();
void AdmStuWindow();
void ClassAnalyWindow();
void AmdAppWindow();
void StuClassWindow();
void StuClassScoreWindow();
void StuAllScoreWindow();
void TeaShowStuWindow();
void AdmInStuWindow();
void AdmOutStuWindow();
void AdmInTeaWindow();
void AdmInCouWindow();
void ShowTeatoAdmWindow();
void ShowCostoAdmWindow();
void AdmEntpunWindow();
void ShowStutoAdmWindow();
void AdmEnthorWindow();
void AdmChangeScoreWindow();
void TeaInCouWindow();
void TeaEnthorWindow();
void TeaOutStuWindow();
void TeaEntpunWindow();
void TeaChangeScoreWindow();
void AdmEntStuorScoWindow(); 
void InputScoreWindow();
void AESorSSon1Window();
void AESorSSon2Window();
void AdmEntStuorScoWindow();
void dealwithch(apt* P,char ch);

#endif
