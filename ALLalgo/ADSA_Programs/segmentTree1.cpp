#include "bits/stdc++.h"
using namespace std;
using LL = long long;


struct sgNode{
    LL minimum;
    LL maximum;
    LL sums;
    LL lazy;
    LL sz;
    sgNode(){};
    sgNode(LL _minimum,LL _maximum,LL _sums,LL _lazy,LL _sz):minimum(_minimum),maximum(_maximum),sums(_sums),lazy(_lazy),sz(_sz){};
};
vector<bool> isNode;
vector<sgNode> tree;
vector<LL> arr;
int N,SZ;

void buildTree(int left,int right,int n){
    if(left>right)return;
    if(left == right){
        tree[n] = {arr[left],arr[left],arr[left],0,1};
        isNode[n] = true;
        return;
    }
    else{
        int mid = (left+right)/2;
        buildTree(left,mid,2*n+1);
        buildTree(mid+1,right,2*n+2);
        isNode[n] = true;
        //tree[n].gcd = __gcd(tree[2*n+2].gcd,tree[2*n+1].gcd);
        tree[n].lazy = 0;
        tree[n].maximum = max(tree[2*n+1].maximum,tree[2*n+2].maximum);
        tree[n].minimum = min(tree[2*n+1].minimum,tree[2*n+2].minimum);
        tree[n].sums = tree[2*n+1].sums + tree[2*n+2].sums;
        tree[n].sz = right-left+1;
        return;
    }
}

void print_lazy(){
    for(int i=0;i<SZ;i++){
        cout<<"#"<<i<<":";
        if(isNode[i])
        cout<<tree[i].lazy<<" ";
        else cout<<"D ";
    }
    cout<<"\n";
}

void print_sumTree(){
    for(int i = 0 ; i < SZ ; i++){
        cout<<"#"<<i<<":";
        if(isNode[i])cout<<tree[i].sums<<"  ";
        else cout<<"D  ";
    }
    cout<<"\n";
}

void print_minTree(){
    for(int i = 0 ; i < SZ ; i++){
        cout<<"#"<<i<<":";
        if(isNode[i])cout<<tree[i].minimum<<"  ";
        else cout<<"D  ";
    }
    cout<<"\n";
}

void print_maxTree(){
    for(int i = 0 ; i < SZ ; i++){
        cout<<"#"<<i<<":";
        if(isNode[i])cout<<tree[i].maximum<<"  ";
        else cout<<"D  ";
    }
    cout<<"\n";
}


void range_update(LL v,LL left,LL right,LL nl,LL nr,LL delta){
    if(v>=SZ || nl>nr || ((nl>right || nr < left))) return;
    if(nl>=left && nr<=right && isNode[v]){
        tree[v].sums = tree[v].sums + tree[v].sz * (delta+tree[v].lazy);
        tree[v].minimum = tree[v].minimum+delta + tree[v].lazy;
        tree[v].maximum = tree[v].maximum+delta + tree[v].lazy;
        tree[v].lazy = 0;
        if(2*v+1 < SZ && isNode[2*v+1]) tree[2*v+1].lazy += delta;
        if(2*v+2 < SZ && isNode[2*v+2]) tree[2*v+2].lazy += delta;
    }
    else{
        LL mid = (nl+nr)/2;
        //if(2*v+2 < SZ)
        range_update(2*v+1,left,right,nl,mid,delta);
        range_update(2*v+2,left,right,mid+1,nr,delta);
        tree[v].minimum = min(tree[2*v+1].minimum,tree[2*v+2].minimum);
        tree[v].maximum = max(tree[2*v+1].maximum,tree[2*v+2].maximum);
        tree[v].sums = tree[2*v+1].sums + tree[2*v+2].sums;
    }
}

LL sum_query(LL v,LL left,LL right,LL nl,LL nr){
    if(nl > nr || v >= SZ || !isNode[v])return 0;
    if(nl<left || nr > right) return 0;
    if(nl >= left && nr <= right) return tree[v].sums;
    return sum_query(2*v+1,left,right,nl,(nl+nr)/2) + sum_query(2*v+2,left,right,(nl+nr)/2 + 1,nr);
}

LL min_query(LL v,LL left,LL right,LL nl,LL nr){
    if(nl > nr || v >= SZ || !isNode[v])return INT_MAX;
    if(nl<left || nr > right) return INT_MAX;
    if(nl >= left && nr <= right) return tree[v].minimum;
    return min(min_query(2*v+1,left,right,nl,(nl+nr)/2),min_query(2*v+2,left,right,(nl+nr)/2 + 1,nr));
}

LL max_query(LL v,LL left,LL right,LL nl,LL nr){
    if(nl > nr || v >= SZ || !isNode[v])return INT_MIN;
    if(nl<left || nr > right) return INT_MIN;
    if(nl >= left && nr <= right) return tree[v].maximum;
    return max(max_query(2*v+1,left,right,nl,(nl+nr)/2),max_query(2*v+2,left,right,(nl+nr)/2 + 1,nr));
}

int main(){
    cout<<"Enter Number of elements in array:\n";
    cin>>N;
    arr.assign(N,-1);
    cout<<"Enter Array Elements:\n";
    for(int i = 0 ; i < N; i++ ){
        cin>>arr[i];
    }
    SZ = N;
    int i = 1;
    while(i<N){
        i<<=1;
    }
    SZ = 2*i-1;
    tree.assign(SZ,{INT_MAX,INT_MIN,0,0,0});
    isNode.assign(SZ,false);
    buildTree(0,N-1,0);
    print_maxTree();
    int Q;
    cout<<"Enter number of Queries:\n";
    cin>>Q;
    int opt;
    cout<<"Enter 1 for query ,2 for range update\n";
    while(Q--){
        cin>>opt;
        if(opt == 1){
            int l,r;
            cin>>l>>r;
            cout<<sum_query(0,l,r,0,N-1)<<"\n";
            print_maxTree();
        }
        else{
            int l,r,delta;
            cin>>l>>r>>delta;
            range_update(0,l,r,0,N-1,delta);
            print_lazy();
        }
    }
}