//
// Created by Геннадий Марьин on 3/7/22.
//

#pragma once

#include <vector>
#include <string>

#include "filters/filters.h"
#include "filters/crop.h"
#include "filters/sketch.h"
#include "filters/edgeDetection.h"
#include "filters/gaussionBlur.h"

#include "parser.h"


namespace ToParser{
    std::vector<Parser::Argument> CropToParser(FilterCrop::CropOption* values);
    Parser::Argument InputToPositionArg(std::string* str);
    Parser::Argument OutputToPositionArg(std::string* str);
    std::vector<Parser::Argument> GaussianBlurToParser(FilterGaussianBlur::GaussianOption* option);
    std::vector<Parser::Argument> EdgeDetectionToParser(FilterEdgeDetection::EdgeDetectionOption* values);
    std::vector<Parser::Argument> SketchToParser(FilterSketch::SketchOptions* options);
}
