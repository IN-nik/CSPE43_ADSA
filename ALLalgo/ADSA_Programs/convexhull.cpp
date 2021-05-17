#include <bits/stdc++.h>
using namespace std;
using LF = double;

struct Point{
    LF x,y;
    int ID;
};


Point P0;
int N;

template<typename T>
T nextToTop(stack<T> &stk){
    Point p = stk.top();
    stk.pop();
    Point q = stk.top();
    stk.push(p);
    return q;
}

LF sqDist(const Point &p,const Point &q){
    return (p.x - q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y);
}

int orientation(const Point &p, const Point &q,const  Point &r){
	LF  val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // colinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}


bool comp(const Point &A,const Point &B){
    LF o = orientation(P0,A,B);
    if(o == 0){
        return sqDist(P0,B) >= sqDist(P0,A);
    }
    return o==2;
}
int cnt;
inline void ConvexHull(vector<Point> &points){
    pair<LF,int> mn = make_pair(points[0].y,0);
    for(int i = 0 ; i < N ; i++){
        mn = min(mn,{points[i].y,i});
    }
    swap(points[0],points[mn.second]);
    auto it = points.begin();
    P0 = *it;
    cout<<"P0 is ("<<P0.x<<","<<P0.y<<")\n";
    it++;
    sort(it,points.end(),comp);
    cout<<"After Sorting according to polar angle points are as\n";
    for(int i = 0 ; i < N ; i++){
        cout<<"("<<points[i].x<<","<<points[i].y<<") ";
    }
    cout<<"\n\n";
    cout<<"If two or more points make same angle with P0,Remove all but the one that is farthest from P0.\n\n";
    vector<Point> cons = {P0};
    for(int i = 1 ; i < N ; i++){
        while(i < N-1 && orientation(P0,points[i],points[i+1]) == 0)i++;
        cons.push_back(points[i]);
    }
    assert(cons.size() >= 3);
    cout<<"Applying Graham Scan now on the following points :\n";
    for(auto x : cons){
        cout<<"("<<x.x<<","<<x.y<<")\t";
    }
    cout<<"\n";
    //cout<<"Push Points P0 ,P1 on a stack:\n";
    stack<Point> stk;
    stk.push(P0);
    cout<<"Push point P0 ("<<P0.x<<","<<P0.y<<") to the stack.\n";
    stk.push(cons[1]);
    cout<<"Push point P1 ("<<cons[1].x<<","<<cons[1].y<<") to the stack.\n";
    stk.push(cons[2]);
    cout<<"Push point P2 ("<<cons[2].x<<","<<cons[2].y<<") to the stack.\n";
    for(int i = 3; i < cons.size() ; i++){
        while(stk.size() > 1 && orientation(nextToTop(stk),stk.top(),cons[i])!=2){
            auto el = nextToTop(stk);
            cout<<"("<<el.x<<","<<el.y<<"), ("<<stk.top().x<<","<<stk.top().y<<"), ("<<cons[i].x<<","<<cons[i].y<<") are not orientated properly. So Pop Point ("<<stk.top().x<<","<<stk.top().y<<") from the stack.\n";
            stk.pop();
        }
        cout<<"Push ("<<cons[i].x<<","<<cons[i].y<<") to the stack.\n";
        stk.push(cons[i]);
    }

    cout<<"After Graham Scan Points on the hull are as :\n";
    while(!stk.empty()){
        cout<<"("<<stk.top().x<<","<<stk.top().y<<")\t";
        stk.pop();
    }
}



int main(){
    ios_base::sync_with_stdio(false);
    cout<<"Enter Number of points :\n";
    cin>>N;
    cout<<"Enter coordinates :\n";
    vector<Point> points(N);
    for(int i = 0 ; i < N ; i++){
        cin>>points[i].x>>points[i].y;
        points[i].ID = i+1;
    }
    ConvexHull(points);
}