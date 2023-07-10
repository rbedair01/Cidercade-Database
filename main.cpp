// Reema Bedair - ryb200001 (CS 1337.007)
// Project 3
/*
    Creating program to interfere with a companies database file to organize their records.
    Program will read in 2 files: database file and batch file
    Database file holds all current records from the company. The batch file holds information
    to either Add, Search, Edit, or Delete a record. The batch file will also determine if the records
    are to be sorted.
    The program will read each record in the database file and place them into nodes. Each record (node)
    will be linked in a list
    Once all records(nodes) are placed into the linked list, each line in the batch file will be read
    The batch file will then determine if a record is to be added, searched for, edited, deleted or if the
    records are to be sorted by name or by plays
    Once the batch file is read until the end of file, the program will print a new database file
    displaying all records in the same format as the old database file.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <cstring>
using namespace std;

// structures
struct Record
{
    string name;
    long int highscore;
    string initials;
    long int plays;
    double revenue;
    Record* next = nullptr;
};


// function prototypes
void CreateList(string , Record *&);
void print(fstream &, Record *&);
void addRecord(string , Record *&);
void searchRecord(string , Record *);
void editRecord(string , Record *&);
void deleteRecord(string, Record *&);
void sortRecords(string, Record *&);


// main
int main()
{
    
    // varaibles to hold file names
    string temp;
    string batch;
    
    // Prompting and allowing user to enter database file
    cout << "Enter database file: ";
    cin >> temp;
    cout << endl;
    
    // Prompting and allowing user to enter batch file
    cout << "Enter batch file: ";
    cin >> batch;
    cout << endl;
    
    // variables defining the file to be read
    fstream data;
    ifstream batchF;
    
    // opening files
    data.open(temp, ios::in);
    batchF.open(batch);
    

    // variables defined for reading and parsing
    string line;

    // creating head pointer
    Record *head = nullptr;
    
    // read records and database file and create a node for each line
    // function call will create the node and link it to a list
    while (getline(data, line))
    {
        if(line.length() == 0)
        {
            continue;
        }
        
        // read line and send each line to function to be placed into a node
        // and linked into a list
        CreateList(line, head);
    }
    
    // close database file
    data.close();
        
    
    // variable defined to read each line in batch file
    string instruct;
    long int index1;
    string command;
    
    // read each line in batch file and determine which command to follow through with
    while (getline(batchF, instruct))
    {
        if(instruct.length() == 0)
        {
            continue;
        }

        // parse the command number that starts off each line in batch file
        // number will tell us which function to proceed with and how to
        // manipulate the record
        index1 = instruct.find(' ');
        command = instruct.substr(0, index1);
        instruct = instruct.substr(index1 + 1);

        /*
            - If command number in front of line is eqguivalent to '1':
            call function to add a record to a node and link it to end of list
            - If command number in front of line is equivalent to '2':
            call function to search for a record in the linked list
            - If command number in front of line is equivalent to '3':
            call function to edit a record in the linked list
            - If command number in front of line is equivalent to '4':
            call function to delete a record anywhere in the linked list
            - If command number in front of line is equivalent to '5':
            call function to sort the records either by name of the game or the amount of plays on each game
         */
        if(command.at(0) == '1')
        {
            addRecord(instruct, head);
        }
        else if(command.at(0) == '2')
        {
            searchRecord(instruct, head);
        }
        else if(command.at(0) == '3')
        {
            editRecord(instruct, head);
        }
        else if(command.at(0) == '4')
        {
            deleteRecord(instruct, head);
        }
        else if(command.at(0) == '5')
        {
            sortRecords(instruct, head);
        }
        
    }
    
    // creating file to hold new database records
    fstream newData;
    newData.open("freeplay.txt", ios::out);
    
    // Function call to print all records and any new changes to a new database file
    // function arguments is the new file and head pointer for the linked list
    print(newData, head);
    
    
    // close files
    batchF.close();
    newData.close();
    
    
    return 0;
}



