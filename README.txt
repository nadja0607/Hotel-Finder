Data Structures
CS-UH 1050 – Spring 2019
Date: May 9th 2019
---------------------------------------------------------------------------------------------------------------------
Project Name: 
	Hotel Finder
---------------------------------------------------------------------------------------------------------------------
Tech/framework used:
	Sublime Text Editor
---------------------------------------------------------------------------------------------------------------------
Prerequisites:
	Linux/FreeBSD C++ environment
---------------------------------------------------------------------------------------------------------------------
Description: 
	In this project, I developed a hotel-finder application termed hotelFinder that can help in searching for
	a hotel in a specific city. The identification of hotels is based on the key produced by the combination
	of hotelName and cityName.
	Information of hotels can be inserted/read from either the tty of hotelFinder or from a text file. The
	application supports deletion of hotel records as well. 

	Program invocation format:
					
			mymachine-prompt >> ./hotelFinder -f <filename>
			
			where the file <filename> contains records to be inserted into your data structure(s).
	
		
	hotelFinder successfully manages (i.e., stores, retrieves, and deletes) records of hotels. 
	Each such record is provided in ASCII format and spans at most one line of text. 
	The line in question consists of the hotelName, cityName, stars, price, countryName and address. 
	An examples of such line is:
					Hosteria Les Eclaireurs,Ushuaia,3,49,Argentina,Staiyakin 2676

	Through its prompt, the hotelFinder is expected to accept different commands which accept as operand a string 
	that provides a hotel’s data to be inserted, or the combination of hotelName and cityName used as the key to 
	look up records. 
	

The hotelFinder commands are the following:
	– find k: Find the element having a key k and display the entire record. Also, print out the number
		  of comparisons made and the actual time taken by the find execution.
	
	– add s: The data provided by string s consisting hotelName, cityName, stars, price, countryName, address 
		 corresponding to a hotel are to be inserted. 
		 If the element already exists, do not add it again,but simply print out a warning to the standard error.

	– delete k: Delete the hotel record with key k.
		    If no such element exists, print out a warning message to the standard error.

	– dump f: Dump the content of the entire structure(s) into the file f and sort the content of the file f
		  according to the hotelName in alphabetically increasing order.

	– allinCity c: List all hotels in the city c.

	– quit: terminate the program with graceful release of all dynamically acquired memory.


Notes:
	- I am assuming that the input to hotelFinder is always syntactically correct.
	  Hence, I am not checking for the input format that user provides.
---------------------------------------------------------------------------------------------------------------------


	
