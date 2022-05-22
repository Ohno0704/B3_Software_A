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

void reverse(char *str)
{
    int i = 0;
    int len = strlen(str);
    char temp;
    // 文字の入れ替え
    for (i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main(void)
{
    FILE *fp;
    int i = 0;
    char str[MAX_STR_LEN]; // ファイルから読み込んだ文字列

    if (fp == NULL)
    {
        printf("file not open!\n");
        return -1;
    }
    else
    {
        while (fgets(str, MAX_STR_LEN, stdin) != NULL)
        {
            reverse(str);
            printf("%s", str);
        }
    }

    fclose(fp);

    return 0;
}