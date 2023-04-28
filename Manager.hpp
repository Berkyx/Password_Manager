//
// Created by berka on 13.05.2022.
//
#pragma once
#ifndef BERKAY_BAYAR_PASSWORD_MANAGER_S25786_MANAGER_HPP
#define BERKAY_BAYAR_PASSWORD_MANAGER_S25786_MANAGER_HPP
#include <string>
#include <fstream>
#include <sstream>
#include "Handler.hpp"
    class Manager {
    protected:
        std::string path = "Manager.berkay";
        Handler hndl;
        std::ofstream new_passwds;
        std::ifstream passwds;
        auto init() -> void;
    public:
        [[maybe_unused]] Handler & handler() {return hndl;}
        Manager();
        auto start() -> void;
        auto execute(const std::string& cmd) -> void;
        auto refresh() -> void;
        static auto Display() -> void;
        auto add_entry() -> void;
        auto remove_entry() -> void;
        auto change_entry() -> void;
        auto all_entries() -> void;
        auto sort_by_cat() -> void;
        auto view_by_cat() -> void;
        auto change_path() -> void;
        auto view_by_pass() -> void;
    private:
        std::string prompt;
    };


#endif //BERKAY_BAYAR_PASSWORD_MANAGER_S25786_MANAGER_HPP
