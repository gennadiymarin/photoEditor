#include "parser.h"
#include "exception.h"

#include <utility>
#include <vector>
#include <string>
#include <variant>


Parser::Argument::Argument(const std::string &name, size_t *value) {
    name_ = name;
    value_ = value;
}

Parser::Argument::Argument(const std::string &name, float *value) : name_(name), value_(value) {}
Parser::Argument::Argument(const std::string &name, std::string *value) : name_(name), value_(value) {}
Parser::Argument::Argument(const std::string &name, long *value) : name_(name), value_(value) {}

void Parser::AddPositionArg(const Argument &argument) {
    positionArgs_.push_back(argument);
}

void Parser::AddKeyArg(std::string_view name, const std::vector<Argument> &arguments) {
    toFind_[name] = arguments;
}

void Parser::Parse(int argc, char *argv[]) {
    if (argc <= positionArgs_.size() + 1) {
        throw Exception("Not enough args");
    }
    for (size_t i = 1; i <= positionArgs_.size(); ++i) {
        std::visit(Assign(argv[i]), positionArgs_[i - 1].value_);
    }
    for (size_t i = positionArgs_.size() + 1; i < argc; ++i) {
        auto it = toFind_.find(argv[i]);
        if (it == toFind_.end()){
            throw Exception("Incorrect name: " + std::string(argv[i]));
        }
        wasFound_.push_back(argv[i]);
        size_t param_required = it->second.size();
        for (size_t j = 0; j < param_required; ++j) {
            std::visit(Assign(argv[i + j + 1]), it->second[j].value_);
        }
        i += param_required;
    }
}

Parser::Assign::Assign(char *value_from) {
    value_from_ = value_from;
}

void Parser::Assign::operator()(float *value_to) const {
    try {
        *value_to = std::stof(std::string(value_from_));
    } catch (...) {
        throw Exception("Incorrect arg type: " + std::string(value_from_));
    }
}

#include <iostream>

void Parser::Assign::operator()(size_t *value_to) const {
    try {
        std::string value_cur = std::string(value_from_);
        if (std::stoi(value_cur) != std::stof(value_cur)){
            throw std::bad_typeid();
        }
        *value_to = size_t(std::stoi(std::string(value_from_)));
    } catch (...) {
        throw Exception("Incorrect arg type: " + std::string(value_from_));
    }
}

void Parser::Assign::operator()(std::string *value_to) const {
    *value_to = std::string(value_from_);
}

void Parser::Assign::operator()(long *value_to) const {
    try {
        *value_to = long(std::stoi(std::string(value_from_)));
    } catch (...) {
        throw Exception("Incorrect arg type: " + std::string(value_from_));
    }
}

std::vector<std::string_view> Parser::GetFound() {
    return wasFound_;
}

void Parser::Help() const {
    std::cout << "parser: ";
    for (const auto &value : positionArgs_) {
        std::cout << "" << value.name_ << " ";
    }
    for (const auto &[name, options] : toFind_) {
        std::cout << "[" << name;
        for (const auto &value : options) {
            std::cout << " " << value.name_ ;
        }
        std::cout << "] ";
    }
}
