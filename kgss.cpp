#include<bits/stdc++.h> 
#define MAX 400000
using namespace std;


struct snode{
  int max1;
  int max2;
  snode(){}
  snode(int a, int b){
    max1 = a;
    max2 = b;
  }
};

typedef struct snode sNode;

sNode minArr[MAX];

int findMax(int a, int b){
  return a > b ? a : b;
}

sNode findMaxSNode(sNode s1, sNode s2){
  sNode newSNode;
  newSNode.max1 = findMax(findMax(s1.max1, s1.max2), findMax(s2.max1, s2.max2));
  int x = INT_MIN;
  if(s1.max1 != newSNode.max1 && s1.max1 >= x){
    x = s1.max1;
  }
  if(s1.max2 != newSNode.max1 && s1.max2 >= x){
    x = s1.max2;
  }
  if(s2.max1 != newSNode.max1 && s2.max1 >= x){
    x = s2.max1;
  }
  if(s2.max2 != newSNode.max1 && s2.max2 >= x){
    x = s2.max2;
  }
  newSNode.max2 = x;
  return newSNode;
}


sNode buildSegTree(int node, int ll, int rl, int arr[]){
  if(ll == rl){
    minArr[node].max1=arr[ll];
    minArr[node].max2=arr[ll];
    return minArr[node];
  }
  sNode lc = buildSegTree(node * 2, ll, ll + (rl - ll)/2, arr);
  sNode rc = buildSegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, arr);
  minArr[node] = findMaxSNode(lc, rc);
  return minArr[node];
}


void printSegTree(int node, int ll, int rl, int arr[]){
  cout<<minArr[node].max1<<","<<minArr[node].max2<<" ";
  if(ll == rl){
    return; 
  }
  printSegTree(node * 2, ll, ll + (rl - ll)/2, arr);
  printSegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, arr);
}


sNode querySegTree(int node, int ll, int rl, int i, int j, int arr[]){

  if(j < ll || i > rl){
    sNode temp;
    temp.max1 = temp.max2 = -1;
    return temp;
  }
  if(i <= ll && rl <= j)
    return minArr[node];

  sNode lc = querySegTree(node * 2, ll, ll + (rl - ll)/2, i, j, arr);
  sNode rc = querySegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, i, j, arr);
  if(lc.max1 == -1)
    return rc;
  if(rc.max1 == -1)
    return lc;
  return findMaxSNode(lc,rc);
}


sNode updateSegTree(int node, int ll, int rl, int i, int arr[]){

  if(i < ll || i > rl)
    return minArr[node];
  if(i == ll && rl == i){
    minArr[node].max1=arr[i];
    minArr[node].max2=arr[i];
    return minArr[node];
  }

  sNode lc = updateSegTree(node * 2, ll, ll + (rl - ll)/2, i, arr);
  sNode rc = updateSegTree(node * 2 + 1, ll + (rl - ll)/2 + 1, rl, i, arr);
  return minArr[node] = findMaxSNode(lc, rc); 
}

int sumNode(sNode s1){
  return s1.max1+s1.max2;
}

int main(){
  int n, q, i, j;
  cin>>n;
  int arr[n];
  for(int i=0; i<n; i++){
   cin>>arr[i]; 
  }
  buildSegTree(1, 0, n-1, arr);
  scanf("%d", &q);
  char op;
  while(q--){
    getchar();
    scanf("%c%d%d", &op, &i, &j);
//    cout<<"Input "<<op<<" "<<i<<" "<<j<<endl;
    if('Q' == op){
      cout<<sumNode(querySegTree(1, 0, n-1, i-1, j-1, arr))<<endl;
    }
    if('U' == op){
      arr[i-1] = j;
      updateSegTree(1, 0, n-1, i-1, arr);
    }
  }
//  int i, j;
//  cin>>i>>j;
//  sNode s1 = querySegTree(1, 0, n-1, i, j, arr);
//  cout<<"Query range "<<i<<","<<j<<" : "<<s1.max1<<","<<s1.max2<<endl;
//  int x,y;
//  cin>>x>>y;
//  cout<<"Index "<<x<<", Value "<<y<<endl;
//  arr[x]=y;
//  updateSegTree(1, 0, n-1, x, arr);
//  s1 = querySegTree(1, 0, n-1, i, j, arr);
//  cout<<"Query range "<<i<<","<<j<<" : "<<s1.max1<<","<<s1.max2<<endl;
//  printSegTree(1, 0, n-1, arr);
  return 0;
}


