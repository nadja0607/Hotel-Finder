#include <chrono> 
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include "Hotel.h"
#include "HotelsMap.h"

using namespace std;
using namespace std::chrono;
void my_find(string key,HotelsMap &mp); 
void my_add(string new_city_data,map<string,list<Hotel>> &my_map, HotelsMap &mp); 
void my_delete(string key,map<string,list<Hotel>> &my_map, HotelsMap &mp); 
void my_dump(string argu,HotelsMap &mp); 
void my_allInCity(string key,map<string,list<Hotel>> &my_map); 
long long prime_generator(long long number);

int main(int numArg, char *args[])
{
    //chcek for sufficient number of arguments
    if (numArg !=3) 
    {
        cerr << "ERROR: Insufficient Arguments." << endl;
        cerr<<"Usage: ./hotelFinder -f <filename>"<<endl; //tell the user the proper invocation pattern
        return EXIT_SUCCESS;
    }
    //if arguemnts are sufficient in number, continue further
    else 
    {           
        string inputFile;
        if (string(args[1])=="-f") 
            inputFile=args[2];
        else
        {
            cerr<<"Correct invocation needs to be: ./hotelFinder -f <filename>"<<endl; //used to tell the user the proper invocation pattern
            return EXIT_SUCCESS; 
        }
        cout<<endl;
        cout<<"Input file used: "<<inputFile<<endl;
        
        // opening the input file
        ifstream fin(inputFile);
        //if the file is not open, the program terminates
        if(not fin.is_open())
        {
            cerr<<"Can't open the file"<<inputFile<<endl;
            return EXIT_FAILURE;
        }
        //if the input file was entered and it exists and can be opened: continue further
        else
        {
            //read input file first time to determine number of lines
            string line;
            long long line_cntr = -1; //-1 is to skip the first line
            
            while (getline(fin, line))
            {
                line_cntr++;
            }
            fin.close();

            long long capa = prime_generator(ceil(1.33333333*line_cntr)); //generate prime number, load factor=0.75
            //create map for allInCity function
            map<string, list<Hotel>> my_map; 
            //create map for all the hotels
            HotelsMap mp(capa);
            //read input file second time to save data
            fin.open(inputFile);
            getline(fin, line); //skip first line
            while (getline(fin, line)) 
            {
                Hotel h = Hotel(line); //create Hotel object
                string city = h.get_city(); //get city 
                my_map[city].push_back(h); //save to CityMap
                mp.insert(line); //send line to all HotelsMap, hotel object will be created there
                
            } 
            
            //getting the input from the user
            string comm;
            string argu;
            string user_input;
            
            while(true)
            {
                cout<<"_________________________________"<<endl;
                cout<<"Commands: find k| add s| delete k| dump f| allinCity c| quit|"<<endl;
                cout<<"Enter the command: ";
                getline(cin, user_input);
                int space_index;
                space_index = user_input.find(" "); // finding the index of the 1st space occurance and using it to split a command and an argument
                // separating the left and right side of the users input based on the 1st occurance of the space
                // left side being the command word and the right side being the argument
                comm = user_input.substr(0,space_index); 
                argu = user_input.substr(space_index+1, user_input.length());
                
                if (comm == "find")
                {
                    my_find(argu, mp); 
                }
                else if (comm == "add")
                {
                    my_add(argu, my_map, mp);
                }   
                else if (comm == "delete")
                {
                    my_delete(argu, my_map, mp); 
                }
                else if (comm == "dump")
                {
                    my_dump(argu, mp); 
                }
                else if (comm == "allinCity")
                {
                    my_allInCity(argu, my_map); 
                }
                else if (comm == "quit")
                {
                    
                    return EXIT_SUCCESS;
                }
                else // this is in case there is no input or the input is invalid
                {
                    cerr<<"Invalid. Enter a valid command instead: "<<endl;
                    cerr<<"find k| add s | delete k | dump f| allinCity c |quit|"<<endl;
                }
            }
        }
    //stay here
    }
    
    return 0;
}       

