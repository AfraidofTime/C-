//
// Created by Echo on 2022/12/11.
//

#include "score.h"

//系统登陆模块
void loginMenu(){
    int cont = 0;
    int flag = 0;
    const char count[10]="csu2022";//系统账号
    const char code[10]="2022";//密码
    char tempCount[20]=" ";//初始化
    char tempCode[20]=" ";
    do {
        printf("          ─────────欢迎使用学生成绩管理系统────────          \n");


        printf("              请输入登陆账号:>");
        scanf("%s",tempCount);
        printf("              请输入密码:>");
        scanf("%s",tempCode);
        if ((0 == strcmp(tempCount,count)) && (strcmp(tempCode,code)==0)){//这里使用到strcmp(),返回值有三种情况0,>0,<0
            printf("登陆成功\n");
            flag = 0;
        }else{
            printf("账号或者密码输入错误,请重新输入\n");
            flag = 1;
        }
        cont ++;//记录登陆次数
        //输入次数过多,退出程序

        if ((cont>2)&&flag){
            printf("你已经输错3次,将退出程序\n");
            exit(0);
        }
    }while(flag);
}
void SelectMenu1() {                      		 //打印老师菜单
    printf("\n");
    printf("         ┌─────────欢迎使用体测成绩判定系统────────┐     \n");
    printf("         │                                          \n");
    printf("         │            请选择操作项目：                 \n");
    printf("         │\t1.录入信息          2.修改信息             \n");
    printf("         │\t3.删除信息          4.查询信息             \n");
    printf("         │\t5.信息排序          6.显示信息             \n");
    printf("         │\t7.保存信息          8.统计数据             \n");
    printf("         │\t9.清屏              0.退出系统            \n");
    printf("         └────────────────────────────────────┘     \n");
}
void PrintMenuSort1() {                      		 //打印排序菜单
    printf("\n");
    printf("         ┌──────学生信息排序菜单──────────┐       \n");
    printf("         │                                          \n");
    printf("         │            请选择排序方式                   \n");
    printf("         │\t1.按学号            2.按姓名(拼音)               \n");
    printf("         │\t3.按总分(升序)        6.显示排序后信息              \n");
    printf("         │\t0.将返回                                 \n");
    printf("         └─────────────────────────────┘         \n");
}
void SearchMenu(){
    printf("\n");
    printf("         ┌───────────学生信息查找菜单─────┐       \n");
    printf("         │                                     \n");
    printf("         │            请选择查找方式              \n");
    printf("         │\t1.按学号            2.按姓名          \n");
    printf("         │\t3.按总分数          4.按成绩等级(good/pass...)\n");
    printf("         │\t0.将返回                           \n");
    printf("         └─────────────────────────────┘        \n");
}

int main(){
    int input = 0;
    int input2 = 0;
    int input3 = 0;
    char tmp;
    //创建学生体测成绩数据库score,里面包含 date 指针 和 size,capacity
    struct ScoreLib score;
    //初始化数据库
    InitScoreLib(&score);

    loginMenu();
    do {
        SelectMenu1();
        printf("请选择:>");
        scanf("%d",&input);
        switch (input) {
            case ADD:
                AddScoreLib2(&score);
                break;
            case MODIFY:
                ModifyScoreLib(&score);
                break;
            case DEL:
                DelScoreLib(&score);
                break;
            case SEARCH:
                do{
                    SearchMenu();
                    printf("请选择:>");
                    scanf("%d",&input3);
                    switch(input3){
                        case EXIT2:
                            printf("退出修改模块\n");
                            break;
                        case SEARCH_BY_ID:
                            SearchById(&score);
                            break;
                        case SEARCH_BY_NAME:
                            SearchByName(&score);
                            break;
                        case SEARCH_BY_SCORE:
                            SearchByScore(&score);
                            break;
                        case SEARCH_BY_SCORE_RANK:
                            SearchByScoreRank(&score);
                            break;
                        default:
                            printf("\t\t\t选择错误!!!\n");
                    }
                }while(input3);
                break;
            case SORT:
                do {
                    PrintMenuSort1();
                    printf("请选择:>");
                    scanf("%d",&input2);
                    switch (input2){
                        case SORT_BY_ID:
                            SortById(&score);
                            break;
                        case SORT_BY_NAME:
                            SortByName(&score);
                            break;
                        case SORT_BY_SCORE:
                            SortByScore(&score);
                            break;
                        case GO_TO_SHOW:
                            goto show;
                        case EXIT1:
                            printf("退出排序模块\n");
                            break;
                        default:
                            printf("\t\t\t选择错误!!!\n");
                    }
                }while(input2);
                break;
            case SHOW:
            show:
                ShowScoreLib(&score);
                break;
            case SAVE:
                SaveScoreLib(&score);
                printf("保存成功\n");
                break;
            case STATIC:
                StatisticScore(&score);
                break;
            case CLEAR:
                clear();
                break;
            case EXIT:
                printf("输入 y/n 再次确认是否退出:>");
                scanf(" %c",&tmp);
                if ((tmp == 'y')||(tmp == 'Y')){
                    //销毁数据库-释放动态开辟的内存,销毁前保存
                    SaveScoreLib(&score);
                    DestroyScoreLib(&score);
                    printf("退出程序\n");break;
                }else {
                    input = 1;
                    break;
                }
            default:
                printf("\t\t\t选择错误!!!\n");
        }
    }while (input);
    return 0;
}