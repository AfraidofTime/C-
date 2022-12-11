//
// Created by Echo on 2022/12/11.
//
#include "score.h"

static int FindById(const struct ScoreLib* ps,char id[]){
    for (int i = 0; i < ps->size; ++i) {
        if(0==strcmp(ps->data[i].id,id)){
            return i;
        }
    }
    return -1;//如果找不到返回-1
}
static int FindByName(const struct ScoreLib* ps,char name[]){
    for (int i = 0; i < ps->size; ++i) {
        if(0==strcmp(ps->data[i].name,name)){
            return i;
        }
    }
    return -1;//如果找不到返回-1
}

void CheckCapacity(struct ScoreLib* ps) {
    if(ps->size == ps->capacity){
        //增容
        struct StuInfo* ptr = realloc(ps->data,(ps->capacity+2)*sizeof(struct StuInfo));
        if(ptr != NULL){
            ps->data = ptr;
            ps->capacity += 10;
            printf("增容成功\n");
        }
        else{
            printf("增容失败\n");
        }
    }
}

void InitScoreLib(struct ScoreLib* ps){
    ps->data = (struct StuInfo*)malloc(DEFAULT_SIZE*sizeof(struct StuInfo));
    if (ps->data == NULL){
        return;
    }
    ps->size = 0;
    ps->capacity = DEFAULT_SIZE;
    //把文件已经存放的信息加载到数据库中struct ScoreLib score中
    LoadScoreLib(ps);
}

void LoadScoreLib(struct ScoreLib* ps){
    struct StuInfo tmp = {0};
    FILE* pfRead = fopen("ScoreLib.dat","rb");
    if(pfRead == NULL){
        printf("LoadScoreLib::%s\n",strerror(errno));
        return;
    }
    //读取文件，存放到数据库中

    while(fread(&tmp, sizeof(struct StuInfo),1,pfRead)){
        CheckCapacity(ps);
        ps->data[ps->size] = tmp;
        ps->size++;
    }

    fclose(pfRead);
    pfRead = NULL;
}

//计算学生体育成绩
static void AddScoreLib1(struct ScoreLib* ps){
    if(((ps->data[ps->size].bim)<17.9)) {
        ps->data[ps->size].BimScore = 80;
    }if((ps->data[ps->size].bim>=17.9)&&((ps->data[ps->size].bim)<=23.9)){
        ps->data[ps->size].BimScore = 100;
    }if((ps->data[ps->size].bim>23.9)&&(ps->data[ps->size].bim<=27.9)){
        ps->data[ps->size].BimScore = 80;
    }if(ps->data[ps->size].bim>27.9){
        ps->data[ps->size].BimScore = 60;
    }if(ps->data[ps->size].bim<=0){
        ps->data[ps->size].BimScore = 30;
    }

    if ( 0 == strcmp(ps->data[ps->size].sex,"男")){
        if(ps->data[ps->size].vcp<=3100){
            ps->data[ps->size].VcpScore = 30;
        }if((ps->data[ps->size].vcp>=3101)&&(ps->data[ps->size].vcp<=4180)){
            ps->data[ps->size].VcpScore = 60;
        }if((ps->data[ps->size].vcp>=4181)&&(ps->data[ps->size].vcp<=4800)){
            ps->data[ps->size].VcpScore = 80;
        }if(ps->data[ps->size].vcp>4800){
            ps->data[ps->size].VcpScore = 100;
        }

        if(ps->data[ps->size].PullSit<=9){
            ps->data[ps->size].PullSitScore = 30;
        }if((ps->data[ps->size].PullSit>=10)&&(ps->data[ps->size].PullSit<=15)){
            ps->data[ps->size].PullSitScore = 60;
        }if((ps->data[ps->size].PullSit>=16)&&(ps->data[ps->size].PullSit<=19)){
            ps->data[ps->size].PullSitScore = 80;
        }if(ps->data[ps->size].PullSit>19) {
            ps->data[ps->size].PullSitScore = 100;
        }
    }

    if ( 0 == strcmp(ps->data[ps->size].sex,"女")) {
        if (ps->data[ps->size].vcp <= 2050) {
            ps->data[ps->size].VcpScore = 30;
        }
        if ((ps->data[ps->size].vcp >= 2051) && (ps->data[ps->size].vcp <= 3000)) {
            ps->data[ps->size].VcpScore = 60;
        }
        if ((ps->data[ps->size].vcp >= 3001) && (ps->data[ps->size].vcp <= 3400)) {
            ps->data[ps->size].VcpScore = 80;
        }
        if (ps->data[ps->size].vcp > 3400) {
            ps->data[ps->size].VcpScore = 100;
        }

        if (ps->data[ps->size].PullSit <= 24) {
            ps->data[ps->size].PullSitScore = 30;
        }
        if ((ps->data[ps->size].PullSit >= 25) && (ps->data[ps->size].PullSit <= 52)) {
            ps->data[ps->size].PullSitScore = 60;
        }
        if ((ps->data[ps->size].PullSit >= 53) && (ps->data[ps->size].PullSit <= 56)) {
            ps->data[ps->size].PullSitScore = 80;
        }
        if (ps->data[ps->size].PullSit > 56){
            ps->data[ps->size].PullSitScore = 100;
        }
    }

    ps->data[ps->size].Score = ps->data[ps->size].BimScore*0.25f+
                               ps->data[ps->size].VcpScore*0.35f+
                               ps->data[ps->size].PullSitScore*0.4f;
    if(ps->data[ps->size].Score<60){
        strcpy(ps->data[ps->size].ScoreRank,"fail");
    }if((ps->data[ps->size].Score>=60)&&(ps->data[ps->size].Score<=79)){
        strcpy(ps->data[ps->size].ScoreRank,"pass");
    }if((ps->data[ps->size].Score>=80)&&(ps->data[ps->size].Score<=94)){
        strcpy(ps->data[ps->size].ScoreRank,"good");
    }if(ps->data[ps->size].Score>=95)
        strcpy(ps->data[ps->size].ScoreRank,"excellent");
    ps->size++;
    printf("学生体测信息添加成功\n");
}

