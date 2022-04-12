//
// Created by Геннадий Марьин on 3/27/22.
//

#include "negative.h"
#include <memory>


void FilterNegative::Apply(FMatrix::Matrix2D &table) const {
    for (auto &line: table) {
        for (auto &pixel: line) {
            pixel.r = 1 - pixel.r;
            pixel.g = 1 - pixel.g;
            pixel.b = 1 - pixel.b;
        }
    }
}

std::unique_ptr<FilterNegative> FilterNegative::Create() {
    return std::make_unique<FilterNegative>();
}
