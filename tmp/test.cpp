#include <iostream>
#include <queue>
#include <string>
#include <vector>

class DividedByZeroException {};
class BigInteger {
 private:
  bool sign;
  void trim();

 public:
  std::vector<char> digits;
  BigInteger(int);
  BigInteger(std::string &);
  BigInteger();
  BigInteger(const BigInteger &);
  BigInteger operator=(const BigInteger &op2);
  BigInteger abs() const;
  BigInteger pow(int a);
  friend BigInteger operator+=(BigInteger &, const BigInteger &);
  friend BigInteger operator-=(BigInteger &, const BigInteger &);
  friend BigInteger operator*=(BigInteger &, const BigInteger &);
  friend BigInteger operator/=(BigInteger &, const BigInteger &);
  inline friend BigInteger operator%=(BigInteger &, const BigInteger &);
  inline friend BigInteger operator+(const BigInteger &, const BigInteger &);
  inline friend BigInteger operator-(const BigInteger &, const BigInteger &);
  inline friend BigInteger operator*(const BigInteger &, const BigInteger &);
  inline friend BigInteger operator/(const BigInteger &, const BigInteger &);
  inline friend BigInteger operator%(const BigInteger &, const BigInteger &);
  inline friend BigInteger operator-(const BigInteger &);
  inline friend BigInteger operator++(BigInteger &);
  inline friend BigInteger operator++(BigInteger &, int);
  inline friend BigInteger operator--(BigInteger &);
  inline friend BigInteger operator--(BigInteger &, int);
  inline friend bool operator>(const BigInteger &, const BigInteger &);
  friend bool operator<(const BigInteger &, const BigInteger &);
  friend bool operator==(const BigInteger &, const BigInteger &);
  inline friend bool operator!=(const BigInteger &, const BigInteger &);
  inline friend bool operator>=(const BigInteger &, const BigInteger &);
  inline friend bool operator<=(const BigInteger &, const BigInteger &);
  friend std::ostream &operator<<(std::ostream &, const BigInteger &);
  friend std::istream &operator>>(std::istream &, BigInteger &);
  std::string get_string();
  static const BigInteger ZERO;
  static const BigInteger ONE;
  static const BigInteger TEN;
};
const BigInteger BigInteger::ZERO = BigInteger(0);
const BigInteger BigInteger::ONE = BigInteger(1);
const BigInteger BigInteger::TEN = BigInteger(10);
BigInteger::BigInteger() { sign = true; }
BigInteger::BigInteger(int val) {
  if (val >= 0)
    sign = true;
  else {
    sign = false;
    val *= (-1);
  }
  do {
    digits.push_back((char)(val % 10));
    val /= 10;
  } while (val != 0);
}
BigInteger::BigInteger(std::string &def) {
  sign = true;
  for (std::string::reverse_iterator iter = def.rbegin(); iter < def.rend();
       iter++) {
    char ch = (*iter);
    if (iter == def.rend() - 1) {
      if (ch == '+') break;
      if (ch == '-') {
        sign = false;
        break;
      }
    }
    digits.push_back((char)((*iter) - '0'));
  }
  trim();
}
void BigInteger::trim() {
  std::vector<char>::reverse_iterator iter = digits.rbegin();
  while (!digits.empty() && (*iter) == 0) {
    digits.pop_back();
    iter = digits.rbegin();
  }
  if (digits.size() == 0) {
    sign = true;
    digits.push_back(0);
  }
}
BigInteger::BigInteger(const BigInteger &op2) {
  sign = op2.sign;
  digits = op2.digits;
}
BigInteger BigInteger::operator=(const BigInteger &op2) {
  digits = op2.digits;
  sign = op2.sign;
  return (*this);
}
BigInteger BigInteger::abs() const {
  if (sign)
    return *this;
  else
    return -(*this);
}
BigInteger BigInteger::pow(int a) {
  BigInteger res(1);
  for (int i = 0; i < a; i++) res *= (*this);

  return res;
}
BigInteger operator+=(BigInteger &op1, const BigInteger &op2) {
  if (op1.sign == op2.sign) {
    std::vector<char>::iterator iter1;
    std::vector<char>::const_iterator iter2;
    iter1 = op1.digits.begin();
    iter2 = op2.digits.begin();
    char to_add = 0;
    while (iter1 != op1.digits.end() && iter2 != op2.digits.end()) {
      (*iter1) = (*iter1) + (*iter2) + to_add;
      to_add = ((*iter1) > 9);
      (*iter1) = (*iter1) % 10;
      iter1++;
      iter2++;
    }
    while (iter1 != op1.digits.end()) {
      (*iter1) = (*iter1) + to_add;
      to_add = ((*iter1) > 9);
      (*iter1) %= 10;
      iter1++;
    }
    while (iter2 != op2.digits.end()) {
      char val = (*iter2) + to_add;
      to_add = (val > 9);
      val %= 10;
      op1.digits.push_back(val);
      iter2++;
    }
    if (to_add != 0) op1.digits.push_back(to_add);
    return op1;
  } else {
    if (op1.sign)
      return op1 -= (-op2);
    else
      return op1 = op2 - (-op1);
  }
}
BigInteger operator-=(BigInteger &op1, const BigInteger &op2) {
  if (op1.sign == op2.sign) {
    if (op1.sign)
      if (op1 < op2)
        return op1 = -(op2 - op1);
      else {
        if (-op1 > -op2)
          return op1 = -((-op1) - (-op2));
        else
          return op1 = (-op2) - (-op1);
      }
    std::vector<char>::iterator iter1;
    std::vector<char>::const_iterator iter2;
    iter1 = op1.digits.begin();
    iter2 = op2.digits.begin();
    char to_substract = 0;
    while (iter1 != op1.digits.end() && iter2 != op2.digits.end()) {
      (*iter1) = (*iter1) - (*iter2) - to_substract;
      to_substract = 0;
      if ((*iter1) < 0) {
        to_substract = 1;
        (*iter1) += 10;
      }
      iter1++;
      iter2++;
    }
    while (iter1 != op1.digits.end()) {
      (*iter1) = (*iter1) - to_substract;
      to_substract = 0;
      if ((*iter1) < 0) {
        to_substract = 1;
        (*iter1) += 10;
      } else
        break;
      iter1++;
      op1.trim();
      return op1;
    }
  } else {
    if (op1 > BigInteger::ZERO)
      return op1 += (-op2);
    else
      return op1 = -(op2 + (-op1));
  }
}
BigInteger operator*=(BigInteger &op1, const BigInteger &op2) {
  BigInteger result(0);
  if (op1 == BigInteger::ZERO || op2 == BigInteger::ZERO)
    result = BigInteger::ZERO;
  else {
    std::vector<char>::const_iterator iter2 = op2.digits.begin();
    while (iter2 != op2.digits.end()) {
      if (*iter2 != 0) {
        std::deque<char> temp(op1.digits.begin(), op1.digits.end());
        char to_add = 0;
        std::deque<char>::iterator iter1 = temp.begin();
        while (iter1 != temp.end()) {
          (*iter1) *= (*iter2);
          (*iter1) += to_add;
          to_add = (*iter1) / 10;
          (*iter1) %= 10;
          iter1++;
        }
        if (to_add != 0) temp.push_back(to_add);
        int num_of_zeros = iter2 - op2.digits.begin();
        while (num_of_zeros--) temp.push_front(0);
        BigInteger temp2;
        temp2.digits.insert(temp2.digits.end(), temp.begin(), temp.end());
        temp2.trim();
        result = result + temp2;
      }
      iter2++;
    }
    result.sign = ((op1.sign && op2.sign) || (!op1.sign && !op2.sign));
  }
  op1 = result;
  return op1;
}
BigInteger operator/=(BigInteger &op1, const BigInteger &op2) {
  if (op2 == BigInteger::ZERO) throw DividedByZeroException();
  BigInteger t1 = op1.abs(), t2 = op2.abs();
  if (t1 < t2) {
    op1 = BigInteger::ZERO;
    return op1;
  }
  std::deque<char> temp;
  std::vector<char>::reverse_iterator iter = t1.digits.rbegin();
  BigInteger temp2(0);
  while (iter != t1.digits.rend()) {
    temp2 = temp2 * BigInteger::TEN + BigInteger((int)(*iter));
    char s = 0;
    while (temp2 >= t2) {
      temp2 = temp2 - t2;
      s = s + 1;
    }
    temp.push_front(s);
    iter++;
  }
  op1.digits.clear();
  op1.digits.insert(op1.digits.end(), temp.begin(), temp.end());
  op1.trim();
  op1.sign = ((op1.sign && op2.sign) || (!op1.sign && !op2.sign));
  return op1;
}
inline BigInteger operator%=(BigInteger &op1, const BigInteger &op2) {
  return op1 -= ((op1 / op2) * op2);
}
inline BigInteger operator+(const BigInteger &op1, const BigInteger &op2) {
  BigInteger temp(op1);
  temp += op2;
  return temp;
}
inline BigInteger operator-(const BigInteger &op1, const BigInteger &op2) {
  BigInteger temp(op1);
  temp -= op2;
  return temp;
}
inline BigInteger operator*(const BigInteger &op1, const BigInteger &op2) {
  BigInteger temp(op1);
  temp *= op2;
  return temp;
}

