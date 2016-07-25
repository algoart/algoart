// kmp.cc - Kmp program by Sergey 2016

#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Kmp (Main Program)
///////////////////////////////////////////////////////////////////////////////


vector<int> kmp_table(const string& W) {
    vector<int> T;
    assert(W.size() > 0);
    int cnd = -1;
    T.push_back(-1);
    for(auto c: W) {
        while (true) {
            if (cnd == -1 || W[cnd] == c) {
                cnd += 1;
                T.push_back(cnd);
                break;
            }
            cnd = T[cnd];
        }
    }
    return T;
}


int kmp_search(const string& W, const string& S) {
    int cnd = 0;
    auto T = kmp_table(W);
    for(unsigned int i=0; i < S.size(); i++) {
        while (true) {
            if (cnd == -1 || W[cnd] == S[i]) {
                cnd += 1;
                break;
            }
            cnd = T[cnd];
        }
        if (cnd == int(W.size())){
            return i - cnd + 1;
        }
    }
    return -1;
}



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

    void single_test() {

        // KMP table generation
        CHECK(kmp_table("A")[0],  -1);
        CHECK(kmp_table("AA")[2], 1);
        CHECK(kmp_table("AB")[2], 0);
        CHECK(kmp_table("ABAB")[4], 2);
        CHECK(kmp_table("ABCDABA")[7], 1)

        // KMP search
        CHECK(kmp_search("A", ""), -1);
        CHECK(kmp_search("AB", "B"), -1);
        CHECK(kmp_search("A", "BBBB"), -1);
        CHECK(kmp_search("A", "A"), 0);
        CHECK(kmp_search("BA", "BA"), 0);
        CHECK(kmp_search("A", "BA"), 1);
        CHECK(kmp_search("AS", "BDAS"), 2);
        CHECK(kmp_search("ABAC", "ABABABACB"), 4);

    }
};

int main() {
    // Unit tests: -ut
    return (new MyCppunit)->run();
}

