//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include "filters.h"
#include <memory>


class FilterGrayscale : public IFilter {
public:
    void Apply(FMatrix::Matrix2D &table) const override;

    static std::unique_ptr<FilterGrayscale> Create();

private:
    struct GrayConsts {
        const float r = 0.299;
        const float g = 0.587;
        const float b = 0.114;
    };
    static GrayConsts consts_;
};
