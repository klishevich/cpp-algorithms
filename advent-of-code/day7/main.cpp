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

void part1(const CrabMap &crab_map, int crabs_cnt)
{
    int min_index = crab_map.begin()->first;

    Cost cost {crab_map.begin()->first, 0, 0, 0, crabs_cnt - crab_map.begin()->second};
    
    for (CrabMap::const_iterator iter = next(crab_map.begin()); iter != crab_map.end(); ++iter)
        cost.right_cost += (iter->first - min_index)*iter->second;

    cost.print();
    
    int cur_cost = cost.get_total_cost();
    
    for (auto iter = next(crab_map.begin()); iter != crab_map.end(); ++iter)
    {
        int curr_index = iter->first;
        int curr_crabs = iter->second;
        int new_left_elements = cost.left_elements + crab_map.at(cost.index);
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
}

int calc_cost(const CrabMap &crab_map, int to)
{
//    CrabMap::iterator it_start = left_cost_calc ? crab_map.begin() : crab_map.rbegin();
//    CrabMap::iterator it_end = left_cost_calc ? crab_map.end() : crab_map.rend();

    int left_cost = 0;
    for(CrabMap::const_iterator iter = crab_map.begin(); iter != crab_map.end(); ++iter)
    {
        int index = iter->first;
        if (index >= to)
            break;
        int crabs = iter->second;
        int n = to - index;
        int arithmitic_progression_sum = n * (n+1) / 2;
        left_cost += arithmitic_progression_sum * crabs;
    }   

    int right_cost = 0;
    for(CrabMap::const_reverse_iterator iter = crab_map.rbegin(); iter != crab_map.rend(); ++iter)
    {
        int index = iter->first;
        if (index <= to)
            break;
        int crabs = iter->second;
        int n = index - to;
        int arithmitic_progression_sum = n * (n+1) / 2;
        right_cost += arithmitic_progression_sum * crabs;
    }  

    return left_cost + right_cost;
}

void part2(const CrabMap &crab_map, int crabs_cnt)
{
    int min_index = crab_map.begin()->first;
    int max_index = crab_map.rbegin()->first;
    print_out_map(crab_map);
    
    int lowest_cost_index = 0;
    int lowest_cost = calc_cost(crab_map, crab_map.begin()->first);
    cout << "current cost " << lowest_cost << endl; 
    
    for (int i = next(crab_map.begin())->first; i<= crab_map.rbegin()->first; ++i)
    {
        int newCost = calc_cost(crab_map, i);
        // cout << "index " << i << ", current cost " << newCost << endl;  
        if (newCost < lowest_cost)
        {
            lowest_cost = newCost;
            lowest_cost_index = i;
        }
    }
    cout << " --- --- --- " << endl; 
    cout << "index " << lowest_cost_index << ", minimal cost is " << lowest_cost << endl; 
}

int main( )
{
    std::cout << "Hello Testing!" << std::endl;
    
    vector<string> file_lines = read_from_file("data.txt");
    cout << "file_lines length: " << file_lines.size() << endl;
    
    vector<int> crabs = parse_str_to_vector(file_lines.at(0));
    print_out_vector(crabs);
    
    CrabMap crab_map;
    for (const auto & c : crabs)
        crab_map[c]++;

    // Choose part1 or part2
    part2(crab_map, crabs.size());
    
    return 0;
}