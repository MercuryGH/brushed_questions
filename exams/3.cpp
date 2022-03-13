#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <memory>
using std::vector, std::string;

int solution(vector<int> &A) {
    const int n = A.size();
    std::unordered_set<int> places;
    for (const int place : A) {
        places.insert(place);
    }
    const int m = places.size();

    // std::unordered_set<int> curPlaces; // places in the window
    std::unordered_map<int, int> curPlaces;
    int curPlacesCnt = 0;
    int ans = n;
    for (int l = 0, r = 0; r < n; r++) {
        if (curPlaces[A[r]] == 0) { // get a new place
            curPlacesCnt++; // no more needed
        }
        curPlaces[A[r]]++;

        if (curPlacesCnt == m) { // all places in the window
            for (; ; l++) { // see if we can add l
                if (curPlaces[A[l]] == 1) { // Must included, can't move
                    break;
                }
                curPlaces[A[l]]--;
            }
            ans = std::min(ans, r - l + 1);

            curPlaces[A[l]]--; // move one place to find answer
            curPlacesCnt--;
            l++;
        }
    }

    return ans;
}


int main() {
    vector<int> a = {7, 5, 2, 7, 2, 7, 4, 7};
    std::cout << solution(a) << "\n";
    return 0;
}