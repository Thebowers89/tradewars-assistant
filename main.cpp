#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>

#include "Utils.h"

using namespace std;

map<int, vector<int>> sectors;
map<int, string> stations;
map<int, string> planets;

const string sectorfile = "sectors.txt";
const string stationfile = "stations.txt";
const string planetfile = "planets.txt";

//print available commands
void help() {
    cout << "List of available commands" <<
    endl << "==========================" << endl;
    cout << "q : Quits the program" << endl;
    cout << "info : displays info on a specific sector" << endl;
    cout << "list : brings up the list menu or you could use: " << endl;
    cout << "\tlist sectors\n\tlist stations\n\tlist planets" << endl;
    cout << "add : brings up the add menu or you could use:" << endl;
    cout << "\tadd sector\n\tadd station\n\tadd planet" << endl;
    cout << "remove : brings up the remove menu or you could use:" << endl;
    cout << "\tremove sector\n\tremove station\n\tremove planet" << endl;
    cout << "? : Shows this list" << endl;
}

void loadStations() {
    if (Utils::doesExist(stationfile)) {
        ifstream stat(stationfile);
        string line;
        while(getline(stat, line)) {
            vector<string> s = Utils::splitString(line, ':');
            int first = stoi(s[0]);
            pair<int, string> station(first, s[1]);
            stations.insert(station);
        }
    } else {
        ofstream file(stationfile);
        file.close();
    }
}

void saveStations() {
    ofstream file(stationfile);
    for (auto station : stations) {
        file << to_string(station.first) << ":" << station.second << endl;
    }
    file.close();
}

void loadPlanets() {
    if (Utils::doesExist(planetfile)) {
        ifstream plan(planetfile);
        string line;
        while(getline(plan, line)) {
            vector<string> p = Utils::splitString(line, ':');
            int first = stoi(p[0]);
            pair<int, string> planet(first, p[1]);
            planets.insert(planet);
        }
    } else {
        ofstream f(planetfile);
        f.close();
    }
}

void savePlanets() {
    ofstream plan(planetfile);
    for (auto planet : planets) {
        int first = planet.first;
        string second = planet.second;
        plan << to_string(first) << ":" << second << endl;
    }
    plan.close();
}

void loadSectors() {
    if (Utils::doesExist(sectorfile)) {
        ifstream sect(sectorfile);
        string line;
        while(getline(sect, line)) {
            vector<string> sector = Utils::splitString(line, ':');
            int first = stoi(sector[0]);
            vector<string> connections = Utils::splitString(sector[1], ',');
            int size = connections.size();
            vector<int> cons;
            for (int i = 0; i < size; i++) {
                cons.push_back(stoi(connections[i]));
            }
            pair<int, vector<int>> p(first,cons);
            sectors.insert(p);
        }
    } else {
        ofstream f(sectorfile);
        f.close();
    }
}

void saveSectors() {
    if (Utils::doesExist(sectorfile)) {
        ofstream sect(sectorfile);
        for (auto elem : sectors) {
            int first = elem.first;
            vector<int> second = elem.second;
            string out = "";
            out.append(to_string(first) + ":");
            for (int i : second) {
                out.append(to_string(i) + ",");
            }
            out.pop_back();
            out.append("\n");
            sect << out;
        }
        sect.close();
    }
}

void listAdjacent() {
    cout << "Listing adjacent stations:" << endl;
    bool adjacent = false;
    for (auto station1 : stations) {
        adjacent = false;
        cout << "Station " << station1.first << " : " << station1.second << endl;
        if (sectors.count(station1.first)) {
            for (int i : sectors[station1.first]) {
                if (stations.count(i)) {
                    adjacent = true;
                    cout << "\t" << i << " : " << stations[i] << endl;
                }
            }
            if (!adjacent) {
                cout << "\tNo adjacent stations known" << endl;
            }
            cout << endl;
        } else {
            cout << "\tSector not known" << endl << endl;
        }
    }
}

void remove() {
    while (true) {
        cout << "What would you like to remove? (?=help): ";
        string input;
        cin >> input;
        cout << endl;
        if (input == "?") {
            cout << "Valid inputs are:\nsector\nstation\nplanet\n(q)uit" << endl;
        } else if (input == "sector") {
            cout << "What sector would you like to remove? : ";
            string input;
            cin >> input;
            int s;
            try {
                s = stoi(input);
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                break;
            }
            for (auto sector : sectors) {
                if (sector.first == s) {
                    sectors.erase(sector.first);
                    cout << "Sector removed!" << endl;
                    return;
                }
            }
            cout << "That sector is not known..." << endl;
            break;
        } else if (input == "station") {
            cout << "Which sector is the station in? : ";
            string input;
            cin >> input;
            int s;
            try {
                s = stoi(input);
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                break;
            }
            for (auto station : stations) {
                if (station.first == s) {
                    stations.erase(station.first);
                    cout << "Station removed!" << endl;
                    return;
                }
            }
            cout << "There is no station in that sector!" << endl;
            break;
        } else if (input == "planet") {
            cout << "Which sector is the planet in? : ";
            string input;
            cin >> input;
            int s;
            try {
                s = stoi(input);
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                break;
            }
            for (auto planet : planets) {
                if (planet.first == s) {
                    planets.erase(planet.first);
                    cout << "Planet removed!" << endl;
                    return;
                }
            }
            cout << "There is no planet in that sector!" << endl;
            break;
        } else if (input == "q") {
            break;
        } else {
            cout << "Invalid input!" << endl;
        }
    }
}

