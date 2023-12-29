#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vs = vector<string>;

template <ll MOD>
class mint {
 public:
  mint() : mint(0) {}
  mint(ll v) { _val = v % MOD; }

 private:
  ll _val{};

 public:
  const ll& val() const noexcept { return _val; }
  void pow(ll b) {
    _val = mpow(_val, b);
    m();
    p();
  }
  void inv() { pow(MOD - 2); }
  mint& operator+=(const mint& other) {
    _val += other._val;
    m();
    p();

    return *this;
  }
  mint& operator-=(const mint& other) {
    _val -= other._val;
    m();
    p();

    return *this;
  }
  mint& operator*=(const mint& other) {
    _val *= other._val;
    m();
    p();

    return *this;
  }
  friend mint operator+(const mint& l, const mint& r) { return mint{l} += r; }
  friend mint operator-(const mint& l, const mint& r) { return mint{l} -= r; }
  friend mint operator*(const mint& l, const mint& r) { return mint{l} *= r; }

 private:
  void m() noexcept { _val %= MOD; }
  void p() noexcept {
    if (_val < 0) {
      _val += MOD;
    }
  }
  ll mpow(ll x, ll b) {
    if (0 == b) {
      return 1;
    }

    if (1 == b) {
      return x;
    }

    if (0 == b % 2) {
      auto y = mpow(x, b / 2);
      y *= y;
      return y % MOD;
    }

    auto y = mpow(x, (b - 1) / 2);
    y *= y;
    y %= MOD;
    y *= x;

    return y % MOD;
  }
};
using Int = mint<10000 + 7>;
using vI = vector<Int>;
using pII = pair<Int, Int>;
using vII = vector<pII>;
using vvI = vector<vI>;

ll n, k;
vI fact;

Int facto(const Int& x) {
  if (fact[x.val()].val() < 0) {
    fact[x.val()] = x * facto(x - 1);
  }

  return fact[x.val()];
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> n >> k;

  auto N = Int{n};
  auto K = Int{k};

  fact = vI(10000 + 7, -1);
  fact[0] = 1;
  fact[1] = 1;

  auto nf = facto(N);
  //cout << "N! = " << nf.val() << '\n';
  auto kf = facto(K);
  //cout << "K! = " << kf.val() << '\n';
  auto df = facto(N - K);
  //cout << "(N-K)! = " << df.val() << '\n';
  df *= kf;
  //cout << "K! * (N-K)! = " << df.val() << '\n';
  df.inv();
  //cout << "1 / (K! * (N-K)!) = " << df.val() << '\n';

  cout << (nf * df).val();

  return 0;
}