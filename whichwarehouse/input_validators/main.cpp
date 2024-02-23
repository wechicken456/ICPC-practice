#include <iostream>

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)

const ::uint32_t
    MAX_WAREHOUSES = 1000;

int64_t
    amounts[MAX_WAREHOUSES][MAX_WAREHOUSES],
    adjm[MAX_WAREHOUSES][MAX_WAREHOUSES];

bool
    visited[MAX_WAREHOUSES];
::uint32_t
    order[MAX_WAREHOUSES],
    nWarehouses,
    top;

void visit1(::uint32_t v) {

    visited[v] = true;

    REPI(i,0,nWarehouses)
        if (adjm[v][i] > 0 && !visited[i])
            visit1(i);

    order[--top] = v;
}

void sweep1() {

    REPI(i,0,nWarehouses)
        visited[i] = false;

    top = nWarehouses;

    REPI(i,0,nWarehouses)
        if (!visited[i])
            visit1(i);
}

void visit2(::uint32_t v) {

    visited[v] = true;

    REPI(i,0,nWarehouses)
        if (adjm[i][v] > 0 && !visited[i])
            visit2(i);
}

void sweep2() {
    bool
        okay = true;

    REPI(i,0,nWarehouses)
        visited[i] = false;

    REPI(i,0,nWarehouses)
        if (!visited[order[i]]) {
            if (okay) {
                visit2(i);
                okay = false;
            } else
                exit(1);
        }
}

int main() {
    uint32_t
        n, m, x;

    cin >> n >> m;

    REPI(i,0,n)
        REPI(j,0,m) {
            cin >> amounts[i][j];
            if (!cin)
            	exit(3);
        }

    REPI(i,0,n)
        REPI(j,0,n) {
            cin >> adjm[i][j];
            if (!cin)
            	exit(4);
        }

    nWarehouses = n;
    
    if (cin >> x)
    	exit(2);
    
//    cout << 'a' << endl;

    sweep1();

//    cout << 'b' << endl;

    sweep2();

    return 42;
}
