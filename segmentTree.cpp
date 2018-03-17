#include "stdc++.h"
#define MAX 400000
using namespace std;

int minArr[MAX];

int buildSegTree(int node, int ll, int rl, int arr[]){
  if(ll == rl){
    return minArr[node]=arr[ll];
  }
  int lc = buildSegTree(node * 2, ll, ll + (rl - ll)/2, arr);
  int rc = buildSegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, arr);
  minArr[node] = lc < rc ? lc : rc;
  return minArr[node];
}


void printSegTree(int node, int ll, int rl, int arr[]){
  cout<<minArr[node]<<" ";
  if(ll == rl){
    return; 
  }
  printSegTree(node * 2, ll, ll + (rl - ll)/2, arr);
  printSegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, arr);
}


int querySegTree(int node, int ll, int rl, int i, int j, int arr[]){

  if(j < ll || i > rl)
    return -1;
  if(i <= ll && rl <= j)
    return minArr[node];

  int lc = querySegTree(node * 2, ll, ll + (rl - ll)/2, i, j, arr);
  int rc = querySegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, i, j, arr);
  if(lc == -1)
    return rc;
  if(rc == -1)
    return lc;
  return lc < rc ? lc : rc;
}


int updateSegTree(int node, int ll, int rl, int i, int arr[]){

  if(i < ll || i > rl)
    return minArr[node];
  if(i == ll && rl == i)
    return minArr[node]=arr[i];

  int lc = updateSegTree(node * 2, ll, ll + (rl - ll)/2, i, arr);
  int rc = updateSegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, i, arr);
  return minArr[node] = lc < rc ? lc : rc; 
}

int main(){
  int n;
  cin>>n;
  int arr[n];
  for(int i=0; i<n; i++){
   cin>>arr[i]; 
  }
  buildSegTree(1, 0, n-1, arr);
  int i, j;
  cin>>i>>j;
  cout<<"Query range "<<i<<","<<j<<" : "<<querySegTree(1, 0, n-1, i, j, arr)<<endl;
  int x,y;
  cin>>x>>y;
  cout<<"Index "<<x<<", Value "<<y<<endl;
  arr[x]=y;
  updateSegTree(1, 0, n-1, x, arr);
  cout<<"Query range "<<i<<","<<j<<" : "<<querySegTree(1, 0, n-1, i, j, arr)<<endl;
  printSegTree(1, 0, n-1, arr);
  cout<<endl;
  return 0;
}