// Function will create a linked list of all the records
/*
    Each line (record) read from the database file is sent to this function to be placed into separate
    nodes and linked into a list. A head pointer pointing to the first node (empty or full) in the list is also
    sent to the function.
    Function will recieve a line read from the database file and will parse the line into 5 sections to be
    placed into the node; Name (of game), initials (of highscoring player), highscore (made in the game),
    plays (amount of plays in game), revenue (amount of money made from each play).
    Once line is parsed into sections and converted to correct data type, function will place each section into the node
    and link each node to the list by adding it to the end of the list
    Parameters: (line(record) read from database file, head pointer pointing to the beginning of the list)
 */
void CreateList(string line, Record *&head)
{
    // defining variables to hold different sections found in each record in the database file
    string tempName;
    string tempInitials;
    string tempHigh;
    string tempPlays;
    string tempRev;
    
    // variable defined for reading and parsing line
    long int index;

    
    // parse name
    index = line.find(',');
    tempName = line.substr(0, index);
    line = line.substr(index + 1);
    
    // parse highscore
    index = line.find(',');
    tempHigh = line.substr(1, index - 1);
    line = line.substr(index + 1);
    
    // parse initials
    index = line.find(',');
    tempInitials = line.substr(1, index - 1);
    line = line.substr(index + 1);
    
    // parse plays
    index = line.find(',');
    tempPlays = line.substr(1, index - 1);
    line = line.substr(index + 1);
    
    // parse revenue
    tempRev = line.substr(2);
    
    
    // convert highscore, plays from a string to an integer
    int tempScore = stoi(tempHigh);
    int tempPlay = stoi(tempPlays);
    
    // convert revenue from a string to a double
    double tempRevenue = stod(tempRev);
    
    
    // creating new node to be linked to list
    Record* newNode = new Record;
    
    // put all data recieved from record into new node
    newNode->name = tempName;
    newNode->highscore = tempScore;
    newNode->initials = tempInitials;
    newNode->plays = tempPlay;
    newNode->revenue = tempRevenue;
    newNode->next = nullptr;
    
    
    // link new node to list
    // if list is empty just add new node to head
    // else add new node to the end of the list
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        // create traversal pointer to move through list
        // to be able to add record to end of the linked list
        Record *traverse;
        traverse = head;
        
        // traverse through list and stop when you reach end of list before last node points to nullptr
        while (traverse->next != nullptr)
        {
            // move to next node in list
            traverse = traverse->next;
        }
        
        // link new node
        newNode->next = traverse->next;
        traverse->next = newNode;
    }
    
}



// function will add a new record(node) to linked list
/*
    A line read in from the batch file is sent to this function to add a record to the list(database).
    The line will contain sections needed to be parsed to be able to add each section to a node. Once the line sent in is parsed
    and any conversions needed to be done are done, the function will place eash section into a node
    The node will then be added to the end of the linked list
    Function will display record to console once record is succesfully added
    Paramters: (line read from batch file, head pointer pointing to the beginning of the list)
 */
void addRecord(string instruct, Record *&head)
{
    // create new node
    Record* newNode = new Record;
    
    // define variables to hold data for each section in record and to aid in parsing of the line
    long int index;
    string tempName = "";
    string tempHigh = "";
    string tempInitials = "";
    string tempPlays = "";
    string tempRevenue = "";
    
    
    // parse name from line
    index = instruct.find('"', 1);
    tempName = instruct.substr(1, index -1);
    instruct = instruct.substr(index + 1);
    
    // parse highscore from line
    index = instruct.find(' ', 1);
    tempHigh = instruct.substr(1, index - 1);
    instruct = instruct.substr(index);
    
    // parse initials from line
    index = instruct.find(' ', 1);
    tempInitials = instruct.substr(1, index -1);
    instruct = instruct.substr(index);
    
    // parse plays from line
    index = instruct.find(' ', 1);
    tempPlays = instruct.substr(1, index - 1);
    tempRevenue = instruct.substr(index + 2);
        
    
    // convert hish score and plays from string to integer
    int tempScore = stoi(tempHigh);
    int tempPlay = stoi(tempPlays);
    
    // convert revenue from to string to double
    double tempRev = stod(tempRevenue);
    
    
    // add new data into a new node
    newNode->name = tempName;
    newNode->highscore = tempScore;
    newNode->initials = tempInitials;
    newNode->plays = tempPlay;
    newNode->revenue = tempRev;
    

    // link new node to list
    // if list is empty just add new node to head
    // else add new node to the end of the list
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        // create traversal pointer to move through list
        Record *traverse;
        
        // initialize traverse to head
        traverse = head;
        
        
        // traverse through list and stop when you reach end of list before last node points to nullptr
        while (traverse->next != nullptr)
        {
            // move to next node in list
            traverse = traverse->next;
        }
        
        // link new node to list
        newNode->next = traverse->next;
        traverse->next = newNode;
        
    }
    
    // Display record to console, to show the record was successfully added to the list (database)
    cout << "RECORD ADDED\n";
    cout << "Name: " << tempName << endl;
    cout << "High Score: " << tempScore << endl;
    cout << "Initials: " << tempInitials << endl;
    cout << "Plays: " << tempPlay << endl;
    cout << "Revenue: $" << fixed << setprecision(2) << tempRev << endl << endl;
      
}



