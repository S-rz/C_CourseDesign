#include "vegetable.h"

unsigned long ul;

/*主函数*/
int main()
{
    COORD size = {SCR_COL, SCR_ROW}; /*窗口缓冲区大小*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* 获取标准输出设备句柄*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* 获取标准输入设备句柄*/

    SetConsoleTitle(gp_sys_name);                 /*设置窗口标题*/
    SetConsoleScreenBufferSize(gh_std_out, size); /*设置窗口缓冲区大小80*25*/

    LoadData();             /*数据加载*/
    Welcome();              /*欢迎界面*/
    InitInterface();        /*界面初始化*/
    RunSys(&gp_head);       /*系统功能模块的选择及运行*/
    CloseSys(gp_head);      /*退出系统*/

    return 0;
}

/**
* 函数名称: Welcome
* 函数功能: 清理屏幕，并欢迎用户登入界面
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*/
void Welcome()
{
    ClearScreen();
    printf("\n\n\n\n\n\n\n\n\n\n\t欢");
    Sleep(250);
    printf("  迎"); Sleep(250);
    printf("  进"); Sleep(250);
    printf("  入"); Sleep(250);
    printf("  菜"); Sleep(250);
    printf("  农"); Sleep(250);
    printf("  种"); Sleep(250);
    printf("  植"); Sleep(250);
    printf("  信"); Sleep(250);
    printf("  息"); Sleep(250);
    printf("  管"); Sleep(250);
    printf("  理"); Sleep(250);
    printf("  系"); Sleep(250);
    printf("  统"); Sleep(250);
    printf("  ."); Sleep(250);
    printf("  ."); Sleep(250);
    printf("  ."); Sleep(250);
    Sleep(1000);
    system("cls");
}


/**
 * 函数名称: LoadData
 * 函数功能: 将代码表和三类基础数据从数据文件载入到内存缓冲区和十字链表中.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: BOOL类型, 功能函数中除了函数ExitSys的返回值可以为FALSE外,
 *           其他函数的返回值必须为TRUE.
 *
 * 调用说明: 为了能够以统一的方式调用各功能函数, 将这些功能函数的原型设为
 *           一致, 即无参数且返回值为BOOL. 返回值为FALSE时, 结束程序运行.
 */
BOOL LoadData()
{
    int Re = 0;
    Re = CreatList(&gp_head);
    gc_sys_state |= Re;
    gc_sys_state &= ~(4 + 8 + 16 - Re);
    if (gc_sys_state < ( 4 | 8 | 16))
    {  /*数据加载提示信息*/
        printf("\n系统基础数据不完整!\n");
        printf("\n按任意键继续...\n");
        getchar();
    }

    printf("\n按任意键继续...\n");
    getchar();

    return TRUE;
}

/**
 * 函数名称: LoadCode
 * 函数功能: 将代码表从数据文件载入到内存缓冲区, 并进行排序和去除空格.
 * 输入参数: FileName 存放代码表的数据文件名.
 * 输出参数: pBuffer 指向内存缓冲区的指针变量的地址.
 * 返 回 值: 存放代码表的内存缓冲区大小(以字节为单位).
 *
 * 调用说明:
 */
int LoadCode(char *FileName, char **pBuffer)
{
    char *pTemp=NULL, *pStr1=NULL, *pStr2=NULL;
    int handle;
    int BufferLen, len, loc1, loc2, i;
    long filelen;

    if ((handle = open(FileName, O_RDONLY | O_TEXT)) == -1) /*如果以只读方式打开失败 */
    {
        handle = open(FileName, O_CREAT | O_TEXT, S_IREAD); /*以创建方式打开*/
    }
    filelen = filelength(handle);      /*数据文件的长度*/
    pTemp = (char *)calloc(filelen + 1, sizeof(char)); /*申请同样大小的动态存储区*/
    BufferLen = read(handle, pTemp, filelen); /*将数据文件的内容全部读入到内存*/
    close(handle);

    *(pTemp + BufferLen) = '\0'; /*在动态存储区尾存一个空字符，作为字符串结束标志*/
    BufferLen++;

    for (i=0; i<BufferLen; i++) /*将动态存储区中的所有换行符替换成空字符*/
    {
        if (*(pTemp + i) == '\n')
        {
            *(pTemp + i) = '\0';
        }
    }

    /*再申请一块同样大小的动态存储区，用于存放排序后的代码串*/
    *pBuffer = (char *)calloc(BufferLen, sizeof(char));
    loc2 = 0;
    pStr1 = pTemp;
    len = strlen(pStr1);

    while (BufferLen > len + 1) /*选择法排序*/
    {
        loc1 = len + 1;
        while (BufferLen > loc1) /*每趟找到序列中最小代码串，首地址存入pStr1*/
        {
            pStr2 = pTemp + loc1;
            if (strcmp(pStr1, pStr2) > 0)
            {
                pStr1 = pStr2;
            }
            loc1 += strlen(pStr2) + 1;
        }
        len = strlen(pStr1);  /*这一趟所找到的最小代码串长度*/

        /*如果不是空串，则进行复制，loc2是下一个最小代码串存放地址的偏移量*/
        if (len > 0)
        {
            strcpy(*pBuffer + loc2, pStr1);
            loc2 += len + 1;  /*已复制的代码串所占存储空间大小*/
        }

        /*将最小代码串从序列中删除掉*/
        for(i=0; i<BufferLen-(pStr1-pTemp)-(len+1); i++)
        {
            *(pStr1 + i) = *(pStr1 + i + len + 1);
        }

        BufferLen -= len + 1; /*下一趟排序所处理序列的长度*/
        pStr1 = pTemp;  /*假定序列的第一个代码串为最小代码串*/
        len = strlen(pStr1);
    } /*序列中只剩下一个代码串时，排序结束*/

    /*复制最后这个代码串*/
    len = strlen(pStr1);
    strcpy(*pBuffer + loc2, pStr1);

    /*修改动态存储区大小，使其正好放下排序后代码串*/
    loc2 += len + 1;
    *pBuffer = (char *)realloc(*pBuffer, loc2);
    free(pTemp);  /*释放最先申请的动态存储区*/

    return loc2;  /*返回存放代码串的内存缓冲区实际大小*/
}

/**
 * 函数名称: CreatList
 * 函数功能: 从数据文件读取基础数据, 并存放到所创建的十字链表中.
 * 输入参数: 无
 * 输出参数: phead 主链头指针的地址, 用来返回所创建的十字链.
 * 返 回 值: int型数值, 表示链表创建的情况.
 *           0  空链, 无数据
 *           4  已加载蔬菜种类信息数据，无蔬菜基本信息和蔬菜种植信息数据
 *           12 已加载蔬菜种类信息和蔬菜基本信息数据，无蔬菜种植信息数据
 *           28 三类基础数据都已加载
 *
 * 调用说明:
 */
