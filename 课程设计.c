#include "vegetable.h"

unsigned long ul;

/*������*/
int main()
{
    COORD size = {SCR_COL, SCR_ROW}; /*���ڻ�������С*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* ��ȡ��׼����豸���*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* ��ȡ��׼�����豸���*/

    SetConsoleTitle(gp_sys_name);                 /*���ô��ڱ���*/
    SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С80*25*/

    LoadData();             /*���ݼ���*/
    Welcome();              /*��ӭ����*/
    InitInterface();        /*�����ʼ��*/
    RunSys(&gp_head);       /*ϵͳ����ģ���ѡ������*/
    CloseSys(gp_head);      /*�˳�ϵͳ*/

    return 0;
}

/**
* ��������: Welcome
* ��������: ������Ļ������ӭ�û��������
* �������: ��
* �������: ��
* �� �� ֵ: ��
*/
void Welcome()
{
    ClearScreen();
    printf("\n\n\n\n\n\n\n\n\n\n\t��");
    Sleep(250);
    printf("  ӭ"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  ũ"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  ֲ"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  Ϣ"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  ��"); Sleep(250);
    printf("  ϵ"); Sleep(250);
    printf("  ͳ"); Sleep(250);
    printf("  ."); Sleep(250);
    printf("  ."); Sleep(250);
    printf("  ."); Sleep(250);
    Sleep(1000);
    system("cls");
}


/**
 * ��������: LoadData
 * ��������: ������������������ݴ������ļ����뵽�ڴ滺������ʮ��������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, ���ܺ����г��˺���ExitSys�ķ���ֵ����ΪFALSE��,
 *           ���������ķ���ֵ����ΪTRUE.
 *
 * ����˵��: Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���, ����Щ���ܺ�����ԭ����Ϊ
 *           һ��, ���޲����ҷ���ֵΪBOOL. ����ֵΪFALSEʱ, ������������.
 */
BOOL LoadData()
{
    int Re = 0;
    Re = CreatList(&gp_head);
    gc_sys_state |= Re;
    gc_sys_state &= ~(4 + 8 + 16 - Re);
    if (gc_sys_state < ( 4 | 8 | 16))
    {  /*���ݼ�����ʾ��Ϣ*/
        printf("\nϵͳ�������ݲ�����!\n");
        printf("\n�����������...\n");
        getchar();
    }

    printf("\n�����������...\n");
    getchar();

    return TRUE;
}

/**
 * ��������: LoadCode
 * ��������: �������������ļ����뵽�ڴ滺����, �����������ȥ���ո�.
 * �������: FileName ��Ŵ����������ļ���.
 * �������: pBuffer ָ���ڴ滺������ָ������ĵ�ַ.
 * �� �� ֵ: ��Ŵ������ڴ滺������С(���ֽ�Ϊ��λ).
 *
 * ����˵��:
 */
int LoadCode(char *FileName, char **pBuffer)
{
    char *pTemp=NULL, *pStr1=NULL, *pStr2=NULL;
    int handle;
    int BufferLen, len, loc1, loc2, i;
    long filelen;

    if ((handle = open(FileName, O_RDONLY | O_TEXT)) == -1) /*�����ֻ����ʽ��ʧ�� */
    {
        handle = open(FileName, O_CREAT | O_TEXT, S_IREAD); /*�Դ�����ʽ��*/
    }
    filelen = filelength(handle);      /*�����ļ��ĳ���*/
    pTemp = (char *)calloc(filelen + 1, sizeof(char)); /*����ͬ����С�Ķ�̬�洢��*/
    BufferLen = read(handle, pTemp, filelen); /*�������ļ�������ȫ�����뵽�ڴ�*/
    close(handle);

    *(pTemp + BufferLen) = '\0'; /*�ڶ�̬�洢��β��һ�����ַ�����Ϊ�ַ���������־*/
    BufferLen++;

    for (i=0; i<BufferLen; i++) /*����̬�洢���е����л��з��滻�ɿ��ַ�*/
    {
        if (*(pTemp + i) == '\n')
        {
            *(pTemp + i) = '\0';
        }
    }

    /*������һ��ͬ����С�Ķ�̬�洢�������ڴ�������Ĵ��봮*/
    *pBuffer = (char *)calloc(BufferLen, sizeof(char));
    loc2 = 0;
    pStr1 = pTemp;
    len = strlen(pStr1);

    while (BufferLen > len + 1) /*ѡ������*/
    {
        loc1 = len + 1;
        while (BufferLen > loc1) /*ÿ���ҵ���������С���봮���׵�ַ����pStr1*/
        {
            pStr2 = pTemp + loc1;
            if (strcmp(pStr1, pStr2) > 0)
            {
                pStr1 = pStr2;
            }
            loc1 += strlen(pStr2) + 1;
        }
        len = strlen(pStr1);  /*��һ�����ҵ�����С���봮����*/

        /*������ǿմ�������и��ƣ�loc2����һ����С���봮��ŵ�ַ��ƫ����*/
        if (len > 0)
        {
            strcpy(*pBuffer + loc2, pStr1);
            loc2 += len + 1;  /*�Ѹ��ƵĴ��봮��ռ�洢�ռ��С*/
        }

        /*����С���봮��������ɾ����*/
        for(i=0; i<BufferLen-(pStr1-pTemp)-(len+1); i++)
        {
            *(pStr1 + i) = *(pStr1 + i + len + 1);
        }

        BufferLen -= len + 1; /*��һ���������������еĳ���*/
        pStr1 = pTemp;  /*�ٶ����еĵ�һ�����봮Ϊ��С���봮*/
        len = strlen(pStr1);
    } /*������ֻʣ��һ�����봮ʱ���������*/

    /*�������������봮*/
    len = strlen(pStr1);
    strcpy(*pBuffer + loc2, pStr1);

    /*�޸Ķ�̬�洢����С��ʹ�����÷����������봮*/
    loc2 += len + 1;
    *pBuffer = (char *)realloc(*pBuffer, loc2);
    free(pTemp);  /*�ͷ���������Ķ�̬�洢��*/

    return loc2;  /*���ش�Ŵ��봮���ڴ滺����ʵ�ʴ�С*/
}

