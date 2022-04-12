//
// Created by Геннадий Марьин on 3/5/22.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>


struct BMPHeader {
    uint16_t id = 0;
    uint32_t size = 0;
    uint32_t unused = 0;
    uint32_t offset = 0;
} __attribute__((packed));

struct DIBHeader {
    uint32_t size = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    uint16_t colorPlanes = 0;
    uint16_t bitsPerPixel = 0;
    uint32_t compression = 0;
    uint32_t imageSize = 0;
    uint32_t horizontalResolution = 0;
    uint32_t verticalResolution = 0;
    uint32_t numberOfColors = 0;
    uint32_t numberOfImportantColors = 0;
} __attribute__((packed));

struct Color {
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color() = default;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

class ColorF{
public:
    explicit ColorF(float r = 0, float g = 0, float b = 0);
    explicit ColorF(const Color& color);
    explicit operator Color() const;
public:
    float r;
    float g;
    float b;
};

class ImageBMP {
public:
    explicit ImageBMP(const std::string &path);
    void Export(const std::string &path);
    void Read();
public:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    std::vector<std::vector<ColorF>> pixels_;
public:
    struct ImageConsts{
        const int COLOR_CHANNELS = 3;
        const int MAX_PADDING = 4;
        long PADDING_AMOUNT_;
    };
    ImageConsts consts;
private:
    std::string_view path_;
    static std::vector<uint8_t> uintToByte(size_t number, size_t bytes);
    static bool checkIfCorrect(const std::vector<uint8_t> &check, const std::vector<uint8_t> &correct);
};