int CreatList(KIND_NODE **phead)
{
    KIND_NODE *hd = NULL, *pKindNode=NULL, tmp1;
    INF_NODE *pInfNode=NULL, tmp2;
    PLANT_NODE *pPlantNode=NULL, tmp3;
    FILE *pFile=NULL;
    int find;
    int re = 0;

    if ((pFile = fopen(gp_kind_info_filename, "rb")) == NULL)
    {
        printf("蔬菜种类信息数据文件打开失败!\n");
        return re;
    }
    printf("蔬菜种类信息数据文件打开成功!\n");

    /*从数据文件中读蔬菜种类信息数据，存入以后进先出方式建立的主链中*/
    while (fread(&tmp1,sizeof(KIND_NODE),1,pFile)==1)
    {
        pKindNode=(KIND_NODE *)malloc(sizeof(KIND_NODE));
        *pKindNode=tmp1;
        pKindNode->inext=NULL;
        pKindNode->next=hd;
        hd=pKindNode;
    }
    fclose(pFile);
    if (hd==NULL)
    {
        printf("蔬菜种类信息数据文件加载失败!\n");
        return re;
    }
    printf("蔬菜种类信息数据文件加载成功!\n");
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_information_info_filename, "rb")) == NULL)
    {
        printf("蔬菜基本信息数据文件打开失败!\n");
        return re;
    }
    printf("蔬菜基本信息数据文件打开成功!\n");
    re += 8;

    /*从数据文件中读取蔬菜基本信息数据，存入主链对应结点的蔬菜基本信息支链中*/
    while (fread(&tmp2, sizeof(INF_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出的蔬菜基本信息*/
        pInfNode = (INF_NODE *)malloc(sizeof(INF_NODE));
        *pInfNode = tmp2;
        pInfNode->pnext = NULL;

        /*在主链上查找该蔬菜基本信息对应的主链结点*/
        pKindNode = hd;
        while (pKindNode != NULL
               && pKindNode->kin_num!=pInfNode->kin_num)
        {
            pKindNode = pKindNode->next;
        }
        if (pKindNode != NULL) /*如果找到，则将结点以后进先出方式插入蔬菜信息支链*/
        {
            pInfNode->next = pKindNode->inext;
            pKindNode->inext = pInfNode;
        }
        else  /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pInfNode);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_plant_info_filename, "rb")) == NULL)
    {
        printf("蔬菜种植信息数据文件打开失败!\n");
        return re;
    }
    printf("蔬菜种植信息数据文件打开成功!\n");
    re += 16;

    /*从数据文件中读取蔬菜种植信息数据，存入蔬菜基本信息支链对应结点的种植支链中*/
    while (fread(&tmp3, sizeof(PLANT_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出蔬菜种植信息*/
        pPlantNode = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        *pPlantNode = tmp3;

        /*查找蔬菜基本信息支链上对应蔬菜种植信息结点*/
        pKindNode = hd;
        find = 0;
        while (pKindNode != NULL && find == 0)
        {
            pInfNode = pKindNode->inext;
            while (pInfNode != NULL && find == 0)
            {
                if((pInfNode->veg_num==pPlantNode->veg_num) &&
                   (pKindNode->kin_num==pInfNode->kin_num))
                {
                    find = 1;
                    break;
                }
                pInfNode = pInfNode->next;
            }
            pKindNode = pKindNode->next;

        }
        if (find)  /*如果找到，则将结点以后进先出方式插入蔬菜种植信息支链中*/
        {
            pPlantNode->next = pInfNode->pnext;
            pInfNode->pnext = pPlantNode;
        }
        else /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);

    return re;
}

/**
 * 函数名称: InitInterface
 * 函数功能: 初始化界面.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void InitInterface()
{
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*黄色前景和蓝色背景*/

    SetConsoleTextAttribute(gh_std_out, att);  /*设置控制台屏幕缓冲区字符属性*/

    ClearScreen();  /* 清屏*/

    /*创建弹出窗口信息堆栈，将初始化后的屏幕窗口当作第一层弹出窗口*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*屏幕字符属性*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;      /*弹出窗口的层号为0*/
    gp_top_layer->rcArea.Left = 0;  /*弹出窗口的区域为整个屏幕窗口*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();     /*显示菜单栏*/
    ShowState();    /*显示状态栏*/

    return;
}

/**
 * 函数名称: ClearScreen
 * 函数功能: 清除屏幕信息.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*取屏幕缓冲区信息*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*计算屏幕缓冲区字符单元数*/

    /*将屏幕缓冲区所有单元的字符属性设置为当前屏幕缓冲区字符属性*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*将屏幕缓冲区所有单元填充为空格字符*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);

    return;
}

/**
 * 函数名称: ShowModule
 * 函数功能: 弹出窗口.
 * 输入参数:
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL ShowModule(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 1;
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};
    char aTag[] = {1};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}

/**
 * 函数名称: ShowMenu
 * 函数功能: 在屏幕上显示主菜单, 并设置热区, 在主菜单第一项上置选中标记.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur;
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++) /*在窗口第一行第一列处输出主菜单项*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*隐藏光标*/

    /*申请动态存储区作为存放菜单条屏幕区字符信息的缓冲区*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*将窗口第一行的内容读入到存放菜单条屏幕区字符信息的缓冲区中*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*将这一行中英文字母置为红色，其他字符单元置为白底黑字*/
    for (i=0; i<size.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*修改后的菜单条字符信息回写到窗口的第一行*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*将光标位置设置在第2行第1列*/

    /*将菜单项置为热区，热区编号为菜单项号，热区类型为0(按钮型)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*定位第i+1号菜单项的起止位置*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; /*设置菜单项所在字符单元的属性值*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*在选中主菜单项上做标记，gi_sel_menu初值为1*/

    return;
}

/**
 * 函数名称: ShowState
 * 函数功能: 显示状态条.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明: 状态条字符属性为白底黑字, 初始状态无状态信息.
 */
void ShowState()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int i;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SMALL_RECT rcMenu ={0, bInfo.dwSize.Y-1, size.X-1, bInfo.dwSize.Y-1};

    if (gp_buff_stateBar_info == NULL)
    {
        gp_buff_stateBar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
        ReadConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);
    }

    for (i=0; i<size.X; i++)
    {
        (gp_buff_stateBar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                                | BACKGROUND_RED;
    }

    WriteConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);

    return;
}

/**
 * 函数名称: TagMainMenu
 * 函数功能: 在指定主菜单项上置选中标志.
 * 输入参数: num 选中的主菜单项号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*num为0时，将会去除主菜单项选中标记*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*否则，定位选中主菜单项的起止位置: PosA为起始位置, PosB为截止位置*/
    {
        for (i=1; i<num; i++)
        {
            PosA += strlen(ga_main_menu[i-1]) + 4;
        }
        PosB = PosA + strlen(ga_main_menu[num-1]);
    }

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;

    /*去除选中菜单项前面的菜单项选中标记*/
    for (i=0; i<PosA; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (gp_buff_menubar_info+i)->Char.AsciiChar;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*在选中菜单项上做标记，黑底白字*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*去除选中菜单项后面的菜单项选中标记*/
    for (i=PosB; i<bInfo.dwSize.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*将做好标记的菜单条信息写到窗口第一行*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}

/**
 * 函数名称: CloseSys
 * 函数功能: 关闭系统.
 * 输入参数: hd 主链头指针
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void CloseSys(KIND_NODE *hd)
{
    KIND_NODE *pKindNode1 = hd, *pKindNode2=NULL;
    INF_NODE *pInfNode1=NULL, *pInfNode2=NULL;
    PLANT_NODE *pPlantNode1=NULL, *pPlantNode2=NULL;

    while (pKindNode1 != NULL) /*释放十字交叉链表的动态存储区*/
    {
        pKindNode2 = pKindNode1->next;
        pInfNode1 = pKindNode1->inext;
        while (pInfNode1 != NULL) /*释放蔬菜基本信息支链的动态存储区*/
        {
            pInfNode2 = pInfNode1->next;
            pPlantNode1 = pInfNode1->pnext;
            while (pPlantNode1 != NULL) /*释放种植信息支链的动态存储区*/
            {
                pPlantNode2 = pPlantNode1->next;
                free(pPlantNode1);
                pPlantNode1 = pPlantNode2;
            }
            free(pInfNode1);
            pInfNode1 = pInfNode2;
        }
        free(pKindNode1);  /*释放主链结点的动态存储区*/
        pKindNode1 = pKindNode2;
    }

    ClearScreen();        /*清屏*/

    /*释放存放菜单条、状态条等信息动态存储区*/
    free(gp_buff_menubar_info);
    free(gp_buff_stateBar_info);

    /*关闭标准输入和输出设备句柄*/
    CloseHandle(gh_std_out);
    CloseHandle(gh_std_in);

    /*将窗口标题栏置为运行结束*/
    SetConsoleTitle("运行结束");

    return;
}

/**
 * 函数名称: RunSys
 * 函数功能: 运行系统, 在系统主界面下运行用户所选择的功能模块.
 * 输入参数: 无
 * 输出参数: phead 主链头指针的地址
 * 返 回 值: 无
 *
 * 调用说明:
 */
