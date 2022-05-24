#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define HASHSIZE 8191

//ハッシュテーブル
typedef struct node { 
    char word[MAX];
    int count; 
    struct node *next;
}HASH;

//ハッシュ関数
int hash(char *str){
    int h=0, n;
    for(n=0;str[n]!='\0';n++){
        h=(h*137+str[n]) % HASHSIZE;
    }
    return h;
}

//ハッシュでリスト操作
int HashList(HASH *node, char *word){
    //重なればカウント
    if(strcmp(node->word,word)==0){
        node->count += 1;
    //そうでなければnextへ
    }else{
        if(node->next==NULL){
            HASH *new_node = (HASH*)malloc(sizeof(HASH));
            //エラー処理
            if(new_node == NULL)printf("ERORR");
            strcpy(new_node->word,word);
            new_node->count = 1;
            new_node->next = NULL;
            node->next = new_node;
        }else{
            HashList(node->next,word);
        }  
    }
    return 0;
}

//ハッシュ表を生成
int MakeHash(HASH **node,char *word){
    int hash_no = hash(word);
    //新規作成
    if (node[hash_no] == NULL){
        node[hash_no] = (HASH*)malloc(sizeof(HASH));
        //エラー処理
        if(node[hash_no] == NULL)printf("ERORR");
        strcpy(node[hash_no]->word,word);
        node[hash_no]->count = 1;
        node[hash_no]->next = NULL;
        return -1;
    }
    HashList(node[hash_no],word);
    return 0;   
}

//ハッシュ表の結果を表示
int PrintHash(HASH **node){
    for(int i=0;i<HASHSIZE;i++){
        HASH *p1=node[i];
        while(p1!=NULL){
            printf("WORD: \"%s\",COUNT: %d\n",p1->word,p1->count);
            p1=p1->next;
        }
    }  
    return 0;
}

int FreeHash(HASH **node){
    for(int i=0;i<HASHSIZE;i++){
        HASH *p1=node[i];
        while(p1!=NULL){
            free(p1);
            p1=p1->next;
        }
    } 
    printf("finish");//デバック
    return 0;
}



int main(void){

    FILE *fp;     //FILE型構造体
    //テキストファイル
    char fname[] = "Alice_in_Wonderland.txt";
    char word[MAX];    //一時格納する文字
    HASH *hash[HASHSIZE];//ハッシュ表
    //アドレスをNULLで初期化
    for(int i=0;i<HASHSIZE;i++)hash[i]=NULL;
    
    //ファイルを開く．例外処理で，失敗ならNULLを返す．
    fp = fopen(fname,"r");
    if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
    }
    

    //1単語ずつ読み取り
    while(fscanf(fp,"%s",word)!=EOF){
        MakeHash(hash,word);
    }

    
    PrintHash(hash);
    FreeHash(hash);
    printf("success!");

  //ファイルを閉じる
  fclose(fp);
}