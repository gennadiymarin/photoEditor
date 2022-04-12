//
// Created by Геннадий Марьин on 3/27/22.
//

#include "sharpening.h"
#include <memory>

void FilterSharpening::Apply(FMatrix::Matrix2D &table) const {
    FMatrix::Matrix2D image_table = table;
    for (size_t y = 0; y < table.size(); ++y) {
        for (size_t x = 0; x < table.at(0).size(); ++x) {
            ColorF new_color = FMatrix::ApplyMatrix2D(FMatrix::Pixel{x, y}, matrix_, table);
            image_table[y][x].r = new_color.r;
            image_table[y][x].g = new_color.g;
            image_table[y][x].b = new_color.b;
        }
    }
    table = std::move(image_table);
}

std::unique_ptr<FilterSharpening> FilterSharpening::Create() {
    return std::make_unique<FilterSharpening>();
}

FMatrix::MatrixCoef2D const FilterSharpening::matrix_ = {{0,  -1, 0},
                                                         {-1, 5,  -1},
                                                         {0,  -1, 0}};
