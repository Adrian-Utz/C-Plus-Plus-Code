#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    const char* str = "1234.56"; // Example string for atof()

    double d = atof(str);
    cout << "atof(\"" << str << "\") = " << d << '\n';

    int i = atoi(str);
    cout << "atoi(\"" << str << "\") = " << i << '\n';

    long l = atol(str);
    cout << "atol(\"" << str << "\") = " << l << '\n';

    long long ll = atoll(str);
    cout << "atoll(\"" << str << "\") = " << ll << '\n';

    double d2 = strtod(str, nullptr);
    cout << "strtod(\"" << str << "\") = " << d2 << '\n';

    float f = strtof(str, nullptr);
    cout << "strtof(\"" << str << "\") = " << f << '\n';

    long double ld = strtold(str, nullptr);
    cout << "strtold(\"" << str << "\") = " << ld << '\n';

    long l2 = strtol(str, nullptr, 10);
    cout << "strtol(\"" << str << "\", base=10) = " << l2 << '\n';

    long long ll2 = strtoll(str, nullptr, 10);
    cout << "strtoll(\"" << str << "\", base=10) = " << ll2 << '\n';

    unsigned long ul = strtoul(str, nullptr, 10);
    cout << "strtoul(\"" << str << "\", base=10) = " << ul << '\n';

    unsigned long long ull = strtoull(str, nullptr, 10);
    cout << "strtoull(\"" << str << "\", base=10) = " << ull << '\n';

    return 0;
}