/**
 * ��������: CreatList
 * ��������: �������ļ���ȡ��������, ����ŵ���������ʮ��������.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ, ����������������ʮ����.
 * �� �� ֵ: int����ֵ, ��ʾ�����������.
 *           0  ����, ������
 *           4  �Ѽ����߲�������Ϣ���ݣ����߲˻�����Ϣ���߲���ֲ��Ϣ����
 *           12 �Ѽ����߲�������Ϣ���߲˻�����Ϣ���ݣ����߲���ֲ��Ϣ����
 *           28 ����������ݶ��Ѽ���
 *
 * ����˵��:
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
        printf("�߲�������Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�߲�������Ϣ�����ļ��򿪳ɹ�!\n");

    /*�������ļ��ж��߲�������Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
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
        printf("�߲�������Ϣ�����ļ�����ʧ��!\n");
        return re;
    }
    printf("�߲�������Ϣ�����ļ����سɹ�!\n");
    *phead = hd;
    re += 4;

    if ((pFile = fopen(gp_information_info_filename, "rb")) == NULL)
    {
        printf("�߲˻�����Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�߲˻�����Ϣ�����ļ��򿪳ɹ�!\n");
    re += 8;

    /*�������ļ��ж�ȡ�߲˻�����Ϣ���ݣ�����������Ӧ�����߲˻�����Ϣ֧����*/
    while (fread(&tmp2, sizeof(INF_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж������߲˻�����Ϣ*/
        pInfNode = (INF_NODE *)malloc(sizeof(INF_NODE));
        *pInfNode = tmp2;
        pInfNode->pnext = NULL;

        /*�������ϲ��Ҹ��߲˻�����Ϣ��Ӧ���������*/
        pKindNode = hd;
        while (pKindNode != NULL
               && pKindNode->kin_num!=pInfNode->kin_num)
        {
            pKindNode = pKindNode->next;
        }
        if (pKindNode != NULL) /*����ҵ����򽫽���Ժ���ȳ���ʽ�����߲���Ϣ֧��*/
        {
            pInfNode->next = pKindNode->inext;
            pKindNode->inext = pInfNode;
        }
        else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pInfNode);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_plant_info_filename, "rb")) == NULL)
    {
        printf("�߲���ֲ��Ϣ�����ļ���ʧ��!\n");
        return re;
    }
    printf("�߲���ֲ��Ϣ�����ļ��򿪳ɹ�!\n");
    re += 16;

    /*�������ļ��ж�ȡ�߲���ֲ��Ϣ���ݣ������߲˻�����Ϣ֧����Ӧ������ֲ֧����*/
    while (fread(&tmp3, sizeof(PLANT_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж����߲���ֲ��Ϣ*/
        pPlantNode = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        *pPlantNode = tmp3;

        /*�����߲˻�����Ϣ֧���϶�Ӧ�߲���ֲ��Ϣ���*/
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
        if (find)  /*����ҵ����򽫽���Ժ���ȳ���ʽ�����߲���ֲ��Ϣ֧����*/
        {
            pPlantNode->next = pInfNode->pnext;
            pInfNode->pnext = pPlantNode;
        }
        else /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);

    return re;
}

/**
 * ��������: InitInterface
 * ��������: ��ʼ������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void InitInterface()
{
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*��ɫǰ������ɫ����*/

    SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

    ClearScreen();  /* ����*/

    /*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*��Ļ�ַ�����*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;      /*�������ڵĲ��Ϊ0*/
    gp_top_layer->rcArea.Left = 0;  /*�������ڵ�����Ϊ������Ļ����*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();     /*��ʾ�˵���*/
    ShowState();    /*��ʾ״̬��*/

    return;
}

/**
 * ��������: ClearScreen
 * ��������: �����Ļ��Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*ȡ��Ļ��������Ϣ*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*������Ļ�������ַ���Ԫ��*/

    /*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);

    return;
}

/**
 * ��������: ShowModule
 * ��������: ��������.
 * �������:
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
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
 * ��������: ShowMenu
 * ��������: ����Ļ����ʾ���˵�, ����������, �����˵���һ������ѡ�б��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
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
    for (i=0; i < 5; i++) /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

    /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
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

    /*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*�����λ�������ڵ�2�е�1��*/

    /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*��λ��i+1�Ų˵������ֹλ��*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; /*���ò˵��������ַ���Ԫ������ֵ*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/

    return;
}

/**
 * ��������: ShowState
 * ��������: ��ʾ״̬��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ״̬���ַ�����Ϊ�׵׺���, ��ʼ״̬��״̬��Ϣ.
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
 * ��������: TagMainMenu
 * ��������: ��ָ�����˵�������ѡ�б�־.
 * �������: num ѡ�е����˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
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

    /*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
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

    /*��ѡ�в˵���������ǣ��ڵװ���*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
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

    /*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: CloseSys
 * ��������: �ر�ϵͳ.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void CloseSys(KIND_NODE *hd)
{
    KIND_NODE *pKindNode1 = hd, *pKindNode2=NULL;
    INF_NODE *pInfNode1=NULL, *pInfNode2=NULL;
    PLANT_NODE *pPlantNode1=NULL, *pPlantNode2=NULL;

    while (pKindNode1 != NULL) /*�ͷ�ʮ�ֽ�������Ķ�̬�洢��*/
    {
        pKindNode2 = pKindNode1->next;
        pInfNode1 = pKindNode1->inext;
        while (pInfNode1 != NULL) /*�ͷ��߲˻�����Ϣ֧���Ķ�̬�洢��*/
        {
            pInfNode2 = pInfNode1->next;
            pPlantNode1 = pInfNode1->pnext;
            while (pPlantNode1 != NULL) /*�ͷ���ֲ��Ϣ֧���Ķ�̬�洢��*/
            {
                pPlantNode2 = pPlantNode1->next;
                free(pPlantNode1);
                pPlantNode1 = pPlantNode2;
            }
            free(pInfNode1);
            pInfNode1 = pInfNode2;
        }
        free(pKindNode1);  /*�ͷ��������Ķ�̬�洢��*/
        pKindNode1 = pKindNode2;
    }

    ClearScreen();        /*����*/

    /*�ͷŴ�Ų˵�����״̬������Ϣ��̬�洢��*/
    free(gp_buff_menubar_info);
    free(gp_buff_stateBar_info);

    /*�رձ�׼���������豸���*/
    CloseHandle(gh_std_out);
    CloseHandle(gh_std_in);

    /*�����ڱ�������Ϊ���н���*/
    SetConsoleTitle("���н���");

    return;
}

