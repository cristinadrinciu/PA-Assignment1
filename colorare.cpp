#include <iostream>
#include <fstream>
#include <vector>

#define MODULO 1000000007

using namespace std;

struct region {
    int nr_squares;
    char type;
};

long long logarithmic_pow(long long base, long long exponent) {
    long long res = 1;

    base = base % MODULO;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            res = (res * base) % MODULO;

        exponent = exponent >> 1;
        base = (base * base) % MODULO;
    }

    return res;
}

long long get_number_of_ways(vector<region> regions, int k) {
    vector<long long> dp(k + 1, 0);

    // we will use dynamic programming to solve this problem
    // base case
    // verify the first region
    if (regions[0].type == 'H') {
        dp[0] = 6;
        dp[0] = (dp[0] * logarithmic_pow(3, regions[0].nr_squares - 1))
                % MODULO;
    } else {
        dp[0] = 3;
        dp[0] = (dp[0] * logarithmic_pow(2, regions[0].nr_squares - 1))
                % MODULO;
    }

    for (int i = 1; i < k; i++) {
        if (regions[i - 1].type == 'H') {
            if (regions[i].type == 'H') {
                // color the first square in the current region
                dp[i] = (dp[i - 1] * 3) % MODULO;  // 3 ways to color H H case

                // color the nexr nr_squares - 1 squares in the current region
                dp[i] = (dp[i] * logarithmic_pow(3, regions[i].nr_squares - 1))
                        % MODULO;
            } else {
                // color the first square in the current region
                dp[i] = (dp[i - 1] * 1) % MODULO;  // one way to color H V case

                // color the next nr_squares - 1 squares in the current region
                dp[i] = (dp[i] * logarithmic_pow(2, regions[i].nr_squares - 1))
                        % MODULO;
            }
        } else if (regions[i - 1].type == 'V') {
            if (regions[i].type == 'H') {
                // color the first square in the current region
                dp[i] = (dp[i - 1] * 2) % MODULO;  // 2 ways to color V H case

                // color the next nr_squares - 1 squares in the current region
                dp[i] = (dp[i] * logarithmic_pow(3, regions[i].nr_squares - 1))
                        % MODULO;
            } else {
                // color the first square in the current region
                dp[i] = (dp[i - 1] * 2) % MODULO;  // 2 ways to color V V case

                // color the next nr_squares - 1 squares in the current region
                dp[i] = (dp[i] * logarithmic_pow(2, regions[i].nr_squares - 1))
                        % MODULO;
            }
        }
    }

    return dp[k - 1];
}

int main() {
    ifstream fin("colorare.in");
    ofstream fout("colorare.out");

    int k;

    fin >> k;

    vector<region> regions(k + 1);

    for (int i = 0; i < k; i++) {
        fin >> regions[i].nr_squares >> regions[i].type;
    }

    fout << get_number_of_ways(regions, k) << endl;

    return 0;
}