void AddScoreLib2(struct ScoreLib* ps) {
    //判断是否存在该学号
    char id[MAX_ID];
    printf("请输入学号:>");
    scanf("%s",id);
    int flag = FindById(ps,id);
    if (flag == -1){
        //检测数据库的容量
        //如果满了就增容，如果不满，不作操作
        CheckCapacity(ps);
        strcpy(ps->data[ps->size].id,id);
        printf("请输入名字:>");
        scanf("%s", ps->data[ps->size].name);
        printf("请输入性别(男/ 女):>");
        scanf(" %s", ps->data[ps->size].sex);
        printf("请输入BIM:>");
        scanf("%f", &(ps->data[ps->size].bim));
        printf("请输入肺活量:>");
        scanf("%d", &(ps->data[ps->size].vcp));
        printf("请输入引体向上或仰卧起坐数:>");
        scanf("%d", &(ps->data[ps->size].PullSit));
        AddScoreLib1(ps);
    }else{
        printf("该学号已存在\n");
    }
}


//打印学生体育成绩
void ShowScoreLib(const struct ScoreLib* ps){
    if (ps->size ==0){
        printf("成绩单为空\n");
    }
    else{
        printf("---------------------------------------学生体测成绩单-------------------------------------------------------\n");
        printf("%10s|\t%8s|\t%5s|\t%5s|\t%6s|\t%9s|\t%9s|\t%9s|\t%5s\n",
                       "学号","名字","性别","BIM","肺活量","引体向上","仰卧起坐","成绩","分数");
        printf("----------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < ps->size; ++i) {
            if (0== strcmp(ps->data[i].sex,"男")){
                printf("%10s|\t%8s|\t%5s|\t%5.1f|\t%6d|\t%9d|\t%9s|\t%9s|\t%5.1f\n"
                       "----------------------------------------------------------------------------------------------------------\n",
                       ps->data[i].id,
                       ps->data[i].name,
                       ps->data[i].sex,
                       ps->data[i].bim,
                       ps->data[i].vcp,
                       ps->data[i].PullSit,
                       "\\",
                       ps->data[i].ScoreRank,
                       ps->data[i].Score);
            }else{
                printf("%10s|\t%8s|\t%5s|\t%5.1f|\t%6d|\t%9s|\t%9d|\t%9s|\t%5.1f\n"
                       "------------------------------------------------------------------------------------------------------------\n",
                       ps->data[i].id,
                       ps->data[i].name,
                       ps->data[i].sex,
                       ps->data[i].bim,
                       ps->data[i].vcp,
                       "\\",
                       ps->data[i].PullSit,
                       ps->data[i].ScoreRank,
                       ps->data[i].Score);
            }
        }
    }
}
//查找学号,static使该函数只能在该文件内部使用，改变了函数的作用域

