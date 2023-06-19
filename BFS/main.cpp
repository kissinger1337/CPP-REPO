#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <queue>

/**
 * @brief class representing public transport lines. Contains functions to read from a file and find the shortest path using BFS.
 */
class CPublicTransport{
public:
    bool read (const std::string &);/**< Iterates through all files in one directory. Does not recursively iterate through deeper directories.*/

    std::map<std::pair<std::string, std::string>, std::string> getAllConnections() const; /**< Getter used only for testing */

    bool find (const std::string & from, const std::string & to);

private:
    bool readOneFile(const std::string &);
    //                   from          to           line name
    std::map<std::pair<std::string, std::string>, std::string> m_AllConnections;/**< map of all straight connections */
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
    std::set<std::string> stops;
    while(getline(ifs, stop)){
        for(const auto& other : stops) {
            //                                          from      to       line name
            m_AllConnections.emplace(std::make_pair(stop, other), lineName);
            m_AllConnections.emplace(std::make_pair(other, stop), lineName);
        }
        stops.insert(stop);
    }

    return true;
}

std::map<std::pair<std::string, std::string>, std::string> CPublicTransport::getAllConnections() const {
    return m_AllConnections;
}

bool CPublicTransport::find(const std::string &from, const std::string &to) {
    if(from == to) return true;

    std::queue<std::string> toVisit;
    std::set  <std::string> visited;

    toVisit.push(from);
    visited.insert(from);

    while(!toVisit.empty()){
        std::string f = toVisit.front();
        toVisit.pop();
        for(const auto & it : m_AllConnections){
            if(it.first.first == f && visited.find(it.first.second) == visited.end() ){
                toVisit.push(it.first.second);
            }
            visited.insert(f);
        }
    }
    return visited.count(to) == 1;

}

int main() {
    CPublicTransport a;

    if(!a.read("/home/fitslave/code/CPP-REPO/BFS/lines"))
        std::cout << "Error opening file" << std::endl;

    std::map<std::pair<std::string, std::string>, std::string> allConnectionsA = a.getAllConnections();

    assert((allConnectionsA.find({"Dejvická", "Depo Hostivař"}))->second == "A");
    assert((allConnectionsA.find({"Depo Hostivař", "Dejvická"}))->second == "A");
    assert((allConnectionsA.find({"Jinonice", "Českomoravská"}))->second == "B");
    assert((allConnectionsA.find({"Ládví", "Háje"}))->second == "C");
    assert(allConnectionsA.find({"Dejvická","Háje"}) == allConnectionsA.end());

    assert(a.find("Dejvická","Háje") == true);
    assert(a.find("Dejvická","Anděl") == true);
    assert(a.find("Dejvická","Ne existuje") == false);

    return 0;
}
