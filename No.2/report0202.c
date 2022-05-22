#include <stdio.h>
#include <ctype.h>

#define MAX_STR_LEN 256 // fgetsで一度に読み込むバッファサイズ

//文字列の長さを返す
int strlen(char *str)
{
    int count = 0;
    while (str[count] != '\0')
        count++;
    return count;
}

//文字列を比較する
int my_strcmp(char *str, char *comp)
{
    int i = 0, j = 0;
    int count = 0; //文字列の数
    int flag = 0;  //判定

    //単語を探す
    while (str[i] != '\n')
    {
        if (str[i] == comp[j])
        {
            flag++;
            j++;
            //比較文字があればカウント1
            if (flag == strlen(comp))
                count++;
        }
        else
        {
            flag = 0;
            j = 0;
        }
        i++;
    }
    return count;
}

int main(void)
{
    int i;
    int comp_count[3] = {0};                                  //検索した総数
    char *comp_name[3] = {"Alice", "wonder", "self"};         //比較文字列
    int comp_no = sizeof(comp_count) / sizeof(comp_count[0]); //比較する文字列の数
    char str[MAX_STR_LEN];                                    //一行の文字列

    //文字列検索
    while (fgets(str, MAX_STR_LEN, stdin) != NULL)
    {
        for (i = 0; i < comp_no; i++)
        {
            comp_count[i] += my_strcmp(str, comp_name[i]);
        }
    }

    //結果表示
    for (i = 0; i < comp_no; i++)
    {
        printf("Nomber of \"%s\"is\t%d\n", comp_name[i], comp_count[i]);
    }
}