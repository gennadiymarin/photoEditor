//
// Created by Геннадий Марьин on 3/27/22.
//

#include "grayscale.h"
#include <memory>


void FilterGrayscale::Apply(FMatrix::Matrix2D &table) const {
    for (auto &line: table) {
        for (auto &pixel: line) {
            float color_new = pixel.r * consts_.r + pixel.g * consts_.g + pixel.b * consts_.b;
            pixel.r = color_new;
            pixel.g = color_new;
            pixel.b = color_new;
        }
    }
}

std::unique_ptr<FilterGrayscale> FilterGrayscale::Create() {
    return std::make_unique<FilterGrayscale>();
}

FilterGrayscale::GrayConsts FilterGrayscale::consts_;
