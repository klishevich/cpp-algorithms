#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using IntType = unsigned long long int;
using FishMapType = map<int, IntType>;

const int DAYS = 256;
// const string FILE_NAME = "test_data.txt";
const string FILE_NAME = "data.txt";

void print_out_vector(const vector<int> &my_vector)
{
    cout << "printing out vector: " << endl;
    for (const auto & v : my_vector)
        cout << v << " ";
    cout << endl;
}

void print_out_map(const FishMapType &my_map)
{
    cout << "printing out map: " << endl;
    for (const auto &[k,v] : my_map)
        cout << k << " : " << v << endl;
}

FishMapType parse_data(const string &str)
{
    vector<int> fishes;
    stringstream ss(str);
    string element;
    while (getline(ss, element, ','))
        fishes.push_back(atoi(element.c_str()));
    print_out_vector(fishes);
    
    FishMapType my_map;
    
    for(const auto fish : fishes) my_map[fish]++;
    return my_map;
}

int main( )
{
    long cppVer = __cplusplus;
    cout << "__cplusplus value is: ";
    cout << to_string( cppVer ) << endl;
    
    vector<string> file_lines;
    
    string line;
    for (ifstream my_file(FILE_NAME); getline(my_file, line);) 
        file_lines.push_back(line);
    cout << "file_lines length: " << file_lines.size() << endl;

    string fishes_str = file_lines.at(0);
    
    FishMapType fish_map = parse_data(fishes_str);
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    for (int i=0;i<DAYS;i++)
    {
        FishMapType new_fish_map;
        for (const auto &[k,v] : fish_map) {
            if (k == 0)
            {
                new_fish_map[6] +=v;
                new_fish_map[8] +=v;
            } else {
                new_fish_map[k-1] +=v;
            }
        }
        fish_map = new_fish_map;
    }
    
    print_out_map(fish_map);

    IntType res = 0;
    for (const auto &[k,v] : fish_map)
        res += v;
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microseconds]" << std::endl;
        
    cout << "Total fishes: " << res << endl; 
}
