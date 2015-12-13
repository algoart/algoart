// disjoint_set.cc - Disjoint_set program by Sergey 2015
// AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

/*

Disjoint set is a data structure that keeps track of a set of elements
partitioned into a number of disjoint (nonoverlapping) subsets. It supports
two useful operations:

new(n) - Create an initial structure with n subsets

find(n) - Determine which subset a particular element is in. Find typically
returns an item from this set that serves as its "representative",
by comparing the result of two Find operations, one can determine whether two
elements are in the same subset.

join(a, b) - Join two subsets into a single subset

check(a, b) - Check two elements to belong to the same subset

NOTE: Rank heuristic is not included in this library due to a negative
performance effect.

Time complexity:    O(alpha(N))
Extra space:        O(N)

*/

#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Disjoint_set Class (Main Program)
///////////////////////////////////////////////////////////////////////////////


class Disjoint_set { public:

    vector<int> root;

    Disjoint_set(int n) { 
        root.resize(n+1); 
        for(int i=0; i<=n; i++) root[i] = i;
    }

    int find(int a){
        int r = root[a];
        while (r != a){
            int rr = root[r];
            root[a] = rr;
            a = r;
            r = rr;
        }
        return a;
    }

    void join(int a, int b) {
        root[find(b)] = find(a);
    }

    bool check(int a, int b){ 
        return find(a) == find(b);
    }
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

    Disjoint_set* d;

    void single_test() {

        d = new Disjoint_set(4);
        d->join(1, 3);
        CHECK(d->find(3), 1);
        CHECK(d->find(2), 2);
        d->join(3, 2);
        CHECKT(d->check(2, 1));

        // Performance test
        int nmax = 500000;
        d = new Disjoint_set(nmax);
        for (int i=0; i<nmax; i++) {
            int r = rand() % 4;
            if (r == 0) d->find(rand() % nmax);
            if (r > 0) d->join(rand() % nmax, rand() % nmax);
        }
    }
};

int main() {
    // Unit tests: -ut
    return (new MyCppunit)->run();
}

