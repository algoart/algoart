// gcd.cc - Gcd program by Sergey 2015
// AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

/*

In mathematics, the greatest common divisor (gcd) of two or more integers,
when at least one of them is not zero, is the largest positive integer that
divides the numbers without a remainder. For example, the GCD of 8 and 12 is 4.

In arithmetic and number theory, the least common multiple of two integers
a and b, usually denoted by LCM(a, b), is the smallest positive integer that
is divisible by both a and b.

LCM(a,b) = |a*b| / GCD(a, b)

Time complexity:    O(log a + log b)
Extra space:        O(1)


*/

#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Gcd (Main Program)
///////////////////////////////////////////////////////////////////////////////


typedef long long ll;

// Euclidean GCD algorithm
ll gcd(ll a, ll b){ while (b != 0){ ll t = b; b = a % b; a = t; } return a;}

// Using GCD to calculate LCM
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }


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


    void single_test() {

        // Euclidean algo
        CHECK(gcd(0, 0), 0);
        CHECK(gcd(100, 0), 100);
        CHECK(gcd(8, 2), 2);
        CHECK(gcd(30, 42), 6);
        CHECK(lcm(10, 15), 30);
        
        // Performance
        for (int i = 0; i < 10000; i++)
            gcd(1LL * rand() * rand() * rand(), 1LL * rand() * rand() * rand());
    }
};

int main() {
    // Unit tests: -ut
    return (new MyCppunit)->run();
}

