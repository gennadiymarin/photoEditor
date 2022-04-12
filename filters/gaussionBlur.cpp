//
// Created by Геннадий Марьин on 3/27/22.
//

#include "gaussionBlur.h"
#include <cmath>
#include <memory>

FilterGaussianBlur::FilterGaussianBlur(const GaussianOption& option) : option_(option) {}

std::unique_ptr<FilterGaussianBlur> FilterGaussianBlur::Create(const GaussianOption& option) {
    return std::make_unique<FilterGaussianBlur>(option);
}

void FilterGaussianBlur::Apply(FMatrix::Matrix2D &table) const {
    matrix_ = CreateGaussMatrix(option_, table);
    FMatrix::Matrix2D image_table;
    image_table.resize(table.size());
    for(auto& line : image_table){
        line.resize(table.at(0).size());
    }
    for (size_t y = 0; y < table.size(); ++y) {
        for (size_t x = 0; x < table.at(0).size(); ++x) {
            image_table[y][x] = FMatrix::ApplyMatrix1D(FMatrix::Pixel{x, y}, FMatrix::Dim::X, matrix_, table);
        }
    }
    table = image_table;
    for (size_t x = 0; x < table.at(0).size(); ++x) {
        for (size_t y = 0; y < table.size(); ++y) {
            image_table[y][x] = FMatrix::ApplyMatrix1D(FMatrix::Pixel{x, y}, FMatrix::Dim::Y, matrix_, table);
        }
    }
    table = std::move(image_table);
}


FMatrix::MatrixCoef1D FilterGaussianBlur::CreateGaussMatrix(const GaussianOption& option, FMatrix::Matrix2D &table) const {
    auto matrix = FMatrix::MatrixCoef1D(
            ceil(option.coef_ * std::min(size_t(6), std::min(table.size(), table.at(0).size()))));
    if (matrix.size() % 2 == 0) {
        matrix.push_back(0.0);
    }
    for (size_t i = 0; i <= matrix.size() / 2; ++i) {
        float value = GetGaussValue(matrix.size() / 2 - i, option);
        matrix[i] = value;
        matrix[matrix.size() - 1 - i] = value;
    }
    return matrix;
}

float FilterGaussianBlur::GetGaussValue(size_t r, const GaussianOption& option) const {
    return (1 / (sqrt(2 * M_PI * option.coef_ * option.coef_))) *
           (pow(M_E, -((r * r) / (2 * option.coef_ * option.coef_))));
}
