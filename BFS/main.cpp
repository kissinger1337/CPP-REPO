#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <queue>

/**
 * @brief class representing public transport lines. Contains functions to read from a directory and find the shortest path using BFS.
 */
class CPublicTransport{
public:
    bool read (const std::string &);/**< Iterates through all files in one directory. Does not recursively iterate through deeper directories.*/

    std::map<std::pair<std::string, std::string>, std::string> getAllConnections() const; /**< Getter used only for testing */

    int find (const std::string & from, const std::string & to) const;

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

int CPublicTransport::find(const std::string &from, const std::string &to) const{
    if(from == to) return 0;

    std::queue<std::string> toVisit;
    //     station name  amount of links needed to get there
    std::map<std::string,    int> visited;

    toVisit.push(from);
    visited.emplace(from,0);

    while(!toVisit.empty())
    {
        std::string f = toVisit.front();
        toVisit.pop();
        //count is an amount of links it takes to get there
        int count = visited [f];

        //lower_bound returns position in our map that has first equal or greater pair of source and destination
        //we will iterate through all of pairs that contain source station, adding all of the destinations
        //to the visited set (that means we can get there) and to toVisit (because we need to visit all of its neighbours)

        //it->first is a pair of source and destination
        //it->first.first is a source station
        for(auto it = m_AllConnections.lower_bound(std::make_pair(f,""));
            it!=m_AllConnections.end() && it->first.first == f; ++it){

            //it->first.second is a destination
            if(visited.count(it->first.second) == 0) {
                visited.emplace(it->first.second, count + 1);
                toVisit.push(it->first.second);
            }
        }
    }

    //visited has station that we want to find way to ? return amount of links it takes to get there, else return -1 as
    //an indicator that there is no path to this station
    return visited . count ( to ) == 1 ? visited [ to ] : -1;

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

    assert(a.find("Dejvická","Depo Hostivař") == 1);
    assert(a.find("Dejvická","Háje") == 2);
    assert(a.find("Dejvická","Anděl") == 2);
    assert(a.find("Dejvická","Ne existuje") == -1);

    return 0;
}
