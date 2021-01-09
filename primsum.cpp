#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2,fma")
using namespace std;
using LL = unsigned long long;
LL func(LL N){
    unordered_map<LL,LL> dp;vector<LL> V;LL r = sqrt(N);
    for(LL i=0;i<r;i++){ V.push_back(N/(i+1));}
    for(LL i=0;i<r;i++){V.push_back(V[V.size()-1]-1);}
    for(LL i=0;i<V.size();i++){ dp[V[i]] = ((V[i]*(V[i]+1))>>1)-1;}
    for(LL p = 2;p<=r;p++){
        if(dp[p]>dp[p-1]){
            LL sp = dp[p-1],p2 = p*p;
            for(LL i=0;i<V.size();i++){
                if(V[i]<p2){
                    break;
                }
                dp[V[i]] = dp[V[i]] - p*(dp[V[i]/p]-sp);
            }
        }
    }
    return dp[N];
}
int main(){ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);LL N;cin>>N;cout<<func(N);}