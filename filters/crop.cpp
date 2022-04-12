//
// Created by Геннадий Марьин on 3/27/22.
//

#include "crop.h"
#include <memory>


void FilterCrop::Apply(FMatrix::Matrix2D &table) const {
    if (options_.width_ >= table.at(0).size() && options_.height_ >= table.size()) {
        return;
    }
    if (options_.height_ < table.size()) {
        std::reverse(table.begin(), table.end());
        table.resize(options_.height_);
        std::reverse(table.begin(), table.end());
        table.shrink_to_fit();
    }
    if (options_.width_ < table.at(0).size()) {
        for (auto &line: table) {
            line.resize(options_.width_);
            line.shrink_to_fit();
        }
    }
}

FilterCrop::FilterCrop(CropOption &options) : options_(options){}

std::unique_ptr<FilterCrop> FilterCrop::Create(CropOption options) {
    return std::make_unique<FilterCrop>(options);
}
