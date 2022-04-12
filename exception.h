//
// Created by Геннадий Марьин on 3/27/22.
//

#pragma once

#include <string>
#include <exception>


class Exception : public std::exception{
public:
    explicit Exception(const std::string& msg);

    ~Exception() throw() override = default;
    const char* what() const throw() override;

private:
    std::string msg_;
};
