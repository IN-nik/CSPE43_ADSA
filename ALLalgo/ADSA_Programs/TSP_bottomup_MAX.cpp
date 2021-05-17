#include "bits/stdc++.h"
#define countSetBits(n) __builtin_popcountll(n);
#define LL long long
using namespace std;

int V;//Number of Vertices in Graph
int starting;
vector<vector<LL>> AM,vec1,dp;
vector<LL> vec2;
int findLeftMostSetBit(LL mask){
    int l = 0;
    while(mask >>= 1)l++;
    return l;
}
string printSubset(LL mask){
    if(mask == 0) return "PHI";
    string res = "{";
    int i,j;
    int x = findLeftMostSetBit(mask);
    for(i=0;i<x;i++){
        if((1<<i) & mask){
            j = i+1;
            res = res + to_string(j) + ",";
        }
    }
    j = x+1;
    res = res + to_string(j);
    res = res + "}";
    return res;
}

//here   i is ZeroIndexed based
LL setDifference(LL a,int i){
    return ~(1<<(i)) & a;
}

int main(){
    ios_base::sync_with_stdio(false);
    //freopen("tsp_in.txt.txt","r",stdin);
    //freopen("tsp_out.txt","w",stdout);
    cout<<"Enter Number of Cities:\n";
    cin>>V;
    AM.assign(V,vector<LL>(V,0));
    dp.assign(V+1,vector<LL>((1<<V)+1,-1));
    vec1.resize(V+1);
    cout<<"Enter Adjacency matrix of the Graph:\n";
    for(int i = 0;i<V;i++){
        for(int j = 0; j<V;j++){
            cin>>AM[i][j];
        }
    }

    cout<<"Enter Starting Point: (1 index based)\n";
    cin>>starting;
    LL setExceptStartingPoint = (1<<V) - 1;
    setExceptStartingPoint = setDifference(setExceptStartingPoint,starting-1);
    for(int i=0;i<(1<<V);i++){
        if((1<<i)&setExceptStartingPoint) vec2.push_back(i);
    }
    //Generating Sets based on Number of set Bits
    for(LL i=0 ; i<(1<<V) ; i++ ){
        int j = countSetBits(i);
        vec1[j].push_back(i);
    }
    cout<<"Step 1\n";
    for(int i = 0;i<V;i++){
        if(i == starting-1)continue;
        dp[i][starting-1] = AM[i][starting-1];
        cout<<"g("<<i+1<<",PHI) = "<<dp[i][starting-1]<<"\n";
    }
    for(int steps = 2;steps < V ; steps ++){
        cout<<"Step "<<steps<<"\n";
        for(int vs : vec2){
            for(LL mask1 : vec1[steps-1]){
                if((1<<vs)&mask1 || (1<<(starting-1))&mask1)continue;
                LL tmp = INT_MAX;
                cout<<"g("<<vs+1<<","<<printSubset(mask1)<<")=";
                cout<<"max{";
                for(int k=0;k<V;k++){
                    if(k==starting-1 || k==vs)continue;
                    if((1<<k)&mask1){
                         cout<<"C["<<vs+1<<"]["<<k+1<<"]+g("<<k+1<<","<<printSubset(setDifference(mask1,k))<<") ,";
                         tmp = max(tmp,AM[vs][k]+dp[k][setDifference(mask1,k)]);
                    }
                }
                cout<<"}=\t";dp[vs][mask1] = tmp;
                cout<<"max{";
                for(int k=0;k<V;k++){
                    if(k==starting-1 || k==vs)continue;
                    if((1<<k)&mask1){
                         cout<<"("<<AM[vs][k]<<"+"<<dp[k][setDifference(mask1,k)]<<") ,";
                    }
                }
                cout<<"}=\t"<<tmp<<"\n";
            }
        }
    }

    cout<<"Step "<<V<<"\n";
    cout<<"g("<<starting<<","<<printSubset(setDifference((1<<V)-1,starting-1))<<"=";
    cout<<"max{";
    LL tmp = INT_MAX;
    for(LL mask1 : vec1[V-1]){
        if((1<<(starting-1))&mask1)continue;
        for(int vs=0; vs<V;vs++){
            if((1<<vs)&mask1){
                tmp = max(tmp,AM[starting-1][vs]+dp[vs][setDifference(mask1,vs)]);
                cout<<"C["<<starting<<"]["<<vs+1<<"]+g("<<vs+1<<","<<printSubset(setDifference(mask1,vs))<<",";
            }
        }
        dp[starting-1][mask1] = tmp;
        cout<<"}=\t";

    }

    cout<<"max{";
    for(LL mask1 : vec1[V-1]){
        if((1<<(starting-1))&mask1)continue;
        for(int vs=0; vs<V;vs++){
            if((1<<vs)&mask1){
                cout<<"("<<AM[starting-1][vs]<<"+"<<dp[vs][setDifference(mask1,vs)]<<"), ";
            }
        }
        cout<<"}=\t"<<tmp;
    }

}