void RunSys(KIND_NODE **phead)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:字符单元层号, cAtt:字符单元属性*/
    char vkc, asc;      /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    while (bRet)
    {
        /*从控制台输入缓冲区中读一条记录*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT) /*如果记录由鼠标事件产生*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*获取鼠标坐标位置*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*取该位置的层号*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*取该字符单元属性*/
            if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
            {
                /* cAtt > 0 表明该位置处于热区(主菜单项字符单元)
                 * cAtt != gi_sel_menu 表明该位置的主菜单项未被选中
                 * gp_top_layer->LayerNo > 0 表明当前有子菜单弹出
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();            /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                    PopMenu(cAtt);       /*弹出鼠标所在主菜单项对应的子菜单*/
                }
            }
            else if (cAtt > 0) /*鼠标所在位置为弹出子菜单的菜单项字符单元*/
            {
                TagSubMenu(cAtt); /*在该子菜单项上做选中标记*/
            }

            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*如果按下鼠标左边第一键*/
            {
                if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
                {
                    if (cAtt > 0) /*如果该位置处于热区(主菜单项字符单元)*/
                    {
                        PopMenu(cAtt);   /*弹出鼠标所在主菜单项对应的子菜单*/
                    }
                    /*如果该位置不属于主菜单项字符单元，且有子菜单弹出*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*关闭弹出的子菜单*/
                        gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                    }
                }
                else /*层号不为0，表明该位置被弹出子菜单覆盖*/
                {
                    if (cAtt > 0) /*如果该位置处于热区(子菜单项字符单元)*/
                    {
                        PopOff(); /*关闭弹出的子菜单*/
                        gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/

                        /*执行对应功能函数:gi_sel_menu主菜单项号,cAtt子菜单项号*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*如果按下鼠标右键*/
            {
                if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
                {
                    PopOff();            /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*如果记录由按键产生*/
                 && inRec.Event.KeyEvent.bKeyDown) /*且键被按下*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*获取按键的虚拟键码*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*获取按键的ASC码*/

            /*系统快捷键的处理*/
            if (vkc == 112) /*如果按下F1键*/
            {
                if (gp_top_layer->LayerNo != 0) /*如果当前有子菜单弹出*/
                {
                    PopOff();            /*关闭弹出的子菜单*/
                    gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
                }
                bRet = ExeFunction(5, 1);  /*运行帮助主题功能函数*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            { /*如果按下左或右Alt键*/
                switch (vkc)  /*判断组合键Alt+字母*/
                {
                    case 88:  /*Alt+X 退出*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,4);
                        break;
                    case 70:  /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77: /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81: /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83: /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72: /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }
            else if (asc == 0) /*其他控制键的处理*/
            {
                if (gp_top_layer->LayerNo == 0) /*如果未弹出子菜单*/
                {
                    switch (vkc) /*处理方向键(左、右、下)，不响应其他控制键*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40:
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else  /*已弹出子菜单时*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
                    switch (vkc) /*方向键(左、右、上、下)的处理*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu < 1)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 38:
                            num = gi_sel_sub_menu - 1;
                            if (num < 1)
                            {
                                num = ga_sub_menu_count[gi_sel_menu-1];
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num--;
                            }
                            TagSubMenu(num);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu > 5)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 40:
                            num = gi_sel_sub_menu + 1;
                            if (num > ga_sub_menu_count[gi_sel_menu-1])
                            {
                                num = 1;
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num++;
                            }
                            TagSubMenu(num);
                            break;
                    }
                }
            }
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*按下普通键*/
                if (gp_top_layer->LayerNo == 0)  /*如果未弹出子菜单*/
                {
                    switch (vkc)
                    {
                        case 70: /*f或F*/
                            PopMenu(1);
                            break;
                        case 77: /*m或M*/
                            PopMenu(2);
                            break;
                        case 81: /*q或Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s或S*/
                            PopMenu(4);
                            break;
                        case 72: /*h或H*/
                            PopMenu(5);
                            break;
                        case 13: /*回车*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*已弹出子菜单时的键盘输入处理*/
                {
                    if (vkc == 27) /*如果按下ESC键*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*如果按下回车键*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*其他普通键的处理*/
                    {
                        /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*依次与当前子菜单中每一项的代表字符进行比较*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*如果匹配成功*/
                                PopOff();
                                gi_sel_sub_menu = 0;
                                bRet = ExeFunction(gi_sel_menu, i-loc+1);
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * 函数名称: PopMenu
 * 函数功能: 弹出指定主菜单项对应的子菜单.
 * 输入参数: num 指定的主菜单项号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PopMenu(int num)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh=NULL;
    int i, j, loc = 0;

    if (num != gi_sel_menu)       /*如果指定主菜单不是已选中菜单*/
    {
        if (gp_top_layer->LayerNo != 0) /*如果此前已有子菜单弹出*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*若已弹出该子菜单，则返回*/
    {
        return;
    }

    gi_sel_menu = num;    /*将选中主菜单项置为指定的主菜单项*/
    TagMainMenu(gi_sel_menu); /*在选中的主菜单项上做标记*/
    LocSubMenu(gi_sel_menu, &rcPop); /*计算弹出子菜单的区域位置, 存放在rcPop中*/

    /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*将该组子菜单项项名存入标签束结构变量*/
    labels.ppLabel = ga_sub_menu + loc;   /*标签束第一个标签字符串的地址*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1]; /*标签束中标签字符串的个数*/
    COORD aLoc[labels.num];/*定义一个坐标数组，存放每个标签字符串输出位置的坐标*/
    for (i=0; i<labels.num; i++) /*确定标签字符串的输出位置，存放在坐标数组中*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*使标签束结构变量labels的成员pLoc指向坐标数组的首元素*/
    /*设置热区信息*/
    areas.num = labels.num;       /*热区的个数，等于标签的个数，即子菜单的项数*/
    SMALL_RECT aArea[areas.num];                    /*定义数组存放所有热区位置*/
    char aSort[areas.num];                      /*定义数组存放所有热区对应类别*/
    char aTag[areas.num];                         /*定义数组存放每个热区的编号*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*热区定位*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*热区类别都为0(按钮型)*/
        aTag[i] = i + 1;           /*热区按顺序编号*/
    }
    areas.pArea = aArea;/*使热区结构变量areas的成员pArea指向热区位置数组首元素*/
    areas.pSort = aSort;/*使热区结构变量areas的成员pSort指向热区类别数组首元素*/
    areas.pTag = aTag;   /*使热区结构变量areas的成员pTag指向热区编号数组首元素*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*给弹出窗口画边框*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    { /*此循环用来在空串子菜项位置画线形成分隔，并取消此菜单项的热区属性*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0) /*串长为0，表明为空串*/
        {   /*首先画横线*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {   /*取消该区域字符单元的热区属性*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*按位与的结果保留了低两位*/
            }
        }

    }
    /*将子菜单项的功能键设为白底红字*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;  /*跳过空串*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * 函数名称: PopUp
 * 函数功能: 在指定区域输出弹出窗口信息, 同时设置热区, 将弹出窗口位置信息入栈.
 * 输入参数: pRc 弹出窗口位置数据存放的地址
 *           att 弹出窗口区域字符属性
 *           pLabel 弹出窗口中标签束信息存放的地址
             pHotArea 弹出窗口中热区信息存放的地址
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer=NULL;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*弹出窗口所在位置字符单元信息入栈*/
    size.X = pRc->Right - pRc->Left + 1;    /*弹出窗口的宽度*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*弹出窗口的高度*/
    /*申请存放弹出窗口相关信息的动态存储区*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*将弹出窗口覆盖区域的字符信息保存，用于在关闭弹出窗口时恢复原样*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*此二重循环将所覆盖字符单元的原先属性值存入动态存储区，便于以后恢复*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*完成弹出窗口相关信息入栈操作*/
    /*设置弹出窗口区域字符的新属性*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*将标签束中的标签字符串在设定的位置输出*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*设置弹出窗口区域字符单元的新属性*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*此二重循环设置字符单元的层号*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*此二重循环设置所有热区中字符单元的热区类型和热区编号*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/**
 * 函数名称: PopOff
 * 函数功能: 关闭顶层弹出窗口, 恢复覆盖区域原外观和字符单元原属性.
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer=NULL;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*栈底存放的主界面屏幕信息，不用关闭*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*恢复弹出窗口区域原外观*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*恢复字符单元原属性*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*释放动态存储区*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * 函数名称: DrawBox
 * 函数功能: 在指定区域画边框.
 * 输入参数: pRc 存放区域位置信息的地址
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*画框用的字符*/
    COORD pos = {pRc->Left, pRc->Top};  /*定位在区域的左上角*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框左上角*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*此循环画上边框横线*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框右上角*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*此循环画边框左边线和右边线*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框左下角*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*画下边框横线*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*画边框右下角*/
    return;
}

/**
 * 函数名称: TagSubMenu
 * 函数功能: 在指定子菜单项上做选中标记.
 * 输入参数: num 选中的子菜单项号
 * 输出参数: 无
 * 返 回 值: 无
 *
 * 调用说明:
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*计算弹出子菜单的区域位置, 存放在rcPop中*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*如果子菜单项号越界，或该项子菜单已被选中，则返回*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*首先取消原选中子菜单项上的标记*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*白底红字*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*在制定子菜单项上做选中标记*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*修改选中子菜单项号*/
    return;
}

/**
 * 函数名称: LocSubMenu
 * 函数功能: 计算弹出子菜单区域左上角和右下角的位置.
 * 输入参数: num 选中的主菜单项号
 * 输出参数: rc 存放区域位置信息的地址
 * 返 回 值: 无
 *
 * 调用说明:
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*区域的上边定在第2行，行号为1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*计算区域左边界位置, 同时计算第一个子菜单项在子菜单字符串数组中的位置*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*暂时存放第一个子菜单项字符串长度*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*查找最长子菜单字符串，将其长度存放在rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*计算区域的右边界*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*计算区域下边的行号*/
    if (rc->Right >= SCR_COL)  /*右边界越界的处理*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * 函数名称: DealInput
 * 函数功能: 在弹出窗口区域设置热区, 等待并相应用户输入.
 * 输入参数: pHotArea
 *           piHot 焦点热区编号的存放地址, 即指向焦点热区编号的指针
 * 输出参数: piHot 用鼠标单击、按回车或空格时返回当前热区编号
 * 返 回 值:
 *
 * 调用说明:
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
    char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*循环*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*方向键(左、上、右、下)的处理*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC键*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*回车键或空格表示按下当前按钮*/
                iRet = 13;
                break;
            }
        }
    }
    return iRet;
}

/**
 * 函数名称: SetHotPoint
 * 函数功能: 把ihot对应的热区选中。.
 * 输入参数: HOT_AREA *pHotArea, int iHot
 * 返 回 值:无
 *
 * 调用说明:
 */
void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    for (i=0; i<pHotArea->num; i++)
    {  /*将按钮类热区置为白底黑字*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*热区是按钮类*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*被激活热区是按钮类*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*被激活热区是文本框类*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/**
 * 函数名称: ExeFunction
 * 函数功能: 执行由主菜单号和子菜单号确定的功能函数.
 * 输入参数: m 主菜单项号
 *           s 子菜单项号
 * 输出参数: 无
 * 返 回 值: BOOL类型, TRUE 或 FALSE
 *
 * 调用说明: 仅在执行函数ExitSys时, 才可能返回FALSE, 其他情况下总是返回TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*函数指针数组，用来存放所有功能函数的入口地址*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*将功能函数入口地址存入与功能函数所在主菜单号和子菜单号对应下标的数组元素*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = ExitSys;

    pFunction[4] = MaintainKindInfo;
    pFunction[5] = NULL;
    pFunction[6] = MaintainInfInfo;
    pFunction[7] = NULL;
    pFunction[8] = MaintainPlantInfo;

    pFunction[9] = QueryKindInfo;
    pFunction[10] = NULL;
    pFunction[11] = QueryInfInfo;
    pFunction[12] = NULL;
    pFunction[13] = QueryPlantInfo;

    pFunction[14] = StatYearKind;
    pFunction[15] = StatVegYear;
    pFunction[16] = StatKind;
    pFunction[17] = StatVegNut;
    pFunction[18] = StatVegInf;

    pFunction[19] = HelpTopic;
    pFunction[20] = NULL;
    pFunction[21] = AboutVegetableSys;
    pFunction[22] = NULL;
    pFunction[23] = AboutCopyright;

    for (i=1,loc=0; i<m; i++)  /*根据主菜单号和子菜单号计算对应下标*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*用函数指针调用所指向的功能函数*/
    }

    return bRet;
}

/**文件模块**/

/**
 * 函数名称: SaveData
 * 函数功能: 数据保存
 * 输入参数: 无
 * 返 回 值: BOOL类型, TRUE
 *
 * 调用说明:
 */
BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：文件",
                           "子菜单项：数据保存",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    SaveSysData(gp_head);

    char *pString[] = { "保存成功",
    "确认"
    };
    ShowModule(pString, 2);

    return bRet;
}

/**
 * 函数名称: BackupData
 * 函数功能: 数据备份
 * 输入参数: 无
 * 返 回 值: BOOL类型, TRUE
 *
 * 调用说明:
 */
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：文件",
                           "子菜单项：数据备份",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    BackupSysData(gp_head);
    char *pString[] = { "备份成功",
    "确认"
    };
    ShowModule(pString, 2);

    return bRet;
}