/**
 * ��������: RunSys
 * ��������: ����ϵͳ, ��ϵͳ�������������û���ѡ��Ĺ���ģ��.
 * �������: ��
 * �������: phead ����ͷָ��ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void RunSys(KIND_NODE **phead)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:�ַ���Ԫ���, cAtt:�ַ���Ԫ����*/
    char vkc, asc;      /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    while (bRet)
    {
        /*�ӿ���̨���뻺�����ж�һ����¼*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
            {
                /* cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
                 * cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
                 * gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    PopMenu(cAtt);       /*��������������˵����Ӧ���Ӳ˵�*/
                }
            }
            else if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                TagSubMenu(cAtt); /*�ڸ��Ӳ˵�������ѡ�б��*/
            }

            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*������������ߵ�һ��*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(���˵����ַ���Ԫ)*/
                    {
                        PopMenu(cAtt);   /*��������������˵����Ӧ���Ӳ˵�*/
                    }
                    /*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    }
                }
                else /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
                    {
                        PopOff(); /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/

                        /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*�����������Ҽ�*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*�����¼�ɰ�������*/
                 && inRec.Event.KeyEvent.bKeyDown) /*�Ҽ�������*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*��ȡ�������������*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*��ȡ������ASC��*/

            /*ϵͳ��ݼ��Ĵ���*/
            if (vkc == 112) /*�������F1��*/
            {
                if (gp_top_layer->LayerNo != 0) /*�����ǰ���Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
                bRet = ExeFunction(5, 1);  /*���а������⹦�ܺ���*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            { /*������������Alt��*/
                switch (vkc)  /*�ж���ϼ�Alt+��ĸ*/
                {
                    case 88:  /*Alt+X �˳�*/
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
            else if (asc == 0) /*�������Ƽ��Ĵ���*/
            {
                if (gp_top_layer->LayerNo == 0) /*���δ�����Ӳ˵�*/
                {
                    switch (vkc) /*�������(���ҡ���)������Ӧ�������Ƽ�*/
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
                else  /*�ѵ����Ӳ˵�ʱ*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                    switch (vkc) /*�����(���ҡ��ϡ���)�Ĵ���*/
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
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*������ͨ��*/
                if (gp_top_layer->LayerNo == 0)  /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)
                    {
                        case 70: /*f��F*/
                            PopMenu(1);
                            break;
                        case 77: /*m��M*/
                            PopMenu(2);
                            break;
                        case 81: /*q��Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s��S*/
                            PopMenu(4);
                            break;
                        case 72: /*h��H*/
                            PopMenu(5);
                            break;
                        case 13: /*�س�*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
                {
                    if (vkc == 27) /*�������ESC��*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*������»س���*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*������ͨ���Ĵ���*/
                    {
                        /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*���ƥ��ɹ�*/
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
 * ��������: PopMenu
 * ��������: ����ָ�����˵����Ӧ���Ӳ˵�.
 * �������: num ָ�������˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
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

    if (num != gi_sel_menu)       /*���ָ�����˵�������ѡ�в˵�*/
    {
        if (gp_top_layer->LayerNo != 0) /*�����ǰ�����Ӳ˵�����*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*���ѵ������Ӳ˵����򷵻�*/
    {
        return;
    }

    gi_sel_menu = num;    /*��ѡ�����˵�����Ϊָ�������˵���*/
    TagMainMenu(gi_sel_menu); /*��ѡ�е����˵����������*/
    LocSubMenu(gi_sel_menu, &rcPop); /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

    /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*�������Ӳ˵������������ǩ���ṹ����*/
    labels.ppLabel = ga_sub_menu + loc;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1]; /*��ǩ���б�ǩ�ַ����ĸ���*/
    COORD aLoc[labels.num];/*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
    for (i=0; i<labels.num; i++) /*ȷ����ǩ�ַ��������λ�ã����������������*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
    /*����������Ϣ*/
    areas.num = labels.num;       /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                      /*��������������������Ӧ���*/
    char aTag[areas.num];                         /*����������ÿ�������ı��*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*������λ*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;           /*������˳����*/
    }
    areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*���������ڻ��߿�*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    { /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0) /*����Ϊ0������Ϊ�մ�*/
        {   /*���Ȼ�����*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {   /*ȡ���������ַ���Ԫ����������*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*��λ��Ľ�������˵���λ*/
            }
        }

    }
    /*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;  /*�����մ�*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * ��������: PopUp
 * ��������: ��ָ�������������������Ϣ, ͬʱ��������, ����������λ����Ϣ��ջ.
 * �������: pRc ��������λ�����ݴ�ŵĵ�ַ
 *           att �������������ַ�����
 *           pLabel ���������б�ǩ����Ϣ��ŵĵ�ַ
             pHotArea ����������������Ϣ��ŵĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer=NULL;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*������������λ���ַ���Ԫ��Ϣ��ջ*/
    size.X = pRc->Right - pRc->Left + 1;    /*�������ڵĿ��*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*�������ڵĸ߶�*/
    /*�����ŵ������������Ϣ�Ķ�̬�洢��*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*��ɵ������������Ϣ��ջ����*/
    /*���õ������������ַ���������*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*����ǩ���еı�ǩ�ַ������趨��λ�����*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*���õ������������ַ���Ԫ��������*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
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
 * ��������: PopOff
 * ��������: �رն��㵯������, �ָ���������ԭ��ۺ��ַ���Ԫԭ����.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer=NULL;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*�ָ�������������ԭ���*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*�ָ��ַ���Ԫԭ����*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * ��������: DrawBox
 * ��������: ��ָ�����򻭱߿�.
 * �������: pRc �������λ����Ϣ�ĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*�����õ��ַ�*/
    COORD pos = {pRc->Left, pRc->Top};  /*��λ����������Ͻ�*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*��ѭ�����ϱ߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*��ѭ�����߿�����ߺ��ұ���*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*���±߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    return;
}

/**
 * ��������: TagSubMenu
 * ��������: ��ָ���Ӳ˵�������ѡ�б��.
 * �������: num ѡ�е��Ӳ˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*���ƶ��Ӳ˵�������ѡ�б��*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*�޸�ѡ���Ӳ˵����*/
    return;
}

/**
 * ��������: LocSubMenu
 * ��������: ���㵯���Ӳ˵��������ϽǺ����½ǵ�λ��.
 * �������: num ѡ�е����˵����
 * �������: rc �������λ����Ϣ�ĵ�ַ
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*����������ұ߽�*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*���������±ߵ��к�*/
    if (rc->Right >= SCR_COL)  /*�ұ߽�Խ��Ĵ���*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * ��������: DealInput
 * ��������: �ڵ�������������������, �ȴ�����Ӧ�û�����.
 * �������: pHotArea
 *           piHot ����������ŵĴ�ŵ�ַ, ��ָ�򽹵�������ŵ�ָ��
 * �������: piHot ����굥�������س���ո�ʱ���ص�ǰ�������
 * �� �� ֵ:
 *
 * ����˵��:
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
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
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
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
            {  /*ESC��*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*�س�����ո��ʾ���µ�ǰ��ť*/
                iRet = 13;
                break;
            }
        }
    }
    return iRet;
}

