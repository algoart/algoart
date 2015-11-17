// binary_search.cc - Bin_search program by Sergey 2015
// AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

/*

Binary search algorithm implementation.

Binary search or half-interval search algorithm finds the position of a target
value within a sorted array

The binary search algorithm can be classified as a dichotomic
divide-and-conquer search algorithm and executes in logarithmic time.

Time complexity:    O(log n)
Extra space:        O(1)

*/

#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Binary_search (Main Program)
///////////////////////////////////////////////////////////////////////////////


// Find lower bound - leftmost position for new element to be inserted
template <typename t> int lbound(vector <t>& v, t n){
    int b = 0, e = v.size();
    while (b != e){
        int mid = (b + e) / 2;
        if (v[mid] < n) b = mid + 1;
        else e = mid;
    }
    return b;
}


// Find upper bound - rightmost position for new element to be inserted
template <typename t> int rbound(vector <t>& v, t n){
    int b = 0, e = v.size();
    while (b != e){
        int mid = (b + e) / 2;
        if (v[mid] <= n) b = mid;
        else e = mid - 1;
    }
    return b;
}


template <typename t> int search(vector <t>& v, t n){
    int lb = lbound(v, n);
    return (lb == (int)v.size() or v[lb] != n) ? -1 : lb;
}


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

        vector <int> v = {1, 2, 5, 5, 10, 90};
        CHECK(lbound<int>(v, 0), 0);
        CHECK(lbound<int>(v, 100), 6);

        // Low and upper bounds
        CHECK(lbound<int>(v, 5), 2);
        CHECK(rbound<int>(v, 5), 3);

        // Search
        CHECK(search<int>(v, 11), -1);
        CHECK(search<int>(v, 10), 4);
    }
};

int main() {
    // Unit tests: -ut
    return (new MyCppunit)->run();
}

