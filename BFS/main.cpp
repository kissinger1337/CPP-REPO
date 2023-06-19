#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>
#include <cassert>

/**
 * @brief class representing public transport lines. Contains functions to read from a file and find the shortest path using BFS.
 */
class CPublicTransport{
public:
    bool read (const std::string &);/**< Iterates through all files in one directory. Does not recursively iterate through deeper directories.*/

    std::map<std::pair<std::string, std::string>, std::string>& getAllConnections(); /**< getter used only for testing */
private:
    bool readOneFile(const std::string &);
    //                   from          to           line name
    std::map<std::pair<std::string, std::string>, std::string> m_AllConnections;
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

    std::string lineName;
    //first line of the file should always contain name of the transport line
    getline(ifs, lineName);

    std::string stop;
    std::vector<std::string> stops;
    while(getline(ifs, stop)){
        for(auto other : stops) {
            m_AllConnections.emplace(std::make_pair(stop, other), lineName);
            m_AllConnections.emplace(std::make_pair(other, stop), lineName);
        }
        stops.push_back(stop);
    }

    return true;
}

std::map<std::pair<std::string, std::string>, std::string> & CPublicTransport::getAllConnections() {
    return m_AllConnections;
}

int main() {
    CPublicTransport a;

    if(!a.read("/home/fitslave/code/CPP-REPO/BFS/lines"))
        std::cout << "Error opening file" << std::endl;

    assert((a.getAllConnections().find({"Dejvická", "Depo Hostivař"}))->second == "A");
    assert((a.getAllConnections().find({"Depo Hostivař", "Dejvická"}))->second == "A");
    assert((a.getAllConnections().find({"Jinonice", "Českomoravská"}))->second == "B");
    assert((a.getAllConnections().find({"Ládví", "Háje"}))->second == "C");

    return 0;
}