/**
 * 函数名称: RestoreData
 * 函数功能: 数据恢复
 * 输入参数: 无
 * 返 回 值: BOOL类型, TRUE
 *
 * 调用说明:
 */
BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：文件",
                           "子菜单项：数据恢复",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    RestoreSysData(&gp_head);
    char *pString[] = { "恢复成功",
    "确认"
    };
    ShowModule(pString, 2);

    return bRet;
}

/**
* 函数名称 : ExitSys
* 函数功能 : 退出系统
* 返 回 值 : BOOL类型, TRUE
*/
BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"确认退出系统吗？", "确定    取消"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}

/**数据维护模块**/

/**
* 函数名称 : MaintainKindInfo
* 函数功能 : 添加、修改或者删除蔬菜种类信息
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL MaintainKindInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：维护蔬菜种类信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    int n;
	printf("请选择:\n");
	printf("  1-插入\n");
	printf("  2-修改\n");
	printf("  3-删除\n");
	scanf("%d", &n);
	getchar();
	switch (n)
	{
	case 1:
		Insert(1);
		break;
	case 2:
		Modify_info(1);
		break;
	case 3:
		Dele_info(1);
		break;
	default:
		printf("输入有误！\n按任意键继返回。。。");
		getchar();
	}
	ClearScreen();
	ShowMenu();

    return bRet;
}

/**
* 函数名称 : MaintainInfInfo
* 函数功能 : 添加、修改或者删除蔬菜基本信息
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL MaintainInfInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：维护蔬菜基本信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    int n;
	printf("请选择:\n");
	printf("  1-插入\n");
	printf("  2-修改\n");
	printf("  3-删除\n");
	scanf("%d", &n);
	getchar();
	switch (n)
	{
	case 1:
		Insert(2);
		break;
	case 2:
		Modify_info(2);
		break;
	case 3:
		Dele_info(2);
		break;
	default:
		printf("输入有误！\n按任意键继返回。。。");
		getchar();
	}

	ClearScreen();
	ShowMenu();

    return bRet;
}

/**
* 函数名称 : MaintainPlantInfo
* 函数功能 : 添加、修改或者删除蔬菜种植信息
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL MaintainPlantInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据维护",
                           "子菜单项：维护蔬菜种植信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    int n;
	printf("请选择:\n");
	printf("  1-插入\n");
	printf("  2-修改\n");
	printf("  3-删除\n");
	scanf("%d", &n);
	getchar();
	switch (n)
	{
	case 1:
		Insert(3);
		break;
	case 2:
		Modify_info(3);
		break;
	case 3:
		Dele_info(3);
		break;
	default:
		printf("输入有误！\n按任意键继返回。。。");
		getchar();
	}

	ClearScreen();
	ShowMenu();

    return bRet;
}

/**数据查询模块**/

/**
* 函数名称 : QueryKindInfo
* 函数功能 : 查询蔬菜种类信息
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL QueryKindInfo(void)
{
    KIND_NODE *pc=NULL;
    char c;
    int i,flag=0;
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：数据查询",
                           "子菜单项：蔬菜种类信息",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    printf("请输入要查询的蔬菜种类所对应的分类编码：");
    scanf("%c",&c);
    getchar();
    for(pc=gp_head;pc!=NULL;pc=pc->next)
    {
        if(c==pc->kin_num)
        {
            flag=1;
            printf("\n蔬菜分类编码：%c\n\n",pc->kin_num);
            printf("蔬菜分类名称：%s\n\n",pc->kin_name);
        }
    }
    if(flag==0)
    {
       printf("未找到对应结果，按任意键返回\n");
    }

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"蔬菜种类信息查询完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* 函数名称 : QueryInfInfo
* 函数功能 : 查询蔬菜基本信息
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL QueryInfInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：蔬菜基本信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    int n;

    loop:
        printf("请选择查询方式：\n");
        printf("  1.蔬菜名称中文字符子串为条件查找\n");
        printf("  2.以分类码和营养成分为条件查找\n");
        scanf("%d",&n);
        getchar();
        if(n==1)
        {
            SeekIVegName();
        }
        else if(n==2)
        {
            SeekIKindNut();
        }

        else
        {
            printf("输入错误\n\n");
            goto loop;
        }

	getchar();
	ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"蔬菜基本信息查询完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* 函数名称 : QueryPlantInfo
* 函数功能 : 查询蔬菜种植信息
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL QueryPlantInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"主菜单项：数据查询",
                           "子菜单项：蔬菜种植信息",
                           "确认"
                          };

    ShowModule(plabel_name, 3);

    int n;

    loop:
        printf("请选择查询方式：\n");
        printf("  1.蔬菜名称中文字符子串以及种植年份为条件查找\n");
        printf("  2.以蔬菜名称为条件查找\n");
        scanf("%d",&n);
        getchar();
        if(n==1)
        {
            SeekPNameYear();
        }
        else if(n==2)
        {
            SeekPVegName();
        }

        else
        {
            printf("输入错误\n\n");
            goto loop;
        }

	getchar();
	ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"蔬菜种植信息查询完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**数据统计模块**/

/**
* 函数名称 : StatYearKind
* 函数功能 : 分别统计某年各类蔬菜种植总面积、收获总重量
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL StatYearKind(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：数据统计",
                           "子菜单项：某年各类蔬菜统计",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Year_Kind();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"统计完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* 函数名称 : StatVegYear
* 函数功能 : 以所输入的起止年份为条件，按蔬菜名称统计该三年内所种各种蔬菜总面积、收获总重量
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL StatVegYear(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：数据统计",
                           "子菜单项：起止年蔬菜统计",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Veg_Year();

    getchar();
	ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"统计完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* 函数名称 : StatKind
* 函数功能 : 分别统计某种类蔬菜的已有的数量
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL StatKind(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：数据统计",
                           "子菜单项：某种蔬菜数量统计",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Kind();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"统计完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* 函数名称 : StatVegNut
* 函数功能 : 给定某个营养成分，显示输出所有含有该营养成分的蔬菜名称
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL StatVegNut(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：数据统计",
                           "子菜单项：营养成分蔬菜统计",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Nut();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"统计完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* 函数名称 : StatVegInf
* 函数功能 : 给定某个蔬菜名称，显示输出该蔬菜种植信息数量
* 返 回 值 : BOOL类型, TRUE
*
* 调用说明:
*/
BOOL StatVegInf(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：数据统计",
                           "子菜单项：蔬菜基本信息统计",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Veg_Inf();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"统计完成",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**帮助信息模块**/

/**
* 函数名称 : HelpTopic
* 函数功能 : 显示帮助信息
* 返回值 : BOOL类型, TRUE
**/
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：帮助",
                           "子菜单项：帮助主题",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

	char *plabel_name2[] = {"    本系统支持中文输入",
	                        "   ",
                            "按ALT+字母可以快捷选择主菜单",
                            "确认"
                          };

    ShowModule(plabel_name2, 4);

	getchar();
	ClearScreen();
	ShowMenu();
    return bRet;
}

