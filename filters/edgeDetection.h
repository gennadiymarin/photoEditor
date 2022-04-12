//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include "filters.h"
#include <memory>


class FilterEdgeDetection : public IFilter {
public:
    struct EdgeDetectionOption{
        float threshold_ = 0.5;
    };
    void Apply(FMatrix::Matrix2D &table) const override;

    explicit FilterEdgeDetection(EdgeDetectionOption option);
    static std::unique_ptr<FilterEdgeDetection> Create(EdgeDetectionOption option);

private:
    EdgeDetectionOption option_;
    static const FMatrix::MatrixCoef2D matrix_;
};
