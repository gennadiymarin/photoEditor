//
// Created by Геннадий Марьин on 3/27/22.
//

#include "exception.h"
#include <string>


Exception::Exception(const std::string &msg) : msg_(msg) {}

const char *Exception::what() const throw() {
    return msg_.c_str();
}
