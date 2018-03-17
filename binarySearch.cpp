#include "./stdc++.h"

using namespace std;

int binarySearch(int l, int r, int x, int *arr){
	int mid = l;
	while(l < r){
		mid  = l + (r - l)/2;
		if(x < arr[mid])
			r = mid-1;
		else if (x > arr[mid])
			l = mid;
		else
			return mid;
	}
	return r;
}

int main(){
	int n;
	cin>>n;
	int *arr=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++) {
		cin>>arr[i];
		cout<<" i : "<<arr[i]<<endl;
	}
	int x;
	cin>>x;
	cout<<binarySearch(0,n-1,x,arr)<<endl;
	return 0;
}

