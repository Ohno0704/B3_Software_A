#include <stdio.h>
#include <ctype.h>

#define FIGURE_N 96 // 図形文字数

int main(void)
{
    FILE *fp;
    char moji;
    int str;
    char fig_char[FIGURE_N];
    int counter[FIGURE_N] = {0};
    int i = 0;

    char fname[] = "Alice_in_Wonderland.txt";

    // カウントする文字の入力
    while ((moji = getchar()) != EOF)
    {
        if (moji == '\n')
            break;
        if (isprint(moji))
        {
            fig_char[i] = moji;
            i++;
        }
        if (i > FIGURE_N)
            break;
    }

    // 終了判定用
    fig_char[i++] = '\0';

    // ファイルでの処理
    fp = fopen64(fname, "r");
    if (fp == NULL)
    {
        printf("%s file not open!\n", fname);
        return -1;
    }
    else
    {
        while ((str = fgetc(fp)) != EOF)
        {
            for (i = 0; fig_char[i] != '\0'; i++)
            {
                if (str == fig_char[i])
                {
                    counter[i]++;
                }
            }
        }
        //結果出力
        for (i = 0; fig_char[i] != '\0'; i++)
        {
            if (counter[i] != 0)
            {
                printf("\"%c\"=%d\n", fig_char[i], counter[i]);
            }
        }
    }

    fclose(fp);

    return 0;
}