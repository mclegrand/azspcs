#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>
#include <cstdlib>
#include <ctime>

#define n 29

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
    for (int i=0;i<a-1;i++){
        int j = a-1;
        int rs = vx[i] * vy[j] - vx[j] * vy[i];
        if(!rs) return false;
    }
    for (int i = 0; i < a - 2; i++) {
        int j = a - 1;
        int rs = vx[i] * vy[j] - vx[j] * vy[i];
        int t0 = (x[j] - x[i]) * vy[j] - (y[j] - y[i]) * vx[j];
        int t1 = (x[j] - x[i]) * vy[i] - (y[j] - y[i]) * vx[i];
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
        for (int i=0;i<n-1;i++){
            int j = n-1;
            int rs = vx[i] * vy[j] - vx[j] * vy[i];
            if(!rs) return false;
        }
        for (int i = 1; i < n - 2; i++) {
            int j = n - 1;
            int rs = vx[i] * vy[j] - vx[j] * vy[i];
            int t0 = (x[j] - x[i]) * vy[j] - (y[j] - y[i]) * vx[j];
            int t1 = (x[j] - x[i]) * vy[i] - (y[j] - y[i]) * vx[i];
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

        if (!no_intersect(a)) {
            used[val]=false;
            continue;
        }
        //on peut mettre i en pos a
        backtrack(a + 1);
        used[val]=false;
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
        t++;
        //printf("%d/100\n", t);
    } while (t < 100000000);//
    //    } while (next_permutation(x.begin(),x.end()) );//

    return 0;
}


