#include <iostream>
#include <fstream>
#include <casci/src/casciv2.hh>
#include <string>

int main (){
    std::ifstream ifile_html ("src/ui/html/index.html");
    std::ifstream ifile_installer ("src/ui/html/installer.html");
    if (!ifile_html.is_open()){
        std::cout << "Error!!! the file src/ui/html/index.html was not found!\n";
        return 3;
    }
    if (!ifile_installer.is_open()){
        std::cout << "Error!!! the file src/ui/html/installer.html was not found!\n";
        return 3;
    }
    std::string temp, content;
    while (std::getline(ifile_html, temp)) content+=temp + '\n';

    std::string encoded_string = CASCIV2 (content).encode("0");
    std::ofstream ofile_hh("src/ui/ui.hh");
    ofile_hh<<"std::string ui_str = R\"("<<encoded_string<<")\";";
    std::cout << "UI Write was performed!!\n";

    content.clear();
    while (std::getline(ifile_installer, temp)) content+=temp + '\n';
    encoded_string = CASCIV2 (content).encode("0");
    ofile_hh<<"std::string installer_str = R\"("<<encoded_string<<")\";";
}