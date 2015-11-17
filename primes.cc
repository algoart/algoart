// primes.cc - Primes program by Sergey 2015
// AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

/*

Helpful functions related to prime numbers and factorization

new(maxn)    - Create an initial structure with precalculated primes up to n
pf(n)        - Prime factor, returns 0 if prime. Sieve of Eratosthenes
is_prime(n)  - Use PF to check for primality
nth_prime(n) - Returns Nth prime number
factorize(n) - Factorize integer, returns map of factors and exponents

Default maxN is 10^6

Time complexity:    O(1), O(N) initialization
Extra space:        O(N)

*/

#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Primes Class (Main Program)
///////////////////////////////////////////////////////////////////////////////


class Primes { public:

    vector <int> pfs, primes;

    Primes(int maxn=1e6){
        pfs.resize(maxn + 1);
        for(int i = 2; i <= maxn; i++)
            if (pfs[i] == 0) {
                pfs[i] = i;
                primes.push_back(i);
                long long s = 1LL*i*i;
                if (s <= maxn)                  
                    for(int j = (int)s; j <= maxn; j += i) pfs[j] = i;
            }
    }

    int pf(int n) { return pfs[n]; }
    bool is_prime(int n) { return n > 1 and pf(n) == n; }
    int nth_prime(int n) { return primes[n]; }

    map <int, int> factorize(int n) {
        map <int, int> r;
        while (n > 1) {
            int ld = pf(n);
            r[ld]++;
            n /= ld;
        }
        return r;
    }
};

///////////////////////////////////////////////////////////////////////////////
// Unit tests
///////////////////////////////////////////////////////////////////////////////


// Cppunit - C++ Unit testing TDD framework (github.com/cppunit/cppunit)
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

    Primes* d;

    void single_test() {


        // LPF function
        d = new Primes(20);
        CHECK(d->pf(0), 0);
        CHECK(d->pf(1), 0);
        CHECK(d->pf(2), 2);
        CHECK(d->pf(6), 2);
        CHECK(d->pf(13), 13);
        CHECK(d->pf(8), 2);
        CHECK(d->pf(14), 2);

        // Is prime
        d = new Primes(30);
        CHECK(d->is_prime(1), false);
        CHECK(d->is_prime(6), false);
        CHECK(d->is_prime(13), true);
        CHECK(d->is_prime(14), false);

        // Nth prime
        d = new Primes;
        CHECK(d->nth_prime(0), 2);
        CHECK(d->nth_prime(5), 13);
        CHECK(d->nth_prime(5), 13);

        // Factorize
        d = new Primes(24);
        auto fact = d->factorize(24);
        CHECK(fact[2], 3);
        CHECK(fact[3], 1);

    }
};

int main() {
    // Unit tests: -ut
    return (new MyCppunit)->run();
}

