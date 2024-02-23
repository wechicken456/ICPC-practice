#include <iostream>

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)

const uint32_t
    MAX_WAREHOUSES = 1000;
const uint64_t
    INF = 999999999999;

int64_t
    amounts[MAX_WAREHOUSES][MAX_WAREHOUSES],
    adjm[MAX_WAREHOUSES][MAX_WAREHOUSES];

uint64_t
    dist[MAX_WAREHOUSES][MAX_WAREHOUSES],
    cost[MAX_WAREHOUSES][MAX_WAREHOUSES];
    
uint32_t
    n, m,
    indexes[MAX_WAREHOUSES * MAX_WAREHOUSES];
    
void floyd(uint32_t n) {
    REPI(k,0,n)
        REPI(i,0,n)
            REPI(j,0,n)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int compareIndex(const void *pa,const void *pb) {
    uint32_t
        a,b,
        i1,j1,i2,j2;
    
    a = *((uint32_t *)pa);
    b = *((uint32_t *)pb);
    
    i1 = a / m;
    j1 = a % m;
    i2 = a / m;
    j2 = a % m;
    
    if (cost[i1][j1] < cost[i2][j2])
        return -1;
    else if (cost[i1][j1] > cost[i2][j2])
        return 1;
    else
        return 0;
}

int main() {
    uint64_t
        sum = 0;
    bool
        wUsed[MAX_WAREHOUSES] = {false},
        pUsed[MAX_WAREHOUSES] = {false};

    cin >> n >> m;

    REPI(i,0,n)
        REPI(j,0,m)
            cin >> amounts[i][j];

    REPI(i,0,n) {
        REPI(j, 0, n) {
            cin >> adjm[i][j];
            dist[i][j] = adjm[i][j];
            if (adjm[i][j] == -1)
                dist[i][j] = INF;
        }
    }

    floyd(n);

    REPI(i,0,n) {
        REPI(j, 0, m) {
            REPI(k, 0, n)
                cost[i][j] += dist[k][i] * amounts[k][j];
        }
    }
    
    REPI(i,0,m*n)
        indexes[i] = i;
        
    qsort(indexes,m*n,sizeof(uint32_t),compareIndex);
    
    REPI(i,0,m*n) {
        uint32_t
            i1,j1;
            
        i1 = indexes[i] / m;
        j1 = indexes[i] % m;
        
        if (!wUsed[i1] && !pUsed[j1]) {
            wUsed[i1] = true;
            pUsed[j1] = true;
            
            sum += cost[i1][j1];
        }
    }

    cout << sum << endl;

    return 0;
}
