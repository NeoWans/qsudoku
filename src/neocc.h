#ifndef _NEOCC_H_
#define _NEOCC_H_

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>

#include <ext/rope>

#define likely(cond)   __builtin_expect(!!(cond), 1)
#define unlikely(cond) __builtin_expect(!!(cond), 0)

#define alphabet_order(ch)                        \
  (((ch) >= 'A' && (ch) <= 'Z')    ? (ch) - 'A' : \
      ((ch) >= 'a' && (ch) <= 'z') ? (ch) - 'a' : \
                                     -1)

#define true_inline inline __attribute__((always_inline))

#define quote_helper(content) #content
#define quote(content)        quote_helper(content)

#define lengthof(array) (sizeof(array) / sizeof((array)[0]))

#ifndef offsetof
  #define offsetof(struct_type, mbr) ((size_t) (&((struct_type*) 0)->mbr))
#endif

#define tostruct(struct_type, mbr, mbrptr) \
  ((struct_type*) ((size_t) mbrptr - offsetof(struct_type, mbr)))

template <typename T>
using pbds_rb_tree = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <typename T>
using pbds_splay_tree = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>,
  __gnu_pbds::splay_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
#define pbds_heap __gnu_pbds::priority_queue
#define pbds_hash __gnu_pbds::gp_hash_table
#define pbds      __gnu_pbds
using __gnu_cxx::crope;
using __gnu_cxx::rope;

#define gcd (std::__gcd)

template <typename T>
static true_inline T lcm(const T& x, const T& y) {
  return x / gcd(x, y) * y;
}

template <typename T>
static true_inline typename std::enable_if<std::is_integral<T>::value, T>::type
lowbit(const T& x) {
  return (x) & (-x);
}

template <typename T>
static true_inline T square(const T& x) {
  return x * x;
}

template <typename T>
static true_inline T cube(const T& x) {
  return x * x * x;
}

template <typename T>
static typename std::enable_if<std::is_arithmetic<T>::value, T>::type fast_pow(
  T __base, long long __exponent) {
  T ans = 1;
  bool r = __exponent < 0;
  if (r) __exponent = -__exponent;
  while (__exponent) {
    if (__exponent & 1) ans *= __base;
    __base *= __base;
    __exponent >>= 1;
  }
  if (r) return (1.0l / ans);
  return ans;
}

template <typename T, typename U>
static typename std::enable_if<std::is_integral<T>::value &&
    std::is_integral<U>::value && sizeof(T) >= sizeof(U),
  T>::type
fast_pow(T __base, unsigned long long __exponent, U __modulo) {
  T ans = 1;
  __base %= __modulo;
  while (__exponent) {
    if (__exponent & 1) {
      ans *= __base;
      ans %= __modulo;
    }
    __base *= __base;
    __base %= __modulo;
    __exponent >>= 1;
  }
  return ans;
}

class cinbuf_keeper_t final {
public:
  std::streambuf* buf = nullptr;

  ~cinbuf_keeper_t() {
    if (this->buf != nullptr) std::cin.rdbuf(this->buf);
  }
};

class coutbuf_keeper_t final {
public:
  std::streambuf* buf = nullptr;

  ~coutbuf_keeper_t() {
    if (this->buf != nullptr) std::cout.rdbuf(this->buf);
  }
};

const auto pil = acos(-1.0l);
const auto el = exp(1.0l);
constexpr auto epsl = 1e-12l;

#endif  // _NEOCC_H_