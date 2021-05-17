#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct{
    char TenDV[20];
    float TL, GT, DG;
    int PA;
}DVat;
DVat *Readfile(float *w, int *n){
    FILE *f;
    f = fopen("CaiBalo3.INP", "r");
    fscanf(f,"%f",w);//Xác định trọng lượng cái balo
    DVat *DsDV;
    DsDV = (DVat*)malloc(sizeof(DVat));
    int i = 0;
    while (!feof(f)){
        fscanf(f,"%f%f%[^\n]",&DsDV[i].TL, &DsDV[i].GT, &DsDV[i].TenDV);
        DsDV[i].DG = DsDV[i].GT/DsDV[i].TL;
        DsDV[i].PA = 0;
        i++;
        DsDV=(DVat*)realloc(DsDV, sizeof(DVat)*(i+1));
    }
    *n = i;
    fclose(f);
    return DsDV;
}
void swap(DVat *a, DVat *b){
    DVat tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void bubblesort(DVat *DsDV, int n){
    int i,j;
    for(i=0;i<= n-2;i++)
        for(j=n-1;j>=i+1;j--){
            if(DsDV[j].DG > DsDV[j-1].DG)
                swap(&DsDV[j], &DsDV[j-1]);
        }
}
void PrintDsDV(DVat *DsDV, int n, float w){
    int i;
    float TongTL = 0.0, TongGT = 0.0;
    printf("\nPhuong An CBL3 dung thuat toan tham an nhu sau:\n");
    printf("|---|------------------|---------|---------|---------|-------|\n");
    printf("|STT|   Ten Do Vat     | Tluong  | Gia Tri | Don Gia |  PAn  |\n");
    printf("|---|------------------|---------|---------|---------|-------|\n");
    for(i=0;i<n;i++){
        printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%6d |\n",i+1,DsDV[i].TenDV,DsDV[i].TL,DsDV[i].GT,DsDV[i].DG,DsDV[i].PA);       
        TongTL += DsDV[i].PA * DsDV[i].TL;
        TongGT += DsDV[i].PA * DsDV[i].GT;
    }
    printf("Trong Luong Cua Balo la: %-9.2f\n", w);
    printf("Tong Trong Luong Cua Balo la: %-9.2f\n", TongTL);
    printf("Tong Gia Tri Cua Balo la: %-9.2f\n", TongGT);
    printf("X(");
    for(i=0;i<n;i++){
        printf("%d, ", DsDV[i].PA);
    }
    printf(")");
}
void Greedy(DVat *DsDV, int n, float w){
    int i = 0;
    for(i=0; i<n; i++){
        DsDV[i].PA = (w/DsDV[i].TL);
        if(DsDV[i].PA > 1)
            DsDV[i].PA = 1;
        w=w-DsDV[i].PA * DsDV[i].TL;
    }
}
int main(){
    int n;
    float w;
    DVat *DsDV;
    DsDV = Readfile(&w,&n);
    bubblesort(DsDV,n);
    Greedy(DsDV,n,w);
    PrintDsDV(DsDV,n,w);
    free(DsDV);
    return 0;
}
