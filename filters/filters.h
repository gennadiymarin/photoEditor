//
// Created by Геннадий Марьин on 3/6/22.
//

#pragma once

#include "../image.h"

#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>

namespace FMatrix {
    enum Dim {
        X,
        Y
    };
    struct Pixel {
        size_t x = 0;
        size_t y = 0;
    };
    using MatrixCoef1D = std::vector<float>;
    using MatrixCoef2D = std::vector<std::vector<float>>;
    using Matrix2D = std::vector<std::vector<ColorF>>;
    using Matrix1D = std::vector<ColorF>;

    ColorF ApplyMatrix1D(Pixel pixel, Dim dim, const MatrixCoef1D &matrix, const Matrix2D &table);
    ColorF ApplyMatrix2D(Pixel pixel, const MatrixCoef2D &matrix, const Matrix2D &table);
}

class IFilter {
public:
    virtual void Apply(FMatrix::Matrix2D &table) const = 0;
    virtual ~IFilter() = default;
};

class IFilterFactory {
public:
    void Register(std::string_view name, std::function<std::unique_ptr<IFilter>()> creator) {
        name_to_func[name] = creator;
    }
    std::unique_ptr<IFilter> Create(std::string_view name) {
        return name_to_func[name]();
    }
private:
    std::unordered_map<std::string_view, std::function<std::unique_ptr<IFilter>()> > name_to_func;
};
