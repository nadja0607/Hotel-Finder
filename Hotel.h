#ifndef HOTEL
#define HOTEL
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Hotel {
    private:
        string name, city, stars, price, country, addr;
    public:
        Hotel(string& line);
        string get_name();
        string get_city() ;
        string get_stars();
        string get_price();
        string get_country();
        string get_addr() ;
        string get_key() ;
        
        string get_content();
        void print_hotel_info_separate_lines();
        void print_hotel_info_formatted();
};

#endif
