#include "Hotel.h"

Hotel::Hotel(string& line) 
{
    istringstream ss(line);
    getline(ss, name, ',');
    getline(ss, city, ',');
    getline(ss, stars, ',');
    getline(ss, price, ',');
    getline(ss, country, ',');
    getline(ss, addr);
}

string Hotel::get_name() { return this->name;}
string Hotel::get_city() { return this->city;}
string Hotel::get_stars() { return this->stars;}
string Hotel::get_price() { return this->price;}
string Hotel::get_country() { return this->country;}
string Hotel::get_addr() { return this->addr;}
string Hotel::get_key() { return name+","+city;}

string Hotel::get_content()
{
    return name+","+city+","+stars+","+price+","+country+","+addr;
}

void Hotel::print_hotel_info_separate_lines()
{
    cout << "Name: "<< name <<endl;
    cout << "City: "<< city <<endl;
    cout << "Stars: " << stars <<endl;
    cout << "Price: " << price <<endl;
    cout << "Country: " << country <<endl;
    cout << "Address: " << addr <<endl;

}

void Hotel::print_hotel_info_formatted()
{
    cout << left <<setw(50) << name;
    cout << setw(20) <<city;
    cout << setw(5) <<stars;
    cout << setw(12) << price;
    cout << setw(15) << country;
    cout << addr;
    cout << endl;
}
