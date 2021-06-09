#include <iostream>
#include <list>
#include "tms.hpp"
#include "toLower.hpp"
#include "tmsFilter.hpp"
#include "tmsCaesar.hpp"

std::string GetStringFromFile(const std::string& _fileName) ;
static std::string words[1];

int main(int argc, char* argv[]) {
    std::vector<std::string> wordsToFilter;
    
    bool lower = false, filter = false, caesar = false;
    std::list<std::string> fileNames;
    
    for (int i = 1 ; i < argc ; ++i) {
        std::string input(argv[i]);
        if(input.compare("-lower") == 0) {
            lower = true;
            continue;
        }
        if(input.find("-filter") != std::string::npos) {
            filter = true;
            
            std::string delimiter = "=";
            size_t pos = input.find(delimiter);
            std::string token = input.substr(pos + 1, input.length());
            
            wordsToFilter.push_back(token);
            continue;
        }
        if(input.compare("-caesar") == 0) {
            caesar = true;
            continue;
        }
        else {
            fileNames.push_back(argv[i]);
            continue;
        }
    
    }

    for(std::list<std::string>::iterator it = fileNames.begin(); it != fileNames.end() ; ++it) {
        std::string manipulated = GetStringFromFile(*it);
        if(lower) {
            experis::ToLower t;
            manipulated = t.Manipulate(manipulated);
        }
        if(filter) {
            experis::TmsFilter t(wordsToFilter);
            manipulated = t.Manipulate(manipulated);
        }
        if(caesar) {
            experis::TmsCaesar t(13);
            manipulated = t.Manipulate(manipulated);
        }
        std::cout << manipulated << std::endl;
    }

    if(fileNames.size() == 0) {
        std::string str;
        std::getline(std::cin, str);
        if(lower) {
            experis::ToLower t;
            str = t.Manipulate(str);
        }
        if(filter) {
            experis::TmsFilter t(wordsToFilter);
            str = t.Manipulate(str);
        }
        std::cout << str << std::endl;
    }

    return 0;
}

std::string GetStringFromFile(const std::string& _fileName) {
    std::fstream file(_fileName.c_str());
    if (!file.good()) {
        throw(std::invalid_argument("invalid filename"));
    }
    std::string manipulated;
    while (!file.eof()) {
        std::string line;
        std::getline(file, line);
        manipulated += line + "\n";
    }
    file.close();
    return manipulated;
}
