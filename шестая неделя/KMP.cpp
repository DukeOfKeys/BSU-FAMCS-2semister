#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
class search_by_KMP
{
public:
    int find_str(const string &str, const string &str_o)
    {
        vector<size_t> prefff = prefix_function(str_o);
        prefix_find(str_o.c_str(), str.c_str(), prefff, [](size_t i)
                    { cout << i << endl; return 1; });
        return 0;
    }

private:
    vector<size_t> prefix_function(const string &s)
    {
        size_t n = s.length();
        vector<size_t> pi(n);
        for (size_t i = 1; i < n; ++i)
        {
            size_t j = pi[i - 1];
            while ((j > 0) && (s[i] != s[j]))
                j = pi[j - 1];

            if (s[i] == s[j])
                ++j;
            pi[i] = j;
        }
        return pi;
    }
    void prefix_find(const char *str, const char *obr, vector<size_t> &pi, int (*f)(size_t))
    {

        pi[0] = 0;
        size_t l;
        for (l = 1; obr[l]; ++l)
        {
            size_t j = pi[l - 1];
            while ((j > 0) && (obr[l] != obr[j]))
                j = pi[j - 1];
            if (obr[l] == obr[j])
                ++j;
            pi[l] = j;
        }
        size_t j = 0;
        for (size_t i = 0; str[i]; ++i)
        {
            while ((j > 0) && (str[i] != obr[j]))
                j = pi[j - 1];

            if (str[i] == obr[j])
                ++j;
            if (j == l)
                if (!f(i - l + 1))
                    return;
        }
    }
};
int main()
{
    srand(time(NULL));
    search_by_KMP el;

    vector<string>
        russianLetters = {
            "а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    string very_long_string = "";

    for (unsigned long long index = 0; index < 1000000000; index++)
        very_long_string.append(russianLetters[rand() % 33]);
    ofstream myfile("very_important_info.txt");
    myfile << very_long_string;
    cout << el.find_str("тест", very_long_string);

    myfile.flush();
    myfile.close();
    return 0;
}
