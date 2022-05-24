#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

//木構造
typedef struct BinaryTree { 
    char word[MAX]; // 格納する文字列
    int count; // 出現回数
    struct BinaryTree *left; // 左部分木
    struct BinaryTree *right; // 右部分木
}BT;

//二分木生成とカウント
int MakeTree(BT *node,char *word){
    int comp = strcmp(node->word,word);
    //文字のカウント
    if(comp == 0){
        node->count += 1;
    }else{
        if(comp>0){
            if(node->right == NULL){
                BT *new_node=(BT*)malloc(sizeof(BT));
                if(new_node == NULL){
                    printf("ERORR");
                }
                strcpy(new_node->word,word);
                new_node->count = 1;
                new_node->left = NULL;
                new_node->right = NULL;
                node->right = new_node;
            }else{
                MakeTree(node->right,word);
            }
        }else{
            if(node->left == NULL){
                BT *new_node=(BT*)malloc(sizeof(BT));
                if(new_node == NULL){
                    printf("ERORR");
                }
                strcpy(new_node->word,word);
                new_node->count = 1;
                new_node->left = NULL;
                new_node->right = NULL;
                node->left = new_node;
            }else{
                MakeTree(node->left,word);
            }
        }
    }
}

//二分木の結果を表示
int PrintTree(BT *tree){
    if(tree!=NULL){
        PrintTree(tree->right);
        printf("WORD:\"%s\",COUNT: %d\n",tree->word,tree->count);
        PrintTree(tree->left);
    }
}
//メモリ解放
void FreeTree(BT *tree){
    if(tree->right != NULL){
        FreeTree(tree->right);
        free(tree->right);
    }
    if(tree->left!=NULL){
        FreeTree(tree->left);
        free(tree->left);
    }
}

int main(void){

    FILE *fp;     //FILE型構造体
    //テキストファイル
    char fname[] = "Alice_in_Wonderland.txt";
    char word[MAX];    //格納する文字
    
    //ファイルを開く．例外処理で，失敗ならNULLを返す．
    fp = fopen(fname,"r");
    if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
    }
    
    //根を生成
    BT *root = (BT*)malloc(sizeof(BT));
    fscanf(fp,"%s",root->word);
    root->count = 1;
    root->left = NULL;
    root->right = NULL;

    //1単語ずつ読み取り
    while(fscanf(fp,"%s",word)!=EOF){
        MakeTree(root,word);
    }

    //表示
    PrintTree(root);
    //メモリの解放
    FreeTree(root);
    free(root);


  //ファイルを閉じる
  fclose(fp);
}