//
// Created by Echo on 2022/12/11.
//

#define MAX_ID 14
#define MAX_NAME 20
#define MAX_SEX 10
#define DEFAULT_SIZE 20 //Ĭ�Ͽռ��С

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//ʹ��ö��ʹswitch�������ױ��������
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
//����ѧ����Ϣ���� struct StuInfo
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


//���������ɼ����ݿ� struct Scorelib
struct ScoreLib{
    struct StuInfo* data;//���ѧ����Ϣ
    int capacity;//��ǰ���ݿ���������
    int size;//��¼��ǰѧ������
};
//��������
//��ʼ�����ݿ�lib
void InitScoreLib(struct ScoreLib* ps);
void AddScoreLib2(struct ScoreLib* ps);
void ShowScoreLib(const struct ScoreLib* ps);
void DelScoreLib(struct ScoreLib* ps);

void SearchByScore(const struct ScoreLib* ps);
void SearchByScoreRank(const struct ScoreLib* ps);
//�޸�ѧ�������ɼ�
void ModifyScoreLib(struct ScoreLib* ps);
//����Ϣ���еĳɼ���������
void SortByScore(struct ScoreLib* ps);
//��ѧ�Ž�������
void SortById(struct ScoreLib* ps);
//��������������
void SortByName(struct ScoreLib* ps);

void StatisticScore(const struct ScoreLib* ps);
//�������ݿ�-�ͷŶ�̬���ٵ��ڴ�
void DestroyScoreLib(struct ScoreLib* ps);
//������Ϣ
void SaveScoreLib(struct ScoreLib* ps);
//�����ļ��е���Ϣ�����ݿ�
void LoadScoreLib(struct ScoreLib* ps);
//����
void clear();
void SearchById(const struct ScoreLib* ps);
void SearchByName(const struct ScoreLib* ps);
void SearchByScore(const struct ScoreLib* ps);





