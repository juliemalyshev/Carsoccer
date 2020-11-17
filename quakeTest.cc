#include <iostream>
#include <string>

std::vector<float> normalizeList(std::vector<float> quakeList) {
    std::vector<float> normalizedQuakes(quakeList.size());
    float min = std::min_element(quakeList.begin(), quakeList.end());
    for(int i = 0; i<quakeList.size() - 1; i++){
        normalizedQuakes.at(i) = quakeList.at(i) - min;
    }
    float max = std::max_element(normalizedQuakes.begin(), normalizedQuakes.end());
    for(int i = 0; i<normalizedQuakes.size() - 1; i++){
        normalizedQuakes.at(i) = normalizedQuakes.at(i) / max;
    }
    return normalizedQuakes;
}

int main{
    std::vector<float> quakes = {0.0, 2.3, 5.1, 1.1, 7.6, 1.7};
    std::vector<float> normalizedQuakes = normalizeList(quakes);

    for (int i = 0; i < normalizedQuakes.size(); i++) {
        std::cout << normalizedQuakes[i] << " ";
    }
    std::cout << std::endl;
}