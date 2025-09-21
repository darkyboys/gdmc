/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Check out the README.md for more information about this project
 * This file is the main source file for this entire project
*/

// Headers
// StdCxx17 libs
#include <chrono>
#include <csignal>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <signal.h>
#include   <vector>
#include   <thread>

// Local libs
#include <HTMLUI/HTMLUI.h>
#include <casci/src/casciv2.hh>
#include <linuxtools/linuxtools.hh>
#include <ulib/ulib.hh>

// Ui lib
#include <ui/ui.hh>

std::string path = linuxtools::get_home_directory() + "/.config/gdmc/";

void exec_backend(std::string msg, HTMLUI& Window){
    std::string dev = msg.substr(0, msg.find(":"));
    std::string event = msg.substr(msg.find(":")+1);
    std::cout << "Event: "<<event<<"\n";
    if (dev == "dci"){
        execl (std::string (path + "dci/dci").c_str(), "dci", "-d", event.c_str(), "-c", "9", (char*)nullptr);
        std::cout << ("Error 'system for f1 failed!'\n");
        std::exit ( 3 );
    }
    else if (dev == "pvpgodmouse"){
        execl (std::string (path + "pvpgodmouse/pvpgodmouse").c_str(),"pvpgod_mouse", event.c_str(), (char*)nullptr);
        std::cout << ("Error 'system for f2 failed!'\n");
        std::exit ( 3 );
    }
}

int main(){

    std::ifstream ifile_dci_backend (path + "dci/dci");
    std::ifstream ifile_pvp_backend (path + "pvpgodmouse");
    if (!ifile_dci_backend.is_open()){
        HTMLUI Installer ("Installing DCI-D backend!", 700, 500);
        Installer.loadHTML(CASCIV2(installer_str).decode("0") + "<script>let ins = new XPDownload('Downloading DCI-D...');\nins.setProgress(0);setTimeout (()=>{window.nativeBridge.invoke ('install', 'null')}, 500);</script>");
        Installer.registerFunction("install", [&Installer](std::string msg){
            std::system (std::string("mkdir -p " + path + "/dci 2>/dev/null").c_str());
            Installer.executeJS ("ins.setWindowTitle('Downloading DCI-D');\nins.setProgress(10);");
            std::system (std::string("git clone https://github.com/darkyboys/double-clicker-injector.git " + path + "dci").c_str());
            Installer.executeJS ("ins.setWindowTitle('Compiling DCI-D');\nins.setProgress(50);");
            std::system (std::string("cd " + path + "dci && g++ x11.cc -o " + path + "dci/dci -std=c++14 -lpthread").c_str());
            Installer.executeJS ("ins.setWindowTitle('Installed DCI-D! Please close this window');\nins.setProgress(100);");
        });
        Installer.run();
    }
    if (!ifile_pvp_backend.is_open()){
        HTMLUI Installer ("Installing PvPGod Mouse backend!", 700, 500);
        Installer.loadHTML(CASCIV2(installer_str).decode("0") + "<script>let ins = new XPDownload('Downloading PvPGod Mouse...');\nins.setProgress(0);setTimeout (()=>{window.nativeBridge.invoke ('install', 'null')}, 500);</script>");
        Installer.registerFunction("install", [&Installer](std::string msg){
            std::system (std::string("mkdir -p " + path + "/pvpgodmouse 2>/dev/null").c_str());
            Installer.executeJS ("ins.setWindowTitle('Downloading DCI-D');\nins.setProgress(10);");
            std::system (std::string("git clone https://github.com/darkyboys/pvpgod_mouse " + path + "pvpgodmouse").c_str());
            Installer.executeJS ("ins.setWindowTitle('Compiling PvPGod Mouse');\nins.setProgress(50);");
            std::system (std::string("cd " + path + "pvpgodmouse && g++ pvpgod_mouse.cpp -o " + path + "pvpgodmouse/pvpgodmouse").c_str());
            Installer.executeJS ("ins.setWindowTitle('Installed PvPGod Mouse! Please close this window');\nins.setProgress(100);");
        });
        Installer.run();
    }


    pid_t f1;
    pid_t f2;
    std::string instance = "2";

    std::vector <std::vector<std::string>> devices = ulib::list_input_devices();

    HTMLUI Window ("GDMC - Goblin's Demonic Mouse Controler", 700, 600);
    Window.loadHTML (CASCIV2(ui_str).decode("0")); // load the UI

    for (std::vector <std::string> dev : devices){
        Window.executeJS ("addDevice('" + dev[0] + "', '" + dev[1] + "')");
    }

    Window.registerFunction ("apply", [&Window, &f1, &f2, &instance](std::string msg){
        f1 = fork();
        if (f1 == 0){
            exec_backend(msg, Window);
        }
        else if (f1 < 0){
            std::cout << "Error 'Fork for f1 failed!'\n";
        }

        if (instance.find("2") != std::string::npos){
            f2 = fork();
            if (f2 == 0){
                exec_backend(msg, Window);
            }
            else if (f1 < 0){
                std::cout << "Error 'Fork for f1 failed!'\n";
            }
        }
    });

    Window.registerFunction("stop", [&Window, &f1, &f2](std::string msg){
        if(f1 > 0){
            kill(f1, SIGKILL);
        }
        if(f2 > 0){
            kill(f2, SIGKILL);
        }
    });

    Window.registerFunction("instance", [&instance](std::string msg){
        instance = msg;
    });

    Window.run();

    if(f1 > 0){
        kill(f1, SIGKILL);
    }
    if(f2 > 0){
        kill(f2, SIGKILL);
    }
}