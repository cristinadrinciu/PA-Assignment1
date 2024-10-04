#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#define MAX_DOUBLE_VALUE 1e9

using namespace std;


double get_min_price(vector<int> prices, int n, int k) {
    vector<double> dp(n + 1, MAX_DOUBLE_VALUE);

    // we will use dynamic programming to solve this problem
    // RUCSAC

    // base case
    dp[0] = 0;  // price for 0 products is 0

    for (int i = 1; i <= n; i++) {
        // but the current product by itself
        dp[i] = dp[i - 1] + prices[i];

        if (i > 1) {
            // group the last 2 products (1 + 1/2 of the cheapest product)
            dp[i] = min(dp[i], dp[i - 2] + prices[i - 1] + prices[i] -
                    0.5 * min(prices[i - 1], prices[i]));
        }

        if (i > 2) {
            // group the last 3 products (1 + 1 + the cheapest product is free)
            dp[i] = min(dp[i], dp[i - 3] + prices[i - 2] + prices[i - 1]
            + prices[i] - double(min(prices[i - 2],
                                    min(prices[i - 1], prices[i]))));
        }
    }

    // return the final price of the n products
    return dp[n];
}


int main() {
    ifstream fin("oferta.in");
    ofstream fout("oferta.out");

    int nr_products, k;

    fin >> nr_products >> k;

    // read the prices of the products
    vector<int> prices(nr_products + 1, 0);

    for (int i = 1; i <= nr_products; i++) {
        fin >> prices[i];
    }

    // find the minimum price
    fout << fixed << setprecision(1) <<
            get_min_price(prices, nr_products, k) << endl;

    return 0;
}
