#include <vector>
#include <iostream>

#include "parser.h"
#include "image.h"
#include "convertor.h"
#include "exception.h"

#include "filters/filters.h"
#include "filters/crop.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include "filters/edgeDetection.h"
#include "filters/gaussionBlur.h"
#include "filters/sobel.h"
#include "filters/sketch.h"


int main(int argc, char *argv[]) {
    std::string input_file;
    std::string output_file;

    Parser parser;
    parser.AddPositionArg(ToParser::InputToPositionArg(&input_file));
    parser.AddPositionArg(ToParser::OutputToPositionArg(&output_file));

    FilterCrop::CropOption crop_options;
    FilterEdgeDetection::EdgeDetectionOption edge_options;
    FilterGaussianBlur::GaussianOption gaussian_coef;
    FilterSketch::SketchOptions sketch_options;

    parser.AddKeyArg("-crop", ToParser::CropToParser(&crop_options));
    parser.AddKeyArg("-gs");
    parser.AddKeyArg("-neg");
    parser.AddKeyArg("-sharp");
    parser.AddKeyArg("-edge", ToParser::EdgeDetectionToParser(&edge_options));
    parser.AddKeyArg("-blur", ToParser::GaussianBlurToParser(&gaussian_coef));
    parser.AddKeyArg("-sobel");
    parser.AddKeyArg("-sketch", ToParser::SketchToParser(&sketch_options));

    try{
        parser.Parse(argc, argv);
    } catch(const Exception& e){
        std::cout << e.what() << std::endl;
        parser.Help();
        return 0;
    } catch(...){
        std::cout << "unexpected exception" << std::endl;
        return 0;
    }

    IFilterFactory factory;
    factory.Register("-crop", std::bind(FilterCrop::Create, crop_options));
    factory.Register("-gs", FilterGrayscale::Create);
    factory.Register("-neg", FilterNegative::Create);
    factory.Register("-sharp", FilterSharpening::Create);
    factory.Register("-edge", std::bind(FilterEdgeDetection::Create, edge_options));
    factory.Register("-blur", std::bind(FilterGaussianBlur::Create, gaussian_coef));
    factory.Register("-sobel", FilterSobel::Create);
    factory.Register("-sketch", std::bind(FilterSketch::Create, sketch_options));

    ImageBMP image(input_file);
    try{
        image.Read();
    } catch(const Exception& e){
        std::cout << e.what() << std::endl;
        return 0;
    } catch(...){
        std::cout << "invalid path" << std::endl;
        return 0;
    }

    for (const auto &value: parser.GetFound()) {
        factory.Create(value)->Apply(image.pixels_);
    }

    image.Export(output_file);
    return 0;
}
