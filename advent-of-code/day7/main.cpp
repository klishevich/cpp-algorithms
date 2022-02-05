#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
using CrabMap = map<int, int>;

void print_out_vector(const vector<int> &my_vector)
{
    cout << "printing out vector: " << endl;
    for (const auto & v : my_vector)
        cout << v << " ";
    cout << endl;
}

void print_out_map(const CrabMap &my_map)
{
    cout << "printing out map: " << endl;
    for (const auto &[k,v] : my_map)
        cout << k << " : " << v << endl;
}

vector<string> read_from_file(string file_name)
{
    vector<string> file_lines_out;
    string line;
    for (ifstream my_file(file_name); getline(my_file, line);) 
        file_lines_out.push_back(line);
    return file_lines_out;
}

vector<int> parse_str_to_vector(string str)
{
    vector<int> v;
    stringstream ss(str);
    string element;
    while (getline(ss, element, ','))
        v.push_back(atoi(element.c_str()));
    return v;
}

struct Cost {
    int index;
    int left_cost;
    int left_elements;
    int right_cost;
    int right_elements;
    int get_total_cost() 
    { 
        return left_cost + right_cost; 
    }
    void print()
    {
        cout << "------------" << endl;
        cout << "index " << index << endl;
        cout << "left_elements " << left_elements << endl;
        cout << "left_cost " << left_cost << endl;
        cout << "right_elements " << right_elements << endl;
        cout << "right_cost " << right_cost << endl;
        cout << "get_total_cost " << get_total_cost() << endl;
    }
};

int main( )
{
    std::cout << "Hello Testing!" << std::endl;
    
    vector<string> file_lines = read_from_file("data.txt");
    cout << "file_lines length: " << file_lines.size() << endl;
    
    vector<int> crabs = parse_str_to_vector(file_lines.at(0));
    print_out_vector(crabs);
    
    CrabMap crab_map;
    int crabs_cnt = crabs.size();
    for (const auto & c : crabs)
        crab_map[c]++;
    int min_index = crab_map.begin()->first;
    int max_index = crab_map.rbegin()->first;
    print_out_map(crab_map);
    cout << "min index " << min_index << endl;
    cout << "max index " << max_index << endl;

    Cost cost {crab_map.begin()->first, 0, 0, 0, crabs_cnt - crab_map.begin()->second};
    
    for (CrabMap::iterator iter = next(crab_map.begin()); iter != crab_map.end(); ++iter)
        cost.right_cost += (iter->first - min_index)*iter->second;

    cost.print();
    
    int cur_cost = cost.get_total_cost();
    
    for (auto iter = next(crab_map.begin()); iter != crab_map.end(); ++iter)
    {
        int curr_index = iter->first;
        int curr_crabs = iter->second;
        int new_left_elements = cost.left_elements + crab_map[cost.index];
        int new_left_cost = cost.left_cost + new_left_elements * (curr_index - cost.index);
        int new_right_elements = cost.right_elements - curr_crabs;
        int new_right_cost = cost.right_cost - cost.right_elements * (curr_index - cost.index);
        cost.index = curr_index;
        cost.left_cost = new_left_cost;
        cost.left_elements = new_left_elements;
        cost.right_cost = new_right_cost;
        cost.right_elements = new_right_elements;
        if (cost.get_total_cost() >= cur_cost) 
        {
            cost.print();
            break;
        }
        cur_cost = cost.get_total_cost();
    }
    cout << "minimal cost is " << cur_cost << endl;
    
    return 0;
}