// binominals.cc - Binominals program by Sergey 2015
// AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

/*

Calculating binominal coefficients, factorials, inverted factorials, fast
exponents, modulo operations etc.

Modulos(mod) - modulo selection
mod(a)      - Modulo operation
add(a,b)    - Modulo addition
mul(a,b)    - Modulo multiplication
pow(e,n)    - Modulo power (using binary exponent)
inv(a)      - Modulo inverse function, i.e. mul(a, inv(a)) == 1

Binominals(mod, maxn) - modulo and max N selection
fact(n)     - Factorial
ifact(n)    - Factorial inverse function
P(n,k)      - Number of permutations
C(n,k)      - Binominal Coefficients

Default modulo is 10^9+7 and default max N is 10^6.

NOTE: Modulo needs to be a prime number of long long type. Operands for all
modulo functions need to be less than modulo.

Time complexity:    O(1), O(N) - initialization
Extra space:        O(N)

*/

#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Modulos Class
///////////////////////////////////////////////////////////////////////////////


class Modulos { public:

    typedef long long ll;
    ll m;

    Modulos(ll mod=1e9+7){ m = mod; }

    inline ll mod(ll a) { return a % m; }
    inline ll add(ll a, ll b){ return mod(a + b); }
    inline ll mul(ll a, ll b){
        if (m <= (1LL << 32)) return mod(a * b);
        ll r = (a * b - (ll)((long double)a * b / m) * m) % m;
        return r < 0 ? r + m : r;
    }
    inline ll pow(ll e, ll n){
        ll r = 1;
        while (n > 0) { if (n & 1) r = mul(r, e); e = mul(e, e); n >>= 1; }
        return r;
    }
    inline ll inv(ll a){ return pow(a, m-2); }
 };


///////////////////////////////////////////////////////////////////////////////
// Binominals Class (Main Program)
///////////////////////////////////////////////////////////////////////////////


class Binominals: public Modulos { public:

    typedef long long ll;

    vector <ll> facts, ifacts;

    // Constructing factorial arrays
    Binominals(ll mod=1e9+7, int maxn=1e6) : Modulos(mod) {

        // Factorials
        facts.resize(maxn + 1);
        for(int i=0; i<=maxn; i++)
            facts[i] = i > 0 ? mul(facts[i-1], i) : 1;

        // Inverse factorial
        ifacts.resize(maxn + 1);
        for(int i=maxn; i>=0; i--)
            ifacts[i] = i < maxn ? mul(ifacts[i+1], i+1) : inv(fact(maxn));
    }

    inline ll fact(int n){ return facts[n]; }
    inline ll ifact(int n){ return ifacts[n]; }
    inline ll P(int n, int k) { return mul(fact(n), ifact(n-k)); }
    inline ll C(int n, int k) { return mul(P(n, k), ifact(k));}
};

///////////////////////////////////////////////////////////////////////////////
// Unit tests
///////////////////////////////////////////////////////////////////////////////


// CPlusPlusUnit - C++ Unit testing TDD framework (github.com/cppunit/cppunit)
class Cppunit { public:
    #define CHECK(a,b)  check<long long>(a, b, #a, #b, __FILE__, __LINE__, __FUNCTION__);
    #define CHECKT(a)   check<bool>(a, true, #a, "true", __FILE__, __LINE__, __FUNCTION__);
    #define CHECKS(a,b) check<cs>(a, b, #a, #b, __FILE__, __LINE__, __FUNCTION__);
    typedef const std::string& cs;
    int checks, fails; std::ostringstream serr; std::istringstream *in;
    Cppunit() { checks = fails = 0;}
    void test_cin(cs s){ in = new std::istringstream(s); std::cin.rdbuf(in->rdbuf()); }
    void fail_hdr(cs stra, cs strb, cs file, int line, cs func) {
        serr << "==================================================" << std::endl;
        serr << "FAIL: " << func << std::endl;
        serr << "--------------------------------------------------" << std::endl;
        serr << "File \"" << file << "\", line " << line << " in " << func << std::endl;
        serr << "  Checking " << stra << " == " << strb << std::endl;
    }
    template <typename T> void check(T a, T b, cs stra, cs strb, cs file, int line, cs func) {
        checks++; if (a == b) { std::cout << "."; return; }
        fails++; std::cout << "F"; fail_hdr(stra, strb, file, line, func);
        serr << "  Error: \"" << a << "\" ! = \"" << b << "\"" << std::endl << std::endl;
    }
    virtual void single_test() {}
    virtual void test_list() { single_test(); }
    double dclock() { return double(clock()) / CLOCKS_PER_SEC; }
    int status() {
        std::cout << std::endl; if (fails) std::cout << serr.str();
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Ran " << checks << " checks in " << dclock() << "s" << std::endl << std::endl;
        if (fails) std::cout << "FAILED (failures=" << fails << ")"; else std::cout << "OK" << std::endl;
        return fails > 0;
    }
    int run() { std::streambuf* ocin = std::cin.rdbuf(); test_list(); std::cin.rdbuf(ocin); return status(); }
};


class MyCppunit: public Cppunit {

    Modulos* m;
    Binominals* d;

    void single_test() {

        // Helping
        m = new Modulos;
        CHECK(m->add(4, 5), 9);
        CHECK(m->mul(4, 5), 20);
        CHECK(m->pow(4, 5), 1024);

        // Small modulo operations
        d = new Binominals(23);
        CHECK(d->add(4, 5), 9);
        CHECK(d->mul(4, 5), 20);
        CHECK(d->pow(4, 5), 12);
        for (int i=1; i<10; i++)
            CHECK(d->mul(i, d->inv(i)), 1);

        // Precomputed factorials
        d = new Binominals((1LL << 30) - 35);
        CHECK(d->fact(0), 1);
        CHECK(d->fact(1), 1);
        CHECK(d->fact(4), 24);

        // Base larger than int
        d = new Binominals((1LL << 62) - 57);

        // Precomputed inverted factorials
        for (int i=1000; i<1010; i++)
            CHECK(d->mul(d->fact(i), d->ifact(i)), 1);

        // Permutations Pn,k
        CHECK(d->P(7, 5), 2520);

        // Binominal Coefficient Cn,k
        CHECK(d->C(7, 4), 35);
    }
};

int main() {
    // Unit tests: -ut
    return (new MyCppunit)->run();
}

