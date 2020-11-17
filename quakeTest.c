#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<float> normalizeList(vector<float> quakeList) {
    vector<float> normalizedQuakes(quakeList.size());
    float min ;
    min = std::min_element(*quakeList.begin(), *quakeList.end());
    for(int i = 0; i<quakeList.size() - 1; i++){
        normalizedQuakes.at(i) = quakeList.at(i) - min;
    }
    float max = std::max_element(*normalizedQuakes.begin(), *normalizedQuakes.end());
    for(int i = 0; i<normalizedQuakes.size() - 1; i++){
        normalizedQuakes.at(i) = normalizedQuakes.at(i) / max;
    }
    return normalizedQuakes;
};

int main()
{
    vector<float> quakes = {0.0, 2.3, 5.1, 1.1, 7.6, 1.7};
    vector<float> normalizedQuakes = normalizeList(quakes);

    for (int i = 0; i < normalizedQuakes.size(); i++) {
        cout << normalizedQuakes[i] << " ";
    }
    cout << endl;
}