// search for record(node) in linked list
/*
    A line read in from the batch file is sent to function to locate a record(node) in the linked list(database)
    The line will contain the name of the game, which will be compared with each record's name
    Once the correct record(node) is successfully found, the function will read from the node and display the
    record to the console.
    If name is not found in any of the nodes, the record will display that the name was not found
    Paramters: (line read from batch file, head pointer pointing to the beginning of the list)
 */
void searchRecord(string instruct, Record *head)
{
    // create traverse pointer to move through list
    Record *traverse;
    
    // initalize traverse to head
    traverse = head;
    
    // variable defined for if record is found it will increment
    int i = 0;
    
    
    // Loop: move pointer through each node in list until the end, once the pointer equals null
    // loop will end
    // while pointer moves through each node it will compare the search term to each record's name
    // if record equal's search term, function will display to console the records information
    // (name, highscore, initials, plays, revenue) and will increment a count variable to keep track of record found
    // once found, loop will break
    while (traverse != nullptr)
    {
        if (traverse->name.find(instruct) != string::npos)
        {
            ++i;
    
            cout << traverse->name << " FOUND" << endl;
            cout << "High Score: " << traverse->highscore << endl;
            cout << "Initials: " << traverse->initials << endl;
            cout << "Plays: " << traverse->plays << endl;
            cout << "Revenue: $" << fixed << setprecision(2) << traverse->revenue << endl << endl;
            
            break;
        }
        
        // move to next node in list
        traverse = traverse->next;

    }
    
    // if count varaible still equals 0, the search was not found
    // the function will then display to console that the search term was not found
    if (i == 0)
    {
        cout << instruct << " NOT FOUND\n" << endl;
    }

}


// function will find a record(node) and edit the node in linked list
/*
    A line read from the batch file is sent to the function to find a record (node) w/ a search term and
    edit the record. The line will indicate what in the record will need to be edited and what change to make to
    the record. (highscore, initials, plays)
    The function will recieve the line and parse the line into 3 sections(name, field number, new value)
    function will find the record(node) to edited and will determine which section needs editing by the number
    shown on the field number
    Function will edit record and will display record to console
    Parameters: (line read from batch file, head pointer pointing to the beginning of the list)
 */
