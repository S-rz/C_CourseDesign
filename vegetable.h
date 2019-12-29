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

#define SCR_ROW 25         /*设置屏幕行数*/
#define SCR_COL 80         /*设置屏幕列数*/

/*便于统计信息的结构*/
typedef struct stat1{
    char kind_name[15];    /*分类名称*/
    int area;              /*种植面积*/
    float output;          /*收获重量*/
    struct stat1 *next;    /*指向下一结点的指针*/
}STAT1;

/*便于统计信息的结构*/
typedef struct stat2{
    char veg_name[15];     /*蔬菜名称*/
    char kind_name[15];    /*分类名称*/
    int area;              /*种植面积*/
    float output;          /*收获重量*/
    struct stat2 *next;    /*指向下一结点的指针*/
}STAT2;

/*蔬菜种植信息表*/
typedef struct plant_node{
    int num;                    /*编号*/
    int veg_num;                /*蔬菜编号*/
    int area;                   /*种植面积*/
    float output;               /*收获重量*/
    char year[5];               /*种植年份*/
    struct plant_node *next;    /*指向下一结点的指针*/
}PLANT_NODE;

/*蔬菜基本信息表*/
typedef struct information_node{
    int veg_num;                        /*蔬菜编号*/
    char veg_name[15];                  /*蔬菜名称*/
    char kin_num;                       /*分类编码*/
    char nutrition[100];                /*营养成分*/
    PLANT_NODE *pnext;                  /*指向种植信息支链的结点*/
    struct information_node *next;      /*指向下一结点的指针*/
}INF_NODE;

/*蔬菜种类信息表*/
typedef struct kind_node{
    char kin_num;                /*分类编码*/
    char kin_name[15];           /*分类名称*/
    INF_NODE *inext;             /*指向基本信息支链的结点*/
    struct kind_node *next;      /*指向下一结点的指针*/
}KIND_NODE;

/*屏幕窗口信息链结点结点结构*/
typedef struct layer_node {
    char LayerNo;            /*弹出窗口层数*/
    SMALL_RECT rcArea;       /*弹出窗口区域坐标*/
    CHAR_INFO *pContent;     /*弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;           /*弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next; /*指向下一结点的指针*/
} LAYER_NODE;

/*标签束结构*/
typedef struct labe1_bundle {
    char **ppLabel;           /*标签字符串数组首地址*/
    COORD *pLoc;              /*标签定位数组首地址*/
    int num;                  /*标签个数*/
} LABEL_BUNDLE;