/**
* 函数名称 : AboutCitySys
* 函数功能 : 显示菜农种植系统信息
* 返回值 : BOOL类型, TRUE
**/
BOOL AboutVegetableSys(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：帮助",
                            "子菜单项：关于...",
                            "确认"
                          };

    ShowModule(plabel_name1, 3);


    char *plabel_name2[] = {"欢迎使用菜农种植信息管理系统！！",
                           "确认"
                          };

    ShowModule(plabel_name2, 2);

	getchar();
	ClearScreen();
	ShowMenu();

    return bRet;
}

/**
* 函数名称 : AboutCopyright
* 函数功能 : 显示作者及相关信息
* 返回值 : BOOL类型, TRUE
**/
BOOL AboutCopyright(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"主菜单项：帮助",
                           "子菜单项：版权说明",
                           "确认"
                          };

    ShowModule(plabel_name1, 3);

    char *plabel_name2[] = {"班级：计算机校际交流班1601",
                            "      姓名：史瑞泽",
                            "    学号：U201615677",
                            "确认"
                          };

    ShowModule(plabel_name2, 4);

	ClearScreen();
	ShowMenu();

    return bRet;
}

/**文件函数**/

/**
 * 函数名称: SaveSysData
 * 函数功能: 保存系统代码表和三类基础数据.
 * 输入参数: hd 主链头结点指针
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL SaveSysData(KIND_NODE *hd)
{
	KIND_NODE *pkind_node=NULL;
	INF_NODE *pinf_node=NULL;
	PLANT_NODE *pplant_node=NULL;
	FILE *pfout=NULL;

	pfout = fopen(gp_kind_info_filename, "wb");
	for (pkind_node = hd; pkind_node != NULL; pkind_node = pkind_node->next)
	{
		fwrite(pkind_node, sizeof(KIND_NODE), 1, pfout);
	}
	fclose(pfout);

	pfout = fopen(gp_information_info_filename, "wb");
	for (pkind_node = hd; pkind_node != NULL; pkind_node = pkind_node->next)
	{
		pinf_node = pkind_node->inext;
		while (pinf_node != NULL)
		{
			fwrite(pinf_node, sizeof(INF_NODE), 1, pfout);
			pinf_node = pinf_node->next;
		}
	}
	fclose(pfout);

	pfout = fopen(gp_plant_info_filename, "wb");
	for (pkind_node = hd; pkind_node != NULL; pkind_node = pkind_node->next)
	{
		pinf_node = pkind_node->inext;
		while (pinf_node != NULL)
		{
			pplant_node = pinf_node->pnext;
			while (pplant_node != NULL)
			{
				fwrite(pplant_node, sizeof(PLANT_NODE), 1, pfout);
				pplant_node = pplant_node->next;
			}
			pinf_node = pinf_node->next;
		}
	}
	fclose(pfout);
	return TRUE;
}

/**
 * 函数名称: BackupSysData
 * 函数功能: 将系统代码表和三类基础数据备份到一个数据文件.
 * 输入参数: hd 主链头结点指针
 *           filename 数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL BackupSysData(KIND_NODE *hd)
{
	KIND_NODE *pkind_node=NULL;
	INF_NODE *pinf_node=NULL;
	PLANT_NODE *pplant_node=NULL;
	FILE *pfout=NULL;

	pfout = fopen(gp_kind_back_filename, "wb");
	for (pkind_node = hd; pkind_node != NULL; pkind_node = pkind_node->next)
	{
		fwrite(pkind_node, sizeof(KIND_NODE), 1, pfout);
	}
	fclose(pfout);

	pfout = fopen(gp_information_back_filename, "wb");
	for (pkind_node = hd; pkind_node != NULL; pkind_node = pkind_node->next)
	{
		pinf_node = pkind_node->inext;
		while (pinf_node != NULL)
		{
			fwrite(pinf_node, sizeof(INF_NODE), 1, pfout);
			pinf_node = pinf_node->next;
		}
	}
	fclose(pfout);

	pfout = fopen(gp_plant_back_filename, "wb");
	for (pkind_node = hd; pkind_node != NULL; pkind_node = pkind_node->next)
	{
		pinf_node = pkind_node->inext;
		while (pinf_node != NULL)
		{
			pplant_node = pinf_node->pnext;
			while (pplant_node != NULL)
			{
				fwrite(pplant_node, sizeof(PLANT_NODE), 1, pfout);
				pplant_node = pplant_node->next;
			}
			pinf_node = pinf_node->next;
		}
	}
	fclose(pfout);
	return TRUE;
}

/**
 * 函数名称: RestoreSysData
 * 函数功能: 从指定数据文件中恢复系统代码表和三类基础数据.
 * 输入参数: phead 主链头结点指针的地址
 *           filename 存放备份数据的数据文件名
 * 输出参数:
 * 返 回 值: BOOL类型, 总是为TRUE
 *
 * 调用说明:
 */
BOOL RestoreSysData(KIND_NODE **phead)
{
    KIND_NODE *hd = NULL, *pKindNode=NULL, tmp1;
    INF_NODE *pInfNode=NULL, tmp2;
    PLANT_NODE *pPlantNode=NULL, tmp3;
    FILE *pFile=NULL;
    int find;

    if ((pFile = fopen(gp_kind_back_filename, "rb")) == NULL)
    {
        printf("蔬菜种类信息恢复文件打开失败!\n");
        return TRUE;
    }
    printf("蔬菜种类信息恢复文件打开成功!\n");

    /*从数据文件中读蔬菜种类信息数据，存入以后进先出方式建立的主链中*/
    while (fread(&tmp1,sizeof(KIND_NODE),1,pFile)==1)
    {
        pKindNode=(KIND_NODE *)malloc(sizeof(KIND_NODE));
        *pKindNode=tmp1;
        pKindNode->inext=NULL;
        pKindNode->next=hd;
        hd=pKindNode;
    }
    fclose(pFile);
    if (hd==NULL)
    {
        printf("蔬菜种类信息恢复文件加载失败!\n");
        return TRUE;
    }
    printf("蔬菜种类信息恢复文件加载成功!\n");
    *phead = hd;

    if ((pFile = fopen(gp_information_back_filename, "rb")) == NULL)
    {
        printf("蔬菜基本信息恢复文件打开失败!\n");
        return TRUE;
    }
    printf("蔬菜基本信息恢复文件打开成功!\n");

    /*从数据文件中读取蔬菜基本信息数据，存入主链对应结点的蔬菜基本信息支链中*/
    while (fread(&tmp2, sizeof(INF_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出的蔬菜基本信息*/
        pInfNode = (INF_NODE *)malloc(sizeof(INF_NODE));
        *pInfNode = tmp2;
        pInfNode->pnext = NULL;

        /*在主链上查找该蔬菜基本信息对应的主链结点*/
        pKindNode = hd;
        while (pKindNode != NULL
               && pKindNode->kin_num!=pInfNode->kin_num)
        {
            pKindNode = pKindNode->next;
        }
        if (pKindNode != NULL) /*如果找到，则将结点以后进先出方式插入蔬菜信息支链*/
        {
            pInfNode->next = pKindNode->inext;
            pKindNode->inext = pInfNode;
        }
        else  /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pInfNode);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_plant_back_filename, "rb")) == NULL)
    {
        printf("蔬菜种植信息恢复文件打开失败!\n");
        return TRUE;
    }
    printf("蔬菜种植信息恢复文件打开成功!\n");

    /*从数据文件中读取蔬菜种植信息数据，存入蔬菜基本信息支链对应结点的种植支链中*/
    while (fread(&tmp3, sizeof(PLANT_NODE), 1, pFile) == 1)
    {
        /*创建结点，存放从数据文件中读出蔬菜种植信息*/
        pPlantNode = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        *pPlantNode = tmp3;

        /*查找蔬菜基本信息支链上对应蔬菜种植信息结点*/
        pKindNode = hd;
        find = 0;
        while (pKindNode != NULL && find == 0)
        {
            pInfNode = pKindNode->inext;
            while (pInfNode != NULL && find == 0)
            {
                if((pInfNode->veg_num==pPlantNode->veg_num) &&
                   (pKindNode->kin_num==pInfNode->kin_num))
                {
                    find = 1;
                    break;
                }
                pInfNode = pInfNode->next;
            }
            pKindNode = pKindNode->next;

        }
        if (find)  /*如果找到，则将结点以后进先出方式插入蔬菜种植信息支链中*/
        {
            pPlantNode->next = pInfNode->pnext;
            pInfNode->pnext = pPlantNode;
        }
        else /*如果未找到，则释放所创建结点的内存空间*/
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);

    ClearScreen();
    ShowMenu();
    return TRUE;
}

