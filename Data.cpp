//
// Created by Berkay on 5/28/2022.
//
#include "Data.hpp"
auto Data::change_username(std::string usr) -> void {
    _username = std::move(usr);
}
auto Data::change_password(std::string pswd) -> void {
    _password = std::move(pswd);
}
auto Data::change_url(std::string url) -> void {
    _url = std::move(url);
}
auto Data::add_cat(std::string& cat) -> void {
    if(std::find(_cat.begin(), _cat.end(), cat) == _cat.end())
        _cat.push_back(cat);
}
auto Data::remove_cat(std::string& cat) -> void {
    auto it=std::find(_cat.begin(),_cat.end(),cat);
    if(it!=_cat.end())
        _cat.erase(it);
}
auto Data::clear_cat() {
    _cat.clear();
}