/**
 * ��������: SetHotPoint
 * ��������: ��ihot��Ӧ������ѡ�С�.
 * �������: HOT_AREA *pHotArea, int iHot
 * �� �� ֵ:��
 *
 * ����˵��:
 */
void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    for (i=0; i<pHotArea->num; i++)
    {  /*����ť��������Ϊ�׵׺���*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*�����ǰ�ť��*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*�����������ǰ�ť��*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*�������������ı�����*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/**
 * ��������: ExeFunction
 * ��������: ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���.
 * �������: m ���˵����
 *           s �Ӳ˵����
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��: ����ִ�к���ExitSysʱ, �ſ��ܷ���FALSE, ������������Ƿ���TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
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

    for (i=1,loc=0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}

/**�ļ�ģ��**/

/**
 * ��������: SaveData
 * ��������: ���ݱ���
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE
 *
 * ����˵��:
 */
BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    SaveSysData(gp_head);

    char *pString[] = { "����ɹ�",
    "ȷ��"
    };
    ShowModule(pString, 2);

    return bRet;
}

/**
 * ��������: BackupData
 * ��������: ���ݱ���
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE
 *
 * ����˵��:
 */
BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    BackupSysData(gp_head);
    char *pString[] = { "���ݳɹ�",
    "ȷ��"
    };
    ShowModule(pString, 2);

    return bRet;
}

/**
 * ��������: RestoreData
 * ��������: ���ݻָ�
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE
 *
 * ����˵��:
 */
BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݻָ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    RestoreSysData(&gp_head);
    char *pString[] = { "�ָ��ɹ�",
    "ȷ��"
    };
    ShowModule(pString, 2);

    return bRet;
}

/**
* �������� : ExitSys
* �������� : �˳�ϵͳ
* �� �� ֵ : BOOL����, TRUE
*/
BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"ȷ���˳�ϵͳ��", "ȷ��    ȡ��"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
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

/**����ά��ģ��**/

/**
* �������� : MaintainKindInfo
* �������� : ��ӡ��޸Ļ���ɾ���߲�������Ϣ
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL MaintainKindInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ά���߲�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    int n;
	printf("��ѡ��:\n");
	printf("  1-����\n");
	printf("  2-�޸�\n");
	printf("  3-ɾ��\n");
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
		printf("��������\n��������̷��ء�����");
		getchar();
	}
	ClearScreen();
	ShowMenu();

    return bRet;
}

/**
* �������� : MaintainInfInfo
* �������� : ��ӡ��޸Ļ���ɾ���߲˻�����Ϣ
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL MaintainInfInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ά���߲˻�����Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    int n;
	printf("��ѡ��:\n");
	printf("  1-����\n");
	printf("  2-�޸�\n");
	printf("  3-ɾ��\n");
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
		printf("��������\n��������̷��ء�����");
		getchar();
	}

	ClearScreen();
	ShowMenu();

    return bRet;
}

/**
* �������� : MaintainPlantInfo
* �������� : ��ӡ��޸Ļ���ɾ���߲���ֲ��Ϣ
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL MaintainPlantInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��ά���߲���ֲ��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    int n;
	printf("��ѡ��:\n");
	printf("  1-����\n");
	printf("  2-�޸�\n");
	printf("  3-ɾ��\n");
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
		printf("��������\n��������̷��ء�����");
		getchar();
	}

	ClearScreen();
	ShowMenu();

    return bRet;
}

/**���ݲ�ѯģ��**/

/**
* �������� : QueryKindInfo
* �������� : ��ѯ�߲�������Ϣ
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL QueryKindInfo(void)
{
    KIND_NODE *pc=NULL;
    char c;
    int i,flag=0;
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���߲�������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    printf("������Ҫ��ѯ���߲���������Ӧ�ķ�����룺");
    scanf("%c",&c);
    getchar();
    for(pc=gp_head;pc!=NULL;pc=pc->next)
    {
        if(c==pc->kin_num)
        {
            flag=1;
            printf("\n�߲˷�����룺%c\n\n",pc->kin_num);
            printf("�߲˷������ƣ�%s\n\n",pc->kin_name);
        }
    }
    if(flag==0)
    {
       printf("δ�ҵ���Ӧ����������������\n");
    }

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"�߲�������Ϣ��ѯ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* �������� : QueryInfInfo
* �������� : ��ѯ�߲˻�����Ϣ
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL QueryInfInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���߲˻�����Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    int n;

    loop:
        printf("��ѡ���ѯ��ʽ��\n");
        printf("  1.�߲����������ַ��Ӵ�Ϊ��������\n");
        printf("  2.�Է������Ӫ���ɷ�Ϊ��������\n");
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
            printf("�������\n\n");
            goto loop;
        }

	getchar();
	ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"�߲˻�����Ϣ��ѯ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* �������� : QueryPlantInfo
* �������� : ��ѯ�߲���ֲ��Ϣ
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL QueryPlantInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵���߲���ֲ��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    int n;

    loop:
        printf("��ѡ���ѯ��ʽ��\n");
        printf("  1.�߲����������ַ��Ӵ��Լ���ֲ���Ϊ��������\n");
        printf("  2.���߲�����Ϊ��������\n");
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
            printf("�������\n\n");
            goto loop;
        }

	getchar();
	ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"�߲���ֲ��Ϣ��ѯ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**����ͳ��ģ��**/

