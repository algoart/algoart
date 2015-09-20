// linked_list.cc - Linked_list quiz by Sergey 2015

/*

Implement linked list (create, traverse, print)
Reverse linked list in O(N)
Find 1cycle loop in list
Find any loop in list

*/

// Standard modules
#include <bits/stdc++.h>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Linked_list Class
///////////////////////////////////////////////////////////////////////////////

typedef int Base;
template <class Base> struct Node: pair <Base, Node<Base>*> {};

template <class Base> class Linked_list { public:

    Node<Base>* list;

    Linked_list() {

        list = NULL;
    }

    insert(Base n) {
        Node<Base>* l = new Node<Base>;
        l->first = n;
        l->second = list;
        list = l;
    }

    Base get(Node<Base>* p) {
        return p->first;
    }

    Node<Base>* start_iter() {
        return list;
    }

    next_iter(Node<Base>*& p) {
        if (p != NULL) p = p->second;
    }

    string str() {
        ostringstream msg;
        Node<Base>* p = start_iter();
        bool first = true;
        while (p != NULL) {
            if (not first) msg << " ";
            first = false;
            msg << get(p);
            next_iter(p);
        }
        return msg.str();
    }

    reverse() {
        Node<Base>* prev = NULL;
        Node<Base>* cur = list;
        Node<Base>* next;
        while (cur != NULL) {
            next = cur->second;
            cur->second = prev;
            prev = cur;
            cur = next;
        }
        list = prev;
    }

    loop1() {
        Node<Base>* prev = NULL;
        Node<Base>* p = start_iter();
        while (p != NULL) {
            if (prev == p->second) return 1;
            prev = p;
            next_iter(p);
        }
        return 0;
    }

    loop() {
        Node<Base>* fast = start_iter();
        Node<Base>* slow = start_iter();
        while (fast != NULL) {
            next_iter(fast);
            next_iter(fast);
            next_iter(slow);
            if (fast == slow) return 1;
        }
        return 0;
    }

    string calculate() {

        long long result = 0;

        ostringstream resstr;
        resstr << result;

        return resstr.str();
    }
};


///////////////////////////////////////////////////////////////////////////////
// Linked_list Class test helping functions
///////////////////////////////////////////////////////////////////////////////

Linked_list<int>* class_wrap_input(const string& test="") {

    streambuf* orig = cin.rdbuf();
    istringstream input(test);
    if (test != "") {
        cin.rdbuf(input.rdbuf());
    };
    Linked_list<int>* d = new Linked_list<int>();
    if (test != "") cin.rdbuf(orig);    
    return d;
}

string calculate(const string& test="") {
    Linked_list<int>* d = class_wrap_input(test);
    string result = d->calculate();
    delete d;
    return result;
}

///////////////////////////////////////////////////////////////////////////////
// Unit tests base Class
///////////////////////////////////////////////////////////////////////////////


class Unittest { public:

