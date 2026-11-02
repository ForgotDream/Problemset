#include <bits/stdc++.h>

using i64 = long long;

enum Suit {
  C,
  D,
  H,
  S
};

enum Type {
  Highcard,
  Pair,
  TwoPairs,
  ThreeOfAKind,
  Straight,
  Flush,
  FullHouse,
  FourOfAKind,
  StraightFlush,
  RoyalFlush
};

struct Card {
  Suit suit;
  int value;

  auto operator<=>(const Card &rhs) const = default;
};

std::istream &operator>>(std::istream &in, Card &card) {
  char suit, val;
  in >> val >> suit;

  if (suit == 'C') card.suit = Suit::C;
  else if (suit == 'D') card.suit = Suit::D;
  else if (suit == 'H') card.suit = Suit::H;
  else card.suit = Suit::S;

  if (std::isupper(val)) {
    if (val == 'T') {
      card.value = 10;
    } else if (val == 'A') {
      card.value = 1;
    } else if (val == 'J') {
      card.value = 11;
    } else if (val == 'Q') {
      card.value = 12;
    } else {
      card.value = 13;
    }
  } else {
    card.value = val - '0';
  }

  return in;
}

struct Hand {
  Card cards[5];

  Type get_type() {
    auto cmp1 = [](const Card &lhs, const Card &rhs) {
      return lhs.value < rhs.value;
    };
    std::sort(cards, cards + 5, cmp1);
    
    if (is_straight()) {
      if (is_straight_flush()) {
        if (is_royal_flush()) {
          return Type::RoyalFlush;
        } else {
          return Type::StraightFlush;
        }
      } else {
        return Type::Straight;
      }
    } else {
      auto cmp = [](const Card &lhs, const Card &rhs) {
        if (lhs.value == rhs.value) return false;
        if (lhs.value == 1) return true;
        if (rhs.value == 1) return false;
        return lhs.value > rhs.value;
      };
      std::sort(cards, cards + 5, cmp);

      int cnt[13] = {0};
      for (auto [suit, value] : cards) cnt[value - 1]++;

      int ccnt[5] = {0};
      for (auto i : cnt) ccnt[i]++;

      if (ccnt[1] == 5) {
        for (int i = 0; i < 4; i++) {
          if (cards[i].suit != cards[i + 1].suit) return Type::Highcard;
        }
        return Type::Flush;
      }
      if (ccnt[4] == 1) {
        if (cards[0].value != cards[1].value) std::rotate(cards, cards + 1, cards + 5);
        return Type::FourOfAKind;
      }
      if (ccnt[2] == 2) {
        int order[] = {0, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        for (int idx = 0, piv = 0; idx < 13; idx++) {
          int i = order[idx];
          if (cnt[i] != 2) continue;
          for (int j = 0; j < 5; j++) {
            if (cards[j].value != i + 1) continue;
            std::swap(cards[j], cards[piv++]);
          }
        }
        return Type::TwoPairs;
      }
      if (ccnt[3] == 1) {
        for (int i = 12, piv = 0; ~i; i--) {
          if (cnt[i] != 3) continue;
          for (int j = 0; j < 5; j++) {
            if (cards[j].value != i + 1) continue;
            std::swap(cards[j], cards[piv++]);
          }
        }
        if (ccnt[2] == 1) {
          return Type::FullHouse;
        } else {
          std::sort(cards + 3, cards + 5, cmp);
          return Type::ThreeOfAKind;
        }
      }
      if (ccnt[2] == 1) {
        for (int i = 0; i < 4; i++) {
          if (cards[i].value != cards[i + 1].value) continue;
          std::rotate(cards, cards + i, cards + 5);
          break;
        }
        std::sort(cards + 2, cards + 5, cmp);
        return Type::Pair;
      }
    }

    return Type::Highcard;
  }
  
  bool is_straight() {
    if (cards[0].value == 1) {
      if (cards[1].value == 2) {
        for (int i = 0; i < 4; i++) {
          if (cards[i].value + 1 != cards[i + 1].value) return false;
        }
      } else {
        std::rotate(cards, cards + 1, cards + 5);
        for (int i = 0; i < 4; i++) {
          if (cards[i].value != i + 10) return false;
        }
      }
    } else {
      for (int i = 0; i < 4; i++) {
        if (cards[i].value + 1 != cards[i + 1].value) return false;
      }
    }
    std::reverse(cards, cards + 5);
    
    // for (int i = 0; i < 5; i++) {
    //   std::cout << cards[i].suit << " " << cards[i].value << "\n";
    // }

    return true;
  }

  bool is_straight_flush() {
    for (int i = 0; i < 4; i++) {
      if (cards[i].suit != cards[i + 1].suit) return false;
    }
    return true;
  }

  bool is_royal_flush() {
    return cards[4].value == 10;
  }

  auto operator<=>(Hand &rhs) {
    Type l = get_type(), r = rhs.get_type();
    
    if (l > r) return 1;
    else if (l < r) return -1;
    else {
      auto cmp = [](const Card &lhs, const Card &rhs) -> int {
        if (lhs.value == rhs.value) return 0;
        if (lhs.value == 1) return 1;
        else if (rhs.value == 1) return -1;
        if (lhs.value > rhs.value) return 1;
        else return -1;
      };

      for (int i = 0; i < 5; i++) {
        auto res = cmp(cards[i], rhs.cards[i]);
        if (res != 0) return res;
      }
      return 0;
    }
  }
};

void solve() {
  std::set<Card> s;
  for (int i = 0; i < 4; i++) {
    Card c;
    if (i == 0) c.suit = Suit::C;
    else if (i == 1) c.suit = Suit::D;
    else if (i == 2) c.suit = Suit::H;
    else c.suit = Suit::S;

    for (int j = 1; j <= 13; j++) {
      c.value = j;
      s.insert(c);
    }
  }

  Hand c, p;
  for (int i = 0; i < 4; i++) std::cin >> p.cards[i], s.erase(p.cards[i]);
  for (int i = 0; i < 4; i++) std::cin >> c.cards[i], s.erase(c.cards[i]);

  // std::cout << s.size() << "\n";
  // for (auto [suit, value] : s) {
  //   std::cout << suit << " " << value << "\n";
  // }

  int win = 0, tie = 0;
  for (auto fir : s) {
    auto d = c;
    d.cards[4] = fir;

    bool flg = false;
    int tie_cnt = 0;

    for (auto sec : s) {
      if (fir == sec) continue;

      auto q = p;
      q.cards[4] = sec;

      if (q > d) {
        flg = true;
        break;
      } else if (q < d) {
        continue;
      } else {
        tie_cnt++;
      }
    }

    if (flg) {
      win++;
    } else if (tie_cnt) {
      tie++;
    }
  }

  // std::cout << win << " " << tie << "\n";
  int lose = 44 - win - tie;

  if (lose) std::cout << "GeiWoCaPiXie\n";
  else if (tie) std::cout << "PaiMeiYouWenTi\n";
  else std::cout << "WoYaoYanPai\n";
  
  // === test ===
  // for (int i = 0; i < 5; i++) {
  //   std::cin >> c.cards[i];
  // }
  // std::cout << c.get_type() << "\n";
  // for (int i = 0; i < 5; i++) {
  //   std::cout << c.cards[i].suit << " " << c.cards[i].value << "\n";
  // }
  // ============
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
