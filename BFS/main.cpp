#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

class CPublicTransport{
public:
    bool read (const std::string &);
private:
    bool readOneFile(const std::string &);
};

bool CPublicTransport::read(const std::string & path) {
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        if(entry.is_regular_file()){
            if(!readOneFile(entry.path()))
                return false;
        }
    }

    return true;
}

bool CPublicTransport::readOneFile(const std::string & path) {
    std::ifstream ifs ( path );
    if(!ifs)
        return false;

    std::string stop;
    std::map<std::string, std::pair<std::string,std::string>> stops;
    while(getline(ifs, stop)){
        std::cout << stop << std::endl;
    }

    return true;
}

int main() {
    CPublicTransport a;

    if(!a.read("/home/fitslave/code/CPP-REPO/BFS/lines"))
        std::cout << "Error opening file" << std::endl;

    return 0;
}
