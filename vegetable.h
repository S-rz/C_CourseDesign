#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include <time.h>

#ifndef VEGETABLE_H
#define VEGETABLE_H

#define SCR_ROW 25         /*������Ļ����*/
#define SCR_COL 80         /*������Ļ����*/

/*����ͳ����Ϣ�Ľṹ*/
typedef struct stat1{
    char kind_name[15];    /*��������*/
    int area;              /*��ֲ���*/
    float output;          /*�ջ�����*/
    struct stat1 *next;    /*ָ����һ����ָ��*/
}STAT1;

/*����ͳ����Ϣ�Ľṹ*/
typedef struct stat2{
    char veg_name[15];     /*�߲�����*/
    char kind_name[15];    /*��������*/
    int area;              /*��ֲ���*/
    float output;          /*�ջ�����*/
    struct stat2 *next;    /*ָ����һ����ָ��*/
}STAT2;

/*�߲���ֲ��Ϣ��*/
typedef struct plant_node{
    int num;                    /*���*/
    int veg_num;                /*�߲˱��*/
    int area;                   /*��ֲ���*/
    float output;               /*�ջ�����*/
    char year[5];               /*��ֲ���*/
    struct plant_node *next;    /*ָ����һ����ָ��*/
}PLANT_NODE;

/*�߲˻�����Ϣ��*/
typedef struct information_node{
    int veg_num;                        /*�߲˱��*/
    char veg_name[15];                  /*�߲�����*/
    char kin_num;                       /*�������*/
    char nutrition[100];                /*Ӫ���ɷ�*/
    PLANT_NODE *pnext;                  /*ָ����ֲ��Ϣ֧���Ľ��*/
    struct information_node *next;      /*ָ����һ����ָ��*/
}INF_NODE;

/*�߲�������Ϣ��*/
typedef struct kind_node{
    char kin_num;                /*�������*/
    char kin_name[15];           /*��������*/
    INF_NODE *inext;             /*ָ�������Ϣ֧���Ľ��*/
    struct kind_node *next;      /*ָ����һ����ָ��*/
}KIND_NODE;

/*��Ļ������Ϣ�������ṹ*/
typedef struct layer_node {
    char LayerNo;            /*�������ڲ���*/
    SMALL_RECT rcArea;       /*����������������*/
    CHAR_INFO *pContent;     /*�������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;           /*�������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next; /*ָ����һ����ָ��*/
} LAYER_NODE;

/*��ǩ���ṹ*/
typedef struct labe1_bundle {
    char **ppLabel;           /*��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;              /*��ǩ��λ�����׵�ַ*/
    int num;                  /*��ǩ����*/
} LABEL_BUNDLE;