/**
* �������� : StatYearKind
* �������� : �ֱ�ͳ��ĳ������߲���ֲ��������ջ�������
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL StatYearKind(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������ͳ��",
                           "�Ӳ˵��ĳ������߲�ͳ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Year_Kind();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"ͳ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* �������� : StatVegYear
* �������� : �����������ֹ���Ϊ���������߲�����ͳ�Ƹ����������ָ����߲���������ջ�������
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL StatVegYear(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������ͳ��",
                           "�Ӳ˵����ֹ���߲�ͳ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Veg_Year();

    getchar();
	ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"ͳ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* �������� : StatKind
* �������� : �ֱ�ͳ��ĳ�����߲˵����е�����
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL StatKind(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������ͳ��",
                           "�Ӳ˵��ĳ���߲�����ͳ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Kind();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"ͳ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* �������� : StatVegNut
* �������� : ����ĳ��Ӫ���ɷ֣���ʾ������к��и�Ӫ���ɷֵ��߲�����
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL StatVegNut(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������ͳ��",
                           "�Ӳ˵��Ӫ���ɷ��߲�ͳ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Nut();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"ͳ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**
* �������� : StatVegInf
* �������� : ����ĳ���߲����ƣ���ʾ������߲���ֲ��Ϣ����
* �� �� ֵ : BOOL����, TRUE
*
* ����˵��:
*/
BOOL StatVegInf(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������ͳ��",
                           "�Ӳ˵���߲˻�����Ϣͳ��",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    Stat_Veg_Inf();

    getchar();
    ClearScreen();
    ShowMenu();

    char *plabel_name2[] = {"ͳ�����",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

    return bRet;
}

/**������Ϣģ��**/

/**
* �������� : HelpTopic
* �������� : ��ʾ������Ϣ
* ����ֵ : BOOL����, TRUE
**/
BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������",
                           "�Ӳ˵����������",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

	char *plabel_name2[] = {"    ��ϵͳ֧����������",
	                        "   ",
                            "��ALT+��ĸ���Կ��ѡ�����˵�",
                            "ȷ��"
                          };

    ShowModule(plabel_name2, 4);

	getchar();
	ClearScreen();
	ShowMenu();
    return bRet;
}

/**
* �������� : AboutCitySys
* �������� : ��ʾ��ũ��ֲϵͳ��Ϣ
* ����ֵ : BOOL����, TRUE
**/
BOOL AboutVegetableSys(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������",
                            "�Ӳ˵������...",
                            "ȷ��"
                          };

    ShowModule(plabel_name1, 3);


    char *plabel_name2[] = {"��ӭʹ�ò�ũ��ֲ��Ϣ����ϵͳ����",
                           "ȷ��"
                          };

    ShowModule(plabel_name2, 2);

	getchar();
	ClearScreen();
	ShowMenu();

    return bRet;
}

/**
* �������� : AboutCopyright
* �������� : ��ʾ���߼������Ϣ
* ����ֵ : BOOL����, TRUE
**/
BOOL AboutCopyright(void)
{
    BOOL bRet = TRUE;
    char *plabel_name1[] = {"���˵������",
                           "�Ӳ˵����Ȩ˵��",
                           "ȷ��"
                          };

    ShowModule(plabel_name1, 3);

    char *plabel_name2[] = {"�༶�������У�ʽ�����1601",
                            "      ������ʷ����",
                            "    ѧ�ţ�U201615677",
                            "ȷ��"
                          };

    ShowModule(plabel_name2, 4);

	ClearScreen();
	ShowMenu();

    return bRet;
}

/**�ļ�����**/

/**
 * ��������: SaveSysData
 * ��������: ����ϵͳ�����������������.
 * �������: hd ����ͷ���ָ��
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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
 * ��������: BackupSysData
 * ��������: ��ϵͳ����������������ݱ��ݵ�һ�������ļ�.
 * �������: hd ����ͷ���ָ��
 *           filename �����ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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
 * ��������: RestoreSysData
 * ��������: ��ָ�������ļ��лָ�ϵͳ�����������������.
 * �������: phead ����ͷ���ָ��ĵ�ַ
 *           filename ��ű������ݵ������ļ���
 * �������:
 * �� �� ֵ: BOOL����, ����ΪTRUE
 *
 * ����˵��:
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
        printf("�߲�������Ϣ�ָ��ļ���ʧ��!\n");
        return TRUE;
    }
    printf("�߲�������Ϣ�ָ��ļ��򿪳ɹ�!\n");

    /*�������ļ��ж��߲�������Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
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
        printf("�߲�������Ϣ�ָ��ļ�����ʧ��!\n");
        return TRUE;
    }
    printf("�߲�������Ϣ�ָ��ļ����سɹ�!\n");
    *phead = hd;

    if ((pFile = fopen(gp_information_back_filename, "rb")) == NULL)
    {
        printf("�߲˻�����Ϣ�ָ��ļ���ʧ��!\n");
        return TRUE;
    }
    printf("�߲˻�����Ϣ�ָ��ļ��򿪳ɹ�!\n");

    /*�������ļ��ж�ȡ�߲˻�����Ϣ���ݣ�����������Ӧ�����߲˻�����Ϣ֧����*/
    while (fread(&tmp2, sizeof(INF_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж������߲˻�����Ϣ*/
        pInfNode = (INF_NODE *)malloc(sizeof(INF_NODE));
        *pInfNode = tmp2;
        pInfNode->pnext = NULL;

        /*�������ϲ��Ҹ��߲˻�����Ϣ��Ӧ���������*/
        pKindNode = hd;
        while (pKindNode != NULL
               && pKindNode->kin_num!=pInfNode->kin_num)
        {
            pKindNode = pKindNode->next;
        }
        if (pKindNode != NULL) /*����ҵ����򽫽���Ժ���ȳ���ʽ�����߲���Ϣ֧��*/
        {
            pInfNode->next = pKindNode->inext;
            pKindNode->inext = pInfNode;
        }
        else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pInfNode);
        }
    }
    fclose(pFile);

    if ((pFile = fopen(gp_plant_back_filename, "rb")) == NULL)
    {
        printf("�߲���ֲ��Ϣ�ָ��ļ���ʧ��!\n");
        return TRUE;
    }
    printf("�߲���ֲ��Ϣ�ָ��ļ��򿪳ɹ�!\n");

    /*�������ļ��ж�ȡ�߲���ֲ��Ϣ���ݣ������߲˻�����Ϣ֧����Ӧ������ֲ֧����*/
    while (fread(&tmp3, sizeof(PLANT_NODE), 1, pFile) == 1)
    {
        /*������㣬��Ŵ������ļ��ж����߲���ֲ��Ϣ*/
        pPlantNode = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
        *pPlantNode = tmp3;

        /*�����߲˻�����Ϣ֧���϶�Ӧ�߲���ֲ��Ϣ���*/
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
        if (find)  /*����ҵ����򽫽���Ժ���ȳ���ʽ�����߲���ֲ��Ϣ֧����*/
        {
            pPlantNode->next = pInfNode->pnext;
            pInfNode->pnext = pPlantNode;
        }
        else /*���δ�ҵ������ͷ������������ڴ�ռ�*/
        {
            free(pPlantNode);
        }
    }
    fclose(pFile);

    ClearScreen();
    ShowMenu();
    return TRUE;
}