    #define CHECK(a, b)\
        test_fail_err(a, b, #a, #b, __FILE__, __LINE__, __FUNCTION__);
    #define CHECKT(a)\
        test_fail_err(a, 1, #a, "true", __FILE__, __LINE__, __FUNCTION__);
    #define CHECKS(a, b)\
        test_fail_errs(a, b, #a, #b, __FILE__, __LINE__, __FUNCTION__);

    int test_cnt, fail_cnt, fail;
    string status, fail_msg;

    Unittest() {
        test_cnt = fail_cnt = fail = 0;
        status = "OK";
    }

    // Override this function in derived class
    virtual test_list() {
        test_basic();
        test_done();
    }

    test_basic() { CHECKT("Base class basic test" == ""); }

    run() {
        test_list();
        double elp_secs = double(clock()) / CLOCKS_PER_SEC;
        cout << endl;
        if (fail_cnt > 0) cout << fail_msg;
        cout << "--------------------------------------------------" << endl;
        cout << "Ran " << test_cnt << " tests in " << elp_secs << "s" << endl;
        cout << endl;
        if (fail_cnt > 0) cout << "FAILED (failures=" << fail_cnt << ")";
        else cout << status << endl;
        if (fail_cnt > 0) return 1;
    }

    test_fail_hdr(const string& stra, const string& strb,
            const string& file, int line, const string& function) {
        fail_cnt ++;
        fail = 1;
        ostringstream msg;
        msg << "==================================================" << endl;
        msg << "FAIL: " << function << endl;
        msg << "--------------------------------------------------" << endl;
        msg << "File \"" << file << "\", line " << line;
        msg << " in " << function << endl;
        msg << "  Checking " << stra << " == " << strb << endl;
        fail_msg += msg.str();
    }

    test_fail_err(long long a, long long b,
            const string& stra, const string& strb,
            const string& file, int line, const string& function) {
        if (a == b) return 0;
        test_fail_hdr(stra, strb, file, line, function);
        ostringstream msg;
        msg << "  Error: " << a << " ! = " << b << endl << endl;
        fail_msg += msg.str();
    }

    test_fail_errs(const string& a, const string& b,
            const string& stra, const string& strb,
            const string& file, int line, const string& function) {
        if (a == b) return 0;
        test_fail_hdr(stra, strb, file, line, function);
        ostringstream msg;
        msg << "  Error: \"" << a << "\" ! = \"" << b << "\"" << endl;
        msg << endl;
        fail_msg += msg.str();
    }

    test_done() {
        test_cnt ++;
        if (fail == 0) cout << ".";
        else cout << "F";
        fail = 0;
    }
};


///////////////////////////////////////////////////////////////////////////////
// Local Unit tests
///////////////////////////////////////////////////////////////////////////////


class LocalUnittest: public Unittest {

    test_class_basic_functions() {

        // Constructor test
        Linked_list<int>* d = new Linked_list<int>();
        CHECKT(d->list == NULL);

        // Insert
        d->insert(1);
        CHECK(d->list->first, 1);
        CHECKT(d->list->second == NULL);
        d->insert(2);
        CHECK(d->list->first, 2);
        CHECK(d->list->second->first, 1);
        d->insert(3);
        CHECK(d->list->second->second->first, 1);
        CHECKT(d->list->second->second->second == NULL);

        // Get and next
        Node<int>* p = d->start_iter();
        CHECK(d->get(p), 3);
        d->next_iter(p);
        CHECK(d->get(p), 2);

        // Str
        CHECKS(d->str(), "3 2 1");

    }

    test_sample_tests() {

        // Reverse linked list in O(N)
        int dlen = 100000;
        Linked_list<int>* d = new Linked_list<int>();
        for(int i=0; i< dlen; i++) d->insert(i);
        CHECK(d->list->first, dlen-1);
        d->reverse();
        CHECK(d->list->first, 0);

        // Find 1cycle loop in list
        d = new Linked_list<int>();
        d->insert(1);
        d->insert(2);
        CHECK(d->loop1(), 0);
        d->list->second->second = d->list->second;
        CHECK(d->loop1(), 1);
        CHECK(d->loop(), 1);

        // Find any loop in list
        d = new Linked_list<int>();
        d->insert(1);
        d->insert(2);
        d->insert(3);
        d->insert(4);
        CHECK(d->loop(), 0);
        d->list->second->second->second->second = d->list->second;
        CHECK(d->loop(), 1);
    }

    test_list() {
        test_class_basic_functions();
        test_done();
        test_sample_tests();
        test_done();
    }
};

///////////////////////////////////////////////////////////////////////////////
// Main Execution
///////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {

    // Faster cin and cout
    ios_base::sync_with_stdio(0);cin.tie(0);

    if (argc > 1 && !strcmp(argv[1], "-ut")) {
        LocalUnittest lut;
        return lut.run();
    }
    cout << calculate() << endl;
    return 0;
}

