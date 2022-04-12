//
// Created by Геннадий Марьин on 3/6/22.
//

#include "filters.h"
#include <vector>
#include <cmath>


ColorF FMatrix::ApplyMatrix2D(Pixel pixel, const MatrixCoef2D &matrix, const Matrix2D &table) {
    auto DEFAULT = ColorF(table[pixel.y][pixel.x]);
    ColorF colorf;
    for (long y = 0; y < matrix.size(); ++y) {
        for (long x = 0; x < matrix.size(); ++x) {
            if (pixel.x >= std::max(long(0), 1 - x) && pixel.y >= std::max(long(0), 1 - y) &&
                pixel.x + x - 1 < table.at(0).size() && pixel.y + y - 1 < table.size()) {
                colorf.r += table[pixel.y + (y - 1)][pixel.x + (x - 1)].r * matrix[y][x];
                colorf.g += table[pixel.y + (y - 1)][pixel.x + (x - 1)].g * matrix[y][x];
                colorf.b += table[pixel.y + (y - 1)][pixel.x + (x - 1)].b * matrix[y][x];
            } else {
                colorf.r += DEFAULT.r * matrix[y][x];
                colorf.g += DEFAULT.g * matrix[y][x];
                colorf.b += DEFAULT.b * matrix[y][x];
            }
        }
    }
    colorf.r = std::min(float(1), std::max(float(0), colorf.r));
    colorf.g = std::min(float(1), std::max(float(0), colorf.g));
    colorf.b = std::min(float(1), std::max(float(0), colorf.b));
    return colorf;
}

ColorF FMatrix::ApplyMatrix1D(Pixel pixel, Dim dim, const MatrixCoef1D &matrix, const Matrix2D &table) {
    ColorF colorf;
    size_t r = matrix.size() / 2;
    if (dim == Dim::X) {
        size_t idx = pixel.x >= r ? 0 : r - pixel.x;
        size_t start_with = idx == 0 ? pixel.x - r : 0;
        size_t end_with = pixel.x + r < table.at(0).size() ? pixel.x + r + 1 : table.at(0).size();
        for (size_t i = start_with; i < end_with; ++i) {
            colorf.r += table[pixel.y][i].r * matrix[idx];
            colorf.g += table[pixel.y][i].g * matrix[idx];
            colorf.b += table[pixel.y][i].b * matrix[idx];
            ++idx;
        }
    } else {
        size_t idx = pixel.y >= r ? 0 : r - pixel.y;
        size_t start_with = idx == 0 ? pixel.y - r : 0;
        size_t end_with = pixel.y + r < table.size() ? pixel.y + r + 1 : table.size();
        for (size_t i = start_with; i < end_with; ++i) {
            colorf.r += table[i][pixel.x].r * matrix[idx];
            colorf.g += table[i][pixel.x].g * matrix[idx];
            colorf.b += table[i][pixel.x].b * matrix[idx];
            ++idx;
        }
    }
    return colorf;
}