/**����ά������**/

/**
 * ��������: Insert
 * ��������: ����������Ϣ
 * �������: int���ͣ�1�������������Ϣ��2������ӻ�����Ϣ��3���������ֲ��Ϣ
 * �������:
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void Insert(int n)
{
    KIND_NODE *p1 = gp_head, *pd=NULL;
	INF_NODE *pp=NULL, *fp=NULL;
	PLANT_NODE  *pm=NULL, *pf=NULL;
	if (n == 1)                    /*�����߲�������Ϣ*/
	{
		printf("��������Ҫ������߲�������Ϣ\n");
		pd = (KIND_NODE *)malloc(sizeof(KIND_NODE));
		pd->inext = NULL;

		printf("������룺");
		scanf("%c",&pd->kin_num);
		getchar();
		printf("�������ƣ�");
		scanf("%s",pd->kin_name);
		getchar();

		pd->next = p1;
		gp_head = pd;

		ClearScreen();
		ShowMenu();

		char *plabel_name[] = { "���ݲ���ɹ���",    /*��ʾ�ɹ���Ϣ*/
			"ȷ��"
		};

		ShowModule(plabel_name, 2);
	}
	if (n == 2)
	{
	    char s;
		printf("�������߲˻�����Ϣ\n\n");
		printf("���������߲˷�����룺");
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
			printf("�߲˱���:");
			scanf("%d",&pp->veg_num);
			getchar();
			printf("�߲�����:");
			scanf("%s",pp->veg_name);
			getchar();
			printf("Ӫ���ɷ�:");
			scanf("%s",pp->nutrition);
			getchar();
			pp->next = p1->inext;
			p1->inext = pp;

			ClearScreen();
			ShowMenu();

			char *plabel_name[] = { "���ݲ���ɹ���",
				"ȷ��"
			};

			ShowModule(plabel_name, 2);
		}
		else                                         /*��ʾʧ����Ϣ*/
		{
			printf("û���ҵ���Ӧ���߲˷��������Ϣ��\n");
			printf("����������ء�����");
			getchar();
			ClearScreen();
			ShowMenu();
		}

	}
	if (n == 3)
	{
	    char s;
	    int i;
		printf("�������߲���ֲ��Ϣ \n\n");
		printf("���������߲˷�����룺");
		scanf("%c",&s);
		getchar();
		printf("�������߲˱�ţ�");
		scanf("%d",&i);
		getchar();
		fp = SeekKindNum(s,i);  /*�����߲˷�����롢�߲˱�Ų����߲˻�����Ϣ���*/
		if (fp != NULL)
		{

			pm = (PLANT_NODE *)malloc(sizeof(PLANT_NODE));
			pm->veg_num=i;
			printf("��ֲ��ţ�");
			scanf("%d",&pm->num);
			getchar();
			printf("��ֲ�����");
			scanf("%d",&pm->area);
			getchar();
			printf("�ջ�������");
			scanf("%f",&pm->output);
			getchar();
			printf("��ֲ��ݣ�");
			scanf("%s",pm->year);
			getchar();

			pm->next = fp->pnext;
			fp->pnext = pm;

			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "���ݲ���ɹ���",
				"ȷ��"
			};

			ShowModule(plabel_name, 2);
		}
		else
		{
			printf("û���ҵ���Ӧ���߲˻�����Ϣ��\n");
			printf("����������ء�����");
			getchar();
			ClearScreen();
			ShowMenu();
		}
	}
	if (n != 1 && n != 2 && n != 3)
	{
		printf("��������");
	}

}

/**
 * ��������: Dele_info
 * ��������: ɾ��������Ϣ
 * �������: int���ͣ�1����ɾ��������Ϣ��2����ɾ��������Ϣ��3����ɾ����ֲ��Ϣ
 * �������:
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void Dele_info(int n)
{
	if (n == 3)
	{
		int n;
		printf("������Ҫɾ�����߲˱�ţ�");
		scanf("%d",&n);
		getchar();
		Seeki(n);
		if (pc != NULL)
		{
			printf("������Ҫɾ����Ϣ���߲���ֲ���:");
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
				char *plabel_name[] = { "����ɾ���ɹ���",
					"ȷ��"
				};
				ShowModule(plabel_name, 2);
			}
			else
			{
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "����ɾ��ʧ�ܣ�",
					"ȷ��"
				};
				ShowModule(plabel_name, 2);
			}
		}
	}

	else if (n == 2)
	{
	    int n;
		printf("������Ҫɾ�����߲˱�ţ�");
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
			char *plabel_name[] = { "����ɾ���ɹ���",
				"ȷ��"
			};
			ShowModule(plabel_name, 2);
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "����ɾ��ʧ�ܣ�",
				"ȷ��"
			};
			ShowModule(plabel_name, 2);
		}
	}
	else if (n == 1)
	{
	    char s;
		printf("������Ҫɾ�����߲˷�����룺");
		scanf("%c",&s);
		getchar();
		Seekk(s);
		if (findt != NULL)
		{
			if (findt == gp_head)             /*�ж��Ƿ�Ϊͷ���*/
				gp_head = findt->next;
			else
				pt->next = findt->next;
			free(findt);                     /*�ͷŽ��*/
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "����ɾ���ɹ���",
				"ȷ��"
			};

			ShowModule(plabel_name, 2);
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "����ɾ��ʧ�ܣ�",
				"ȷ��"
			};

			ShowModule(plabel_name, 2);
		}
	}
}

