//
// Created by berka on 14.05.2022.
//
#pragma once
#ifndef BERKAY_BAYAR_PASSWORD_MANAGER_S25786_LOCK_HPP
#define BERKAY_BAYAR_PASSWORD_MANAGER_S25786_LOCK_HPP
#include <string>
namespace s25786 {

    class Lock {
    public:
        static auto encrypt (std::string str) -> std::string;
        static auto decrypt (std::string str) -> std::string;
    };

} // s25786

#endif //BERKAY_BAYAR_PASSWORD_MANAGER_S25786_LOCK_HPP
