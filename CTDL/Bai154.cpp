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

ll r;

struct node
{
	vector<ll>a;
	node()
	{
		a.resize(4, 0);
	}
	node(ll aa, ll b, ll c, ll d)
	{
		a.resize(4);
		a[0] = aa;
		a[1] = b;
		a[2] = c;
		a[3] = d;
	}
};

void Out(node a)
{
	cout << a.a[0] << " " << a.a[1] << "\n" << a.a[2] << " " << a.a[3] << "\n";
}

node nhan(node& a, node& b)
{
	node ans;
	ans.a[0] = (a.a[0] * b.a[0] + a.a[1] * b.a[2]) % r;
	ans.a[1] = (a.a[0] * b.a[1] + a.a[1] * b.a[3]) % r;
	ans.a[2] = (a.a[2] * b.a[0] + a.a[3] * b.a[2]) % r;
	ans.a[3] = (a.a[2] * b.a[1] + a.a[3] * b.a[3]) % r;
	return ans;
}

class segtree
{
private:
	vector<node>st;
	ll n;
public:
	void merge(ll si)
	{
		st[si] = nhan(st[si * 2], st[si * 2 + 1]);
	}
	void build(vector<node>& a, ll l, ll r, ll si)
	{
		if (l > r)return;
		if (l == r)
		{
			st[si] = a[l];
			return;
		}
		ll m = (l + r) / 2;
		build(a, l, m, si * 2);
		build(a, m + 1, r, si * 2 + 1);
		merge(si);
	}
	node query(ll l, ll r, ll ql, ll qr, ll si)
	{
		if (l > r || qr<l || ql>r)
			return node(1, 0, 0, 1);
		if (ql <= l && r <= qr)
			return st[si];
		ll m = (l + r) >> 1;
		node a = query(l, m, ql, qr, si * 2);
		node b = query(m + 1, r, ql, qr, si * 2 + 1);
		return nhan(a, b);
	}
	node query(ll ql, ll qr)
	{
		return query(1, n, ql, qr, 1);
	}
	segtree(vector<node>& a, ll nn)
	{
		n = nn;
		st.resize(4 * n);
		build(a, 1, n, 1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> r >> n >> m;
	vector<node>a(n + 1);

	for (ll i = 1; i <= n; i++)
	{
		ll aa, bb, cc, dd;
		cin >> aa >> bb >> cc >> dd;
		node temp(aa, bb, cc, dd);
		a[i] = temp;
	}
	segtree t(a, n);
	for (ll i = 1; i <= m; i++)
	{
		ll l, r;
		cin >> l >> r;
		Out(t.query(l, r));
		cout << "\n";
	}

	return 0;
}