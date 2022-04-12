#pragma once

#include "filters.h"
#include <memory>


class FilterCrop : public IFilter {
public:
    struct CropOption {
        size_t width_ = 0;
        size_t height_ = 0;
    };
    void Apply(FMatrix::Matrix2D &table) const override;

    explicit FilterCrop(CropOption& options);
    static std::unique_ptr<FilterCrop> Create(CropOption options);

private:
    CropOption options_;
};
