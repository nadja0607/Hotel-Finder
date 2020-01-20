#include "HotelsMap.h"
#include "Hotel.h"

HotelsMap::HotelsMap(int capacity) //constructor
{
    buckets = new list<Hotel>[capacity];
    this->capacity = capacity;
    this->size = 0;
}

HotelsMap::~HotelsMap() //destructor
{
    delete [] this->buckets;
    this-> buckets = nullptr;
}

long long HotelsMap::getSize() //returns number of elements in the map
{
    return this->size;
}

long long  HotelsMap::hashCode(const string key) //generates hashcode, returns bucket index
{
    long long sum = 0;
    for(int i=0; i<key.length(); i++)
        sum += key[i]*(i+1);        //Add ascci code of each letter times i+1

    return sum%this->capacity;      //make sure that the key is with in the capacity of array
}

void HotelsMap::insert(string line) //insert hotel function, argument is a string of form: hotelName,cityName,stars,price,countryName,address
{
    Hotel hotel = Hotel(line); //create hotel object
    string key = hotel.get_key(); //get key of form: hotelName,cityName
    long long index = hashCode(key); //find the bucket index where the new node will fall using hashcode fuction
    
    for(auto it:buckets[index]) //iterate over bucket[hashCode]
    {
        if(it.get_key()== key) //if element already exist, display error, do not overwrite
        {
            cerr << "element already in map warning"<<endl;
            return;
        }
    } 

    buckets[index].push_back(hotel);  //Add the new element into the bucket->list
    this->size++;                     //Increate number of elements in the array, i.e size of map
}

void HotelsMap::find (const string key) //find function
{
    long long comparison_cntr=0; //counter of comparisons
    long long index = hashCode(key); //Find the bucket index where the new node will fall
    
    for(auto it:buckets[index]) //search the bucket
    { 
        comparison_cntr++;
        //hotel found
        if(it.get_key()== key) 
        {
            
            cout<<"--------"<<endl;
            cout<<"Following hotel info found: "<<endl; //display match
            it.print_hotel_info_separate_lines();
            cout<<"--------"<<endl;
            cout<<"Number of comparisons: "<<comparison_cntr <<endl; //display counter

            return;
        }
    }
    //hotel not found
    cout<<"Number of comparisons: "<<comparison_cntr <<endl; //display counter
    cerr<<"Hotel not found"<<endl; //
    return;
 
}

void HotelsMap::remove(const string key){
    int index = hashCode(key);  //Get the index of the bucket
    long long comparison_cntr = 0; //create counter

    for(list<Hotel>::iterator it = buckets[index].begin(); it!=buckets[index].end(); ++it) //iterate over the bucket contents
    {
        comparison_cntr++;
        if((*it).get_key()==key) //if you find match
        {
            cout<<"Deleted :"<<it->get_content()<<endl; //display what is deleted
            buckets[index].erase(it); //delete it
            this->size--; //decreemnt size
            cout<<"Number of comparisons: "<<comparison_cntr <<endl;
            return;
        }
    }
    // hotel not found
    cout<<"Number of comparisons: "<<comparison_cntr <<endl;
    cerr<<"Cannot delete warning - Record Not Found"<<endl;
    return; 
}

void HotelsMap::dump(string fileName)
{
    std::vector<Hotel> v; //create vector of Hotels
    for (long long i=0; i<capacity; i++) //loop over the map
    {
        for(auto it:buckets[i])
        {
            v.push_back(it); //push Hotel object to vecor
        }
    }
    //sort in place, complexity O(n log n)
    sort(v.begin(), v.end(), [](Hotel a, Hotel b){return a.get_name() < b.get_name();});
    
    //create output file
    ofstream myfile;
    myfile.open(fileName);
    myfile <<"hotelName,cityName,stars,price,countryName,address"<<endl; //write the first line
    for(int i=0; i<v.size(); i++)
        {
             myfile << v[i].get_content()<<endl; //write to output file
            
        }
   myfile.close(); //close outfile

}
