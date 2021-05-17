#include "bits/stdc++.h"
using namespace  std;

int N;//Number of keys
vector<double> P,Q;

int main(){
    ios_base::sync_with_stdio(false);
    //freopen("optbst_in.txt","r",stdin);
    //freopen("optbst_out.txt","w",stdout);
    cout<<"Enter number of keys\n";
    cin>>N;
    P.resize(N+1);Q.resize(N+1);
    P[0] = 0;
    cout<<"Enter Succesful Probabilities:\n";
    for(int i = 1; i <= N ; i++ ){
        cin>>P[i];
    }
    cout<<"Enter Unsuccesful Probabilities\n";
    for(int i = 0; i <=0; i++ ){
        cin>>Q[i];
    }
    for(int i = 1 ; i <=N ;i++){
        Q[i] = 1-P[i];
        cout<<fixed<<setprecision(3)<<Q[i]<<"\n";
    }

    double W[N+1][N+1]={0},C[N+1][N+1]={0};
    vector<int> root[N+1][N+1];
    cout<<"Computing W array..................\n";
    for( int i = 0 ; i <= N ; i++ ){
        for( int j = i; j <= N ; j++ ){
            if( j == i) {
                C[i][j] = 0;
                root[i][j].emplace_back(0);
                W[i][j] = Q[i];
                //Check Indentation
                cout<<"W["<<i<<"]["<<j<<"] = "<<Q[j]<<"\n";
            }
            else{
                W[i][j] = W[i][j-1] + P[j] + Q[j];
                //Check
                cout<<"W["<<i<<"]["<<j<<"] = "<<W[i][j-1]<<" + "<<P[j]<<" + "<<Q[j]<<" = "<<W[i][j]<<"\n";
            }
        }
    }

    cout<<"\nComputing Cost Array................................\n";
    
    cout<<"For j-i=0\n";
    for(int i = 0; i <= N ; i++){
        cout<<"C["<<i<<"]["<<i<<"]=0\t";
    }
    cout<<"\n";

    for( int diff = 1 ; diff <= N ; diff++){
        cout<<"Computing For j-i = "<<diff<<"\n";
        for(int i = 0; i <= N ; i++)
            for(int j = i+diff;j <= i+diff && j<=N ; j++){
                double temp = 1e10;
                cout<<"C["<<i<<"]["<<j<<"] = min (";
                for( int k = i+1 ; k<=j ; k++){
                    temp = min(temp,C[i][k-1]+C[k][j]);
                    cout<<C[i][k-1]+C[k][j]<<" | ";
                }cout<<") + "<<W[i][j]<<" = "<<temp<<"+ "<<W[i][j]<<" = ";
                C[i][j] = temp + W[i][j];
                cout<<C[i][j]<<"\n";
                for(int k = i+1; k <= j ; k++){
                    if(C[i][k-1]+C[k][j] == temp )root[i][j].push_back(k);
                }
            }
    }

    cout<<"\nFinal Minimum cost = "<<C[0][N]<<"\n";

    cout<<"Now Possible roots of each possible subtree:\n";
    for(int i = 0 ; i <= N ; i++ ){
        for( int j = i ; j <= N ; j++){
            cout<<"root["<<i<<","<<j<<"] :- ";
            for(int k = 0 ; k < root[i][j].size() ; k++ ){
                cout<<root[i][j][k]<<" ";
            }
            cout<<"\n";
        }
    }

}