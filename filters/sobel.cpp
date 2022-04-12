//
// Created by Геннадий Марьин on 3/27/22.
//

#include "sobel.h"
#include "grayscale.h"
#include <cmath>
#include <memory>


FMatrix::MatrixCoef2D const FilterSobel::matrixX_ = {{-1, -2, -1},
                                                     {0,  0,  0},
                                                     {1,  2,  1}};

FMatrix::MatrixCoef2D const FilterSobel::matrixY_ = {{-1, 0, 1},
                                                     {-2, 0, 2},
                                                     {-1, 0, 1}};

std::unique_ptr<FilterSobel> FilterSobel::Create() {
    return std::make_unique<FilterSobel>();
}

void FilterSobel::Apply(FMatrix::Matrix2D &table) const {
    FilterGrayscale grayscale;
    grayscale.Apply(table);
    FMatrix::Matrix2D image_tableX, image_tableY;
    image_tableX.resize(table.size());
    image_tableY.resize(table.size());
    for (size_t i = 0; i < table.size(); ++i) {
        image_tableX[i].resize(table.at(0).size());
        image_tableY[i].resize(table.at(0).size());
    }
    for (size_t y = 0; y < table.size(); ++y) {
        for (size_t x = 0; x < table.at(0).size(); ++x) {
            image_tableX[y][x] = FMatrix::ApplyMatrix2D(FMatrix::Pixel{x, y}, matrixX_, table);
            image_tableY[y][x] = FMatrix::ApplyMatrix2D(FMatrix::Pixel{x, y}, matrixY_, table);
        }
    }
    for (size_t y = 0; y < table.size(); ++y) {
        for (size_t x = 0; x < table.at(0).size(); ++x) {
            table[y][x].r =
                    sqrt(image_tableX[y][x].r * image_tableX[y][x].r +
                         image_tableY[y][x].r * image_tableY[y][x].r);
            table[y][x].g =
                    sqrt(image_tableX[y][x].g * image_tableX[y][x].g +
                         image_tableY[y][x].g * image_tableY[y][x].g);
            table[y][x].b =
                    sqrt(image_tableX[y][x].b * image_tableX[y][x].b +
                         image_tableY[y][x].b * image_tableY[y][x].b);
        }
    }
}
