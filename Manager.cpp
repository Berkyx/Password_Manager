//
// Created by berka on 13.05.2022.
//
#include "Manager.hpp"
#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <map>
#include "Lock.hpp"
#include "Data.hpp"
std::string art = "\n"
                  "______________________________________________________________________________________________________________________\n"
                  "    ____                       _      _                               _   _                                           \n"
                  "    /    )                     |  |  /                       /        /  /|                                           \n"
                  "---/____/-----__----__----__---|-/|-/------__----)__-----__-/--------/| /-|-----__-----__-----__-----__-----__----)__-\n"
                  "  /         /   )  (_ `  (_ `  |/ |/     /   )  /   )  /   /        / |/  |   /   )  /   )  /   )  /   )  /___)  /   )\n"
                  "_/_________(___(__(__)__(__)___/__|_____(___/__/______(___/________/__/___|__(___(__/___/__(___(__(___/__(___ __/_____\n"
                  "                                                                                                     /                \n"
                  "                                                                                                 (_ /                 ";
Manager::Manager() {
    system("title Password Manager");
    passwds.open(path);
    init();
    passwds.close();
}
auto Manager::init() -> void {
    hndl.clear();
    std::string user, password, url, cat, aux;
    int catsx, i;
    while (std::getline(passwds, user)) {
        if (user == "")
            break;
        passwds >> std::ws;
        std::getline(passwds, password);
        passwds >> std::ws;
        std::getline(passwds, url);
        passwds >> std::ws;
        std::getline(passwds, cat);
        passwds >> std::ws;
        hndl.add_data(Data(s25786::Lock::decrypt(user), s25786::Lock::decrypt(password), s25786::Lock::decrypt(url)));
        catsx = i = 0;
        while (i < cat.size() && std::isdigit(cat[i]))
            catsx = catsx*10+cat[i++]-'0';
        i++;
        for(;i<cat.size(); i++)
            if(cat[i] == ' ')
                hndl.datas().back().add_cat(aux), aux.clear();
        else
            aux.push_back(cat[i]);
        aux.clear();
    }
}
auto Manager::refresh() -> void {
    std::ostringstream oss;
    for(int i = 0; i < hndl.datas().size(); i++) {
        oss << s25786::Lock::encrypt(hndl.datas()[i].username()) << '\n' << s25786::Lock::encrypt(hndl.datas()[i].password()) << '\n' << s25786::Lock::encrypt(hndl.datas()[i].url()) << '\n';
        oss << hndl.datas()[i].cat().size();
        if(hndl.datas()[i].cat().size())
            oss << " ";
        for(int j = 0; j < hndl.datas()[i].cat().size(); j++)
            oss << hndl.datas()[i].cat()[j] << " ";
        oss << '\n';
    }
    hndl.clear();
    new_passwds.open(path);
    new_passwds << oss.str();
    new_passwds.flush();
    new_passwds.close();
    passwds.open(path);
    init();
    passwds.close();
}
auto Manager::Display() -> void{
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout
        << "- help \n"
        << "- add entry \n"
        << "- remove entry \n"
        << "- change entry \n"
        << "- all entries \n"
        << "- sort by cat \n"
        << "- view by cat \n"
        << "- change path \n"
        << "- view by pass \n"
        << "- exit \n" << '\n';
}
auto Manager::start() -> void {
    Display();
    prompt = "Manager: ";
    while(true) {
        char buf[1024];
        std::cout << prompt;
        std::flush(std::cout);
        std::cin.getline(buf, sizeof(buf));
        execute(buf);
        std::cout << '\n';
    }
}
static auto is_command(const std::string& cmd, const std::string& token) -> bool {
    return 0 == cmd.compare(0, token.length(), token);
}
static auto help_text() -> void {
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout
        << "- 'add entry': Adds a new password to your list.  \n"
        << "- 'remove entry': Removes a specified password of your list. \n"
        << "- 'change entry': Changes a specified password of your list. \n"
        << "- 'all entries': Lists all of your passwords. \n"
        << "- 'sort by cat': Sorts your passwords by category. \n"
        << "- 'view by cat': Lists your passwords by a specified category. \n"
        << "- 'exit' or 'quit': Saves and exits from the program. \n";
}
auto Manager::add_entry() -> void {
    std::string usr, pswd, url, cat;
    char ch;
    int cats = 0;
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Username: ";
    std::getline(std::cin, usr);
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Password: ";
    do {
        ch = _getch();
        pswd.push_back(ch);
        if (ch == 8)
            pswd.erase(pswd.begin() + pswd.size() - 1);
    } while (ch != VK_RETURN);
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Url: ";
    std::getline(std::cin, url);
    if(!hndl.add_data(Data(usr,pswd,url)))
        add_entry();
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Enter a number of categories: ";
    std::cin >> cats;
    std::cin.ignore();
    for (int i = 0; i < cats; i++) {
        std::cout << "\nCat #" << i << " : ";
        std::getline(std::cin, cat);
        hndl.datas().back().add_cat(cat);
    }
    refresh();
}
auto Manager::remove_entry() -> void {
    std::string url, user;
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Url: ";
    std::getline(std::cin, url);
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Username: ";
    std::getline(std::cin, user);
    hndl.remove_data(Data(user, "", url));
    refresh();
}
auto Manager::change_entry() -> void {
    std::string url, user;
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Url: ";
    std::getline(std::cin, url);
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    std::cout << "Username: ";
    std::getline(std::cin, user);
    hndl.remove_data(Data(user, "", url));
    add_entry();
}
auto Manager::all_entries() -> void {
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    for(int i = 0; i < hndl.datas().size(); i++) {
        std::cout << "Entry # " << i+1 << '\n';
        std::cout << "\tUsername: " << hndl.datas()[i].username() << '\n' << "\tPassword: " << hndl.datas()[i].password();
        std::cout << '\n' << "\tUrl: " << hndl.datas()[i].url() << '\n';
    }
    std::cout << "Press any keys to continue";
    _getch();
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    Display();
}
auto Manager::sort_by_cat() -> void {
    system("cls");
    std::cout<<std::string(50,' ')<<art<<std::string(3,'\n');
    std::map<std::string, std::vector<Data> >map;
    for(int i = 0; i < hndl.datas().size(); i++) {
        if(hndl.datas()[i].cat().size() == 0)
            map[""].push_back(hndl.datas()[i]);
        for(int j = 0; j < hndl.datas()[i].cat().size(); j++)
            map[hndl.datas()[i].cat()[j]].push_back(hndl.datas()[i]);
    }
    for(auto& it:map) {
        std::cout << '\n' << "Category: " << it.first << '\n';
        for(auto aux:it.second) {
            std::cout << "\tUsername: " << aux.username() << '\n';
            std::cout << "\tPassword: " << aux.password() << '\n';
            std::cout << "\tUrl: " << aux.url() << '\n';
        }
    }
    std::cout << "Press any keys to continue";
    _getch();
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    Display();
}
auto Manager::view_by_cat() -> void {
    system("cls");
    std::string cat;
    std::cout<<std::string(50,' ')<<art<<std::string(3,'\n');
    std::cout << "Enter category name: ";
    std::getline(std::cin, cat);
    if(cat=="") {
        system("cls");
        all_entries();
    }
    std::cout << "Category: " << cat << '\n' << '\n';
    for(auto it:hndl.datas())
        for(auto& it2:it.cat())
            if(it2==cat) {
                std::cout << "\tUsername: " << it.username() << '\n';
                std::cout << "\tPassword: " << it.password() << '\n';
                std::cout << "\tUrl: " << it.url() << '\n';
            }
    std::cout << "Press any keys to continue";
    _getch();
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    Display();
}
auto Manager::change_path() -> void {
    system("cls");
    std::string new_path;
    std::cout<<std::string(50,' ')<<art<<std::string(3,'\n');
    std:: cout << "Your current path is: " << path << '\n';
    std::cout << "Enter a new absoloute path: ";
    std::getline(std::cin, new_path);
    if(new_path=="") {
        system("cls");
        std::cout << "No input." << '\n';
        std::cout << "Press any keys to continue";
        _getch();
        system("cls");
        std::cout << std::string(50, ' ') << art << std::string(3, '\n');
        Display();
    }
    path = new_path;

    std::cout << "Your path has changed." << '\n';
    std::cout << "Press any keys to continue";
    _getch();
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    Display();
}
auto Manager::view_by_pass() -> void {
    system("cls");
    std::string pass;
    std::cout<<std::string(50,' ')<<art<<std::string(3,'\n');
    std::cout << "Enter a password: ";
    std::getline(std::cin, pass);
    if(pass=="") {
        system("cls");
        all_entries();
    }
    std::cout << "Password: " << pass << '\n' << '\n';
    for(auto it:hndl.datas())
        for(auto& it2:it.cat())
            if(it2==pass) {
                std::cout << "\tUsername: " << it.username() << '\n';
                std::cout << "\tUrl: " << it.url() << '\n';
            }
    std::cout << "Press any keys to continue";
    _getch();
    system("cls");
    std::cout << std::string(50, ' ') << art << std::string(3, '\n');
    Display();
}
auto Manager::execute(const std::string& cmd) -> void {
    if (cmd.length() == 0) {
        std::cout << "Please provide a command \n";
    } else if (is_command(cmd, "help")) {
        help_text();
    } else if (is_command(cmd, "add entry")) {
        add_entry();
    } else if (is_command(cmd, "remove entry")) {
        remove_entry();
    } else if (is_command(cmd, "change entry")) {
        change_entry();
    } else if (is_command(cmd, "all entries")) {
        all_entries();
    } else if (is_command(cmd, "sort by cat")) {
        sort_by_cat();
    } else if (is_command(cmd, "view by cat")) {
        view_by_cat();
    } else if (is_command(cmd, "change path")) {
        change_path();
    } else if (is_command(cmd, "view by pass")) {
        view_by_pass();
    } else if (is_command(cmd, "quit") || is_command(cmd, "exit")) {
        refresh();
        exit(0);
    }
}
auto main() -> int {
    Manager mgr;
    mgr.start();
}