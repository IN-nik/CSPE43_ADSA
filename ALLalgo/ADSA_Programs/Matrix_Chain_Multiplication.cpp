#include <iostream>
#include <vector>
#include <list>
#include<string>

#define INF 10000000

using namespace std;

int min(int a, int b) { return a < b ? a : b; }
int min(int a, int b, int c) { return min(a, min(b, c)); }

void mcm(vector<vector<int>>& cost, vector<vector<int>>& split, vector<int>& dims, int n) {
    for(int i = 1; i < n; i++)
        cost[i][i] = 0;
    for(int i = 1; i < n - 1; i++)
        split[i][i + 1] = i;
    for(int x = 2; x < n; x++)  {
        for(int i = 1; i < n - x + 1; i++) {
            int j = i + x - 1;
            cost[i][j] = INF;
            for(int k = i; k < j; k++) {
               int new_cost = cost[i][k] + cost[k + 1][j] + dims[i - 1] * dims[j] * dims[k];
               if(new_cost < cost[i][j]) {
                   cost[i][j] = new_cost;
                   split[i][j] = k;
               }
            }
        }
    }
}

void print_exp(list<string>& exp) {
    for(list<string>::iterator it = exp.begin(); it != exp.end(); ++it)
        cout << *it << " ";
    cout << "\n";
}

void insert_brackets(list<string>& exp, int l, int r, vector<vector<int>>& split) {
    if(l == r)
        return;
    
    string open_before = 'A'+to_string(l);
    string close_after = 'A'+to_string(r);
    string split_after = 'A'+to_string(split[l][r]);

    if(split[l][r] == l)
        split_after = "X";

    for(list<string>::iterator it = exp.begin(); it != exp.end(); ++it) {
        if(*it == open_before) {
            if(it == exp.begin())
                exp.push_front("(");
            else
                exp.insert(it, "(");
        } else if(*it == close_after) {
            exp.insert(++it, ")");
        } else if(*it == split_after) {
            exp.insert(++it, ")");
            exp.insert(it, "(");
        }
    }
    int x = split[l][r];

    insert_brackets(exp, l, x, split);
    insert_brackets(exp, x+1, r, split);
}

int main() {
	int n;
	
	cout << "Enter the number of matrices: ";
	cin >> n;
	n++;
	vector<int> dims(n);

	for(int i = 0; i < n; i++) {
		cout << "Enter P" << i << ": ";
		cin >> dims[i];
	}

	vector<vector<int>> cost(n, vector<int>(n, -1));
	vector<vector<int>> split(n, vector<int>(n, 0));

        mcm(cost, split, dims, n);

	cout << "Cost Matrix\n";

	for(int i = 1; i < n; i++) {
		for(int j = 1; j < n; j++)
		    cout << cost[i][j] << "\t";
		cout << "\n";
	}

	cout << "Split Matrix\n";

	for(int i = 1; i < n; i++) {
		for(int j = 1; j < n; j++) 
		    cout << split[i][j] << "\t";
		cout << "\n";
	}

	cout << "Minimum number of multiplications is: " << cost[1][n - 1] << "\n";
	cout << "The grouping for multiplication is: ";
	
        list<string> ans;
        for(int i = 0; i < n - 1; i++)
            ans.emplace_back('A'+to_string(i+1));
        insert_brackets(ans, 1, n-1, split);
        ans.push_back(")");
        for(string x: ans)
            cout << x;
        cout << "\n";
	return 0;
}
