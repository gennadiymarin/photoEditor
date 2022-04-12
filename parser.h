//
// Created by Геннадий Марьин on 3/6/22.
//

#pragma once

#include <variant>
#include <string>
#include <unordered_map>
#include <string_view>
#include <vector>
#include <iostream>


class Parser {
public:
    struct Argument {
        Argument(const std::string &name, size_t *value);
        Argument(const std::string &name, float *value);
        Argument(const std::string &name, std::string *value);
        Argument(const std::string &name, long *value);
        std::string name_;
        std::variant<size_t *, float *, std::string *, long *> value_;
    };
    void AddKeyArg(std::string_view name, const std::vector<Argument> &arguments = {});
    void AddPositionArg(const Argument &argument);
    std::vector<std::string_view> GetFound();
    void Parse(int argc, char *argv[]);
    void Help() const;

private:
    std::vector<Argument> positionArgs_;
    std::unordered_map<std::string_view, std::vector<Argument>> toFind_;
    std::vector<std::string_view> wasFound_;

private:
    class Assign {
    public:
        explicit Assign(char* value_from);
        void operator()(std::string *value_to) const;
        void operator()(size_t *value_to) const;
        void operator()(float *value_to) const;
        void operator()(long *value_to) const;

    private:
        char* value_from_ = nullptr;
    };
};
