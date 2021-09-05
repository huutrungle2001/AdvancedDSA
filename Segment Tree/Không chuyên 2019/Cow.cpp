/*
Link contest: https://oj.vnoi.info/contest/olp_kc19
Solved by: Le Huu Trung
Note: Must use double and printf("%.0f", answer) instead of float and cout
*/

#include<bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    void init(){
        cin >> x >> y;
    }

    double distance(Point p){
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

struct Circle {
    Point center;
    double R;

    void init(){
        center.init();
        cin >> R;
    }

    double distance(Point p){
        return center.distance(p) - R;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Point cow;
    cow.init();

    Circle hay[n];
    double answer = INT_MAX;
    for(int i = 0; i < n; i++){
        hay[i].init();
        answer = min(answer, hay[i].distance(cow));
    }

    answer = ((answer - (int)answer == 0) ? answer - 1 : (int)answer);

    printf("%.0f", answer);
}