//根据学号删除
void DelScoreLib(struct ScoreLib* ps) {
    char id[MAX_ID];
    char tmp;
    printf("请输入要删除人的学号:>");
    scanf("%s",id);
    //查找删除人的位置
    //找到了返回id所在下标
    int pos = FindById(ps,id);
    //删除元素
    if  (pos == -1){
        printf("要删除的人不存在\n");
    }else{
        printf("输入 y/n 再次确认:>");
        scanf(" %c", &tmp);
        if (('y' == tmp) || ('Y' == tmp)){
            for (int j = pos; j < ps->size-1; ++j) {
                ps->data[j] = ps->data[j+1];
            }
            ps->size--;
            printf("删除成功\n");
        }
    }
}
static void print(const struct ScoreLib* ps, int pos) {
    if (-1 == pos) {
        printf("要查找的人不存在\n");
    } else {
        printf("%10s|\t%10s|\t%6s|\t%10.1f|\t%8d|\t%10d|\t%10s|\t%10.1f\n",
               ps->data[pos].id,
               ps->data[pos].name,
               ps->data[pos].sex,
               ps->data[pos].bim,
               ps->data[pos].vcp,
               ps->data[pos].PullSit,
               ps->data[pos].ScoreRank,
               ps->data[pos].Score);
    }
}
void SearchById(const struct ScoreLib* ps){
    char id[MAX_ID];
    char cmd;
    int pos = 0;
    printf("请输入需要查找的学号:>");
    scanf("%s",id);
    pos = FindById(ps,id);
    if(-1!= pos){
        printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s\n",
               "学号", "名字", "性别", "BIM", "肺活量", "引体或仰卧", "成绩");
        print(ps,pos);
    }else{
        printf("该同学信息未录入\n");
    }

}

void SearchByName(const struct ScoreLib* ps){
    char name[MAX_NAME];
    char cmd;
    int pos = 0;
    printf("请输入需要查找的名字:>");
    scanf("%s",name);

    pos = FindByName(ps,name);
    if (-1 != pos){
        printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s|\t%10s\n",
               "学号", "名字", "性别", "BIM", "肺活量", "引体或仰卧", "成绩","分数");
        print(ps,pos);
    }else{
        printf("该同学信息未录入\n");
    }
}
//按成绩等级(pass/good...)搜索
void SearchByScoreRank(const struct ScoreLib* ps){
    char score[10];
    int cnt=0;
    printf("请输入需要查找人的成绩等级(psss/ good...):>");
    scanf("%s",score);

    printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s|\t%10s\n",
           "学号", "名字", "性别", "BIM", "肺活量", "引体或仰卧", "成绩","分数");
    for (int i = 0; i < ps->size; ++i) {
        if(0==strcmp(ps->data[i].ScoreRank,score)){
            print(ps,i);
            cnt++;
        }
    }
    printf("搜索完成，有%d个学生符合要求\n",cnt);
}
// 按成绩(分数)排序
void SearchByScore(const struct ScoreLib* ps){
    float score = 0.0f;
    int pos[ps->size];
    int cnt =0;//记录下符合条件的学生在数据库中的下标
    printf("请输入需要查找人的分数:>");
    scanf("%f",&score);
    for (int i = 0; i < ps->size; ++i) {
        if(score == ps->data[i].Score){
            pos[cnt] = i;
            cnt++;
        }
    }
    if(cnt==0){
        printf("没有分数为%.1f的学生,请重新查找\n",score);
    }else{
        printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s|\t%10s\n",
               "学号", "名字", "性别", "BIM", "肺活量", "引体或仰卧", "成绩","分数");
        for (int i = 0; i < cnt; ++i) {
            print(ps,pos[i]);
        }
        printf("搜索完成,有%d个学生符合要求\n",cnt);
    }
};
void ModifyScoreLib(struct ScoreLib* ps){
    char id[MAX_ID];
    char tmp;
    printf("请输入被修改人的学号id:>");
    scanf("%s",id);
    int pos = FindById(ps,id);
    if (pos == -1){
        printf("要修改人的信息不存在\n");
    }else {
        printf("输入 y/n 再次确认:>");
        scanf(" %c", &tmp);
        if (('y' == tmp) || ('Y' == tmp)) {
            printf("请输入学号:>");
            scanf("%s", ps->data[pos].id);
            printf("请输入名字:>");
            scanf("%s", ps->data[pos].name);
            printf("请输入性别(男/ 女):>");
            scanf(" %s", ps->data[pos].sex);
            printf("请输入BIM:>");
            scanf("%f", &(ps->data[pos].bim));
            printf("请输入肺活量:>");
            scanf("%d", &(ps->data[pos].vcp));
            printf("请输入引体向上或仰卧起坐数:>");
            scanf("%d", &(ps->data[pos].PullSit));

            printf("修改完成\n");
        } else {
            printf("修改失败\n");
        }
    }
}

