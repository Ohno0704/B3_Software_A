#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128

//データの特徴次元毎の平均からなる平均ベクトル
double *get_mean(int ndim, double **data, int ndata);
//特徴次元間の分散共分散行列
double **get_cova(int ndim, double **data, int ndata);

//多次元配列の動的確保
double **get_matrix(int col, int row);
//多次元メモリ解放
void free_matrix(double **ptri, int col, int row);

//文字列をスペースで分割
void strdiv(char *str, double *str_no);

int main(void)
{

    FILE *fp;
    char fname[] = "A01M0007-0007.dat";

    //ファイルオープン
    fp = fopen(fname, "r");
    if ((fp = fopen(fname, "r")) == NULL)
    {
        printf("File open Error\n");
        return 0;
    }

    char str[MAX_SIZE];
    int nframe; //フレームの数
    int ndim;   //各フレームの次元数
    fgets(str, MAX_SIZE, fp);
    sscanf(str, "%d %d", &nframe, &ndim);

    //行列の生成
    double **matrix = get_matrix(nframe, ndim);

    int row = 0; //行
    double no[ndim];
    int count_str_no = 0;
    int count;

    //一行ずつ読み取り
    while (fgets(str, MAX_SIZE, fp) != NULL)
    {
        strdiv(str, no);
        for (int col = 0; col < ndim; col++)
        {
            matrix[row][col] = no[col];
        }
        row++;
    }

    //平均ベクトル
    double *mean = get_mean(ndim, matrix, nframe);
    //平均ベクトル表示
    printf("mean vector\n");
    for (int i = 0; i < ndim; i++)
    {
        printf("%lf\n", mean[i]);
    }
    free(mean); //メモリの解放

    //分散共分散行列
    double **cova = get_cova(ndim, matrix, nframe);
    //分散共分散行列
    printf("\nvariarance covariance matrix\n");
    for (int i = 0; i < ndim; i++)
    {
        for (int j = 0; j < ndim; j++)
        {
            printf("%lf ", cova[i][j]);
        }
        printf("\n");
    }
    free_matrix(cova, nframe, nframe);

    //メモリの解放
    free_matrix(matrix, nframe, ndim);

    //ファイルを閉じる
    fclose(fp);
}

double *get_mean(int ndim, double **data, int ndata)
{
    double *mean; //平均ベクトル

    //メモリの確保
    mean = (double *)malloc(ndata * sizeof(double));
    if (mean == NULL)
    {
        perror("failed to allocate");
    }

    //平均ベクトル計算
    for (int i = 0; i < ndim; i++)
    {
        mean[i] = 0;
        for (int j = 0; j < ndata; j++)
        {
            mean[i] += data[j][i];
        }
        mean[i] = mean[i] / ndata;
    }
    return mean;
}

double **get_cova(int ndim, double **data, int ndata)
{
    double **cova = get_matrix(ndata, ndata);   //分散共分散行列
    double *mean = get_mean(ndim, data, ndata); //平均ベクトル
    for (int i = 0; i < ndim; i++)
    {
        for (int j = 0; j < ndim; j++)
        {
            for (int n = 0; n < ndata; n++)
            {
                cova[i][j] += ((data[n][i] - mean[i]) * (data[n][j] - mean[j])) / ndata;
            }
        }
    }
    free(mean);
    return cova;
}

//多次元配列の動的確保
double **get_matrix(int col, int row)
{
    double **ptri;
    ptri = (double **)malloc(col * sizeof(double *));

    if (ptri == NULL)
    {
        perror("failed to allocate");
    }
    for (int i = 0; i < col; i++)
    {
        ptri[i] = (double *)malloc(row * sizeof(double));
        if (ptri[i] == NULL)
        {
            perror("failed to allocate");
        }
    }
    return ptri;
}

//メモリ解放
void free_matrix(double **ptri, int col, int row)
{
    for (int i = 0; i < col; i++)
    {
        free(ptri[i]);
    }
    free(ptri);
}

//文字列をスペースで分割
void strdiv(char *str, double *no)
{
    char temp[MAX_SIZE];
    int count = 0;
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' || str[i] == '\n')
        {
            no[count++] = atof(temp);
            j = 0;
            // tempを初期化
            memset(temp, '\0', strlen(temp));
        }
        else
        {
            temp[j++] = str[i];
        }
    }
}