/**数据维护函数**/

/**
 * 函数名称: Insert
 * 函数功能: 插入三种信息
 * 输入参数: int类型：1代表添加种类信息，2代表添加基本信息，3代表添加种植信息
 * 输出参数:
 * 返 回 值: 无
 *
 * 调用说明:
 */
void Insert(int n)
{
    KIND_NODE *p1 = gp_head, *pd=NULL;
	INF_NODE *pp=NULL, *fp=NULL;
	PLANT_NODE  *pm=NULL, *pf=NULL;
	if (n == 1)                    /*插入蔬菜种类信息*/
	{
		printf("请输入您要插入的蔬菜种类信息\n");
		pd = (KIND_NODE *)malloc(sizeof(KIND_NODE));
		pd->inext = NULL;

		printf("分类编码：");
		scanf("%c",&pd->kin_num);
		getchar();
		printf("分类名称：");
		scanf("%s",pd->kin_name);
		getchar();

		pd->next = p1;
		gp_head = pd;

		ClearScreen();
		ShowMenu();

		char *plabel_name[] = { "数据插入成功！",    /*提示成功信息*/
			"确认"
		};

		ShowModule(plabel_name, 2);
	}
	if (n == 2)
	{
	    char s;
		printf("请输入蔬菜基本信息\n\n");
		printf("请先输入蔬菜分类编码：");
		scanf("%c",&s);
		getchar();
		while (p1 != NULL)
		{
			if (s==p1->kin_num)
				break;
			p1 = p1->next;
		}
		if (p1 != NULL)
		{
			pp = (INF_NODE *)malloc(sizeof(INF_NODE));
			pp->pnext = NULL;
			pp->kin_num=s;
			printf("蔬菜编码:");
			scanf("%d",&pp->veg_num);
			getchar();
			printf("蔬菜名称:");
			scanf("%s",pp->veg_name);
			getchar();
			printf("营养成分:");
			scanf("%s",pp->nutrition);
			getchar();
			pp->next = p1->inext;
			p1->inext = pp;

			ClearScreen();
			ShowMenu();

			char *plabel_name[] = { "数据插入成功！",
				"确认"
			};

			ShowModule(plabel_name, 2);
		}
		else                                         /*提示失败信息*/
		{
			printf("没有找到对应的蔬菜分类编码信息！\n");
			printf("按任意键返回。。。");
			getchar();
			ClearScreen();
			ShowMenu();
		}

	}
	if (n == 3)
	{
	    char s;
	    int i;
		printf("请输入蔬菜种植信息 \n\n");
		printf("请先输入蔬菜分类编码：");
		scanf("%c",&s);
		getchar();
		printf("再输入蔬菜编号：");
		scanf("%d",&i);
		getchar();
		fp = SeekKindNum(s,i);  /*按照蔬菜分类编码、蔬菜编号查找蔬菜基本信息结点*/
		if (fp != NULL)
		{

			pm = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
			pm->veg_num=i;
			printf("种植编号：");
			scanf("%d",&pm->num);
			getchar();
			printf("种植面积：");
			scanf("%d",&pm->area);
			getchar();
			printf("收获重量：");
			scanf("%f",&pm->output);
			getchar();
			printf("种植年份：");
			scanf("%s",pm->year);
			getchar();

			pm->next = fp->pnext;
			fp->pnext = pm;

			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "数据插入成功！",
				"确认"
			};

			ShowModule(plabel_name, 2);
		}
		else
		{
			printf("没有找到对应的蔬菜基本信息！\n");
			printf("按任意键返回。。。");
			getchar();
			ClearScreen();
			ShowMenu();
		}
	}
	if (n != 1 && n != 2 && n != 3)
	{
		printf("输入有误！");
	}

}

/**
 * 函数名称: Dele_info
 * 函数功能: 删除三种信息
 * 输入参数: int类型：1代表删除种类信息，2代表删除基本信息，3代表删除种植信息
 * 输出参数:
 * 返 回 值: 无
 *
 * 调用说明:
 */
void Dele_info(int n)
{
	if (n == 3)
	{
		int n;
		printf("请输入要删除的蔬菜编号：");
		scanf("%d",&n);
		getchar();
		Seeki(n);
		if (pc != NULL)
		{
			printf("请输入要删除信息的蔬菜种植编号:");
			scanf("%d",&n);
			getchar();
			Seekp(n);
			if (finds != NULL)
			{
				if (finds == findc->pnext)
					findc->pnext = finds->next;
				else
					ps->next = finds->next;
				free(finds);
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "数据删除成功！",
					"确认"
				};
				ShowModule(plabel_name, 2);
			}
			else
			{
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "数据删除失败！",
					"确认"
				};
				ShowModule(plabel_name, 2);
			}
		}
	}

	else if (n == 2)
	{
	    int n;
		printf("请输入要删除的蔬菜编号：");
		scanf("%d",&n);
		getchar();
		Seeki(n);
		if (findc != NULL)
		{
			if (findc == findt->inext)
				findt->inext = findc->next;
			else
				pc->next = findc->next;
			free(findc);
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "数据删除成功！",
				"确认"
			};
			ShowModule(plabel_name, 2);
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "数据删除失败！",
				"确认"
			};
			ShowModule(plabel_name, 2);
		}
	}
	else if (n == 1)
	{
	    char s;
		printf("请输入要删除的蔬菜分类编码：");
		scanf("%c",&s);
		getchar();
		Seekk(s);
		if (findt != NULL)
		{
			if (findt == gp_head)             /*判断是否为头结点*/
				gp_head = findt->next;
			else
				pt->next = findt->next;
			free(findt);                     /*释放结点*/
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "数据删除成功！",
				"确认"
			};

			ShowModule(plabel_name, 2);
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "数据删除失败！",
				"确认"
			};

			ShowModule(plabel_name, 2);
		}
	}
}

/**
* 函数名称: Modify_info
* 函数功能: 修改结点信息.
* 输入参数: int类型：1代表修改种类信息，2代表修改基本信息，3代表修改种植信息
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void Modify_info(int n)
{
	KIND_NODE *p1 = gp_head, *pd=NULL;
	INF_NODE *pp=NULL, *fp=NULL;
	PLANT_NODE  *pm=NULL, *pf=NULL;

	if (n == 1)
	{
	    char s;
		printf("请输入需要修改的蔬菜分类编码：\n");
		scanf("%c",&s);
		getchar();
		while (p1 != NULL)
		{
			if (s==p1->kin_num)
				break;
			p1 = p1->next;
		}
		if (p1 != NULL)
		{
			printf("请输入修改信息：\n\n");
			printf("分类编码：");
			scanf("%c",&p1->kin_num);
			getchar();
			printf("分类名称：");
			scanf("%s",p1->kin_name);
			getchar();

			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "信息修改成功！",
				"确认"
			};

			ShowModule(plabel_name, 2);
		}

		else
		{
			char *plabel_name[] = { "信息修改失败！",
				"确认"
			};

			ShowModule(plabel_name, 2);
		}
	}
	if (n == 2)
	{
	    int n;
		printf("请输入修改的蔬菜编号：");
		scanf("%d",&n);
		getchar();
		Seeki(n);
		if (findc != NULL)
		{
			printf("修改哪条信息：\n");
			printf("  1：蔬菜名称\n");
			printf("  2：分类码\n");
			printf("  3：营养成分\n");
			int t;
			scanf("%d", &t);
			getchar();
			if (t == 1)
			{
			    char c[10];
				printf("请输入修改后的蔬菜名称：");
				scanf("%s",c);
				getchar();
				strcpy(findc->veg_name, c);
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "信息修改成功！",
					"确认"
				};
				ShowModule(plabel_name, 2);
			}
			else if (t == 2)
			{
			    char c;
				printf("请输入修改后的分类码：");
				scanf("%c",&c);
				getchar();
				findc->kin_num=c;
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "信息修改成功！",
					"确认"
				};
				ShowModule(plabel_name, 2);
			}
			else if (t == 3)
			{
			    char c[50];
				printf("请输入修改后的营养成分：");
				scanf("%s",c);
				getchar();
				strcpy(findc->nutrition,c);
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "信息修改成功！",
					"确认"
				};
				ShowModule(plabel_name, 2);
			}
			else
			{
				printf("输入有误！");
			}
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "信息修改失败！",
				"确认"
			};
			ShowModule(plabel_name, 2);
		}
	}
	if (n == 3)
	{
		printf("请输入修改的蔬菜分类编码：");
		char s;
		scanf("%c",&s);
		getchar();
		printf("请输入修改的蔬菜编号：");
		int n;
		scanf("%d",&n);
		getchar();
		pc = SeekKindNum(s,n);
		if (pc != NULL)
		{
		    int i;
			printf("请输入要修改信息在%s中的编号：",pc->veg_name);
			scanf("%d",&i);
			getchar();
			Seekp(i);
			if (finds != NULL)
			{
			    int t,s;
			    float f;
			    char c[5];

				printf("修改哪条信息：\n");
				printf("  1：种植面积\n");
				printf("  2：收获重量\n");
				printf("  3：种植年份\n");
				scanf("%d", &t);
				getchar();
				if (t == 1)
				{
					printf("请输入修改后的种植面积：");
					scanf("%d",&s);
					getchar();
					finds->area=s;
					ClearScreen();
					ShowMenu();
					char *plabel_name[] = { "信息修改成功！",
						"确认"
					};
					ShowModule(plabel_name, 2);
				}
				else if (t == 2)
				{
					printf("请输入修改后的收获重量：");
					scanf("%f",&f);
					getchar();
					finds->output=f;
					ClearScreen();
					ShowMenu();
					char *plabel_name[] = { "信息修改成功！",
						"确认"
					};
					ShowModule(plabel_name, 2);
				}
				else if (t == 3)
				{
					printf("请输入修改后的种植年份：");
					scanf("%s", c);
					getchar();
					strcpy(finds->year, c);
					ClearScreen();
					ShowMenu();
					char *plabel_name[] = { "信息修改成功！",
						"确认"
					};
					ShowModule(plabel_name, 2);
				}
				else
				{
					printf("输入有误！");
				}

			}
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "信息修改失败！",
				"确认"
			};
			ShowModule(plabel_name, 2);
		}
	}
}

/**数据查询函数**/

