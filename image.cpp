//
// Created by Геннадий Марьин on 3/5/22.
//

#include "image.h"
#include "exception.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <tuple>


const std::vector<uint8_t> BMP_HEADER_ID = {'B', 'M'};
const std::vector<uint8_t> DIB_HEADER_SIZE = {0x28, 0x00, 0x00, 0x00};
const std::vector<uint8_t> DIB_HEADER_COLOR_PLANES = {0x01, 0x00};
const std::vector<uint8_t> DIB_HEADER_BPP = {0x18, 0x00};
const std::vector<uint8_t> DIB_HEADER_COMPRESSION = {0x00, 0x00, 0x00, 0x00};


Color::Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

ColorF::ColorF(const Color& color) {
    r = color.r / 255.0;
    g = color.g / 255.0;
    b = color.b / 255.0;
}

ColorF::ColorF(float r, float g, float b) : r(r), g(g), b(b) {}

ColorF::operator Color() const {
    return {uint8_t(255 * std::min(float(1) ,r)),uint8_t(255 * std::min(float(1) ,g)),uint8_t(255 * std::min(float(1) ,b))};
}

ImageBMP::ImageBMP(const std::string &path) : path_(path) {}

void ImageBMP::Read() {
    std::ifstream stream(path_, std::ios::binary);
    stream.read((char *) &bmp_header_, sizeof(bmp_header_));
    stream.read((char *) &dib_header_, sizeof(dib_header_));

    if (!checkIfCorrect(uintToByte(bmp_header_.id, 2), BMP_HEADER_ID)){
        throw Exception("Invalid bmp_header_id");
    }
    if (!checkIfCorrect(uintToByte(dib_header_.size, 4), DIB_HEADER_SIZE)){
        throw Exception("Invalid dib_header_size");
    }
    if (!checkIfCorrect(uintToByte(dib_header_.colorPlanes, 2), DIB_HEADER_COLOR_PLANES)){
        throw Exception("Invalid  dib_header_color_planes");
    }
    if (!checkIfCorrect(uintToByte(dib_header_.bitsPerPixel, 2), DIB_HEADER_BPP)){
        throw Exception("Invalid dib_header_bpp");
    }
    if (!checkIfCorrect(uintToByte(dib_header_.compression, 4), DIB_HEADER_COMPRESSION)){
        throw Exception("Invalid dib_header_compression");
    }

    consts.PADDING_AMOUNT_ = (consts.MAX_PADDING - ((dib_header_.width * consts.COLOR_CHANNELS) % consts.MAX_PADDING)) %
                             consts.MAX_PADDING;
    pixels_.reserve(dib_header_.height);

    for (size_t y = 0; y < dib_header_.height; ++y) {
        std::vector<ColorF> cur_line;
        cur_line.reserve(dib_header_.width);
        for (size_t x = 0; x < dib_header_.width; ++x) {
            Color color_cur;
            stream.read((char *) &color_cur.b, sizeof(color_cur.b));
            stream.read((char *) &color_cur.g, sizeof(color_cur.g));
            stream.read((char *) &color_cur.r, sizeof(color_cur.r));
            cur_line.push_back(ColorF(color_cur));
        }
        stream.ignore(consts.PADDING_AMOUNT_);
        pixels_.push_back(cur_line);
    }
}

void ImageBMP::Export(const std::string &path) {
    dib_header_.width = pixels_.at(0).size();
    dib_header_.height = pixels_.size();
    dib_header_.imageSize = (dib_header_.height + dib_header_.width) * consts.COLOR_CHANNELS
                            + consts.PADDING_AMOUNT_ * dib_header_.height;
    std::ofstream stream(path, std::ios::out | std::ios::binary);
    stream.write((char *) &bmp_header_, sizeof(bmp_header_));
    stream.write((char *) &dib_header_, sizeof(dib_header_));
    for (size_t y = 0; y < dib_header_.height; ++y) {
        for (size_t x = 0; x < dib_header_.width; ++x) {
            auto color_cur = Color(pixels_[y][x]);
            stream.write((char *) &color_cur.b, sizeof(color_cur.b));
            stream.write((char *) &color_cur.g, sizeof(color_cur.g));
            stream.write((char *) &color_cur.r, sizeof(color_cur.r));
        }
        int8_t padding = 0;
        for (size_t i = 0; i < consts.PADDING_AMOUNT_; ++i) {
            stream.write((char *) &padding, sizeof(padding));
        }
    }
}

std::vector<uint8_t> ImageBMP::uintToByte(size_t number, size_t bytes) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < bytes; ++i) {
        result.push_back((number >> 8 * i) & 0xFF);
    }
    return result;
}

bool ImageBMP::checkIfCorrect(const std::vector<uint8_t> &check, const std::vector<uint8_t> &correct) {
    return std::tie(check) == std::tie(correct);
}
