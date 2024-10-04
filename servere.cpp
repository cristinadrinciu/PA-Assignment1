#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> vectors_sum(vector<int> v, vector<int> w, int n) {
    vector<double> sum(n, 0);

    for (int i = 0; i < n; i++) {
        sum[i] = v[i] + w[i];
    }

    return sum;
}

vector<double> vectors_diff(vector<int> v, vector<int> w, int n) {
    vector<double> diff(n, 0);

    for (int i = 0; i < n; i++) {
        diff[i] = v[i] - w[i];
    }

    return diff;
}

double get_min(vector<double> v, int n) {
    double min = v[0];

    for (int i = 1; i < n; i++) {
        if (v[i] < min) {
            min = v[i];
        }
    }

    return min;
}

double get_max(vector<double> v, int n) {
    double max = v[0];

    for (int i = 1; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }

    return max;
}



double get_system_power(vector<int> powers,
                        vector<int> currents, int n) {
    // we have the equation :
    vector<double> vector_sum = vectors_sum(powers, currents, n);
    vector<double> vector_diff = vectors_diff(currents, powers, n);

    double max = get_max(vector_diff, n);
    double min = get_min(vector_sum, n);

    double common_power = (double)(max + min) / 2;

    vector<double> system_power(n, 0);

    for (int i = 0; i < n; i++) {
        system_power[i] = powers[i]
                - double(abs(common_power - currents[i]));
    }

    return get_min(system_power, n);
}

int main() {
    ifstream fin("servere.in");
    ofstream fout("servere.out");

    int n;
    fin >> n;

    vector<int> powers(n, 0);
    vector<int> currents(n, 0);

    for (int i = 0; i < n; i++) {
        fin >> powers[i];
    }

    for (int i = 0; i < n; i++) {
        fin >> currents[i];
    }

    fout << fixed << setprecision(1) <<
            get_system_power(powers, currents, n);

    return 0;
}
