#include<stdio.h>
#include<stdlib.h>

int greedy;			//jenis algortma yg digunakan

typedef struct {
	int s;	//start point
	int f;	//finish point
	int dur;	//duration
	int oldnum;	//number before sorted
} activity;

void shortest_duration(activity arr[], int l, int m, int h)
{
    activity arr1[255], arr2[255];
    int n1, n2, i, j, k;
    n1 = m - l + 1;
    n2 = h - m;

    for(i = 0; i < n1; i++)
        arr1[i] = arr[l + i];

    for(j = 0; j < n2; j++)
        arr2[j] = arr[m + j + 1];

    arr1[i].dur = 9999;
    arr2[j].dur = 9999;

    i = 0;
    j = 0;

    for(k = l; k <= h; k++)
    {
        if(arr1[i].dur <= arr2[j].dur)
            arr[k] = arr1[i++];
        else
            arr[k] = arr2[j++];
    }
    return;
}

void start_first(activity arr[], int l, int m, int h)
{
    activity arr1[255], arr2[255];
    int n1, n2, i, j, k;
    n1 = m - l + 1;
    n2 = h - m;

    for(i = 0; i < n1; i++)
        arr1[i] = arr[l + i];

    for(j = 0; j < n2; j++)
        arr2[j] = arr[m + j + 1];

    arr1[i].s = 9999;
    arr2[j].s = 9999;

    i = 0;
    j = 0;

    for(k = l; k <= h; k++)
    {
        if(arr1[i].s <= arr2[j].s)
            arr[k] = arr1[i++];
        else
            arr[k] = arr2[j++];
    }
    return;
	
}

void finish_first(activity arr[], int l, int m, int h)
{
    activity arr1[255], arr2[255];
    int n1, n2, i, j, k;
    n1 = m - l + 1;
    n2 = h - m;

    for(i = 0; i < n1; i++)
        arr1[i] = arr[l + i];

    for(j = 0; j < n2; j++)
        arr2[j] = arr[m + j + 1];

    arr1[i].f = 9999;
    arr2[j].f = 9999;

    i = 0;
    j = 0;

    for(k = l; k <= h; k++)
    {
        if(arr1[i].f <= arr2[j].f)
            arr[k] = arr1[i++];
        else
            arr[k] = arr2[j++];
    }
    return;
	
}

void merge_sort(activity A[], int low, int high)
{
    int mid;

    if(low < high) 
    {
        mid = (low + high) / 2;

        merge_sort(A, low, mid); 

        merge_sort(A, mid + 1, high); 

		if(greedy==1)
	        shortest_duration(A, low, mid, high); 
		if(greedy==2)
	        start_first(A, low, mid, high); 
		if(greedy==3)
	        finish_first(A, low, mid, high); 
    }
    return;
}

void greedy_activity_selector(activity A[], int n)
{
/*	printf("\nSorted activity:\n");
        printf("start		finish		duration\n");
    for(int i = 1; i <= n; i++)
        printf("%d		%d		%d\n", A[i].s, A[i].f, A[i].dur);
*/
	activity B[255];	//deklarasi activity yang nantinya berisi aktivitas yg terpilih
    int j=1;
	
	B[1] = A[1];
    
    for(int i=2; i<=n; i++)
    {
		if(B[j].f <= A[i].s)	//jika finish activity sebelumnya lebih dahulu selesai daripada start activity selanjutnya
		{
		    j++;
			B[j] = A[i];
		}
	}
    printf("\nTotal activity duration: %d",B[j].f - B[1].s);
    
	printf("\nChosen activities: ");

	for(int i = 1; i <= j; i++)
		printf("%d ",B[i].oldnum);
}

int main()
{
	activity A[255];	//deklarasi activity
	int n;				//jumlah activity
	
	printf("Choose your algorithm\n");
	printf("Shortest duration: 1\n");
	printf("Start first: 2\n");
	printf("Finish first: 3\n");
	
	printf("Choose your algorithm: ");
	scanf("%d",&greedy);
	if(greedy < 1 || greedy > 3)	
	{
		printf("\nthe algorithm number is incorrect.\n");
		return 0;
	}
	printf("\nPlease enter the number of activities: ");
	scanf("%d",&n);
	printf("Please enter start and finish point for each activity:\n");
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i].s);	//start point
		scanf("%d",&A[i].f);	//finish point
		A[i].dur = A[i].f - A[i].s;	//computing duration
		A[i].oldnum = i;
	}

	merge_sort(A, 1, n);	//sorting menggunakan merge sort dan sorting berdasarkan kode algoritma

	greedy_activity_selector(A, n);		//mencari solusi sesuai dengan array A yg telah disort sesuai algoritma

	return 0;
}
