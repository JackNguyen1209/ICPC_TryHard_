/*
Nguyen Duc Anh Phuc_Jacke
*/

#include <limits.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <fstream>
#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<pll, ll>plll;

class SparseTable
{
private:
	vector<vector<ll>>st;
	ll n;

	vector<ll>lg;
	vector<ll>a;
public:
	void build()
	{
		for (ll j = 0 ;j <= lg[n]; j++)
			for (ll i = 1; i + (1LL<<(j)) - 1 <= n; i++)
				if (j == 0)
					st[i][j] = a[i];
				else
					st[i][j] = min(st[i][j - 1], st[i + (1LL << (j - 1))][j - 1]);
	}
	ll query(ll l, ll r)
	{
		ll len = lg[r - l + 1];
		return min(st[l][len], st[r - (1LL<<len) + 1][len]);
	}
	SparseTable(vector<ll>& aa, ll nn)
	{
		a = aa;
		n = nn;
		lg.resize(n + 1);
		lg[1] = 0;
		for (ll i = 2; i <= n; i++)
			lg[i] = lg[i / 2] + 1;
		st.resize(n + 1, vector<ll>(lg[n] + 1));
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, q;
	cin >> n >> q;
	vector<ll>a(n + 1);
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	SparseTable t(a, n);
	t.build();
	for (ll i = 1,a,b; i <= q; i++)
	{
		cin >> a >> b;
		cout<<t.query(a, b) << "\n";
	}

	return 0;
}