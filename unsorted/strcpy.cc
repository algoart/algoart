// strcpy.cc - Strcpy program by Sergey 2015

// All standard modules
#include <bits/stdc++.h>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Strcpy Class
///////////////////////////////////////////////////////////////////////////////


class Strcpy { public:

    static int const N = 100001;

    char* chars;

    Strcpy(){

        string s;
        cin >> s;
        chars = new char[N];
        mystrcopy(chars, s.c_str());
    }

    mystrcopy(char* dst, const char* src){
        while (*src != '\0') *dst++ = *src++;
        *dst = '\0';
    }

    int mystrlen(const char* src){
        int result = 0;
        while (*src++ != '\0') result += 1;
        return result;
    }

    string calculate(){

        long long result = 0;

        ostringstream resstr;
        resstr << result;

        return resstr.str();
    }
};


///////////////////////////////////////////////////////////////////////////////
// Strcpy Class test helping functions
///////////////////////////////////////////////////////////////////////////////

Strcpy* class_wrap_input(const string& test="") {

    streambuf* orig = cin.rdbuf();
    istringstream input(test);
    if (test != "") {
        cin.rdbuf(input.rdbuf());
    };
    Strcpy* d = new Strcpy();
    if (test != "") cin.rdbuf(orig);
    return d;
}

string calculate(const string& test="") {
    Strcpy* d = class_wrap_input(test);
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

    test_list() {
        test_class_basic_functions();
        test_done();
        test_sample_tests();
        test_done();
        test_time_limit_test();
        test_done();
    }

    test_class_basic_functions() {

        // Constructor test
        string test = "test";
        Strcpy* d = class_wrap_input(test);
        CHECK(d->chars[0], 't');
        char* chars = new char[5];
        d->mystrcopy(chars, d->chars);
        CHECKS(chars, d->chars);
        chars[0] = 'a';

        // Make sure these are different arrays
        CHECKT((string)chars != (string)d->chars);

        const char* ch = "data0";
        CHECK(d->mystrlen(ch), 5);

    }

    test_sample_tests() {

    }

    test_time_limit_test() {

        int imax = 100;
        string test;
        ostringstream o_test;

        for(int i = 0; i < imax; i++) o_test << "a";
        test = o_test.str();

        double start = double(clock()) / CLOCKS_PER_SEC;
        Strcpy* d = class_wrap_input(test);

        double calc = double(clock()) / CLOCKS_PER_SEC;
        d->calculate();

        double stop = double(clock()) / CLOCKS_PER_SEC;
        cout << "Time Test: " << stop - start << "s (input " << calc - start;
        cout << "s calc " << stop - calc << "s)" << endl;
    }
};

///////////////////////////////////////////////////////////////////////////////
// Main Execution
///////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {

    // Faster cin and cout
    ios_base::sync_with_stdio(0);cin.tie(0);

    cout << calculate() << endl;
    return 0;
}

