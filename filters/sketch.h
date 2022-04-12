//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include "filters.h"
#include <memory>


class FilterSketch : public IFilter{
public:
    struct SketchOptions {
        float blur_ = 2;
        float coef_ = 0.3;
        long moveX_ = 0;
        long moveY_ = 0;
    };
    void Apply(FMatrix::Matrix2D &table) const override;

    FilterSketch(const SketchOptions& options);
    static std::unique_ptr<FilterSketch> Create(const SketchOptions& options);

private:
    SketchOptions options_;
};
