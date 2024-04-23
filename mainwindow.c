#ifndef MAINWINDOW
#define MAINWINDOW

//学生登录后界面
LRESULT CALLBACK StuWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BUTTON_VIEW_BASIC_INFO: //查看信息
            ShowStuWindow();
            break;
        case ID_BUTTON_VIEW_ALL_COURSES:
            StuClassWindow();
            break;
        case ID_BUTTON_QUERY_SUBJECT_SCORE:
            StuClassScoreWindow();
            break;
        case ID_BUTTON_QUERY_TOTAL_SCORE:
            StuAllScoreWindow();
            break;
        case ID_BUTTON_VIEW_RANKING:
            SearchGradeWindow();
            break;
        case ID_BUTTON_CHANGE_PASSWORD:
            ChangeStuWindow();
            break;
        case ID_BUTTON_EXIT_SYSTEM:
            DestroyWindow(hwnd);
            UnregisterClass("StudentWin", GetModuleHandle(NULL));
            break;
            break;
        }
        break;

    case WM_CLOSE: //关闭确认
        if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
        {
            DestroyWindow(hwnd);
            UnregisterClass("StudentWin", GetModuleHandle(NULL));
        }
        else   
            return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

//教师登录后界面
LRESULT CALLBACK TeaWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case ID_BUTTON_TEA_VIEW_BASIC_INFO:
                TeaShowStuWindow();
                break;
            case ID_BUTTON_TEA_VIEW_ALL_COURSES:
                StuClassWindow();
                break;
            case ID_BUTTON_TEA_QUERY_DETAILED_SCORE:
                AdmStuWindow();
                break;
            case ID_BUTTON_TEA_VIEW_RANKING:
                SearchGradeWindow();
                break;
            case ID_BUTTON_TEA_ANALISE_COURSE:
                ClassAnalyWindow();
                break;
            case ID_BUTTON_TEA_INPUT_SCORE:
                AdmEntStuorScoWindow();
                break;
            case ID_BUTTON_TEA_CHANGE_SCORE:
                TeaChangeScoreWindow();
                break;
            case ID_BUTTON_TEA_INPUT_NEWCOURSE:
                TeaInCouWindow();
                break;
            case ID_BUTTON_TEA_DELETE_STUDENT:
                TeaOutStuWindow();
                break;
            case ID_BUTTON_TEA_INPUT_HONOR:
                TeaEnthorWindow();
                break;
            case ID_BUTTON_TEA_INPUT_PUNISH:
                TeaEntpunWindow();
                break;
            case ID_BUTTON_TEA_CHANGE_PASSWORD:
                ChangeTeaWindow();
                break;
            case ID_BUTTON_TEA_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("TeacherWin", GetModuleHandle(NULL));
                break;
                break;
        }
        break;

        case WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("TeacherWin", GetModuleHandle(NULL));
            }
            else   
                return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

//管理员登录后界面
LRESULT CALLBACK AdminWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case ID_BUTTON_ROOT_VIEW_STUDENT_INFO:
                ShowStutoAdmWindow(); 
                break;
            case ID_BUTTON_ROOT_VIEW_TEACHER_INFO:
                ShowTeatoAdmWindow();
                break;
            case ID_BUTTON_ROOT_VIEW_COURSES_INFO:
                ShowCostoAdmWindow();
                break;
            case ID_BUTTON_ROOT_VIEW_DETAILED_SCORE:
                AdmStuWindow();
                break;
            case ID_BUTTON_ROOT_VIEW_RANKING:
                SearchGradeWindow();
                break;
            case ID_BUTTON_ROOT_CHANGE_SCORE:
                AdmChangeScoreWindow();
                break;
            case ID_BUTTON_ROOT_INPUT_NEWCOURSE:
                AdmInCouWindow();
                break;
            case ID_BUTTON_ROOT_INPUT_NEWTEACHER:
                AdmInTeaWindow();
                break;
            case ID_BUTTON_ROOT_INPUT_NEWSTUDENT:
                AdmInStuWindow();
                break;
            case ID_BUTTON_ROOT_DELETE_STUDENT:
                AdmOutStuWindow();
                break;
            case ID_BUTTON_ROOT_INPUT_HONOR:
                AdmEnthorWindow();
                break;
            case ID_BUTTON_ROOT_INPUT_PUNISH:
                AdmEntpunWindow();
                break;
            case ID_BUTTON_ROOT_ANALISE_COURSE:
                ClassAnalyWindow();
                break;
            case ID_BUTTON_ROOT_INPUT_SCORE:
                AdmEntStuorScoWindow();
                break;
            case ID_BUTTON_ROOT_EXAMINE_APPLY:
                AmdAppWindow();
                break;
            case ID_BUTTON_ROOT_CHANGE_PASSWORD:
                ChangeAdmWindow();
                break;  
            case ID_BUTTON_ROOT_EXIT_SYSTEM:
                DestroyWindow(hwnd);
                UnregisterClass("AdminWin", GetModuleHandle(NULL));
                break;
                break;
        }
        break;

        case WM_CLOSE: 
            if(MessageBox(NULL,TEXT("是否退出"),TEXT("提示"),MB_YESNO)==IDYES)
            {
                DestroyWindow(hwnd);
                UnregisterClass("AdminWin", GetModuleHandle(NULL));
            }
            else   
                return 0;
	
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }	

    return 0;
}

void StudentWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = StuWndProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"StudentWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("学生窗口注册失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("StudentWin"), TEXT("修改学生"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
    600, 200, 500, 480, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("修改学生窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("查看自己的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 50, 200, 30, hwndChange, (HMENU)ID_BUTTON_VIEW_BASIC_INFO, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查看当前所有课程的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 100, 200, 30, hwndChange, (HMENU)ID_BUTTON_VIEW_ALL_COURSES, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查询自己的分科成绩"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 150, 200, 30, hwndChange, (HMENU)ID_BUTTON_QUERY_SUBJECT_SCORE, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查询自己的总体成绩"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 200, 200, 30, hwndChange, (HMENU)ID_BUTTON_QUERY_TOTAL_SCORE, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查看本专业成绩排榜"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 250, 200, 30, hwndChange, (HMENU)ID_BUTTON_VIEW_RANKING, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("修改密码"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 300, 200, 30, hwndChange, (HMENU)ID_BUTTON_CHANGE_PASSWORD, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
    130, 350, 200, 30, hwndChange, (HMENU)ID_BUTTON_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void AdminWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = AdminWndProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"AdminWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("管理员窗口注册失败"),TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("AdminWin"), TEXT("管理员"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
	500, 200, 650, 550, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("管理员窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("查看当前所有学生的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 50, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_VIEW_STUDENT_INFO, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查看当前所有老师的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 100, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_VIEW_TEACHER_INFO, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("查看当前所有课程的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 150, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_VIEW_COURSES_INFO, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查看学生详细信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 200, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_VIEW_DETAILED_SCORE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("查看成绩排名"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 250, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_VIEW_RANKING, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("修改学生成绩"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 300, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_CHANGE_SCORE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("录入新课程"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 350, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_INPUT_NEWCOURSE, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("导入新老师信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 400, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_INPUT_NEWTEACHER, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("转入学生"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 50, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_INPUT_NEWSTUDENT, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("转出学生"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 100, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_DELETE_STUDENT, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("录入学生综合素质加分项"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 150, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_INPUT_HONOR, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("录入学生处分情况"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 200, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_INPUT_PUNISH, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("查看课程成绩分析"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 250, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_ANALISE_COURSE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("批量录入成绩"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 300, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_INPUT_SCORE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("审批申请"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 350, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXAMINE_APPLY, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("修改密码"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 400, 250, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_CHANGE_PASSWORD, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	100, 450, 400, 30, hwndChange, (HMENU)ID_BUTTON_ROOT_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void TeacherWindow()
{
    WNDCLASSW wndclass = { 0 };
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = TeaWndProc;
    wndclass.hInstance = GetModuleHandle(NULL);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = L"TeacherWin";
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    if (!RegisterClassW(&wndclass))
    {
        MessageBox(NULL, TEXT("老师窗口注册失败"),TEXT("错误"), MB_ICONERROR);
        return;
    }

    HWND hwndChange = CreateWindow(TEXT("TeacherWin"), TEXT("教师"), WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, 
	500, 200, 650, 700, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwndChange == NULL)
    {
        MessageBox(NULL, TEXT("教师窗口创建失败"), TEXT("错误"), MB_ICONERROR);
        return;
    }

    CreateWindow(TEXT("BUTTON"), TEXT("查看当前所有学生的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 150, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_VIEW_BASIC_INFO, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查看当前所有课程的基本信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 200, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_VIEW_ALL_COURSES, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("查看学生详细信息"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 250, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_QUERY_DETAILED_SCORE, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("查看成绩排名"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 300, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_VIEW_RANKING, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("查看课程成绩分析"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 350, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_ANALISE_COURSE, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("批量录入成绩"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	50, 400, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_INPUT_SCORE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("申请修改学生成绩"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 150, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_CHANGE_SCORE, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("申请录入新课程"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 200, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_INPUT_NEWCOURSE, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("申请转出学生"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 250, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_DELETE_STUDENT, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("申请录入学生综合素质加分项"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 300, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_INPUT_HONOR, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("申请录入学生处分情况"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 350, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_INPUT_PUNISH, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("修改密码"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	320, 400, 250, 30, hwndChange, (HMENU)ID_BUTTON_TEA_CHANGE_PASSWORD, NULL, NULL);
	CreateWindow(TEXT("BUTTON"), TEXT("退出系统"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
	100, 450, 350, 30, hwndChange, (HMENU)ID_BUTTON_TEA_EXIT_SYSTEM, NULL, NULL);

    ShowWindow(hwndChange, SW_SHOWNORMAL);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#endif
