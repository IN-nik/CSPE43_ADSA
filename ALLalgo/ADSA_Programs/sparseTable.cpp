#include <bits/stdc++.h>
using namespace std;


struct Node{
    int minID,maxID,sum;
    Node(int _minID=-1,int _maxID = -1,int _sum=0):minID(_minID),maxID(_maxID),sum(_sum){};

};

int rows,cols;
vector<vector<Node>> sparse;
vector<int> immut;
vector<vector<bool>> isValid;

Node merge(const Node &A,const Node &B){
    Node res = {immut[A.minID]<immut[B.minID] ? A.minID:B.minID ,immut[A.maxID] > immut[B.maxID] ? A.maxID : B.maxID,A.sum+B.sum};
    return res;
}
inline void build(){
    for(int i = 0; i < rows ; i++){
        sparse[i][0] = {i,i,immut[i]};
        isValid[i][0] = true;
    }
    for(int j = 1 ; j < cols ;j++){
        for(int i = 0 ; i + (1 <<j) <= rows ;i++){
            cout<<"st["<<i<<"]["<<j<<"] = "<<"f(st["<<i<<"]["<<j-1<<"],st["<<(i+(1<<(j-1)))<<"]["<<j-1<<"])\n";
            sparse[i][j] = merge(sparse[i][j-1],sparse[i+(1<<(j-1))][j-1]);
            isValid[i][j] = true;
        }
    }
}

void print_minsparse(){
    cout<<"Minimum Sparse Table is as :\n";
    for(int i = 0 ; i < rows ; i++){
        for(int j = 0 ; j < cols ; j++){
            if(isValid[i][j]){
                cout<<sparse[i][j].minID<<"  ";
            }
            else cout<<"D  ";
        }
        cout<<"\n";
    }
}

void print_maxsparse(){
    cout<<"Maximum Sparse Table is as ;\n";
    for(int i = 0 ; i < rows ; i++){
        for(int j = 0 ; j < cols ; j++){
            if(isValid[i][j]){
                cout<<sparse[i][j].maxID<<"  ";
            }
            else cout<<"D  ";
        }
        cout<<"\n";
    }
}

void print_sumsparse(){
    cout<<"Summation Sparse Table is as :\n";
    for(int i = 0 ; i < rows ; i++){
        for(int j = 0 ; j < cols ; j++){
            if(isValid[i][j]){
                cout<<sparse[i][j].sum<<"  ";
            }
            else cout<<"D  ";
        }
        cout<<"\n";
    }
}

void print_minquery(int left ,int right){
    int ans = INT_MAX;
    int ansID = -1;
    cout<<"ans = INF\n";
    cout<<"For range : "<<left<<"-"<<right<<" we will need results of st[";
    for(int j = cols-1 ; j >= 0 ; j--){
        if((1<<j)<=right-left+1){
            cout<<left<<"]["<<j<<"] , [";
            ans = min(ans,immut[sparse[left][j].minID]);
            left += (1<<j);
        }
    }
    cout<<"\n";
    cout<<ans<<"\n";
}
void print_maxquery(int left ,int right){
    int ans = INT_MIN;
    int ansid = -1;
    cout<<"ans = -INF\n";
    cout<<"For range : "<<left<<"-"<<right<<" we will need results of st[";
    for(int j = cols-1 ; j >= 0 ; j--){
        if((1<<j)<=right-left+1){
            cout<<left<<"]["<<j<<"] , [";
            ans = max(ans,immut[sparse[left][j].maxID]);
            left += (1<<j);
        }
    }
    cout<<ans<<"\n";
}
void print_sumquery(int left ,int right){
    int ans = 0;
    cout<<"For range : "<<left<<"-"<<right<<" we will need results of st[";
    for(int j = cols-1 ; j >= 0 ; j--){
        if((1<<j)<=right-left+1){
            cout<<left<<"]["<<j<<"] , [";
            ans = ans + sparse[left][j].sum;
            left += (1<<j);
        }
    }
    cout<<ans<<"\n";
}

int main(){
    cout<<"Enter nummber of elements:\n";
    cin>>rows;
    cols = log2(rows)+1;
    sparse.resize(rows,vector<Node>(cols));
    isValid.assign(rows,vector<bool>(cols,false));
    immut.resize(rows);
    for(int i = 0 ; i < rows ;i++){
        cin>>immut[i];
    }
    build();
    print_minsparse();
    //print_maxsparse();
    //print_sumsparse();
    cout<<"Enter number of queries :\n";
    int q;
    cin>>q;
    for(int k = 1 ; k <= q ; k++){
        cout<<"Query #"<<k<<":\n";
        int left,right;
        cin>>left>>right;
        print_minquery(left,right);
        //print_maxquery(left,right);
        //print_sumquery(left,right);
    }
}