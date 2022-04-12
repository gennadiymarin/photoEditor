//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include "filters.h"
#include <memory>


class FilterNegative : public IFilter {
public:
    void Apply(FMatrix::Matrix2D &table) const override;
    static std::unique_ptr<FilterNegative> Create();
};