void editRecord(string instruct, Record *&head)
{
    // define variable to hold data and to aid in parsing the line
    long int index;
    string findName, fieldNum, newVal;
    
    // parse name from line
    index = instruct.find('"', 1);
    findName = instruct.substr(1, index - 1);
    instruct = instruct.substr(index + 1);
    
    // parse field number from line
    index = instruct.find(' ', 1);
    fieldNum = instruct.substr(1, index - 1);
    
    // parse new value from line
    newVal = instruct.substr(index + 1);
    
    
    // create traverse pointer to move through list
    Record *traverse;
    
    // intialize traverse to head
    traverse = head;
    
    
    // Loop: while pointer doesn't equal null, loop will move through each node finding which node to edit
    // once the node is found, if the field number equals '1', the function will edit the highscore
    // if the field number equals '2', the function will edit the initials
    // if the field number equals '3', the function will edit the plays.. if plays are edited the revenue
    // will also change in the record
    // once the record is successfully edited, the record will be displayed to the console
    while (traverse != nullptr)
    {
        if (traverse->name.find(findName) != string::npos)
        {
            if (fieldNum == "1") // edit high score
            {
                // convert new value from string to integer
                int value = stoi(newVal);
                
                // edit highscore in node
                traverse->highscore = value;
                
                // display updated record to console
                cout << traverse->name << " UPDATED\n";
                cout << "UPDATE TO high score - VALUE " << value << endl;
                cout << "Name: " << traverse->name << endl;
                cout << "High Score: " << traverse->highscore << endl;
                cout << "Initials: " << traverse->initials << endl;
                cout << "Plays: " << traverse->plays << endl;
                cout << "Revenue: $" << traverse->revenue << endl << endl;
                
                // break out of loop once record is edited
                break;
            }
            else if (fieldNum == "2") // edit initials
            {
                // edit initials in node
                traverse->initials = newVal;
                
                // display updated record to console
                cout << traverse->name << " UPDATED\n";
                cout << "UPDATE TO initials - VALUE " << newVal << endl;
                cout << "Name: " << traverse->name << endl;
                cout << "High Score: " << traverse->highscore << endl;
                cout << "Initials: " << traverse->initials << endl;
                cout << "Plays: " << traverse->plays << endl;
                cout << "Revenue: $" << traverse->revenue << endl << endl;
                
                // break out of loop once record is edited
                break;
            }
            else if (fieldNum == "3") // edit number of plays, which will also change revenue
            {
                // convert new value from string to integer
                int value = stoi(newVal);
                
                // edit plays in node
                traverse->plays = value;
                
                // since plays is edited, revenue will also change in node
                traverse->revenue = value * 0.25;
                
                // display updated record to console
                cout << traverse->name << " UPDATED\n";
                cout << "UPDATE TO plays - VALUE " << newVal << endl;
                cout << "Name: " << traverse->name << endl;
                cout << "High Score: " << traverse->highscore << endl;
                cout << "Initials: " << traverse->initials << endl;
                cout << "Plays: " << traverse->plays << endl;
                cout << "Revenue: $" << traverse->revenue << endl << endl;
                
                // break out of loop once record is edited
                break;
            }
            
        }

        // move to next node in list
        traverse = traverse->next;
    }
    
}


// this function will find record(node) in list and delete the record(node)
/*
    A line read from the batch file is sent to this function to find a record and remove that record from the
    linked list, then delete the node from the program
    The line will contain a name of the game to compared and found with each record's name in each node
    Once the node is located, the function will locate the node that comes before the specified
    node in the list to be able to remove the node from the list by connecting that pointer to the node
    after the specified node for deletion
    Once the record is removed from the list and deleted, the record will be displayed to the console
    Parameters: (line read from batch file, head pointer pointing to the beginning of the list)
 */
void deleteRecord(string instruct, Record *&head)
{
    // create pointer to hold node you want removed
    // and point to head pointer
    Record *hold;
    hold = head;
    
    // pointer to hold previous node of deleting node
    Record *temp;
    temp = head;
    
    // keep track of number of nodes
    int count = 0;
    
    // If list is empty, return function with no changes
    // if list is not empty, find record you want deleted
    // remove it from linked list and then delete
    if (head == nullptr)
    {
        return;
    }
    else
    {
        /* while pointer isn't pointing to a null node, find the record(node) meant to be deleted
           if the node isn't found go to next node in list and increment the count variable (to keep track of
           of the nodes before the node needed for deletion)
           once the node is found, break out of the loop
         */
        while (hold != nullptr)
        {
            if (hold->name.find(instruct) == string::npos)
            {
                // move to next node
                hold = hold->next;
                 
                // increment variable for counting nodes
                count++;
            }
            else
            {
                // break out of loop once correct node is found
                break;
            }
        }
        
        /* If node to be deleted is in middle/end of linked list, loop to find previous node
           loop will move through the nodes using the count variable from previous loop
           to stop at node before the specified node for deletion and remove node
           Otherwise, node to be delted is in the beginning of the linked list,
           move head to the next node and remove node from list
        */
        if (count > 0) // if node needed to be deleted is in middle/end of list
        {
            for (int i = 0; i < count-1; i++)
            {
                // move to next node
                temp = temp->next;
            }
        
            // point a new next pointer to the node after the node specified for deletion
            Record *next = temp->next->next;
            // connect the previous node (before specified node for deletion) to the node after the specified node
            temp->next = next;
            
            // point the pointer's 'next' to null so the specified node can be disconnected
            // from the linked list
            hold->next = nullptr;
            
        }
        else if (count == 0) // if node needed to be deleted is in beginning of list
        {
            // move head pointer to next node, to make new beginning node
            head = hold->next;
            
            // the other pointer on the first node will be removed from list by pointing to NULL
            hold->next = nullptr;
        }
        
        // Before removing nodes information from program, display the records contents to console
        // to show successfull deletion of record
        cout << "RECORD DELETED\n";
        cout << "Name: " << hold->name << endl;
        cout << "High Score: " << hold->highscore << endl;
        cout << "Initials: " << hold->initials << endl;
        cout << "Plays: " << hold->plays << endl;
        cout << "Revenue: $" << hold->revenue << endl << endl;
        
        
        // delete node after removing from list
        delete hold;
    }
 
}


