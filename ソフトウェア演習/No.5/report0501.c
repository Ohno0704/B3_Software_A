#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//リスト要素数の範囲
#define N_max 100
#define N_min 3

//RGB値の範囲
#define RGB_max 1.0
#define RGB_min 0.0

//ベクトル値の範囲
#define XY_max 550.0
#define XY_min 50.0

//座標ベクトル
typedef struct vector{
    double x;   //x座標
    double y;   //y座標
}VECTOR;

//三角形
typedef struct Triangle { 
    VECTOR v[3];            //座標
    double R,G,B;           //色
    struct Triangle *next;  //次のリストを指すポインタ
}TRIANGLE;

//指定範囲のランダム(返り値:double)
double randrange(double max,double min){
    return rand()/(RAND_MAX/(max-min))+min;
}

//ランダム値で初期化したリスト生成
TRIANGLE *MakeTriList(int N){
    if(N>0){
        TRIANGLE *node=(TRIANGLE*)malloc(sizeof(TRIANGLE));
        //ベクトル
        for(int i=0;i<3;i++){
            node->v[i].x = randrange(XY_max,XY_min);
            node->v[i].y = randrange(XY_max,XY_min);
        }
        
        //色
        node->R = randrange(RGB_max,RGB_min);
        node->G = randrange(RGB_max,RGB_min);
        node->B = randrange(RGB_max,RGB_min);

        //次のノードへ
        node->next = MakeTriList(N-1);

        return node;
    }
    return NULL; 
}

//三角形をPS出力
void TrianglePrint(FILE *fp,TRIANGLE *node){
    
    if (node != NULL){
        
        //新しい描画セット
        fprintf(fp,"newpath\n");

        //色指定
        fprintf(fp,"%f %f %f setrgbcolor\n",node->R,node->G,node->B);

        //線の描写
        fprintf(fp,"%f %f moveto\n",node->v[0].x,node->v[0].y);
        fprintf(fp,"%f %f lineto\n",node->v[1].x,node->v[1].y);
        fprintf(fp,"%f %f lineto\n",node->v[2].x,node->v[2].y);
        fprintf(fp,"closepath\n");

        //描写終了
        fprintf(fp,"stroke\n");

        //次へ移動
        TrianglePrint(fp,node->next);
    }
}

//メモリ解放
int FreeList(TRIANGLE *node){
    if (node != NULL){
        FreeList(node->next);
        free(node);
    }
    return 0;
}

int main(void){

    // 時間による乱数系列の変更 
    srand((unsigned)time(NULL));

    //リスト作成
    double N = randrange((double)N_max,(double)N_min);
    TRIANGLE *top = MakeTriList((int)N);
    
    //ファイルの生成
    FILE *fp;                   //FILE型構造体
    char fname[] = "output.ps"; //出力ファイル
    fp = fopen(fname,"w");
    if(fp == NULL) {
		printf("%s file not make!\n", fname);
		return -1;
    }
    
    //三角形リストをファイルに出力
    TrianglePrint(fp,top);
    
    //メモリ解放
    FreeList(top);

    //ファイルを閉じる
    fclose(fp);
}