/*热区结构*/
typedef struct hot_area {
    SMALL_RECT *pArea;     /*热区定位数组首地址*/
    char *pSort;           /*热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;            /*热区序号数组首地址*/
    int num;               /*热区个数*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;          /*弹出窗口信息链链头*/
KIND_NODE *gp_head = NULL;                /*主链头指针*/

/*定义的外部变量，用于修改、删除、查询等等*/
KIND_NODE *findt, *pt;
INF_NODE *findc, *pc;
PLANT_NODE *finds, *ps;


char *gp_sys_name = "菜农种植信息管理系统";              /*系统名称*/
char *gp_kind_info_filename = "kind.dat";                /*蔬菜种植信息数据文件*/
char *gp_information_info_filename = "information.dat";  /*蔬菜基本信息数据文件*/
char *gp_plant_info_filename = "plant.dat";              /*菜农种植信息数据文件*/

/**数据备份文件**/
char *gp_kind_back_filename = "backupkind.dat";
char *gp_information_back_filename = "backupinformation.dat";
char *gp_plant_back_filename = "backupplant.dat";

/**系统主菜单名**/
char *ga_main_menu[] = {"文件(F)",
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计(S)",
                        "帮助(H)"
                       };
/**系统子菜单名**/
char *ga_sub_menu[] = {"[S] 数据保存",
                       "[B] 数据备份",
                       "[R] 数据恢复",
                       "[X] 退出    Alt+X",

                       "[K] 蔬菜种类信息",
                       "",                   /*空串用来在弹出菜单中分隔子菜单项，下同*/
                       "[I] 蔬菜基本信息",
                       "",
                       "[P] 菜农种植信息",

                       "[K] 蔬菜种类信息",
                       "",
                       "[I] 蔬菜基本信息",
                       "",
                       "[P] 菜农种植信息",

                       "[Y] 某年各类蔬菜情况",
                       "[N] 某几年蔬菜情况",
                       "[k] 各类蔬菜已有数量情况",
                       "[I] 营养成分情况",
                       "[A] 某蔬菜的种植情况",

                       "[T] 帮助主题",
                       "",
                       "[A] 关于...",
                       "",
                       "[B] 版权说明"
                      };

int ga_sub_menu_count[] = {4, 5, 5, 5, 5};  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/

HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/

void Welcome();                                 /*欢迎界面*/
int LoadCode(char *filename, char **ppbuffer);  /*代码表加载*/
int CreatList(KIND_NODE **pphead);              /*数据链表初始化*/
void InitInterface(void);                       /*系统界面初始化*/
void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopPrompt(int num);                        /*显示弹出窗口*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/
void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
void RunSys(KIND_NODE **pphd);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(KIND_NODE *phd);                  /*退出系统*/

/**系统文件模块**/
BOOL LoadData(void);           /*数据加载*/
BOOL SaveData(void);           /*数据保存*/
BOOL BackupData(void);         /*数据备份*/
BOOL RestoreData(void);        /*数据恢复*/
BOOL ExitSys(void);            /*退出系统*/

/**数据维护模块**/
BOOL MaintainKindInfo(void);   /*维护蔬菜种类信息*/
BOOL MaintainInfInfo(void);    /*维护蔬菜基本信息*/
BOOL MaintainPlantInfo(void);  /*维护蔬菜种植信息*/

/**数据查询模块**/
BOOL QueryKindInfo(void);      /*查询蔬菜种类信息*/
BOOL QueryInfInfo(void);       /*查询蔬菜基本信息*/
BOOL QueryPlantInfo(void);     /*查询蔬菜种植信息*/

/**数据统计模块**/
BOOL StatYearKind(void);       /*某年各类蔬菜统计*/
BOOL StatVegYear(void);        /*起止年蔬菜统计*/
BOOL StatKind(void);           /*某种蔬菜数量统计*/
BOOL StatVegNut(void);         /*营养成分蔬菜统计*/
BOOL StatVegInf(void);         /*蔬菜基本信息统计*/

/**帮助信息模块**/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL AboutVegetableSys(void);  /*关于系统*/
BOOL AboutCopyright(void);     /*版权说明*/


BOOL SaveSysData(KIND_NODE *phd);       /*保存系统数据*/
BOOL BackupSysData(KIND_NODE *phd);     /*备份系统数据*/
BOOL RestoreSysData(KIND_NODE **pphd);  /*恢复系统数据*/
void Insert(int n);                          /*数据插入*/
void Dele_info(int n);                       /*数据删除*/
void Modify_info(int n);                     /*数据修改*/

/*数据查找*/
void* Seekk(char s);               /*查找蔬菜种类信息函数*/
void* Seeki(int n);                /*查找蔬菜基本信息函数*/
void* Seekp(int n);                /*查找蔬菜种植信息函数*/

INF_NODE *SeekKindNum(char kind_num, int veg_num);   /*按照蔬菜分类编码、蔬菜编号查找蔬菜基本信息结点*/
void SeekIVegName(void);                             /*按照蔬菜名称子串查找蔬菜基本信息*/
void SeekIKindNut(void);                             /*按照蔬菜分类编码和营养成分查找蔬菜基本信息*/
void SeekPNameYear(void);                            /*按照蔬菜部分名称以及种植年份查找蔬菜种植信息*/
void SeekPVegName(void);                             /*按照蔬菜名称查找蔬菜种植信息*/
void Year(PLANT_NODE *head);                         /*按照年份输出蔬菜信息*/

void Stat_Year_Kind(void);        /*统计某年各类蔬菜*/
void Stat_Veg_Year(void);         /*以所输入的起止年份为条件，按蔬菜名称统计*/
void Stat_Kind(void);             /*统计某种类蔬菜的已有的数量*/
void Stat_Nut(void);              /*统计含某种营养成分的蔬菜*/
void Stat_Veg_Inf(void);          /*统计某种蔬菜基本信息*/

#endif // VEGETABLE_H_INCLUDED1