//Brings up the add menu
void add() {
    while (true) {
        cout << "What would you like to add? (?=help): ";
        string input;
        cin >> input;
        cout << endl;
        if (input == "?") {
            cout << "Valid inputs are:\nsector\nstation\nplanet\n(q)uit" << endl;
        } else if (input == "sector") {
            cout << "What sector would you like to add? : ";
            string input;
            cin >> input;
            int first;
            try {
                first = stoi(input);
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                return;
            }
            cout << "What are the connections? : ";
            string cons;
            cin >> cons;
            vector<int> second;
            try {
                vector<string> strings = Utils::splitString(cons, ',');
                for (string s : strings) {
                    second.push_back(stoi(s));
                }
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                break;
            }
            pair<int, vector<int>> p(first, second);
            sectors.insert(p);
            return;
        } else if (input == "station") {
            cout << "What sector is the station in? : ";
            string input;
            cin >> input;
            int s;
            try {
                s = stoi(input);
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                break;
            }
            cout << "Please write a brief description of the station.\n> ";
            string des;
            cin.ignore();
            getline(cin, des);
            pair<int, string> station(s, des);
            stations.insert(station);
            return;
        } else if (input == "planet") {
            cout << "What sector is the planet in? : ";
            string input;
            cin >> input;
            int s;
            try {
                s = stoi(input);
            } catch (exception e) {
                cout << "Please enter a valid number!" << endl;
                break;
            }
            cout << "Please write a brief description of the planet.\n> ";
            string des;
            cin.ignore();
            getline(cin, des);
            pair<int, string> planet(s, des);
            planets.insert(planet);
            return;
        } else if (input == "q") {
            return;
        } else {
            cout << "Invalid input!" << endl;
        }
    }
}

void list() {
    while (true) {
        cout << "What you like to list? (?=help): ";
        string input;
        cin >> input;
        cout << endl;
        if (input == "sectors") {
            cout << "List of known sectors:" <<
            endl << "======================" << endl;
            for (auto s : sectors) {
                cout << s.first << " : " << Utils::vectorToString(s.second) << endl;
            }
            return;
        } else if (input == "stations") {
            cout << "List of known stations:" <<
            endl << "======================" << endl;
            for (auto s : stations) {
                cout << s.first << " : " << s.second << endl;
            }
            return;
        } else if (input == "planets") {
            cout << "List of known planets:" <<
            endl << "======================" << endl;
            for (auto p : planets) {
                cout << p.first << " : " << p.second << endl;
            }
            return;
        } else if (input == "?") {
            cout << "Valid options are:\nsectors\nstations\nplanets\n(q)uit" << endl;
        } else if (input == "q") {
            return;
        } else if (input == "adjacent") {
            listAdjacent();
        } else {
            cout << "Invalid input!" << endl;
        }
    }
}

void info() {
    cout << "Which sector would you like information on? : ";
    string input;
    cin >> input;
    int i;
    try {
        i = stoi(input);
    } catch (exception e) {
        cout << "Please enter a valid number!" << endl;
        return;
    }
    cout << "\n\nListing information on sector " << i << ":" << endl;
    if (sectors.count(i)) {
        cout << "\tConnections: " << Utils::vectorToString(sectors[i]) << endl;
    } else {
        cout << "\tSector is not on map..." << endl;
    }
    if (stations.count(i)) {
        cout << "\tStation " << i << " : " << stations[i] << endl;
        cout << "\t\tAdjacent stations:" << endl;
        bool found = false;
        for (int s : sectors[i]) {
            if (stations.count(s)) {
                found = true;
                cout << "\t\t" << s << " : " << stations[s] << endl;
            }
        }
        if (!found) {
            cout << "\t\tNo adjacent stations known" << endl;
        }
    } else {
        cout << "\tNo known station in sector..." << endl;
    }
    if (planets.count(i)) {
        cout << "\tPlanet " << i << ": " << planets[i] << endl;
    } else {
        cout << "\tNo known planet in sector..." << endl;
    }
}

void test() {
    listAdjacent();
}

int main() {
    bool running = true;
    loadPlanets();
    loadStations();
    loadSectors();
    while (running) {
        cout << "\nWelcome to the TradeWars Assistant!" << endl
        << "What would you like to do? (?=help): ";
        string input;
        cin >> input;
        input = Utils::ignoreCase(input);
        if (input == "?" || input == "help") {
            help();
        } else if (input == "q") {
            running = false;
            cout << "Goodbye!" << endl;
        } else if (input == "test") {
            test();
        } else if (input == "add") {
            add();
        } else if (input == "list") {
            list();
        } else if (input == "remove") {
            remove();
        } else if (input == "info") {
            info();
        } else {
            cout << "Invalid command!" << endl;
        }
    }
    saveSectors();
    savePlanets();
    saveStations();
}