/*�����ṹ*/
typedef struct hot_area {
    SMALL_RECT *pArea;     /*������λ�����׵�ַ*/
    char *pSort;           /*�������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;            /*������������׵�ַ*/
    int num;               /*��������*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;          /*����������Ϣ����ͷ*/
KIND_NODE *gp_head = NULL;                /*����ͷָ��*/

/*������ⲿ�����������޸ġ�ɾ������ѯ�ȵ�*/
KIND_NODE *findt, *pt;
INF_NODE *findc, *pc;
PLANT_NODE *finds, *ps;


char *gp_sys_name = "��ũ��ֲ��Ϣ����ϵͳ";              /*ϵͳ����*/
char *gp_kind_info_filename = "kind.dat";                /*�߲���ֲ��Ϣ�����ļ�*/
char *gp_information_info_filename = "information.dat";  /*�߲˻�����Ϣ�����ļ�*/
char *gp_plant_info_filename = "plant.dat";              /*��ũ��ֲ��Ϣ�����ļ�*/

/**���ݱ����ļ�**/
char *gp_kind_back_filename = "backupkind.dat";
char *gp_information_back_filename = "backupinformation.dat";
char *gp_plant_back_filename = "backupplant.dat";

/**ϵͳ���˵���**/
char *ga_main_menu[] = {"�ļ�(F)",
    	                "����ά��(M)",
                        "���ݲ�ѯ(Q)",
                        "����ͳ��(S)",
                        "����(H)"
                       };
/**ϵͳ�Ӳ˵���**/
char *ga_sub_menu[] = {"[S] ���ݱ���",
                       "[B] ���ݱ���",
                       "[R] ���ݻָ�",
                       "[X] �˳�    Alt+X",

                       "[K] �߲�������Ϣ",
                       "",                   /*�մ������ڵ����˵��зָ��Ӳ˵����ͬ*/
                       "[I] �߲˻�����Ϣ",
                       "",
                       "[P] ��ũ��ֲ��Ϣ",

                       "[K] �߲�������Ϣ",
                       "",
                       "[I] �߲˻�����Ϣ",
                       "",
                       "[P] ��ũ��ֲ��Ϣ",

                       "[Y] ĳ������߲����",
                       "[N] ĳ�����߲����",
                       "[k] �����߲������������",
                       "[I] Ӫ���ɷ����",
                       "[A] ĳ�߲˵���ֲ���",

                       "[T] ��������",
                       "",
                       "[A] ����...",
                       "",
                       "[B] ��Ȩ˵��"
                      };

int ga_sub_menu_count[] = {4, 5, 5, 5, 5};  /*�����˵������Ӳ˵��ĸ���*/
int gi_sel_menu = 1;                        /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

char *gp_scr_att = NULL;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/
char gc_sys_state = '\0';   /*��������ϵͳ״̬���ַ�*/

HANDLE gh_std_out;          /*��׼����豸���*/
HANDLE gh_std_in;           /*��׼�����豸���*/

void Welcome();                                 /*��ӭ����*/
int LoadCode(char *filename, char **ppbuffer);  /*��������*/
int CreatList(KIND_NODE **pphead);              /*���������ʼ��*/
void InitInterface(void);                       /*ϵͳ�����ʼ��*/
void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
void PopPrompt(int num);                        /*��ʾ��������*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/
void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(KIND_NODE **pphd);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(KIND_NODE *phd);                  /*�˳�ϵͳ*/

/**ϵͳ�ļ�ģ��**/
BOOL LoadData(void);           /*���ݼ���*/
BOOL SaveData(void);           /*���ݱ���*/
BOOL BackupData(void);         /*���ݱ���*/
BOOL RestoreData(void);        /*���ݻָ�*/
BOOL ExitSys(void);            /*�˳�ϵͳ*/

/**����ά��ģ��**/
BOOL MaintainKindInfo(void);   /*ά���߲�������Ϣ*/
BOOL MaintainInfInfo(void);    /*ά���߲˻�����Ϣ*/
BOOL MaintainPlantInfo(void);  /*ά���߲���ֲ��Ϣ*/

/**���ݲ�ѯģ��**/
BOOL QueryKindInfo(void);      /*��ѯ�߲�������Ϣ*/
BOOL QueryInfInfo(void);       /*��ѯ�߲˻�����Ϣ*/
BOOL QueryPlantInfo(void);     /*��ѯ�߲���ֲ��Ϣ*/

/**����ͳ��ģ��**/
BOOL StatYearKind(void);       /*ĳ������߲�ͳ��*/
BOOL StatVegYear(void);        /*��ֹ���߲�ͳ��*/
BOOL StatKind(void);           /*ĳ���߲�����ͳ��*/
BOOL StatVegNut(void);         /*Ӫ���ɷ��߲�ͳ��*/
BOOL StatVegInf(void);         /*�߲˻�����Ϣͳ��*/

/**������Ϣģ��**/
BOOL HelpTopic(void);          /*��������*/
BOOL AboutVegetableSys(void);  /*����ϵͳ*/
BOOL AboutCopyright(void);     /*��Ȩ˵��*/


BOOL SaveSysData(KIND_NODE *phd);       /*����ϵͳ����*/
BOOL BackupSysData(KIND_NODE *phd);     /*����ϵͳ����*/
BOOL RestoreSysData(KIND_NODE **pphd);  /*�ָ�ϵͳ����*/
void Insert(int n);                          /*���ݲ���*/
void Dele_info(int n);                       /*����ɾ��*/
void Modify_info(int n);                     /*�����޸�*/

/*���ݲ���*/
void* Seekk(char s);               /*�����߲�������Ϣ����*/
void* Seeki(int n);                /*�����߲˻�����Ϣ����*/
void* Seekp(int n);                /*�����߲���ֲ��Ϣ����*/

INF_NODE *SeekKindNum(char kind_num, int veg_num);   /*�����߲˷�����롢�߲˱�Ų����߲˻�����Ϣ���*/
void SeekIVegName(void);                             /*�����߲������Ӵ������߲˻�����Ϣ*/
void SeekIKindNut(void);                             /*�����߲˷�������Ӫ���ɷֲ����߲˻�����Ϣ*/
void SeekPNameYear(void);                            /*�����߲˲��������Լ���ֲ��ݲ����߲���ֲ��Ϣ*/
void SeekPVegName(void);                             /*�����߲����Ʋ����߲���ֲ��Ϣ*/
void Year(PLANT_NODE *head);                         /*�����������߲���Ϣ*/

void Stat_Year_Kind(void);        /*ͳ��ĳ������߲�*/
void Stat_Veg_Year(void);         /*�����������ֹ���Ϊ���������߲�����ͳ��*/
void Stat_Kind(void);             /*ͳ��ĳ�����߲˵����е�����*/
void Stat_Nut(void);              /*ͳ�ƺ�ĳ��Ӫ���ɷֵ��߲�*/
void Stat_Veg_Inf(void);          /*ͳ��ĳ���߲˻�����Ϣ*/

#endif // VEGETABLE_H_INCLUDED1