inline BigInteger operator/(const BigInteger &op1, const BigInteger &op2) {
  BigInteger temp(op1);
  temp /= op2;
  return temp;
}
inline BigInteger operator%(const BigInteger &op1, const BigInteger &op2) {
  BigInteger temp(op1);
  temp %= op2;
  return temp;
}
inline BigInteger operator-(const BigInteger &op) {
  BigInteger temp = BigInteger(op);
  temp.sign = !temp.sign;
  return temp;
}
inline BigInteger operator++(BigInteger &op) {
  op += BigInteger::ONE;
  return op;
}
inline BigInteger operator++(BigInteger &op, int x) {
  BigInteger temp(op);
  ++op;
  return temp;
}
inline BigInteger operator--(BigInteger &op) {
  op -= BigInteger::ONE;
  return op;
}
inline BigInteger operator--(BigInteger &op, int x) {
  BigInteger temp(op);
  --op;
  return temp;
}
bool operator<(const BigInteger &op1, const BigInteger &op2) {
  if (op1.sign != op2.sign)
    return !op1.sign;
  else {
    if (op1.digits.size() != op2.digits.size())
      return (op1.sign && op1.digits.size() < op2.digits.size()) ||
             (!op1.sign && op1.digits.size() > op2.digits.size());
    std::vector<char>::const_reverse_iterator iter1, iter2;
    iter1 = op1.digits.rbegin();
    iter2 = op2.digits.rbegin();
    while (iter1 != op1.digits.rend()) {
      if (op1.sign && *iter1 < *iter2) return true;
      if (op1.sign && *iter1 > *iter2) return false;
      if (!op1.sign && *iter1 > *iter2) return true;
      if (!op1.sign && *iter1 < *iter2) return false;
      iter1++;
      iter2++;
    }
    return false;
  }
}
bool operator==(const BigInteger &op1, const BigInteger &op2) {
  if (op1.sign != op2.sign || op1.digits.size() != op2.digits.size())
    return false;
  std::vector<char>::const_iterator iter1, iter2;
  iter1 = op1.digits.begin();
  iter2 = op2.digits.begin();
  while (iter1 != op1.digits.end()) {
    if (*iter1 != *iter2) return false;
    iter1++;
    iter2++;
  }
  return true;
}
bool operator!=(const BigInteger &op1, const BigInteger &op2) {
  return !(op1 == op2);
}
bool operator>=(const BigInteger &op1, const BigInteger &op2) {
  return (op1 > op2) || (op1 == op2);
}
bool operator<=(const BigInteger &op1, const BigInteger &op2) {
  return (op1 < op2) || (op1 == op2);
}
bool operator>(const BigInteger &op1, const BigInteger &op2) {
  return !(op1 <= op2);
}
std::ostream &operator<<(std::ostream &stream, const BigInteger &val) {
  if (!val.sign) stream << "-";
  for (auto iter = val.digits.rbegin(); iter != val.digits.rend(); iter++)
    stream << (char)((*iter) + '0');
  return stream;
}
std::istream &operator>>(std::istream &stream, BigInteger &val) {
  std::string str;
  stream >> str;
  val = BigInteger(str);
  return stream;
}