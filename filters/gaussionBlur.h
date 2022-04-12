//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include "filters.h"
#include <memory>


class FilterGaussianBlur : public IFilter {
public:
    struct GaussianOption{
        float coef_ = 0.84;
    };
    void Apply(FMatrix::Matrix2D &table) const override;

    explicit FilterGaussianBlur(const GaussianOption& option);
    static std::unique_ptr<FilterGaussianBlur> Create(const GaussianOption& option);

private:
    FMatrix::MatrixCoef1D CreateGaussMatrix(const GaussianOption& option, FMatrix::Matrix2D &table) const;
    float GetGaussValue(size_t r, const GaussianOption& option) const;
private:
    GaussianOption option_;
    mutable FMatrix::MatrixCoef1D matrix_;
};
