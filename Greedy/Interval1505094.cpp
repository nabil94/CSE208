#include<iostream>
#define INFINITY 99999;

using namespace std;


struct interval{
    int start,finish;
};

void Merge(interval A[],int p,int q,int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    interval L[n1],R[n2];

    for(int m = 0; m < n1; m++)
        L[m] = A[p+m];

    for(int m = 0; m < n2; m++)
        R[m] = A[q+m+1];

   // L[n1] = INFINITY;
    //R[n2] = INFINITY;

    int i = 0;
    int j = 0;
    for(int k = p; k <= r; k++){
        if(L[i].finish <= R[j].finish){
            A[k] = L[i];
            i++;
        }
        else{
            A[k] = R[j];
            j++;
        }
    }
}

void mergeSort(interval a[],int p,int r){
    if(p < r){
        int q = (p + r)/2;
        mergeSort(a,p,q);
        mergeSort(a,q+1,r);
        Merge(a,p,q,r);
    }
}

/*
int intervalScheduling(interval a[],int n){
    int sum = 0;
    int left = 0;
    int right = n;
    mergeSort(a,left,right);

    int j = 0;

    cout<<a[j].start<<" "<<a[j].finish<<endl;

    for(int i = 1;i < n;i++){
        if(a[i].start >= a[j].finish){
            cout<<a[i].start<<" "<<a[i].finish<<endl;
            sum++;
            j = i;
        }
    }

    //cout<<sum+1;

}*/



int main(){
    int n;
    cin>>n;
    interval a[n];
    for(int i = 0; i < n; i++){
        cin>>a[i].start>>a[i].finish;
    }
    cout<<"Answer is"<<endl;
    int sum = 1;
    int left = 0;
    int right = n;
    mergeSort(a,left,right);

    int k = 0;
    for(int i = 1; i < n;i++){
        if(a[i].start >= a[k].finish){
            sum++;
            k = i;
        }

    }
    cout<<sum<<endl;
    cout<<a[0].start<<" "<<a[0].finish<<endl;
    k = 0;
    for(int i = 1; i < n;i++){
        if(a[i].start >= a[k].finish){
            cout<<a[i].start<<" "<<a[i].finish<<endl;
            k = i;
        }

    }


    return main();
}
