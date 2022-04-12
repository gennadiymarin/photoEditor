//
// Created by Геннадий Марьин on 3/27/22.
//

#include "edgeDetection.h"
#include "grayscale.h"
#include <memory>

void FilterEdgeDetection::Apply(FMatrix::Matrix2D &table) const {
    FilterGrayscale grayscale;
    grayscale.Apply(table);
    FMatrix::Matrix2D image_table = table;
    for (size_t y = 0; y < table.size(); ++y) {
        for (size_t x = 0; x < table.at(0).size(); ++x) {
            ColorF new_color = FMatrix::ApplyMatrix2D(FMatrix::Pixel{x, y}, matrix_, table);
            image_table[y][x].r = new_color.r;
            image_table[y][x].g = new_color.g;
            image_table[y][x].b = new_color.b;
            float grayColor = image_table[y][x].r + image_table[y][x].g + image_table[y][x].b;
            grayColor > option_.threshold_ ? image_table[y][x] = ColorF(1, 1, 1)
                                           : image_table[y][x] = ColorF(0, 0, 0);
        }
    }
    table = std::move(image_table);
}

FilterEdgeDetection::FilterEdgeDetection(EdgeDetectionOption option) : option_(option) {}

std::unique_ptr<FilterEdgeDetection> FilterEdgeDetection::Create(EdgeDetectionOption option) {
    return std::make_unique<FilterEdgeDetection>(option);
}

FMatrix::MatrixCoef2D const FilterEdgeDetection::matrix_ = {{0,  -1, 0},
                                                            {-1, 4,  -1},
                                                            {0,  -1, 0}};
