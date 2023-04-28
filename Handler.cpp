//
// Created by Berkay on 5/28/2022.
//
#include "Handler.hpp"
auto Handler::add_data(Data data) -> int {
    bool x = true;
    for (int i = 0; i < _data.size(); i++)
        if(_data[i].url() == data.url() && _data[i].username() == data.username()) {
            x = false;
            break;
        }
    if(x)
        _data.push_back(data);
    return x;
}
auto Handler::remove_data(Data data) -> void {
    for (int i = 0; i < _data.size(); i++)
        if(_data[i].url() == data.url() && _data[i].username() == data.username()) {
            _data.erase(_data.begin()+i);
            break;
        }
}
