//
// Created by Echo on 2022/12/11.
//

#include "score.h"

//ϵͳ��½ģ��
void loginMenu(){
    int cont = 0;
    int flag = 0;
    const char count[10]="csu2022";//ϵͳ�˺�
    const char code[10]="2022";//����
    char tempCount[20]=" ";//��ʼ��
    char tempCode[20]=" ";
    do {
        printf("          ��������������������ӭʹ��ѧ���ɼ�����ϵͳ����������������          \n");


        printf("              �������½�˺�:>");
        scanf("%s",tempCount);
        printf("              ����������:>");
        scanf("%s",tempCode);
        if ((0 == strcmp(tempCount,count)) && (strcmp(tempCode,code)==0)){//����ʹ�õ�strcmp(),����ֵ���������0,>0,<0
            printf("��½�ɹ�\n");
            flag = 0;
        }else{
            printf("�˺Ż��������������,����������\n");
            flag = 1;
        }
        cont ++;//��¼��½����
        //�����������,�˳�����

        if ((cont>2)&&flag){
            printf("���Ѿ����3��,���˳�����\n");
            exit(0);
        }
    }while(flag);
}
void SelectMenu1() {                      		 //��ӡ��ʦ�˵�
    printf("\n");
    printf("         ����������������������ӭʹ�����ɼ��ж�ϵͳ������������������     \n");
    printf("         ��                                          \n");
    printf("         ��            ��ѡ�������Ŀ��                 \n");
    printf("         ��\t1.¼����Ϣ          2.�޸���Ϣ             \n");
    printf("         ��\t3.ɾ����Ϣ          4.��ѯ��Ϣ             \n");
    printf("         ��\t5.��Ϣ����          6.��ʾ��Ϣ             \n");
    printf("         ��\t7.������Ϣ          8.ͳ������             \n");
    printf("         ��\t9.����              0.�˳�ϵͳ            \n");
    printf("         ����������������������������������������������������������������������������     \n");
}
void PrintMenuSort1() {                      		 //��ӡ����˵�
    printf("\n");
    printf("         ��������������ѧ����Ϣ����˵�����������������������       \n");
    printf("         ��                                          \n");
    printf("         ��            ��ѡ������ʽ                   \n");
    printf("         ��\t1.��ѧ��            2.������(ƴ��)               \n");
    printf("         ��\t3.���ܷ�(����)        6.��ʾ�������Ϣ              \n");
    printf("         ��\t0.������                                 \n");
    printf("         ��������������������������������������������������������������         \n");
}
void SearchMenu(){
    printf("\n");
    printf("         ������������������������ѧ����Ϣ���Ҳ˵�������������       \n");
    printf("         ��                                     \n");
    printf("         ��            ��ѡ����ҷ�ʽ              \n");
    printf("         ��\t1.��ѧ��            2.������          \n");
    printf("         ��\t3.���ܷ���          4.���ɼ��ȼ�(good/pass...)\n");
    printf("         ��\t0.������                           \n");
    printf("         ��������������������������������������������������������������        \n");
}

int main(){
    int input = 0;
    int input2 = 0;
    int input3 = 0;
    char tmp;
    //����ѧ�����ɼ����ݿ�score,������� date ָ�� �� size,capacity
    struct ScoreLib score;
    //��ʼ�����ݿ�
    InitScoreLib(&score);

    loginMenu();
    do {
        SelectMenu1();
        printf("��ѡ��:>");
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
                    printf("��ѡ��:>");
                    scanf("%d",&input3);
                    switch(input3){
                        case EXIT2:
                            printf("�˳��޸�ģ��\n");
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
                            printf("\t\t\tѡ�����!!!\n");
                    }
                }while(input3);
                break;
            case SORT:
                do {
                    PrintMenuSort1();
                    printf("��ѡ��:>");
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
                            printf("�˳�����ģ��\n");
                            break;
                        default:
                            printf("\t\t\tѡ�����!!!\n");
                    }
                }while(input2);
                break;
            case SHOW:
            show:
                ShowScoreLib(&score);
                break;
            case SAVE:
                SaveScoreLib(&score);
                printf("����ɹ�\n");
                break;
            case STATIC:
                StatisticScore(&score);
                break;
            case CLEAR:
                clear();
                break;
            case EXIT:
                printf("���� y/n �ٴ�ȷ���Ƿ��˳�:>");
                scanf(" %c",&tmp);
                if ((tmp == 'y')||(tmp == 'Y')){
                    //�������ݿ�-�ͷŶ�̬���ٵ��ڴ�,����ǰ����
                    SaveScoreLib(&score);
                    DestroyScoreLib(&score);
                    printf("�˳�����\n");break;
                }else {
                    input = 1;
                    break;
                }
            default:
                printf("\t\t\tѡ�����!!!\n");
        }
    }while (input);
    return 0;
}