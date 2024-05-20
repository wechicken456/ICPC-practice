#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vector<ll>>
#define vb vector<bool>

using namespace std;

ull numberOfDivisors(ull num) {
    ull total = 1;
    for (ull i = 2; (ull)i * i <= num; i++) {
        if (num % i == 0) {
            ull e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}

bool isPrime(ull num) {
	for (ull i = 2; (ull)i * i <= num; i++) {
        if (num % i == 0) {
			return false;
        }
    }
    return true;
}

int main(){
	
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	map<ull, ull>m;
	// since number of divisors N = (e1 + 1) * (e2 + 2) * ..., where e's are the exponenets of the prime factors of the number
	// the smallest N is 2, then 3 (if n == p^2), and then 4.
	// here we can precompute all the numbers that have N >= 4, => n <= 10^(18 / 4).
	for (ull i = 1 ; i < 50000; i++) {
		ull d = numberOfDivisors(i);
		ull tmp = 1, log = log10((long double)i);
		ull prev_tmp = 1;
		bool check = true;
		while (d-- > 0) {
			tmp *= i;
			if (tmp < prev_tmp) {
				//cout << i << ": " << old_d << " " << tmp << " " << prev_tmp << "\n";

				check = false;
				break;
			}
			prev_tmp = tmp;
		}
		if (check) {
			if (m[tmp] == 0) m[tmp] = i;
		}
	}
	// precompute all the numbers that have N = 3, => x = (p ^ 2 ) ^ 3 == p ^ 6 => p <= 10^(18/6).
	for (ull i = 2 ; i <= 1000; i++) {
		if (isPrime(i)) {
			ull squared = i*i;
			ull tmp = squared * squared * squared;
			if (m[tmp] == 0) {
				m[tmp] = squared;
			}
		}
	}
	
	ull n;
	ll ans = -1;
	cin >> n;
	if (m[n] != 0) {
		cout << m[n] << "\n";
	}
	else {
		// the only thing left is N = 2
		long double s = sqrt((long double)n);
		ull ss = (ull)floor(s);
		ull ss2 = ss + 1;
		if (ss*ss == n) {
			if (isPrime(ss)) {
				ans = ss;
			}
		}
		if (ans != -1) {
			cout << ans << "\n";
			return 0;
		}
		else if (ss2 * ss2 == n) {
			if (isPrime(ss2)) {
				ans = ss2;
			}
		}
		cout << ans << "\n";
	}
}


