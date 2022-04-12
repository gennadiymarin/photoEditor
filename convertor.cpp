//
// Created by Геннадий Марьин on 3/7/22.
//

#include "convertor.h"
#include <vector>

std::vector<Parser::Argument> ToParser::CropToParser(FilterCrop::CropOption* values) {
    std::vector<Parser::Argument> result;
    result.reserve(2);
    result.push_back(Parser::Argument("width", &values->width_));
    result.push_back(Parser::Argument("height", &values->height_));
    return result;
}

Parser::Argument ToParser::InputToPositionArg(std::string* str) {
    return  Parser::Argument("input_file", str);
}

Parser::Argument ToParser::OutputToPositionArg(std::string *str) {
    return Parser::Argument("output_file", str);
}

std::vector<Parser::Argument> ToParser::GaussianBlurToParser(FilterGaussianBlur::GaussianOption* option) {
    return  std::vector<Parser::Argument> {Parser::Argument("sigma", &option->coef_)};
}

std::vector<Parser::Argument> ToParser::EdgeDetectionToParser(FilterEdgeDetection::EdgeDetectionOption* values) {
    return std::vector<Parser::Argument> {Parser::Argument("threshold", &values->threshold_)};
}

std::vector<Parser::Argument> ToParser::SketchToParser(FilterSketch::SketchOptions *options) {
    std::vector<Parser::Argument> result;
    result.reserve(4);
    result.push_back(Parser::Argument("amount_of_lines(blur)", &options->blur_));
    result.push_back(Parser::Argument("thickness_of_lines", &options->coef_));
    result.push_back(Parser::Argument("moveX", &options->moveX_));
    result.push_back(Parser::Argument("moveY", &options->moveY_));
    return result;
}