/**
* 函数名称: SeekKindNum
* 函数功能: 按照蔬菜分类编码、蔬菜编号查找蔬菜基本信息结点.
* 输入参数: char kind_num, int veg_num
* 输出参数: 无
* 返 回 值: 蔬菜基本信息结点
*
* 调用说明:
*/
INF_NODE *SeekKindNum(char kind_num, int veg_num)    /*按照蔬菜分类编码、蔬菜编号查找蔬菜基本信息结点*/
{
    KIND_NODE *pkind_node=NULL;
	INF_NODE *pinf_node=NULL;
	PLANT_NODE *pplant_node=NULL;
	int find = 0;

	for (pkind_node = gp_head; pkind_node != NULL; pkind_node = pkind_node->next)
	{  /*二重循环依次搜索主链每个结点的学生信息支链*/
		if (pkind_node->kin_num==kind_num)
		{
			pinf_node = pkind_node->inext;
			while (pinf_node != NULL)
			{
				if (pinf_node->veg_num==veg_num)
				{
					find = 1;
					break;
				}

				pinf_node = pinf_node->next;
			}
			if (find)
			{
				break;
			}
		}

	}
	if (find)
	{
		return pinf_node;
	}
	else
	{
		return NULL;
	}
}

/**
* 函数名称: Seekk
* 函数功能: 查找蔬菜种类信息.
* 输入参数: 蔬菜分类编码
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void* Seekk(char s)
{
	findt = gp_head;
	while (findt != NULL)
    {
        if (findt->kin_num==s)
            return;
        pt = findt;
        findt = findt->next;
    }
}

/**
* 函数名称: Seeki
* 函数功能: 查找蔬菜基本信息
* 输入参数: 蔬菜基本信息编号
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void* Seeki(int n)
{
    findt = gp_head;
    while (findt != NULL)
    {
        findc = findt->inext;
        while (findc != NULL)
        {
				if (n==findc->veg_num)
					return;
				pc = findc;
				findc = findc->next;
        }
			findt = findt->next;
    }
}


/**
* 函数名称: Seekp
* 函数功能: 查找蔬菜种植信息.
* 输入参数: 蔬菜种植编号
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void* Seekp(int n)
{
	findt = gp_head;
	while (findt != NULL)
    {
        findc = findt->inext;
        while (findc)
        {
            finds = findc->pnext;
            {
                while (finds != NULL)
                {
                    if (finds->num==n)
                        return;
                    ps = finds;
                    finds = finds->next;
                }
            }
            pc = findc;
            findc = findc->next;
        }
        pt = findt;
        findt = findt->next;
    }
}

/**
* 函数名称: SeekIVegName
* 函数功能: 按照蔬菜名称子串查找蔬菜基本信息
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void SeekIVegName(void)
{
    int flag=0;
    char c1[10],*c2;
    printf("请输入想要查找的蔬菜名称中文字符子串：");
    scanf("%s",c1);
    getchar();
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(pi;pi!=NULL;pi=pi->next)
        {
            c2=strstr(pi->veg_name,c1);
            if(c2!=NULL)
            {
                if(flag==0)
                {
                    printf("\n%-10s","蔬菜编号");
                    printf("%-15s","蔬菜名称");
                    printf("%-10s","分类编码");
                    printf("%-100s\n\n","营养成分");
                }
                flag=1;
                printf("%-10d",pi->veg_num);
                printf("%-15s",pi->veg_name);
                printf("%-10c",pi->kin_num);
                printf("%-100s\n",pi->nutrition);
            }
        }
    }
    if(flag==0)
    {
        printf("\n未查找到对应蔬菜。。。\n");
    }
    getchar();
}

/**
* 函数名称: SeekIKindNut
* 函数功能: 按照蔬菜分类编码和营养成分查找蔬菜基本信息
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void SeekIKindNut(void)
{
    int flag=0;
    char c1,c2[10],*c3;
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    printf("请输入需要查询的蔬菜的分类编码：");
    scanf("%c",&c1);
    getchar();
    printf("\n请输入需要查询的蔬菜所包含的一种营养成分：");
    scanf("%s",c2);
    getchar();
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        if(pk->kin_num==c1)
        {
            pi=pk->inext;
            for(;pi!=NULL;pi=pi->next)
            {
                c3=strstr(pi->nutrition,c2);
                if(c3!=NULL)
                {
                    if(flag==0)
                {
                    printf("\n%-10s","蔬菜编号");
                    printf("%-15s","蔬菜名称");
                    printf("%-10s","分类编码");
                    printf("%-100s\n\n","营养成分");
                }
                flag=1;
                printf("%-10d",pi->veg_num);
                printf("%-15s",pi->veg_name);
                printf("%-10c",pi->kin_num);
                printf("%-100s\n",pi->nutrition);
                }
            }
        }
    }

    if(flag==0)
    {
        printf("\n未查找到对应蔬菜。。。\n");
    }

    getchar();
}

/**
* 函数名称: SeekPNameYear
* 函数功能: 按照蔬菜部分名称以及种植年份查找蔬菜种植信息
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void SeekPNameYear(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp=NULL;
    int flag=0;
    char c1[10],c2[5],*c3;
    printf("请输入要查询的蔬菜的部分名称：");
    scanf("%s",c1);
    getchar();
    printf("请输入要查询蔬菜的种植年份：");
    scanf("%s",c2);
    getchar();
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            c3=strstr(pi->veg_name,c1);
            if(c3!=NULL)
            {
                pp=pi->pnext;
                for(;pp!=NULL;pp=pp->next)
                {
                    if(strcmp(c2,pp->year)==0)
                    {
                        flag=1;
                        printf("\n蔬菜名称：%s\n\n",pi->veg_name);
                        printf("蔬菜种植信息编号：%d\n\n",pp->num);
                        printf("蔬菜编号：%d\n\n",pp->veg_num);
                        printf("种植面积：%d\n\n",pp->area);
                        printf("收获重量：%f\n\n",pp->output);
                        printf("种植年份：%s\n\n\n",pp->year);
                    }
                }
            }
        }
    }
    if(flag==0)
    {
        printf("\n未查找到对应蔬菜。。。\n");
    }
}

/**
* 函数名称: SeekPVegName
* 函数功能: 按照蔬菜名称查找蔬菜种植信息
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void SeekPVegName(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp;
    int i,flag=0;
    char c1[20];
    printf("请输入要查询的蔬菜名称：");
    scanf("%s",c1);
    getchar();
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            if(strcmp(pi->veg_name,c1)==0)
            {
                pp=pi->pnext;
                if(pp==NULL)
                {
                    printf("\n该蔬菜下无种植信息。。\n");
                    return;
                }
                flag=1;
                Year(pp);
            }
         }
    }
    if(flag==0)
    {
        printf("\n未查找到对应蔬菜。。。\n");
    }
}

/**
* 函数名称: Year
* 函数功能: 按照年份输出蔬菜信息
* 输入参数: PLANT_NODE *head
* 返 回 值: 无
*
* 调用说明:
*/
void Year(PLANT_NODE *head)
{
    PLANT_NODE *endpt=NULL,*pp1=NULL,*pp2=NULL,*pp3=NULL;

    pp1=(PLANT_NODE *)malloc(sizeof(PLANT_NODE));
    pp1->next=head;
    head=pp1;
    for(endpt=NULL;endpt!=head;endpt=pp3)
    {
        for(pp3=pp1=head;pp1->next->next!=endpt;pp1=pp1->next)
        {
            if(strcmp(pp1->next->year,pp1->next->next->year)<0)
            {
                pp2=pp1->next->next;
                pp1->next->next=pp2->next;
                pp2->next=pp1->next;
                pp1->next=pp2;
                pp3=pp1->next->next;
            }
        }
    }
    pp1=head;
    head=head->next;
    for(;head!=NULL;head=head->next)
    {
        printf("\n蔬菜种植信息编号：%d\n\n",head->num);
        printf("蔬菜编号：%d\n\n",head->veg_num);
        printf("种植面积：%d\n\n",head->area);
        printf("收获重量：%f\n\n",head->output);
        printf("种植年份：%s\n\n\n",head->year);
    }
}

