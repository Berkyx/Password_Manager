//
// Created by Berkay on 5/28/2022.
//
#pragma once
#ifndef BERKAY_BAYAR_PASSWORD_MANAGER_S25786_HANDLER_HPP
#define BERKAY_BAYAR_PASSWORD_MANAGER_S25786_HANDLER_HPP
#include "Data.hpp"
class Handler {
protected:
    std::vector<Data> _data;
public:
    auto add_data(Data) -> int;
    auto clear() {_data.clear();}
    auto remove_data(Data) -> void;
    std::vector<Data> & datas() {return _data;}
};


#endif //BERKAY_BAYAR_PASSWORD_MANAGER_S25786_HANDLER_HPP