void my_find(string key,HotelsMap &mp)
{
    // at this instant use function now() 
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //search hotelsmap
    mp.find(key);
    // After function call stop time
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time taken: " << duration <<" microseconds"<<endl;

} 
void my_add(string new_city_data,map<string,list<Hotel>> &my_map, HotelsMap &mp)
{
    /* The data provided by string s consisting hotelName, cityName, stars, price, countryName,
address corresponding to a hotel are to be inserted. If the element already exists, do not add it again,
but simply print out a warning to the standard error.*/
    // at this instant use function now() 
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //__________________________________________________________
    //1)adding to all hotels map
    mp.insert(new_city_data);
    //2)adding to allinCity map
    Hotel h = Hotel(new_city_data); //create Hotel object
    string city = h.get_city(); //get city of the one we are inserting
    string key = h.get_key(); //get key of the one we are inserting
    map<string,list<Hotel>>::iterator it; //iterator for map
    it = my_map.find(city); // if city hash code not in map, add right away
    if (it == my_map.end())
       {
        my_map[city].push_back(h);
        cout<<"hotel"<<h.get_content()<<" added"<<endl;
        cout<<"-----------"<<endl;
       } 
        
    else
    {
        //city hash code is in map
        list<Hotel>::iterator iter2; //iterator for the list
        for (iter2 = my_map[city].begin(); iter2 != my_map[city].end(); ++iter2)
        {
            if (iter2->get_key() == key) 
            {
                cerr<<"hotel already in map warning"<<endl;
                return;
            }
        }
        my_map[city].push_back(h);
        cout<<"hotel"<<h.get_content()<<" added"<<endl;
        cout<<"-----------"<<endl;
    }
    //--------------------------
    // After function call stop time
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time taken: " << duration <<" microseconds"<<endl;


}
void my_delete(string key,map<string,list<Hotel>> &my_map, HotelsMap &mp){
    /* Delete the hotel record with key k1. If no such element exists, print out a warning message
to the standard error.*/
    // start timer
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //1. delete from all hotels map
    mp.remove(key);
    //2.delete from all cities map
    long long comma_index = key.find(",");
    string city_key = key.substr(comma_index+1, key.length());

    map<string,list<Hotel>>::iterator it; //iterator for map
    it = my_map.find(city_key); 
    if (it == my_map.end())
        cerr<<"hotel not in map warning"<<endl;
    else
    {
        //city hashcode exist in map
        list<Hotel>::iterator iter2; //iterator for the list
        for (iter2 = my_map[city_key].begin(); iter2 != my_map[city_key].end(); ++iter2)
        {
            if (iter2->get_key() == key) //search and delete hotel
            {
                iter2 = my_map[city_key].erase(iter2);
                cout<<"hotel deleted"<<endl;

            }
        }
        cout<<"--------------"<<endl;
    }
    //--------------------------
    // After function call stop time
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time taken: " << duration <<" microseconds"<<endl;

}
void my_dump(string argu,HotelsMap &mp){
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //start timer
    mp.dump(argu); //call dump function in all hotels map
    //stop timer
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time taken: " << duration <<" microseconds"<<endl;
} 
void my_allInCity(string key,map<string,list<Hotel>> &my_map)    //key is the city name
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //timer
    long long num_cities =0;
    map<string,list<Hotel>>::iterator it; //iterator for map
    it = my_map.find(key); 
    if (it == my_map.end()) //if hashcode of a city not even in map, display error
        cerr<<"city not in map warning"<<endl;
    else
    {
        //city (i.e city's hash code) is in map
        cout<<"-----------"<<endl;
        cout<<"Hotels in "<<key<<": "<<endl<<endl;
            cout << left <<setw(50) << "Name"<< setw(20) <<"City"<<setw(5) <<"Stars"<< setw(12) << "Price"<<setw(15) << "Country"<< "Address"<<endl;
        list<Hotel>::iterator iter2; //iterator for the list
        for (iter2 = my_map[key].begin(); iter2 != my_map[key].end(); ++iter2)
        {
            if (iter2->get_city() == key) 
            {
                num_cities++;
                iter2->print_hotel_info_formatted();
            }
        }
        cout<<endl;
        cout<<"There are "<<num_cities<< " hotels in "<<key<<endl;
    }
    // After function call stop time
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Time taken: " << duration <<" microseconds"<<endl;
} 
 

long long prime_generator(long long num)
{
    vector<bool> vect(num, true);
    for (long long i=2; i<vect.size(); ++i)
    {
        
        while (vect[i] == false && i<vect.size())
            i++;
        
        for (long long e=2; i*e<vect.size(); ++e)
        {
            vect[i*e] = false;
        }
    }
    
    long long r=vect.size()-1; 
    do
    {
        if (vect[r]==true)
            return r;
        else
            r--;
    } while (r>=0);

}