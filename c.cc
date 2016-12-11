#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>
#include <cstdlib>
#include <ctime>

#define n 11

using namespace std;

vector<int> vx(n); //vx,vy[i] is vector from i to i+1
vector<int> vy(n);

vector<int> x(n);
vector<int> y(n);

int maxarea = 0;
int minarea = n * n * 2;

vector<int> xmax(n);
vector<int> ymax(n);
vector<int> xmin(n);
vector<int> ymin(n);
set<float> vn;//normalized
vector<bool> used(n,false);

int gt = 0;

//https://en.wikipedia.org/wiki/Shoelace_formula
int area() //computes 2*area
{
    int r = 0;
    for (int i = 0; i < n; i++) {
        r += x[i] * (y[(i + 1) % n] - y[(i + n - 1) % n]);
    }
    return (r < 0) ? (0 - r) : r;
}

void pv(const vector<int> &vx, const vector<int> &vy)
{
    for (int i = 0; i < n; i++) {
        printf("(%d,%d),", 1 + vx[i], 1 + vy[i]);
    }
    printf("\n");
}

bool no_intersect(int a)
{
    for (int i = 0; i < a - 2; i++) {
        int j = a - 1;
        int rs = vx[i % n] * vy[j % n] - vx[j % n] * vy[i % n];
        int t0 = (x[j % n] - x[i % n]) * vy[j % n] - (y[j % n] - y[i % n]) * vx[j % n];
        int t1 = (x[j % n] - x[i % n]) * vy[i % n] - (y[j % n] - y[i % n]) * vx[i % n];
        if (rs < 0) {
            rs = 0 - rs;
            t0 = 0 - t0;
            t1 = 0 - t1;
        }
        if (t0 >= 0 && t0 <= rs && t1 >= 0 && t1 <= rs) {
            return false;
        }
    }
    if (a == n - 1) {
        for (int i = 1; i < n - 2; i++) {
            int j = n - 1;
            int rs = vx[i % n] * vy[j % n] - vx[j % n] * vy[i % n];
            int t0 = (x[j % n] - x[i % n]) * vy[j % n] - (y[j % n] - y[i % n]) * vx[j % n];
            int t1 = (x[j % n] - x[i % n]) * vy[i % n] - (y[j % n] - y[i % n]) * vx[i % n];
            if (rs < 0) {
                rs = 0 - rs;
                t0 = 0 - t0;
                t1 = 0 - t1;
            }
            if (t0 >= 0 && t0 <= rs && t1 >= 0 && t1 <= rs) {
                return false;
            }
        }
    }
    return true;
}
/*
inline bool yhas(int a, int val)
{
    for (int i = 0; i < a; i++) if (y[i] == val) {
            return true;
        }
    return false;
}*/
inline bool penteok(int a)
{
    if (!vn.insert((float)(y[a] - y[a - 1]) / (float)(x[a] - x[a - 1])).second) {
        return false;
    }

    if (a == n - 1 && !vn.insert((float)(y[0] - y[n - 1]) / (float)(x[0] - x[n - 1])).second) {
        vn.erase((float)(y[a] - y[a - 1]) / (float)(x[a] - x[a - 1]));
        return false;
    }
    return true;
}

void backtrack(int a)
{
    gt++;
    if (gt > 1e8) {
        return;
    }
    if (a == n) {
        int ar = area();
        if (ar > maxarea) {
            maxarea = ar;
            xmax = x;
            ymax = y;
            printf("%d:\n", ar);
            pv(x, y);
        }
        if (ar < minarea) {
            minarea = ar;
            xmin = x;
            ymin = y;
            printf("%d:\n", ar);
            pv(x, y);
        }
        return;
    }
    vector<int>p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    random_shuffle(p.begin(), p.end());


    for (auto val : p) {
        if(used[val]) continue;
//        if (yhas(a, val)) {
//            continue;
//        }
        used[val]=true;
        y[a] = val;
        if (a > 0) {
            vx[a - 1] = x[a % n] - x[a - 1];
            vy[a - 1] = y[a % n] - y[a - 1];
        }
        if (a == n - 1) {
            vx[n - 1] = x[0] - x[n - 1];
            vy[n - 1] = y[0] - y[n - 1];
        }

        if (!penteok(a)) {
            used[val]=false;
            continue;
        }
        if (!no_intersect(a)) {
            used[val]=false;
            vn.erase((float)(y[a] - y[a - 1]) / (float)(x[a] - x[a - 1]));
            if(a==n-1) vn.erase((float)(y[a] - y[a - 1]) / (float)(x[a] - x[a - 1]));
            continue;
        }
        //on peut mettre i en pos a
        backtrack(a + 1);
        used[val]=false;
        vn.erase((float)(y[a] - y[a - 1]) / (float)(x[a] - x[a - 1]));
        if(a==n-1) vn.erase((float)(y[a] - y[a - 1]) / (float)(x[a] - x[a - 1]));
    }
}




int main()
{
    std::srand(std::time(0));
    int t = 0;
    for (int i = 0; i < n; i++) {
        x[i] = y[i] = i;
    }
    do {
        random_shuffle(x.begin(), x.end()); //
        backtrack(0);
        gt = 0;
        std::fill(used.begin(), used.end(), false);
        vn.clear();
        t++;
        //printf("%d/100\n", t);
    } while (t < 100000000);//
    //    } while (next_permutation(x.begin(),x.end()) );//

    return 0;
}


