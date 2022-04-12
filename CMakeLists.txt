set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wpedantic -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -fsanitize=address,undefined -fno-sanitize-recover=all")

#-fsanitize=address,undefined -fno-sanitize-recover=all

add_executable(image_processor main.cpp image.cpp image.h
        parser.cpp parser.h
        filters/filters.cpp filters/filters.h
        convertor.cpp convertor.h
        filters/crop.cpp filters/crop.h
        filters/grayscale.cpp filters/grayscale.h
        filters/negative.cpp filters/negative.h
        filters/sharpening.cpp filters/sharpening.h
        filters/edgeDetection.cpp filters/edgeDetection.h
        filters/gaussionBlur.cpp filters/gaussionBlur.h
        filters/sobel.cpp filters/sobel.h
        filters/sketch.cpp filters/sketch.h exception.cpp exception.h)
