//
// Created by Геннадий Марьин on 3/27/22.
//
#include <cmath>
#include <memory>

#include "sketch.h"
#include "gaussionBlur.h"
#include "sobel.h"


FilterSketch::FilterSketch(const SketchOptions &options) : options_(options) {}

std::unique_ptr<FilterSketch> FilterSketch::Create(const SketchOptions &options) {
    return std::make_unique<FilterSketch>(options);
}

void FilterSketch::Apply(FMatrix::Matrix2D &table) const {
    auto image_tmp = table;
    FilterGaussianBlur gaussianBlur(FilterGaussianBlur::GaussianOption{options_.blur_});
    gaussianBlur.Apply(image_tmp);
    FilterSobel sobel;
    sobel.Apply(image_tmp);
    std::round(options_.moveX_);
    for (long y = std::max(options_.moveY_, long(0)); y < long(table.size()) + std::min(options_.moveY_, long(0)); ++y) {
        for (long x = std::max(options_.moveX_, long(0));
             x < long(table.at(0).size()) + std::min(options_.moveX_, long(0)); ++x) {
            //принудительно убираем полоски с краев, которые показывает Собель после Гауса
            if (y - options_.moveY_ <= 3 || x - options_.moveX_ <= 3 ||
                x - options_.moveX_ >= image_tmp.at(0).size() - 4 ||
                y - options_.moveY_ >= image_tmp.size() - 4) {
                image_tmp[y - options_.moveY_][x - options_.moveX_] = ColorF(0, 0, 0);
            }

            float grayColor = image_tmp[y - options_.moveY_][x - options_.moveX_].r +
                              image_tmp[y - options_.moveY_][x - options_.moveX_].g +
                              image_tmp[y - options_.moveY_][x - options_.moveX_].b;
            if (grayColor > options_.coef_) {
                table[y][x] = ColorF(1, 1, 1);
            }
        }
    }
}
