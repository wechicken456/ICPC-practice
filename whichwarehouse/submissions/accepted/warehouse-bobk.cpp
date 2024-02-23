#include <iostream>

using namespace std;

#define REPI(ctr,start,limit) for (uint32_t ctr=(start);(ctr)<(limit);(ctr)++)

const uint32_t
    MAX_WAREHOUSES = 1000;
const uint64_t
    INF = 999999999999;

int64_t
    amounts[MAX_WAREHOUSES][MAX_WAREHOUSES],
    adjm[MAX_WAREHOUSES][MAX_WAREHOUSES],
    ans[MAX_WAREHOUSES],
    ls[MAX_WAREHOUSES],
    lt[MAX_WAREHOUSES];

uint64_t
    dist[MAX_WAREHOUSES][MAX_WAREHOUSES],
    cost[MAX_WAREHOUSES][MAX_WAREHOUSES],
    mm[MAX_WAREHOUSES][MAX_WAREHOUSES],
//    nn[MAX_WAREHOUSES][MAX_WAREHOUSES],
    vv[MAX_WAREHOUSES],
    pp[MAX_WAREHOUSES],
    uu[MAX_WAREHOUSES];

bool
    xx[MAX_WAREHOUSES][MAX_WAREHOUSES],
    ss[MAX_WAREHOUSES],
    st[MAX_WAREHOUSES];

void floyd(uint32_t n) {
    REPI(k,0,n)
        REPI(i,0,n)
            REPI(j,0,n)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

void hungarian(::uint32_t n) {
    uint64_t
        maxM = 0, minM = INF,
        f = 0,
        d1, d2, d;
    ::int64_t
        s, r, ll;

    REPI(i,0,n) {
        pp[i] = INF;
        ls[i] = -1;
        lt[i] = -2;
        ans[i] = -1;
    }

    REPI(i,0,n)
        REPI(j,0,n) {
            if (cost[i][j] < minM)
                minM = cost[i][j];
            if (cost[i][j] > maxM)
                maxM = cost[i][j];
        }

    REPI(i,0,n)
        REPI(j,0,n) {
            mm[i][j] = minM + maxM - cost[i][j];
//            mm[i][j] = minM + cost[i][j];
            if (mm[i][j] > f)
                f = mm[i][j];
        }

    REPI(i,0,n)
        uu[i] = f;

    while (true) {
        f = INF;
        REPI(i,0,n)
            if (ls[i] != -2 && !ss[i]) {
                f = i;
                break;
            }

        if (f != INF) {
            ss[f] = true;
            REPI(i,0,n)
                if (!xx[f][i] && uu[f] + vv[i] - mm[f][i] < pp[i]) {
                    lt[i] = f;
                    pp[i] = uu[f] + vv[i] - mm[f][i];
                }
        } else {
            REPI(i,0,n)
                if (lt[i] != -2 && !st[i] && pp[i] == 0) {
                    f = i;
                    break;
                }

            if (f == INF) {
                d1 = d2 = INF;
                REPI(i,0,n) {
                    if (uu[i] < d1)
                        d1 = uu[i];
                    if (pp[i] > 0 && pp[i] < d2)
                        d2 = pp[i];
                }
                d = d1;
                if (d2 < d)
                    d = d2;

                REPI(i,0,n)
                    if (ls[i] != -2)
                        uu[i] -= d;

                REPI(i,0,n) {
                    if (pp[i] == 0)
                        vv[i] += d;
                    if (pp[i] > 0 && lt[i] != -2)
                        pp[i] -= d;
                }

                if (d2 >= d1)
                    break;
            } else {
                st[f] = true;

                s = -1;
                REPI(i,0,n)
                    if (xx[i][f]) {
                        s = i;
                        break;
                    }

                if (s == -1) {
                    while (true) {
                        r = f;
                        ll = lt[r];

                        if (r >= 0 && ll >= 0)
                            xx[ll][r] = !xx[ll][r];
                        else
                            break;

                        r = ls[ll];
                        if (r >= 0 && ll >= 0)
                            xx[ll][r] = !xx[ll][r];
                        else
                            break;

                        f = r;
                    }

                    REPI(i,0,n) {
                        pp[i] = INF;
                        lt[i] = ls[i] = -2;
                        ss[i] = st[i] = false;
                    }

                    REPI(i,0,n) {
                        bool ex = true;
                        REPI(j,0,n) {
                            ex = !xx[i][j];
                            if (!ex)
                                break;
                        }
                        if (ex)
                            ls[i] = -1;
                    }
                } else {
                    ls[s] = f;
                }
            }
        }
    }

    REPI(i,0,n)
        REPI(j,0,n)
            if (xx[i][j])
                ans[j] = i;
}

int main() {
    uint32_t
        n, m;
    uint64_t
        sum = 0;

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
//            cout << dist[i][j] << ' ';
        }
//        cout << endl;
    }

    floyd(n);

//    REPI(i,0,n) {
//        REPI(j,0,n) {
//            cout << dist[i][j] << ' ';
//        }
//        cout << endl;
//    }

    REPI(i,0,n) {
        REPI(j, 0, m) {
            REPI(k, 0, n)
                cost[i][j] += dist[k][i] * amounts[k][j];
//            cout << cost[i][j] << ' ';
        }
//        cout << endl;
    }

    // at this point, cost[i][j] *should* be the cost to move product j to warehouse i

    hungarian(n);

    REPI(i,0,m) {
        sum += cost[ans[i]][i];
//        cout << ans[i] << endl;
    }

    cout << sum << endl;

    return 0;
}
