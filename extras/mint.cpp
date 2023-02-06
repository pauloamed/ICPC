template <class LOW, class HIGH, const LOW mod>
struct modBase {
  using mint = modBase<LOW, HIGH, mod>;
  constexpr modBase() : val(0) {}
  // be careful of negative numbers!
  constexpr modBase(const LOW v) : val((v % mod + mod) % mod) {} 
  LOW val;

  #define add(a, b) a + b >= mod ? a + b - mod : a + b
  #define sub(a, b) a < b ? a + mod - b : a - b

  constexpr mint &operator += (const mint &o) { return val = add(val, o.val), *this; }
  constexpr mint &operator -= (const mint &o) { return val = sub(val, o.val), *this; }
  constexpr mint &operator *= (const mint &o) { return val = (LOW) ((HIGH) val * o.val % mod), *this; }
  constexpr mint &operator /= (const mint &o) { return *this *= o.inverse(); }

  constexpr mint operator + (const mint &b) const { return mint(*this) += b; }
  constexpr mint operator - (const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator * (const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator / (const mint &b) const { return mint(*this) /= b; }

  constexpr mint operator - () const { return mint() - mint(*this); }
  constexpr bool operator == (const mint &b) const { return val == b.val; }
  constexpr bool operator != (const mint &b) const { return val != b.val; }

  template<class E> constexpr mint pow (E e) const { return fexp(*this, e); }
  constexpr mint inverse() const { return pow(mod - 2); }
  constexpr LOW get() const { return val; }
  static constexpr LOW getMod() { return mod; }

  friend std::ostream& operator << (std::ostream &os, const mint &p) { return os << p.val; }
  friend std::istream& operator >> (std::istream &is, mint &p) { return is >> p.val; }
};

const int MOD = 1e9 + 7;
using mint = modBase<int, long long, MOD>;
