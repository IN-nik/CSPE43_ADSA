#include <iostream>
#include <stack>
#include <queue>
#include <limits>
#include <vector>

using namespace std;

struct Node {
	int id;
	int parent_id;
	float lower_bound;
	float upper_bound;
	vector<char> path;
	Node() {
		id = -1;
		parent_id = -1;
		lower_bound = 0;
		upper_bound = 0;
		path.resize(0);
	}
	Node(const int& pid, const int& _id, const float& lb, const float& ub) {
		id = _id;
		parent_id = pid;
		lower_bound = lb;
		upper_bound = ub;
		path.resize(0);
	}
	friend bool operator<(const Node& l, const Node& r) {
		if(l.lower_bound == r.lower_bound)
			return l.upper_bound > r.upper_bound;
		else
			return l.lower_bound > r.lower_bound;
	}
};

stack<Node> st;
queue<Node> q;
priority_queue<Node> pq;

float global_upper_bound = numeric_limits<float>::max();
vector<float> wt, val;
int n, id_num = 1;
float W;

Node get_next(int op) {
	Node next_node;
	switch(op) {
		case 1: next_node = st.top();st.pop();break;
		case 2: next_node = q.front();q.pop(); break;
		case 3: next_node = pq.top();pq.pop();break;
	}
	return next_node;
}

void push_node(Node node, int op) {
	switch(op) {
		case 1: st.push(node);break;
		case 2: q.push(node);break;
		case 3: pq.push(node);break;
	}
}

void knapsack(int op) {
	int i;
	float ub, lb, w;

	for(i = 0; i < n && (w + wt[i] <= W); ++i) {
		w += wt[i];
		ub += val[i];
	}
	lb = ub + ((1.0 * (W - w)) / wt[i]) * (i < n  ? val[i] : 0);
	if(ub < global_upper_bound) {
		global_upper_bound = ub;
		cout << "Global UB updated to " << global_upper_bound
			<< " by node 1\n";
	}
	
	Node node(0, id_num++, lb, ub);
	push_node(node, op);
	cout << "Pushed node 1 with LB = " << lb
		<< " and UB = " << ub << " at level 0\n";
	
	while(!st.empty() || !q.empty() || !pq.empty()) {
		Node nxt = get_next(op);
		cout << "Next node is node " << nxt.id << "\n";
	
		if(nxt.lower_bound > global_upper_bound) {
			cout << "Kill node " << nxt.id << " at level " 
				<< nxt.path.size() << " as LB > Global UB\n";
			continue;
		}
		if(nxt.path.size() == n) {
			cout << "Node " << nxt.id << " is in last level\n";
			cout << "Items: ";
			int i = 1;
			for(char x: nxt.path) {
				if(x == '1')
					cout << i << ", ";
				++i;
			}
			cout << "\n";
			continue;
		}
		float ub0 = 0, ub1 = 0, w0 = 0, w1 = 0;
		int i = 0;
		for(char x: nxt.path) {
			ub0 += x == '1' ? val[i] : 0;
			w0 += x == '1' ? wt[i] : 0;
			++i;
		}

		ub1 = ub0 + val[i];
		w1 = w0 + wt[i];
		int j = ++i;
		if(w1 <= W) {
			Node nxt1(nxt.id, id_num++, 0, 0);
			nxt1.path = nxt.path;
			nxt1.path.push_back('1');
			while(i < n && (wt[i] + w1 <= W)) {
				w1 += wt[i];
				ub1 += val[i];
				++i;
			}
			nxt1.upper_bound = ub1;
			nxt1.lower_bound = ub1 + ((1.0 * (W - w1)) / wt[i]) * (i < n  ? val[i] : 0);
			if(nxt1.lower_bound > global_upper_bound) {
				cout << "Kill node " << nxt1.id << " as LB > Global UB; "
					<<	"LB = " << nxt1.lower_bound << " UB = " << nxt1.upper_bound
					<<	" at level " << nxt1.path.size() <<"\n";
			} else {
				push_node(nxt1, op);
				cout << "Pushed node " << nxt1.id << " with LB = "
					<< nxt1.lower_bound << " UB = " << nxt1.upper_bound 
					<< " parent " << nxt1.parent_id << "->1 at level " << nxt1.path.size() <<"\n";
				if(nxt1.upper_bound < global_upper_bound) {
					global_upper_bound = nxt1.upper_bound;
					cout << "Global UB updated to " << global_upper_bound
						<< " by node " << nxt1.id << "\n";
				}
			}	
		} else {
			cout << "Kill node " << id_num++ 
				<< " parent " << nxt.id << "->1 at level "
				<< nxt.path.size() + 1 << " as capacity is exceeded\n";
		}
		Node nxt0(nxt.id, id_num++, 0, 0);
		nxt0.path = nxt.path;
		nxt0.path.push_back('0');
		while(j < n && (wt[j] + w0 <= W)) {
			w0 += wt[j];
			ub0 += val[j];
			++j;
		}			
		nxt0.upper_bound = ub0;
		nxt0.lower_bound = ub0 + ((1.0 * (W - w0)) / wt[j]) * (j < n  ? val[j] : 0);
		
		if(nxt0.lower_bound > global_upper_bound) {
			cout << "Kill node " << nxt0.id << " as LB > Global UB; "
				<<	"LB = " << nxt0.lower_bound << " UB = " << nxt0.upper_bound
				<<	" at level " << nxt0.path.size() <<"\n";
		} else {
			push_node(nxt0, op);
			cout << "Pushed node " << nxt0.id << " with LB = "
				<< nxt0.lower_bound << " UB = " << nxt0.upper_bound 
				<< " parent " << nxt0.parent_id << "->0 at level " << nxt0.path.size() << "\n";
			if(nxt0.upper_bound < global_upper_bound) {
				global_upper_bound = nxt0.upper_bound;
				cout << "Global UB updated to " << global_upper_bound
					<< " by node " << nxt0.id << "\n";
			}
		}
	}
	cout << "Answer: " << -1 * global_upper_bound << "\n";
}

int main() {
	int op;
	cout << "Enter the number of items: ";
	cin >> n;
	wt.assign(n, 0);
	val.assign(n, 0);
	cout << "Enter weights array: ";
	for(int i = 0; i < n; ++i)
		cin >> wt[i];
	cout << "Enter profits array(positive): ";
	for(int i = 0; i < n; ++i) {
		cin >> val[i];
		val[i] *= -1;
	}
	cout << "Enter the capacity: ";
	cin >> W;
	cout << "Enter the type of branch and bound\n"
		<<	"1. LIFO\n"
		<<	"2. FIFO\n"
		<<	"3. Least Cost\n";
	cin >> op;
	knapsack(op);
	return 0;
}