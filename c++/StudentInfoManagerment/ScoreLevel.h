#ifndef __ScoreLevel_H__
#define __ScoreLevel_H__
#define MAX 100
struct ScoreLevel
{
    //���������
 //   char scoreScope[10];
    //����óɼ��ε�ѧ��ѧ��
    char math_num[MAX];
    char cProgram_num[MAX];
    char english_num[MAX];
};
struct Level
{
    struct ScoreLevel A;
    struct ScoreLevel B;
    struct ScoreLevel C;
    struct ScoreLevel D;
};
#endif // __ScoreLevel_H__
