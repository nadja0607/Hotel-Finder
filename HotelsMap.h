#ifndef HOTELSMAP
#define HOTELSMAP
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include "Hotel.h"

using namespace std;

class HotelsMap
{
    private:
        list<Hotel> *buckets;        // Array of Pointers to Hotel objects
        int size;                   //Current Size of HashMap
        int capacity;               // Total Capacity of HashMap
    public:
        HotelsMap(int capacity);
        long long hashCode(const string key);
        void insert(string line);
        
        void find(const string key);
        void remove(const string key);
        void dump(string fileName);
        long long getSize();
        ~HotelsMap();
 

};
#endif