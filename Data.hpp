//
// Created by Berkay on 5/28/2022.
//
#pragma once
#ifndef BERKAY_BAYAR_PASSWORD_MANAGER_S25786_DATA_HPP
#define BERKAY_BAYAR_PASSWORD_MANAGER_S25786_DATA_HPP
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

class Data {
protected:
    std::string _username, _password, _url;
    std::vector<std::string> _cat;
public:
    const std::string & username() {return _username;}
    const std::string & password() {return _password;}
    const std::string & url() {return _url;}
    std::vector<std::string> & cat() {return _cat;}
    Data(std::string usr, std::string pswd, std::string url): _username(std::move(usr)), _password(std::move(pswd)), _url(std::move(url)) {}
    auto add_cat (std::string& cat) -> void;
    auto remove_cat (std::string& cat) -> void;
    auto change_username (std::string usr) -> void;
    auto change_password (std::string pswd) -> void;
    auto change_url (std::string url) -> void;
    auto clear_cat();
};


#endif //BERKAY_BAYAR_PASSWORD_MANAGER_S25786_DATA_HPP
