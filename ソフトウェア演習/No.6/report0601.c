#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

#define READ_SIZE 256
#define BM_SKIP_SIZE 256

//力任せのプログラム
int power(char *text, char *pattern){
    
    int i, n, len, filesize;

    clock_t t1, t2;
    n = 0;
    len = strlen(pattern);
    filesize = strlen(text);
    t1 = clock();
    for (i = 0; i < filesize; i++) {
        if (strncmp(text + i, pattern, len) == 0) {
        n++;
        }
    }
    t2 = clock();
    printf("\"%s\" found %d times!¥n", pattern, n);
    printf("Used CPU time: %.10f¥n",
        (double)(t2 - t1) / CLOCKS_PER_SEC);
}

int make_skip(int *table, char *pattern, int ptn_len)
{

    //パターンに無い文字はパターン文字列長をずらし幅にする
    for(int i = 0; i < BM_SKIP_SIZE; i++){
	table[i] = ptn_len;
    }

    //パターンに含まれる文字のずらし幅を決定する
    for(int i = 0; i < ptn_len; i++){
	table[(int)pattern[i]] = ptn_len - i - 1;
    }

    
    return 0;
}

int next_step(int *skip, char target, int remain){
    //ループ防止のために確認する
    if(skip[(int)target] > remain){
        //ずらし表から値を取得する 
        return(skip[(int)target]);
    }else{
        //照合を開始した地点の次の文字に進める
        return(remain);
    }
}

int BM_search(const char *text,char *pattern){
    int skip[BM_SKIP_SIZE];
    int txt_len = 0;
    int ptn_len = 0;
    int i = 0;      //テキストの比較位置
    int j = 0;      //パターンの比較位置 
    int n = 0;      //観測カウント
    
    LARGE_INTEGER freq;
    if( !QueryPerformanceFrequency(&freq))return 0;//単位取得
    LARGE_INTEGER start, end;

    ptn_len = strlen(pattern);
    txt_len = strlen(text);

    //計測開始
    if( !QueryPerformanceCounter(&start))return 0; 
    
    //スキップ表を作成
    make_skip(skip, pattern, ptn_len);

    //比較処理
    i = j = ptn_len - 1; //比較位置をパターン末尾にする
    while(i < txt_len){
        while(text[i] == pattern[j]){ 
            //文字が全て一致すればカウント
            if (j==0){
                n++;
                break;
            }
            // 文字が一致したので、前の文字を照合していく 
            j--;
            i--;
        }
        //ずらし表を参照して、次の比較位置を設定する
        i += next_step(skip, text[i], (ptn_len - j));
        j = ptn_len - 1;   //比較位置をパターン末尾にする
    }
    //計測終了
    if( !QueryPerformanceCounter(&end))return 0;
    printf("\"%s\"found %dtimes!\n",pattern,n);
    printf("UsedCPUtime:%.10f\n",(double)(end.QuadPart-start.QuadPart)/freq.QuadPart);
    return 0;
}

int main(int argc,char *argv[]){

    char *pattern = argv[2];
    char *text;
    
    FILE *fp;     //FILE型構造体
    //ファイルを開く．例外処理で，失敗ならNULLを返す．
    fp = fopen(argv[1],"r");
    if(fp == NULL) {
		printf("%s file not open!\n", argv[1]);
		return -1;
    }
    
    //ファイルサイズの読み取り
    fseek(fp,0,SEEK_END);
    int size = ftell(fp); 
    char buf[READ_SIZE];
    text = (char *)malloc(sizeof(char)*size);
    fseek(fp, 0L, SEEK_SET);

    //テキストをメモリに格納
    while (fgets(buf,READ_SIZE,fp)!=NULL){
        buf[strlen(buf)-1] = '\0';  //終端処理
        strcat(text,buf);
    
    }
    
    //力任せの検索
    printf("POWER METHOD\n");
    power(text,pattern);
    //Boyer-Moore法を用いた検索
    printf("\nBoyer-Moore METHOD\n");
    BM_search(text,pattern);
    
    fclose(fp);
    free(text);
}