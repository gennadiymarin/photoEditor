//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include "filters.h"
#include <memory>


class FilterSobel : public IFilter {
public:
    void Apply(FMatrix::Matrix2D &table) const override;
    static std::unique_ptr<FilterSobel> Create();

private:
    static const FMatrix::MatrixCoef2D matrixX_;
    static const FMatrix::MatrixCoef2D matrixY_;
};
