#include "bits/stdc++.h"
using namespace std;

vector<int> lps(const string &s){
    int n = s.length();
    vector<int> res(n);
    cout<<"lps[0]=0\n";
    for(int i = 1; i < n ; i++){
        cout<<"For i = "<<i<<": \nj = lps[j-1] = "<<res[i-1]<<'\n';
        int j = res[i-1];
        while(j>0 && s[i]!=s[j]){
            cout<<"j>0 && str["<<i<<"]!=str["<<j<<"]. So j = lps[j-1] = "<<res[j-1]<<"\n";
            j = res[j-1];
        }
        if(s[i] == s[j]){
            cout<<"str["<<i<<"] == str["<<j<<"]. j++";
            j++;
        }
        cout<<"lps["<<i<<"] = "<<j<<"\n";
        res[i] = j;
    }

    return res;
}

string text,pattern;


int main(){
    cout<<"Enter text:\n";
    cin>>text;
    cout<<"Enter pattern:\n";
    cin>>pattern;
    int i =0 ,j = 0;
    int N = text.length();
    int M = pattern.length();
    vector<int> pi = lps(pattern);
    cout<<"The LPS array is as :\n";
    for(int i = 0 ; i < pi.size() ; i++){
        cout<<pi[i]<<" ";
    }
    cout<<"\n";
    while( i < N ){
        if(pattern[j] == text[i]){
            cout<<pattern[j]<<" = "<<text[i]<<",i++;j++\n";
            i++;
            j++;
        }

        if(j==M){
            cout<<"Pattern at index "<<i-j<<"\n";
            j = pi[j-1];
        }
        else if(i<N && pattern[j] != text[i]){
            if(j!=0){
                j = pi[j-1];
            }
            else{
                i = i+1;
            }
        }
    }
}