/**数据统计函数**/

/**
* 函数名称: Stat_Year_Kind
* 函数功能: 统计某年各类蔬菜
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void Stat_Year_Kind(void)
{
    char a[10],s[5];
    int b;
    float c;
    int len=0,flag=0,i,j;
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp=NULL;
    STAT1 *ps1=NULL,*ps2=NULL,*ps3=NULL;
    ps1=(STAT1 *)malloc(sizeof(STAT1));
    ps1->next=NULL;
    ps3=ps1;
    printf("请输入想要统计的年份：");
    scanf("%s",s);
    getchar();
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        ps1->area=0;
        ps1->output=0;
        strcpy(ps1->kind_name,pk->kin_name);
        for(;pi!=NULL;pi=pi->next)
        {
            pp=pi->pnext;
            for(;pp!=NULL;pp=pp->next)
            {
                if(strcmp(s,pp->year)==0)
                {
                    ps1->area+=pp->area;
                    ps1->output+=pp->output;
                }
            }
        }
        if(pk->next!=NULL)
        {
            ps1->next=(STAT1 *)malloc(sizeof(STAT1));
            ps1=ps1->next;
            ps1->next=NULL;
        }
    }

    ps1=ps3;
    while(ps1)
    {
        len++;
        ps1=ps1->next;
    }
    for(i=0,ps1=ps3;i<len-1;i++,ps1=ps1->next)
    {
        for(j=i+1,ps2=ps1->next;j<len;j++,ps2=ps2->next)
        {
            if(ps1->output<ps2->output)
            {
                strcpy(a,ps1->kind_name);
                strcpy(ps1->kind_name,ps2->kind_name);
                strcpy(ps2->kind_name,a);

                b=ps1->area;
                ps1->area=ps2->area;
                ps2->area=b;

                c=ps1->output;
                ps1->output=ps2->output;
                ps2->output=c;
            }
        }
    }
    printf("\n%s年各类蔬菜的统计结果为：\n\n",s);
    for(ps1=ps3;ps1!=NULL;ps1=ps1->next)
    {
        if(flag==0)
        {
            printf("%-15s","蔬菜分类名称");
            printf("%-20s","该类蔬菜种植总面积");
            printf("%-20s\n\n","该类蔬菜收获总重量");
        }
        flag=1;
        printf("%-15s",ps1->kind_name);
        printf("%-20d",ps1->area);
        printf("%-20f\n\n",ps1->output);
    }
    if(flag==0)
    {
        printf("\n统计失败，按任意键返回\n");
        getchar();
    }
}

/**
* 函数名称: Stat_Veg_Year
* 函数功能: 以所输入的起止年份为条件，按蔬菜名称统计
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void Stat_Veg_Year(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp=NULL;
    STAT2 *ps1=NULL,*ps2=NULL,*ps3=NULL;
    int len=0,flag=0,i,j;
    char year1[5],year2[5];
    char a[10],b[10];
    int c;
    float d;

    printf("请输入需要查询的起始年份：");
    scanf("%s",year1);
    getchar();
    printf("\n请输入需要查询的终止年份：");
    scanf("%s",year2);
    getchar();
    ps1=(STAT2 *)malloc(sizeof(STAT2));
    ps1->next=NULL;
    ps3=ps1;
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            pp=pi->pnext;
            ps1->area=0;
            ps1->output=0;
            strcpy(ps1->kind_name,pk->kin_name);
            strcpy(ps1->veg_name,pi->veg_name);
            for(;pp!=NULL;pp=pp->next)
            {
                if((strcmp(year1,pp->year)<=0)&&(strcmp(year2,pp->year)>=0))
                {
                    flag=1;
                    ps1->area+=pp->area;
                    ps1->output+=pp->output;
                }
            }
            if((pi->next!=NULL)||(pk->next!=NULL))
            {
                ps1->next=(STAT2 *)malloc(sizeof(STAT2));
                ps1=ps1->next;
                ps1->next=NULL;
            }
        }
    }

    if(flag==0)
    {
        printf("\n统计失败，按任意键返回\n");
        getchar();
        return;
    }

    ps1=ps3;
    while(ps1)
    {
        len++;
        ps1=ps1->next;
    }
    for(i=0,ps1=ps3;i<len-1;i++,ps1=ps1->next)
    {
        for(j=i+1,ps2=ps1->next;j<len;j++,ps2=ps2->next)
        {
            if(ps1->output<ps2->output)
            {
                strcpy(a,ps1->kind_name);
                strcpy(ps1->kind_name,ps2->kind_name);
                strcpy(ps2->kind_name,a);

                strcpy(b,ps1->veg_name);
                strcpy(ps1->veg_name,ps2->veg_name);
                strcpy(ps2->veg_name,b);

                c=ps1->area;
                ps1->area=ps2->area;
                ps2->area=c;

                d=ps1->output;
                ps1->output=ps2->output;
                ps2->output=d;
            }
        }
    }
    printf("\n%s年到%s年蔬菜的统计结果为：\n\n",year1,year2);
    printf("%-15s","蔬菜名称");
    printf("%-15s","蔬菜分类名称");
    printf("%-20s","该蔬菜种植总面积");
    printf("%-20s\n\n","该蔬菜收获总重量");
    for(ps1=ps3;ps1!=NULL;ps1=ps1->next)
    {
        printf("%-15s",ps1->veg_name);
        printf("%-15s",ps1->kind_name);
        printf("%-20d",ps1->area);
        printf("%-20f\n\n",ps1->output);
    }
}

/**
* 函数名称: Stat_Kind
* 函数功能: 统计某种类蔬菜的已有的数量
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void Stat_Kind(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    int num,flag=0;
    printf("各种蔬菜已有数量统计结果为：\n\n");
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        flag=1;
        num=0;
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            num++;
        }
        printf("蔬菜分类名称：%s\n\n",pk->kin_name);
        printf("该种类中共包含蔬菜%d种\n\n\n",num);
    }
    if(flag==0)
    {
        printf("\n统计失败...\n");
        getchar();
    }
}

/**
* 函数名称: Stat_Nut
* 函数功能: 统计含某种营养成分的蔬菜
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void Stat_Nut(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    char nut[50],*c;
    int flag=0;

    printf("请输入需要统计的营养成分：");
    scanf("%s",nut);
    getchar();
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            c=strstr(pi->nutrition,nut);
            if(c!=NULL)
            {
                flag=1;
                printf("蔬菜名称：%s\n\n",pi->veg_name);
            }
        }
    }
    if(flag==0)
    {
        printf("\n统计失败，按任意键返回\n");
        getchar();
    }
}

/**
* 函数名称: Stat_Veg_Inf
* 函数功能: 统计某种蔬菜基本信息
* 输入参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void Stat_Veg_Inf(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp=NULL;
    char name[10];
    int flag=0,num=0;

    printf("请输入想要统计的蔬菜名称：");
    scanf("%s",name);
    getchar();

    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            if(strcmp(pi->veg_name,name)==0)
            {
                flag=1;
                pp=pi->pnext;
                for(;pp!=NULL;pp=pp->next)
                {
                    num++;
                }
            }
        }
    }
    printf("\n该蔬菜结构下共有%d条蔬菜种植信息，分别是：\n\n",num);

    printf("%-5s","编号");
    printf("%-10s","蔬菜编号");
    printf("%-10s","种植面积");
    printf("%-10s","收获重量");
    printf("%-10s\n\n","种植年份");

    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            if(strcmp(pi->veg_name,name)==0)
            {
                pp=pi->pnext;
                for(;pp!=NULL;pp=pp->next)
                {
                    printf("%-5d",pp->num);
                    printf("%-10d",pp->veg_num);
                    printf("%-10d",pp->area);
                    printf("%-10f",pp->output);
                    printf("%-10s\n\n",pp->year);
                }
            }
        }
    }
    if(flag==0)
    {
        printf("\n统计失败，按任意键返回。。。\n");
        getchar();
    }
}