// sorts the records(nodes) in a linked list
/*
    A line from batch file is sent to this function to determine how the records will be sorted
    The records are either sorted by name or plays.
    The function will first find out how many nodes are in the linked list, once that is determined
    2 pointers are made to allow each node in the list to be compared with one another
    If the records are sorted by plays, the function will compare the node's data containing 'plays' with the
    node's data (plays) next to it
    If the records are sorted by name, the function will compare the node's data containing the 'name' with the
    node's data (name) next to it
    For both comaprisons, the function will decide if the node ahead is greater than the next node, if so,
    the node will swap data with the next node.. this will continue until the records are sorted in ascending order.
    Once all records are sorted, the function will display all the records in the list in the same format as the
    database file
 */
void sortRecords(string instruct,Record *&head)
{
    // will find how many records(nodes)are in the linked list
    int count = 0;
    
    // pointer created to move through list
    Record *traverse;
    traverse = head;
    
    // the pointer will move through list in the node and with each loop, the count variable will increment
    // this tells us how many nodes are in the list
    while (traverse != nullptr)
    {
        // count variable, increments by 1 w/ each loop
        count++;
        
        // moves pointer to the next node in list
        traverse = traverse->next;
    }
    
    // 2 pointers created to move though the list and allow each node to be compared with one another
    // both are initialized to NULL
    Record *current;
    current = nullptr;
    
    Record *hold;
    hold = nullptr;
    
    // allow the 2 pointers to start at the beginning of the list be equalling it to the head pointer
    hold = head;
    current = head;

    // if line sent in from batch file equals the word 'plays', the function will sort the records by
    // the amount of plays on the game
    // Otherwise, if the line sent in from the batch file equals the word 'name', the function will sort the
    // records by the name of the game
    if (instruct == "plays") // sort by the amount of plays in the game
    {
        // displat that the records are sorted by plays
        cout << "RECORDS SORTED BY plays" << endl;
        
        // make sure pointer starts at the beginning of the list
        hold = head;
        
        // loop will continue as long as the pointer does not reach the end of the list
        // with each loop there is a nested loop that will deal with the swaps within the nodes
        // the outer loop will allow the nested loop to check that each node is sorted in the correct position
        while (hold != nullptr)
        {
            
            // nested loop will swap the nodes data to allow the plays to be sorted in ascending order
            while (current->next != nullptr)
            {
             
                // if the current node's 'plays' data, the pointer is pointing at is greater than the next nodes
                // 'plays' data, swap all the data in the nodes to allow the greater 'plays' number (the record it is
                // established in) to be near the end of the list
                if (current->plays > current->next->plays)
                {
                    // store the pointers data into variables to be able to swap all data with the next node
                    string name = current->name;
                    long int highScore = current->highscore;
                    string initials = current->initials;
                    long int plays = current->plays;
                    double revenue = current->revenue;

                    // place the next node's data in the current position the pointer is in
                    current->name = current->next->name;
                    current->highscore = current->next->highscore;
                    current->initials = current->next->initials;
                    current->plays = current->next->plays;
                    current->revenue = current->next->revenue;
                    
                    // using the varaibles created in the beginning of loop, store the data the from the node
                    // the pointer was pointing at to the next node
                    current->next->name = name;
                    current->next->highscore = highScore;
                    current->next->initials = initials;
                    current->next->plays = plays;
                    current->next->revenue = revenue;
                }
                // move the pointer to the next node to be compared with the one beside it
                current = current->next;
            }

            // reset the pointer to the beginning of the list, to ensure that the records are sorted correctly
            // looping again and again until all are sorted
            current = head;
            
            // move the pointer to the next node, to allow the outer loop to make sure that all the nodes are checked
            // through the nested loop
            hold = hold->next;
        }
    }
    else if (instruct == "name") // sort by name of the game
    {
        // ensure both pointers start at the beginning of the list
        hold = head;
        current = head;
        
        // display to console that the records are sorted by name
        cout << "RECORDS SORTED BY name" << endl;
        
        // loop will continue as long as the pointer does not reach the end of the list
        // with each loop there is a nested loop that will deal with the swaps within the nodes
        // the outer loop will allow the nested loop to check that each node is sorted in the correct position
        while (hold != nullptr)
        {
            
            // nested loop will swap the nodes data to allow the name of the games to be sorted in ascending order
            while (current->next != nullptr)
            {
                
                // the strings will be compared by their ASCII numbers using relational operations
                // if the current node's name, the pointer is pointing at is greater than the next nodes
                // name, swap all the data in the nodes to allow the greater name ASCII number (the record it is
                // established in) to be near the end of the list
                if (current->name > current->next->name)
                {
                    
                    // store the pointers data into variables to be able to swap all data with the next node
                    string name = current->name;
                    long int highScore = current->highscore;
                    string initials = current->initials;
                    long int plays = current->plays;
                    double revenue = current->revenue;

                    // place the next node's data in the current position the pointer is in
                    current->name = current->next->name;
                    current->highscore = current->next->highscore;
                    current->initials = current->next->initials;
                    current->plays = current->next->plays;
                    current->revenue = current->next->revenue;
                               
                    // using the varaibles created in the beginning of loop, store the data the from the node
                    // the pointer was pointing at to the next node
                    current->next->name = name;
                    current->next->highscore = highScore;
                    current->next->initials = initials;
                    current->next->plays = plays;
                    current->next->revenue = revenue;
                }
                
                // move the pointer to the next node to be compared with the one beside it
                current = current->next;
                
            }
            
            // reset the pointer to the beginning of the list, to ensure that the records are sorted correctly
            // looping again and again until all are sorted
            current = head;
            
            // move the pointer to the next node, to allow the outer loop to make sure that all the nodes are checked
            // through the nested loop
            hold = hold->next;
        }
        
    }

    
    // create pointer to move through list from beginning to end
    Record *display;
    display = head;
    
    
    
    // Once all records are sorted, Loop through and display records to console in the same format as the database file
    // loop will end once the pointer contains NULL
    while (display != nullptr)
    {
        cout << display->name << ", ";
        cout << display->highscore << ", ";
        cout << display->initials << ", ";
        cout << display->plays << ", ";
        cout << "$" << fixed << setprecision(2) << display->revenue << endl;
        
        // move to next node in list
        display = display->next;
    }
    
    // empty line
    cout << endl;
}



// print nodes in list (RECURSIVE)
/*
    This function will recursively read in each line in the linked list and display the record into
    a new database file. head pointer will move through each node, once the head pointer contains a null node
    the function won't call on itself to print any information
    Parameters: (referenced file to write in the records into the new database file, head pointer to
                    move through each node in list)
 */
void print(fstream &newData, Record *&head)
{
    // if list is not empty and the next after head poiner isn't a null pointer
    // print node and call function again with the next node in the argument of function call
    if (head != nullptr)
    {
        // print current node
        newData << head->name << ", ";
        newData << head->highscore << ", ";
        newData << head->initials << ", ";
        newData << head->plays << ", $";
        newData << fixed << setprecision(2) <<  head->revenue << "\n";
        
        // call function for next node in list
        print(newData, head->next);
    }
    
}


