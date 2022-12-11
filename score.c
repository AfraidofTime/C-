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
    return -1;//����Ҳ�������-1
}
static int FindByName(const struct ScoreLib* ps,char name[]){
    for (int i = 0; i < ps->size; ++i) {
        if(0==strcmp(ps->data[i].name,name)){
            return i;
        }
    }
    return -1;//����Ҳ�������-1
}

void CheckCapacity(struct ScoreLib* ps) {
    if(ps->size == ps->capacity){
        //����
        struct StuInfo* ptr = realloc(ps->data,(ps->capacity+2)*sizeof(struct StuInfo));
        if(ptr != NULL){
            ps->data = ptr;
            ps->capacity += 10;
            printf("���ݳɹ�\n");
        }
        else{
            printf("����ʧ��\n");
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
    //���ļ��Ѿ���ŵ���Ϣ���ص����ݿ���struct ScoreLib score��
    LoadScoreLib(ps);
}

void LoadScoreLib(struct ScoreLib* ps){
    struct StuInfo tmp = {0};
    FILE* pfRead = fopen("ScoreLib.dat","rb");
    if(pfRead == NULL){
        printf("LoadScoreLib::%s\n",strerror(errno));
        return;
    }
    //��ȡ�ļ�����ŵ����ݿ���

    while(fread(&tmp, sizeof(struct StuInfo),1,pfRead)){
        CheckCapacity(ps);
        ps->data[ps->size] = tmp;
        ps->size++;
    }

    fclose(pfRead);
    pfRead = NULL;
}

//����ѧ�������ɼ�
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

    if ( 0 == strcmp(ps->data[ps->size].sex,"��")){
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

    if ( 0 == strcmp(ps->data[ps->size].sex,"Ů")) {
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
    printf("ѧ�������Ϣ��ӳɹ�\n");
}

void AddScoreLib2(struct ScoreLib* ps) {
    //�ж��Ƿ���ڸ�ѧ��
    char id[MAX_ID];
    printf("������ѧ��:>");
    scanf("%s",id);
    int flag = FindById(ps,id);
    if (flag == -1){
        //������ݿ������
        //������˾����ݣ������������������
        CheckCapacity(ps);
        strcpy(ps->data[ps->size].id,id);
        printf("����������:>");
        scanf("%s", ps->data[ps->size].name);
        printf("�������Ա�(��/ Ů):>");
        scanf(" %s", ps->data[ps->size].sex);
        printf("������BIM:>");
        scanf("%f", &(ps->data[ps->size].bim));
        printf("������λ���:>");
        scanf("%d", &(ps->data[ps->size].vcp));
        printf("�������������ϻ�����������:>");
        scanf("%d", &(ps->data[ps->size].PullSit));
        AddScoreLib1(ps);
    }else{
        printf("��ѧ���Ѵ���\n");
    }
}


//��ӡѧ�������ɼ�
void ShowScoreLib(const struct ScoreLib* ps){
    if (ps->size ==0){
        printf("�ɼ���Ϊ��\n");
    }
    else{
        printf("---------------------------------------ѧ�����ɼ���-------------------------------------------------------\n");
        printf("%10s|\t%8s|\t%5s|\t%5s|\t%6s|\t%9s|\t%9s|\t%9s|\t%5s\n",
                       "ѧ��","����","�Ա�","BIM","�λ���","��������","��������","�ɼ�","����");
        printf("----------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < ps->size; ++i) {
            if (0== strcmp(ps->data[i].sex,"��")){
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
//����ѧ��,staticʹ�ú���ֻ���ڸ��ļ��ڲ�ʹ�ã��ı��˺�����������

//����ѧ��ɾ��
void DelScoreLib(struct ScoreLib* ps) {
    char id[MAX_ID];
    char tmp;
    printf("������Ҫɾ���˵�ѧ��:>");
    scanf("%s",id);
    //����ɾ���˵�λ��
    //�ҵ��˷���id�����±�
    int pos = FindById(ps,id);
    //ɾ��Ԫ��
    if  (pos == -1){
        printf("Ҫɾ�����˲�����\n");
    }else{
        printf("���� y/n �ٴ�ȷ��:>");
        scanf(" %c", &tmp);
        if (('y' == tmp) || ('Y' == tmp)){
            for (int j = pos; j < ps->size-1; ++j) {
                ps->data[j] = ps->data[j+1];
            }
            ps->size--;
            printf("ɾ���ɹ�\n");
        }
    }
}
static void print(const struct ScoreLib* ps, int pos) {
    if (-1 == pos) {
        printf("Ҫ���ҵ��˲�����\n");
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
    printf("��������Ҫ���ҵ�ѧ��:>");
    scanf("%s",id);
    pos = FindById(ps,id);
    if(-1!= pos){
        printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s\n",
               "ѧ��", "����", "�Ա�", "BIM", "�λ���", "���������", "�ɼ�");
        print(ps,pos);
    }else{
        printf("��ͬѧ��Ϣδ¼��\n");
    }

}

void SearchByName(const struct ScoreLib* ps){
    char name[MAX_NAME];
    char cmd;
    int pos = 0;
    printf("��������Ҫ���ҵ�����:>");
    scanf("%s",name);

    pos = FindByName(ps,name);
    if (-1 != pos){
        printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s|\t%10s\n",
               "ѧ��", "����", "�Ա�", "BIM", "�λ���", "���������", "�ɼ�","����");
        print(ps,pos);
    }else{
        printf("��ͬѧ��Ϣδ¼��\n");
    }
}
//���ɼ��ȼ�(pass/good...)����
void SearchByScoreRank(const struct ScoreLib* ps){
    char score[10];
    int cnt=0;
    printf("��������Ҫ�����˵ĳɼ��ȼ�(psss/ good...):>");
    scanf("%s",score);

    printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s|\t%10s\n",
           "ѧ��", "����", "�Ա�", "BIM", "�λ���", "���������", "�ɼ�","����");
    for (int i = 0; i < ps->size; ++i) {
        if(0==strcmp(ps->data[i].ScoreRank,score)){
            print(ps,i);
            cnt++;
        }
    }
    printf("������ɣ���%d��ѧ������Ҫ��\n",cnt);
}
// ���ɼ�(����)����
void SearchByScore(const struct ScoreLib* ps){
    float score = 0.0f;
    int pos[ps->size];
    int cnt =0;//��¼�·���������ѧ�������ݿ��е��±�
    printf("��������Ҫ�����˵ķ���:>");
    scanf("%f",&score);
    for (int i = 0; i < ps->size; ++i) {
        if(score == ps->data[i].Score){
            pos[cnt] = i;
            cnt++;
        }
    }
    if(cnt==0){
        printf("û�з���Ϊ%.1f��ѧ��,�����²���\n",score);
    }else{
        printf("%10s|\t%10s|\t%6s|\t%10s|\t%8s|\t%10s|\t%10s|\t%10s\n",
               "ѧ��", "����", "�Ա�", "BIM", "�λ���", "���������", "�ɼ�","����");
        for (int i = 0; i < cnt; ++i) {
            print(ps,pos[i]);
        }
        printf("�������,��%d��ѧ������Ҫ��\n",cnt);
    }
};
void ModifyScoreLib(struct ScoreLib* ps){
    char id[MAX_ID];
    char tmp;
    printf("�����뱻�޸��˵�ѧ��id:>");
    scanf("%s",id);
    int pos = FindById(ps,id);
    if (pos == -1){
        printf("Ҫ�޸��˵���Ϣ������\n");
    }else {
        printf("���� y/n �ٴ�ȷ��:>");
        scanf(" %c", &tmp);
        if (('y' == tmp) || ('Y' == tmp)) {
            printf("������ѧ��:>");
            scanf("%s", ps->data[pos].id);
            printf("����������:>");
            scanf("%s", ps->data[pos].name);
            printf("�������Ա�(��/ Ů):>");
            scanf(" %s", ps->data[pos].sex);
            printf("������BIM:>");
            scanf("%f", &(ps->data[pos].bim));
            printf("������λ���:>");
            scanf("%d", &(ps->data[pos].vcp));
            printf("�������������ϻ�����������:>");
            scanf("%d", &(ps->data[pos].PullSit));

            printf("�޸����\n");
        } else {
            printf("�޸�ʧ��\n");
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
    printf("�������������\n");
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

//��ѧ������
void SortById(struct ScoreLib* ps){
    qsort(ps->data,ps->size,sizeof(struct StuInfo), cmpid1);
    printf("ѧ���������\n");
}
//����������
void SortByName(struct ScoreLib* ps){
    qsort(ps->data,ps->size,sizeof(struct StuInfo), cmpid2);
    printf("�����������\n");
}
//ͳ�ƹ���
void StatisticScore(const struct ScoreLib* ps){//����bim�������\С\ƽ��ֵ
    int ContMale=0,ContFemale=0;
    float arr[3][3]={0};
    float start=0.0f;float end=0.0f;

    float max = 0;
    float min = 0;
    float aver = 0;
    float sum = 0;
    int SumStu = 0;
    int pos[ps->size];//��¼����Ҫ����±�
    //2.ͳ���ܳɼ��ڲ�ͬ��������Ů������,��ӡ����
    printf("����ͳ�Ƶķ��������:>");
    scanf("%f",&start);
    printf("����ͳ�Ƶķ����ν�β:>");
    scanf("%f",&end);

    for (int i = 0; i < ps->size; ++i) {
        if(0 == strcmp(ps->data[i].sex,"��")){
            if((ps->data[i].Score>=start)&&(ps->data[i].Score<=end)){
                ContMale++;
                pos[ContFemale+ContMale-1]=i;
            }
        }if(0 == strcmp(ps->data[i].sex,"Ů")){
            if((ps->data[i].Score>=start)&&(ps->data[i].Score<=end)){
                ContFemale++;
                pos[ContFemale+ContMale-1]=i;
            }
        }
    }
    //����Ҫ�������
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
        //bmi ��ֵ
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
        //vcp ��ֵ
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
        //PullSit ��ֵ
        for (int i = 0; i < SumStu; ++i) {
            sum += ps->data[pos[i]].PullSit;
        }aver = sum / (float)SumStu;
        arr[2][2] = aver;

        printf("--------�������ܷ�����%.1f~%.1f��ͳ�Ʊ�--------\n",start,end);
        printf("\t��������|\tŮ������|\n");
        printf("\t%d��\t\t%d��  \n",ContMale,ContFemale);
        printf("-------------------------------------------------\n");

        printf("\t%8s|\t%6s|\t%8s\n",
               "����ָ��","�λ���","��������/��������");
        printf("-------------------------------------------------\n");

        printf("���ֵ|\t%8.1f|\t%6.1f|\t%8.1f\n",arr[0][0],arr[1][0],arr[2][0]);
        printf("-------------------------------------------------\n");

        printf("��Сֵ|\t%8.1f|\t%6.1f|\t%8.1f\n",arr[0][1],arr[1][1],arr[2][1]);
        printf("-------------------------------------------------\n");

        printf("ƽ��ֵ|\t%8.1f|\t%6.1f|\t%8.1f\n",arr[0][2],arr[1][2],arr[2][2]);
        printf("-------------------------------------------------\n");
        printf("�������\n");
    }else{
        printf("�޷���ѯ������������\n");
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
    //дScoreLib���ݿ������ݵ��ļ���
    for (int i = 0; i < ps->size; ++i) {
        fwrite(&(ps->data[i]),sizeof(struct StuInfo),1,pfWrite);
    }
    fclose(pfWrite);
    pfWrite = NULL;
}
