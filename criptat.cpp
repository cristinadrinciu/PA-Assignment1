#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#define MAX_LONG_LEN 10000

using namespace std;

void set_char_freq(vector<unordered_map<char, int>> &char_freq,
                    vector<string> words, int nr_words,
                    unordered_set<char> &distinct_chars) {
    for (int i = 0; i < nr_words; i++) {
        // mark frequency of each char in each word
        for (int j = 0; j < words[i].size(); j++) {
            if (char_freq[i].find(words[i][j]) == char_freq[i].end())
                char_freq[i][words[i][j]] = 1;
            else
                char_freq[i][words[i][j]]++;

            // insert i the set of distinct chars
            distinct_chars.insert(words[i][j]);
        }
    }
}

void get_possible_concatenations(vector<vector<long>> &chars_combinations,
                                unordered_set<char> distinct_chars,
                                vector<unordered_map<char, int>> &char_freq,
                                int nr_words, vector<string> &words) {
    int i = 0;  // index for building the combinations matrix

    for (char curr_char : distinct_chars) {
        /* for each char, we will try to find the concatenations possible,
        based on the frequency of the dominant char */
        for (int j = 0; j < nr_words; j++) {
            int word_len = words[j].size();
            if (char_freq[j].find(curr_char) == char_freq[j].end()) {
                continue;
            }

            // extract the freq of the current char from the current word
            int curr_freq = char_freq[j].at(curr_char);

            /* parse backwards to avoid using updated values,
            that can lead to lengths that are too long or impossible to reach */
            for (int k = MAX_LONG_LEN - 1; k >= 0; k--) {
                if (chars_combinations[i][k] == 0 && k != 0) {
                    continue;
                }

                /* update the value of the freq
                of the dominant char after concatenation */
                chars_combinations[i][k + word_len] =
                max(chars_combinations[i][k + word_len],
                                    chars_combinations[i][k] + curr_freq);
            }
        }
        i++;
    }
}


int main() {
    ifstream fin("criptat.in");
    ofstream fout("criptat.out");

    int nr_words;

    fin >> nr_words;

    vector<string> words(nr_words);

    for (int i = 0; i < nr_words; i++) {
        fin >> words[i];
    }

    // for each word, we will store the frequency of each char
    vector<unordered_map<char, int>> char_freq(nr_words);

    // store the distinct chars
    unordered_set<char> distinct_chars = {};

    set_char_freq(char_freq, words, nr_words, distinct_chars);

    /* for each distinct char,
    we will try to find combinations of concatenations,
    based on the frequency of the dominant char
    the index represents the length of the concatenation,
    and the value the frequency of the dominant char after concatenation */

    // matrix of concatenations frequency values
    vector<vector<long>> chars_combinations(distinct_chars.size(),
                                    vector<long>(MAX_LONG_LEN, 0));

    get_possible_concatenations(chars_combinations,
                        distinct_chars, char_freq, nr_words, words);

    long max_password_len = 0;

    // find the maximum length of the password
    for (int i = 0; i < chars_combinations.size(); i++) {
        for (long j = 0; j < MAX_LONG_LEN; j++) {
            if (j < 2 * chars_combinations[i][j]) {
                max_password_len = max(max_password_len, j);
            }
        }
    }

    fout << max_password_len;

    return 0;
}
