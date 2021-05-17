#include <stdio.h>

typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype otherfields;
} recordtype;

void Swap(recordtype &x, recordtype &y){
	recordtype temp;
	temp = x;
	x = y;
	y = temp;
}

/*FindPivot*/
int FindPivot(recordtype a[], int i, int j){
	keytype firstkey;
	int k;
	k = i+1;
	firstkey = a[i].key;
	while((k<=j) && (a[k].key == firstkey)) k++;
	if (k>j) return -1;
	if (a[k].key > firstkey) return k;
	return i;
}

/*Partition*/
int Partition(recordtype a[], int i, int j, keytype pivot){
	int L,R;
	L = i;
	R = j;
	while (L<=R){
		while (a[L].key < pivot) L++;
		while (a[R].key >= pivot) R--;
		if (L<R) Swap(a[L],a[R]);
	}
	return L;
}

void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivot(a,i,j);
	if (pivotindex != -1){
		pivot = a[pivotindex].key;
		k = Partition(a,i,j,pivot);
		QuickSort(a,i,k-1);
		QuickSort(a,k,j);
	}
}

main(){
	int n,i;
	recordtype a[100];
	
	FILE* file = fopen("dayso.inp", "r");
	fscanf(file, "%d",&n);
	for (i = 0; i <= n-1; i++) {
		fscanf(file, "%d", &a[i]);
	}
	
	QuickSort(a,0,n-1);
	
	for(i=0; i<=n-1; i++){
		printf("%d ",a[i]);
	}
}