/**
* ��������: Modify_info
* ��������: �޸Ľ����Ϣ.
* �������: int���ͣ�1�����޸�������Ϣ��2�����޸Ļ�����Ϣ��3�����޸���ֲ��Ϣ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void Modify_info(int n)
{
	KIND_NODE *p1 = gp_head, *pd=NULL;
	INF_NODE *pp=NULL, *fp=NULL;
	PLANT_NODE  *pm=NULL, *pf=NULL;

	if (n == 1)
	{
	    char s;
		printf("��������Ҫ�޸ĵ��߲˷�����룺\n");
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
			printf("�������޸���Ϣ��\n\n");
			printf("������룺");
			scanf("%c",&p1->kin_num);
			getchar();
			printf("�������ƣ�");
			scanf("%s",p1->kin_name);
			getchar();

			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
				"ȷ��"
			};

			ShowModule(plabel_name, 2);
		}

		else
		{
			char *plabel_name[] = { "��Ϣ�޸�ʧ�ܣ�",
				"ȷ��"
			};

			ShowModule(plabel_name, 2);
		}
	}
	if (n == 2)
	{
	    int n;
		printf("�������޸ĵ��߲˱�ţ�");
		scanf("%d",&n);
		getchar();
		Seeki(n);
		if (findc != NULL)
		{
			printf("�޸�������Ϣ��\n");
			printf("  1���߲�����\n");
			printf("  2��������\n");
			printf("  3��Ӫ���ɷ�\n");
			int t;
			scanf("%d", &t);
			getchar();
			if (t == 1)
			{
			    char c[10];
				printf("�������޸ĺ���߲����ƣ�");
				scanf("%s",c);
				getchar();
				strcpy(findc->veg_name, c);
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
					"ȷ��"
				};
				ShowModule(plabel_name, 2);
			}
			else if (t == 2)
			{
			    char c;
				printf("�������޸ĺ�ķ����룺");
				scanf("%c",&c);
				getchar();
				findc->kin_num=c;
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
					"ȷ��"
				};
				ShowModule(plabel_name, 2);
			}
			else if (t == 3)
			{
			    char c[50];
				printf("�������޸ĺ��Ӫ���ɷ֣�");
				scanf("%s",c);
				getchar();
				strcpy(findc->nutrition,c);
				ClearScreen();
				ShowMenu();
				char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
					"ȷ��"
				};
				ShowModule(plabel_name, 2);
			}
			else
			{
				printf("��������");
			}
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "��Ϣ�޸�ʧ�ܣ�",
				"ȷ��"
			};
			ShowModule(plabel_name, 2);
		}
	}
	if (n == 3)
	{
		printf("�������޸ĵ��߲˷�����룺");
		char s;
		scanf("%c",&s);
		getchar();
		printf("�������޸ĵ��߲˱�ţ�");
		int n;
		scanf("%d",&n);
		getchar();
		pc = SeekKindNum(s,n);
		if (pc != NULL)
		{
		    int i;
			printf("������Ҫ�޸���Ϣ��%s�еı�ţ�",pc->veg_name);
			scanf("%d",&i);
			getchar();
			Seekp(i);
			if (finds != NULL)
			{
			    int t,s;
			    float f;
			    char c[5];

				printf("�޸�������Ϣ��\n");
				printf("  1����ֲ���\n");
				printf("  2���ջ�����\n");
				printf("  3����ֲ���\n");
				scanf("%d", &t);
				getchar();
				if (t == 1)
				{
					printf("�������޸ĺ����ֲ�����");
					scanf("%d",&s);
					getchar();
					finds->area=s;
					ClearScreen();
					ShowMenu();
					char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
						"ȷ��"
					};
					ShowModule(plabel_name, 2);
				}
				else if (t == 2)
				{
					printf("�������޸ĺ���ջ�������");
					scanf("%f",&f);
					getchar();
					finds->output=f;
					ClearScreen();
					ShowMenu();
					char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
						"ȷ��"
					};
					ShowModule(plabel_name, 2);
				}
				else if (t == 3)
				{
					printf("�������޸ĺ����ֲ��ݣ�");
					scanf("%s", c);
					getchar();
					strcpy(finds->year, c);
					ClearScreen();
					ShowMenu();
					char *plabel_name[] = { "��Ϣ�޸ĳɹ���",
						"ȷ��"
					};
					ShowModule(plabel_name, 2);
				}
				else
				{
					printf("��������");
				}

			}
		}
		else
		{
			ClearScreen();
			ShowMenu();
			char *plabel_name[] = { "��Ϣ�޸�ʧ�ܣ�",
				"ȷ��"
			};
			ShowModule(plabel_name, 2);
		}
	}
}

/**���ݲ�ѯ����**/