void SortByScore(struct ScoreLib* ps){
    struct StuInfo tmp;
    for (int j = 0; j < ps->size-1; ++j) {
        for (int i = 0; i < ps->size-1-j; ++i) {
            if(ps->data[i].Score < ps->data[i+1].Score){
                tmp = ps->data[i];
                ps->data[i] = ps->data[i+1];
                ps->data[i+1] = tmp;
            }
        }
    }
    printf("分数排序已完成\n");
}

static int cmpid1(const void* a, const void* b){
    struct StuInfo* ps1 = (struct StuInfo*)a;
    struct StuInfo* ps2 = (struct StuInfo*)b;
    if(strcmp(ps1->id, ps2->id) != 0){
        return strcmp(ps1->id , ps2->id);
    }
}
static int cmpid2(const void* a, const void* b){
    struct StuInfo* ps1 = (struct StuInfo*)a;
    struct StuInfo* ps2 = (struct StuInfo*)b;
    if(strcmp(ps1->name, ps2->name) != 0){
        return strcmp(ps1->name , ps2->name);
    }
}

//按学号排序
void SortById(struct ScoreLib* ps){
    qsort(ps->data,ps->size,sizeof(struct StuInfo), cmpid1);
    printf("学号排序完成\n");
}
//按姓名排序
void SortByName(struct ScoreLib* ps){
    qsort(ps->data,ps->size,sizeof(struct StuInfo), cmpid2);
    printf("名字排序完成\n");
}
//统计功能
void StatisticScore(const struct ScoreLib* ps){//返回bim数据最大\小\平均值
    int ContMale=0,ContFemale=0;
    float arr[3][3]={0};
    float start=0.0f;float end=0.0f;

    float max = 0;
    float min = 0;
    float aver = 0;
    float sum = 0;
    int SumStu = 0;
    int pos[ps->size];//记录符合要求的下标
    //2.统计总成绩在不同分数段男女生人数,打印数据
    printf("输入统计的分数段起点:>");
    scanf("%f",&start);
    printf("输入统计的分数段结尾:>");
    scanf("%f",&end);

    for (int i = 0; i < ps->size; ++i) {
        if(0 == strcmp(ps->data[i].sex,"男")){
            if((ps->data[i].Score>=start)&&(ps->data[i].Score<=end)){
                ContMale++;
                pos[ContFemale+ContMale-1]=i;
            }
        }if(0 == strcmp(ps->data[i].sex,"女")){
            if((ps->data[i].Score>=start)&&(ps->data[i].Score<=end)){
                ContFemale++;
                pos[ContFemale+ContMale-1]=i;
            }
        }
    }
    //符合要求的人数
    SumStu = ContMale+ ContFemale;
    if(SumStu>=1){
        //bmi max
        max = ps->data[pos[0]].bim;
        for (int i = 1; i < SumStu; ++i) {
            if (max < ps->data[pos[i]].bim) {
                max = ps->data[pos[i]].bim;
            }
        }
        arr[0][0] = max;
        //bmi min
        min = ps->data[pos[0]].bim;
        for (int i = 1; i < SumStu; ++i) {
            if (min > ps->data[pos[i]].bim) {
                min = ps->data[pos[i]].bim;
            }
        }
        arr[0][1] = min;
        //bmi 均值
        for (int i = 0; i < SumStu; ++i) {
            sum += ps->data[pos[i]].bim;
        }aver = sum / (float)SumStu;
        arr[0][2] = aver;

        //vcp max
        sum = 0;
        max = ps->data[pos[0]].vcp;
        for (int i = 1; i < SumStu; ++i) {
            if (max < ps->data[pos[i]].vcp) {
                max = ps->data[pos[i]].vcp;
            }
        }arr[1][0] = max;
        //vcp min
        min = ps->data[pos[0]].vcp;
        for (int i = 1; i < ps->size; ++i) {
            if (min > ps->data[pos[i]].vcp) {
                min = ps->data[pos[i]].vcp;
            }
        }arr[1][1] = min;
        //vcp 均值
        for (int i = 0; i < SumStu; ++i) {
            sum += ps->data[pos[i]].vcp;
        }aver = sum / (float)SumStu;
        arr[1][2] = aver;

        //PullSit max
        sum = 0;
        max = ps->data[pos[0]].PullSit;
        for (int i = 1; i < SumStu; ++i) {
            if (max < ps->data[pos[i]].PullSit) {
                max = ps->data[pos[i]].PullSit;
            }
        }arr[2][0] = max;
        //PullSit min
        min = ps->data[pos[0]].PullSit;
        for (int i = 1; i < SumStu; ++i) {
            if (min > ps->data[pos[i]].PullSit) {
                min = ps->data[pos[i]].PullSit;
            }
        }arr[2][1] = min;
        //PullSit 均值
        for (int i = 0; i < SumStu; ++i) {
            sum += ps->data[pos[i]].PullSit;
        }aver = sum / (float)SumStu;
        arr[2][2] = aver;

        printf("--------以下是总分数在%.1f~%.1f的统计表--------\n",start,end);
        printf("\t男生人数|\t女生人数|\n");
        printf("\t%d人\t\t%d人  \n",ContMale,ContFemale);
        printf("-------------------------------------------------\n");

        printf("\t%8s|\t%6s|\t%8s\n",
               "体重指数","肺活量","仰卧起坐/引体向上");
        printf("-------------------------------------------------\n");

        printf("最大值|\t%8.1f|\t%6.1f|\t%8.1f\n",arr[0][0],arr[1][0],arr[2][0]);
        printf("-------------------------------------------------\n");

        printf("最小值|\t%8.1f|\t%6.1f|\t%8.1f\n",arr[0][1],arr[1][1],arr[2][1]);
        printf("-------------------------------------------------\n");

        printf("平均值|\t%8.1f|\t%6.1f|\t%8.1f\n",arr[0][2],arr[1][2],arr[2][2]);
        printf("-------------------------------------------------\n");
        printf("加载完成\n");
    }else{
        printf("无法查询，请重新输入\n");
    }

}
void clear(){
    system("cls");
}
void DestroyScoreLib(struct ScoreLib* ps){
    free(ps->data);
    ps->data = NULL;
}
void SaveScoreLib(struct ScoreLib* ps){
    FILE* pfWrite = fopen("ScoreLib.dat","wb");
    if(pfWrite == NULL){
        printf("SaveScoreLib::%s\n", strerror(errno));
        return;
    }
    //写ScoreLib数据库中数据到文件中
    for (int i = 0; i < ps->size; ++i) {
        fwrite(&(ps->data[i]),sizeof(struct StuInfo),1,pfWrite);
    }
    fclose(pfWrite);
    pfWrite = NULL;
}
