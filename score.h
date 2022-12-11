//
// Created by Echo on 2022/12/11.
//

#define MAX_ID 14
#define MAX_NAME 20
#define MAX_SEX 10
#define DEFAULT_SIZE 20 //默认空间大小

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//使用枚举使switch语句更容易被他人理解
enum Option1{
    EXIT,
    ADD,
    MODIFY,
    DEL,
    SEARCH,
    SORT,
    SHOW,
    SAVE,
    STATIC,
    CLEAR
};
enum Option2{
    EXIT1,
    SORT_BY_ID,
    SORT_BY_NAME,
    SORT_BY_SCORE,
    GO_TO_SHOW
};
enum Option3{
    EXIT2,
    SEARCH_BY_ID ,
    SEARCH_BY_NAME,
    SEARCH_BY_SCORE,
    SEARCH_BY_SCORE_RANK
};
//定义学生信息类型 struct StuInfo
struct StuInfo{
    char id[MAX_ID];
    char name[MAX_NAME];
    char sex[MAX_SEX];
    float bim;
    int vcp;
    int PullSit;
    float Score;
    int BimScore;
    int VcpScore;
    int PullSitScore;
    char ScoreRank[10];
};


//定义体育成绩数据库 struct Scorelib
struct ScoreLib{
    struct StuInfo* data;//存放学生信息
    int capacity;//当前数据库的最大容量
    int size;//记录当前学生人数
};
//声明函数
//初始化数据库lib
void InitScoreLib(struct ScoreLib* ps);
void AddScoreLib2(struct ScoreLib* ps);
void ShowScoreLib(const struct ScoreLib* ps);
void DelScoreLib(struct ScoreLib* ps);

void SearchByScore(const struct ScoreLib* ps);
void SearchByScoreRank(const struct ScoreLib* ps);
//修改学生体育成绩
void ModifyScoreLib(struct ScoreLib* ps);
//对信息库中的成绩进行排序
void SortByScore(struct ScoreLib* ps);
//对学号进行排序
void SortById(struct ScoreLib* ps);
//对姓名进行排序
void SortByName(struct ScoreLib* ps);

void StatisticScore(const struct ScoreLib* ps);
//销毁数据库-释放动态开辟的内存
void DestroyScoreLib(struct ScoreLib* ps);
//保存信息
void SaveScoreLib(struct ScoreLib* ps);
//加载文件中的信息到数据库
void LoadScoreLib(struct ScoreLib* ps);
//清屏
void clear();
void SearchById(const struct ScoreLib* ps);
void SearchByName(const struct ScoreLib* ps);
void SearchByScore(const struct ScoreLib* ps);





