/*
Nguyen Duc Anh Phuc_Jacke
*/

#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ll, pll>plll;


class LCP
{
private:
	vector<ll> s;
	ll n;
	vector<ll>sa;   // (0->n-1)
	vector<ll> lcp; // (lcp[i]=lcp(suf[i],suf[i+1]))
public:

	void build()
	{
		// Suffix array
		for (ll i = n - 1; i >= 0; i--)
			sa.push_back(i);
		stable_sort(sa.begin(), sa.end(), [&](ll a, ll b) { return s[a] < s[b]; });
		vector<ll> classes(n);
		for (ll i = 0; i < n; ++i)
			classes[i] = s[i];
		for (ll len = 1; len < n; len *= 2)
		{
			vector<ll> c = classes;
			for (ll i = 0; i < n; i++)
				if (i > 0 && c[sa[i - 1]] == c[sa[i]] && sa[i - 1] + len < n && c[sa[i - 1] + len / 2] == c[sa[i] + len / 2])
					classes[sa[i]] = classes[sa[i - 1]];
				else
					classes[sa[i]] = i;
			vector<ll> cnt(n);
			iota(cnt.begin(), cnt.end(), 0);
			vector<ll> s = sa;
			for (ll i = 0; i < n; i++)
			{
				ll s1 = s[i] - len;
				if (s1 >= 0)
					sa[cnt[classes[s1]]++] = s1;
			}
		}
		// LCP
		vector<ll> rank(n);
		for (ll i = 0; i < n; i++)
			rank[sa[i]] = i;
		lcp.resize(n - 1);
		for (ll i = 0, h = 0; i < n; i++)
			if (rank[i] < n - 1)
			{
				for (ll j = sa[rank[i] + 1]; s[i + h] == s[j + h]; ++h);
				lcp[rank[i]] = h;
				if (h > 0) --h;
			}
	}
	void sol()
	{
		//LCP 1->n-2
		vector<ll>le(n, 0);
		vector<ll>ri(n, n - 1);
		stack<ll>st;
		for (ll i = 1; i <= n - 2; i++)
		{
			while (!st.empty() && lcp[i] <= lcp[st.top()])
				st.pop();
			if (!st.empty())
				le[i] = st.top();
			st.push(i);
		}
		stack<ll>stt;
		for (ll i = n - 2; i >= 1; i--)
		{
			while (!stt.empty() && lcp[i] <= lcp[stt.top()])
				stt.pop();
			if (!stt.empty())
				ri[i] = stt.top();
			stt.push(i);
		}

		ll pos = 0;
		for (ll i = 0; i <= n - 1; i++)
			if (sa[i] == 0)
				pos = i;
		ll ans = n - 1;
		ll len = n - 1;
		for (ll i = 1; i <= n - 2; i++)
			ans = max(ans, lcp[i] * (ri[i] - le[i] - 1 + 1));
		for (ll i = 1; i <= n - 2; i++)
			if (ans == lcp[i] * (ri[i] - le[i] - 1 + 1))
			{
				pos = i;
				len = lcp[i];
				break;
			}		
		cout << ans << "\n" << len << "\n";
		for (ll i = sa[pos]; i <= sa[pos] + len - 1; i++)
			cout << s[i] << " ";
		
	}
	LCP(vector<ll>& t)
	{
		s = t;
		s.push_back(0);
		n = (ll)s.size();
		build();
	}
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<ll>s(n);
	for (ll i = 0; i <= n - 1; i++)
		cin >> s[i];
	LCP t(s);
	t.sol();
	return 0;
}