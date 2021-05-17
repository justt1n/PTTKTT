#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int PA, SL;
}DoVat;

DoVat * ReadFromFile(float *W, int *n){
	FILE *f = fopen("CaiBalo3.inp", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f %f %d %[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

void swap(DoVat *x, DoVat *y){
	DoVat tmp = *x;
	*x = *y;
	*y = tmp;
}

void Sort(DoVat *dsdv, int n){
	int i, j;
	for(i = 0;  i < n - 1; i++){
		for(j = n - 1; j > i; j--){
			if(dsdv[j].DG > dsdv[j - 1].DG)
				swap(&dsdv[j], &dsdv[j-1]);
		}
	}
}

void inDSDV(DoVat *dsdv, int n, float W){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	for(i = 0; i < n; i++){
		printf("%.2f %.2f %d %s %d\n", dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].TenDV, dsdv[i].PA);
		TongTL = TongTL + dsdv[i].TL * dsdv[i].PA;
		TongGT = TongGT + dsdv[i].GT * dsdv[i].PA;
	}
	printf("Tong trong luong: %d\n", TongTL);
	printf("Tong gia tri: %d\n", TongGT);
	printf("(%d, ", dsdv[0].PA);
	for(i = 1; i < n - 1; i++){
		printf("%d, ", dsdv[i].PA);
	}
	printf("%d)", dsdv[n-1].PA);
}

void taoNutGoc(float W, float *tmpW, float *CT, float *GLNTT, float *TGT, float DG_Max){
	*TGT = 0.0;
	*tmpW = W;
	*CT = *tmpW *DG_Max;
	*GLNTT = 0.0;
}

void capNhatGLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n){
	int i;
	if(*GLNTT < TGT){
		*GLNTT = TGT;
		for(i = 0; i < n; i++)
			dsdv[i].PA = x[i];
	}
}

int min(int a, int b){
	return a < b ? a : b;
}

void nhanhCan(int i, float *TGT, float *CT, float *tmpW, float *GLNTT, int x[], DoVat *dsdv, int n){
	int j;
	int yk;
	yk = min(dsdv[i].SL, *tmpW/dsdv[i].TL);
	for(j = yk; j >= 0; j--){
		*TGT = *TGT + j*dsdv[i].GT;
		*tmpW = *tmpW - j*dsdv[i].TL;
		*CT = *TGT + *tmpW *dsdv[i+1].DG;
		if (*CT > *GLNTT){
			x[i] = j;
			if((i == n-1) || (*tmpW == 0))
				capNhatGLNTT(*TGT, GLNTT, x, dsdv, n);
			else
				nhanhCan(i+1, TGT, CT, tmpW, GLNTT, x, dsdv, n);
		}
		x[i] = 0;
		*TGT = *TGT - j*dsdv[i].GT;
		*tmpW = *tmpW + j*dsdv[i].TL;
	}
}

int main(){
	DoVat * dsdv;	
	int n; 			
	float W; 			
	float CT; 		
	float TGT; 		
	float V; 		
	float GLNTT; 	 
	
	dsdv = ReadFromFile(&W, &n);
	
	int x[n];		// Luu phuong an tot nhat tam thoi
	
	Sort(dsdv,n);
	taoNutGoc(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	nhanhCan(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	inDSDV(dsdv,n,W);
	
	free(dsdv);
	return 0;
}
