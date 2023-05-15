#include <bits/stdc++.h>

using namespace std;

namespace FastIO {
		class FastIOBase {
				protected:
#ifdef OPENIOBUF
						static const int BUFSIZE = 1 << 22;
						char buf[BUFSIZE + 1];
						int buf_p = 0;
#endif
						FILE*target;
				public:
#ifdef OPENIOBUF
						virtual void flush() = 0;
#endif
						FastIOBase(FILE*f): target(f) {}~FastIOBase() = default;
		};
		class FastOutput: public FastIOBase {
#ifdef OPENIOBUF
				public:
						inline void flush() {
								fwrite(buf, 1, buf_p, target), buf_p = 0;
						}
#endif
				protected:
						inline void __putc(char x) {
#ifdef OPENIOBUF
								if (buf[buf_p++] = x, buf_p == BUFSIZE)flush();
#else
								putc(x, target);
#endif
						} template<typename T>inline void __write(T x) {
								static char stk[64], *top;
								top = stk;
								if (x < 0)return __putc('-'), __write(-x);
								do*(top++) = x % 10, x /= 10;
								while (x);
								for (; top != stk; __putc(*(--top) + '0'));
						} public:
						FastOutput(FILE*f = stdout): FastIOBase(f) {}
#ifdef OPENIOBUF
						inline void setTarget(FILE*f) {
								this->flush(), target = f;
						}~FastOutput() {
								flush();
						}
#else
						inline void setTarget(FILE*f) {
								target = f;
						}
#endif
						template<typename...T>inline void writesp(const T&...x) {
								initializer_list<int> {(this->operator<<(x), __putc(' '), 0)...};
						} template<typename...T>inline void writeln(const T&...x) {
								initializer_list<int> {(this->operator<<(x), __putc('\n'), 0)...};
						} inline FastOutput&operator<<(char x) {
								return __putc(x), *this;
						} inline FastOutput&operator<<(const char*s) {
								for (; *s; __putc(*(s++)));
								return*this;
						} inline FastOutput&operator<<(const string&s) {
								return (*this) << s.c_str();
						} template<typename T, typename = typename enable_if<is_integral<T>::value>::type>inline FastOutput & operator<<(const T&x) {
								return __write(x), *this;
						}
		} qout;
		class FastInput: public FastIOBase {
#ifdef OPENIOBUF
				public:
						inline void flush() {
								buf[fread(buf, 1, BUFSIZE, target)] = '\0', buf_p = 0;
						}
#endif
				protected:
						inline char __getc() {
#ifdef OPENIOBUF
								if (buf_p == BUFSIZE)flush();
								return buf[buf_p++];
#else
								return getc(target);
#endif
						} public:
#ifdef OPENIOBUF
						FastInput(FILE*f = stdin): FastIOBase(f) {
								buf_p = BUFSIZE;
						} inline void setTarget(FILE*f) {
								this->flush(), target = f;
						}
#else
						FastInput(FILE*f = stdin): FastIOBase(f) {} inline void setTarget(FILE*f) {
								target = f;
						}
#endif
						inline char getchar() {
								return __getc();
						} template<typename...T>inline void read(T&...x) {
								initializer_list<int> {(this->operator>>(x), 0)...};
						} inline FastInput&operator>>(char&x) {
								while (isspace(x = __getc()));
								return*this;
						} template<typename T, typename = typename enable_if<is_integral<T>::value>::type>inline FastInput & operator>>(T&x) {
								static char ch, sym;
								x = sym = 0;
								while (isspace(ch = __getc()));
								if (ch == '-')sym = 1, ch = __getc();
								for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = __getc());
								return sym ? x = -x : x, *this;
						} inline FastInput&operator>>(char*s) {
								while (isspace(*s = __getc()));
								for (; !isspace(*s) && *s && ~*s; * (++s) = __getc());
								return*s = '\0', *this;
						} inline FastInput&operator>>(string&s) {
								char str_buf[(1 << 8) + 1], *p = str_buf;
								char*const buf_end = str_buf + (1 << 8);
								while (isspace(*p = __getc()));
								for (s.clear(), p++;; p = str_buf) {
										for (; p != buf_end && !isspace(*p = __getc()) && *p && ~*p; p++);
										*p = '\0', s.append(str_buf);
										if (p != buf_end)break;
								}
								return*this;
						}
		} qin;
} using namespace FastIO;
