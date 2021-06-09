 #include "tms.hpp"

namespace experis {

typedef std::fstream Fstream;

String Tms::ManipulateFromFile(const String& _fileName) {
    Fstream file(_fileName.c_str());
    if (!file.good()) {
        throw(std::invalid_argument("invalid filename"));
    }
    String manipul;
    while (!file.eof()) {
        String line;
        std::getline(file, line);
        manipul += Manipulate(line) + "\n";
    }
    file.close();
    return manipul;
}

}//experis