/**
* ��������: SeekKindNum
* ��������: �����߲˷�����롢�߲˱�Ų����߲˻�����Ϣ���.
* �������: char kind_num, int veg_num
* �������: ��
* �� �� ֵ: �߲˻�����Ϣ���
*
* ����˵��:
*/
INF_NODE *SeekKindNum(char kind_num, int veg_num)    /*�����߲˷�����롢�߲˱�Ų����߲˻�����Ϣ���*/
{
    KIND_NODE *pkind_node=NULL;
	INF_NODE *pinf_node=NULL;
	PLANT_NODE *pplant_node=NULL;
	int find = 0;

	for (pkind_node = gp_head; pkind_node != NULL; pkind_node = pkind_node->next)
	{  /*����ѭ��������������ÿ������ѧ����Ϣ֧��*/
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
* ��������: Seekk
* ��������: �����߲�������Ϣ.
* �������: �߲˷������
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
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
* ��������: Seeki
* ��������: �����߲˻�����Ϣ
* �������: �߲˻�����Ϣ���
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
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
* ��������: Seekp
* ��������: �����߲���ֲ��Ϣ.
* �������: �߲���ֲ���
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
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
* ��������: SeekIVegName
* ��������: �����߲������Ӵ������߲˻�����Ϣ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void SeekIVegName(void)
{
    int flag=0;
    char c1[10],*c2;
    printf("��������Ҫ���ҵ��߲����������ַ��Ӵ���");
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
                    printf("\n%-10s","�߲˱��");
                    printf("%-15s","�߲�����");
                    printf("%-10s","�������");
                    printf("%-100s\n\n","Ӫ���ɷ�");
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
        printf("\nδ���ҵ���Ӧ�߲ˡ�����\n");
    }
    getchar();
}

/**
* ��������: SeekIKindNut
* ��������: �����߲˷�������Ӫ���ɷֲ����߲˻�����Ϣ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void SeekIKindNut(void)
{
    int flag=0;
    char c1,c2[10],*c3;
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    printf("��������Ҫ��ѯ���߲˵ķ�����룺");
    scanf("%c",&c1);
    getchar();
    printf("\n��������Ҫ��ѯ���߲���������һ��Ӫ���ɷ֣�");
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
                    printf("\n%-10s","�߲˱��");
                    printf("%-15s","�߲�����");
                    printf("%-10s","�������");
                    printf("%-100s\n\n","Ӫ���ɷ�");
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
        printf("\nδ���ҵ���Ӧ�߲ˡ�����\n");
    }

    getchar();
}

/**
* ��������: SeekPNameYear
* ��������: �����߲˲��������Լ���ֲ��ݲ����߲���ֲ��Ϣ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void SeekPNameYear(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp=NULL;
    int flag=0;
    char c1[10],c2[5],*c3;
    printf("������Ҫ��ѯ���߲˵Ĳ������ƣ�");
    scanf("%s",c1);
    getchar();
    printf("������Ҫ��ѯ�߲˵���ֲ��ݣ�");
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
                        printf("\n�߲����ƣ�%s\n\n",pi->veg_name);
                        printf("�߲���ֲ��Ϣ��ţ�%d\n\n",pp->num);
                        printf("�߲˱�ţ�%d\n\n",pp->veg_num);
                        printf("��ֲ�����%d\n\n",pp->area);
                        printf("�ջ�������%f\n\n",pp->output);
                        printf("��ֲ��ݣ�%s\n\n\n",pp->year);
                    }
                }
            }
        }
    }
    if(flag==0)
    {
        printf("\nδ���ҵ���Ӧ�߲ˡ�����\n");
    }
}

/**
* ��������: SeekPVegName
* ��������: �����߲����Ʋ����߲���ֲ��Ϣ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void SeekPVegName(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp;
    int i,flag=0;
    char c1[20];
    printf("������Ҫ��ѯ���߲����ƣ�");
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
                    printf("\n���߲�������ֲ��Ϣ����\n");
                    return;
                }
                flag=1;
                Year(pp);
            }
         }
    }
    if(flag==0)
    {
        printf("\nδ���ҵ���Ӧ�߲ˡ�����\n");
    }
}

/**
* ��������: Year
* ��������: �����������߲���Ϣ
* �������: PLANT_NODE *head
* �� �� ֵ: ��
*
* ����˵��:
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
        printf("\n�߲���ֲ��Ϣ��ţ�%d\n\n",head->num);
        printf("�߲˱�ţ�%d\n\n",head->veg_num);
        printf("��ֲ�����%d\n\n",head->area);
        printf("�ջ�������%f\n\n",head->output);
        printf("��ֲ��ݣ�%s\n\n\n",head->year);
    }
}

/**����ͳ�ƺ���**/

/**
* ��������: Stat_Year_Kind
* ��������: ͳ��ĳ������߲�
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
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
    printf("��������Ҫͳ�Ƶ���ݣ�");
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
    printf("\n%s������߲˵�ͳ�ƽ��Ϊ��\n\n",s);
    for(ps1=ps3;ps1!=NULL;ps1=ps1->next)
    {
        if(flag==0)
        {
            printf("%-15s","�߲˷�������");
            printf("%-20s","�����߲���ֲ�����");
            printf("%-20s\n\n","�����߲��ջ�������");
        }
        flag=1;
        printf("%-15s",ps1->kind_name);
        printf("%-20d",ps1->area);
        printf("%-20f\n\n",ps1->output);
    }
    if(flag==0)
    {
        printf("\nͳ��ʧ�ܣ������������\n");
        getchar();
    }
}

/**
* ��������: Stat_Veg_Year
* ��������: �����������ֹ���Ϊ���������߲�����ͳ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
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

    printf("��������Ҫ��ѯ����ʼ��ݣ�");
    scanf("%s",year1);
    getchar();
    printf("\n��������Ҫ��ѯ����ֹ��ݣ�");
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
        printf("\nͳ��ʧ�ܣ������������\n");
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
    printf("\n%s�굽%s���߲˵�ͳ�ƽ��Ϊ��\n\n",year1,year2);
    printf("%-15s","�߲�����");
    printf("%-15s","�߲˷�������");
    printf("%-20s","���߲���ֲ�����");
    printf("%-20s\n\n","���߲��ջ�������");
    for(ps1=ps3;ps1!=NULL;ps1=ps1->next)
    {
        printf("%-15s",ps1->veg_name);
        printf("%-15s",ps1->kind_name);
        printf("%-20d",ps1->area);
        printf("%-20f\n\n",ps1->output);
    }
}

/**
* ��������: Stat_Kind
* ��������: ͳ��ĳ�����߲˵����е�����
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void Stat_Kind(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    int num,flag=0;
    printf("�����߲���������ͳ�ƽ��Ϊ��\n\n");
    for(pk=gp_head;pk!=NULL;pk=pk->next)
    {
        flag=1;
        num=0;
        pi=pk->inext;
        for(;pi!=NULL;pi=pi->next)
        {
            num++;
        }
        printf("�߲˷������ƣ�%s\n\n",pk->kin_name);
        printf("�������й������߲�%d��\n\n\n",num);
    }
    if(flag==0)
    {
        printf("\nͳ��ʧ��...\n");
        getchar();
    }
}

/**
* ��������: Stat_Nut
* ��������: ͳ�ƺ�ĳ��Ӫ���ɷֵ��߲�
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void Stat_Nut(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    char nut[50],*c;
    int flag=0;

    printf("��������Ҫͳ�Ƶ�Ӫ���ɷ֣�");
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
                printf("�߲����ƣ�%s\n\n",pi->veg_name);
            }
        }
    }
    if(flag==0)
    {
        printf("\nͳ��ʧ�ܣ������������\n");
        getchar();
    }
}

/**
* ��������: Stat_Veg_Inf
* ��������: ͳ��ĳ���߲˻�����Ϣ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void Stat_Veg_Inf(void)
{
    KIND_NODE *pk=NULL;
    INF_NODE *pi=NULL;
    PLANT_NODE *pp=NULL;
    char name[10];
    int flag=0,num=0;

    printf("��������Ҫͳ�Ƶ��߲����ƣ�");
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
    printf("\n���߲˽ṹ�¹���%d���߲���ֲ��Ϣ���ֱ��ǣ�\n\n",num);

    printf("%-5s","���");
    printf("%-10s","�߲˱��");
    printf("%-10s","��ֲ���");
    printf("%-10s","�ջ�����");
    printf("%-10s\n\n","��ֲ���");

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
        printf("\nͳ��ʧ�ܣ�����������ء�����\n");
        getchar();
    }
}
