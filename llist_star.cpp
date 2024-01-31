#include <iostream>
#include <fstream>
#include <string>
#include "star_data.h"
#include "llist_star.h"
#include "star.h"

llist_star::llist_star()
{
    // llist_star default constructor variables
    int records_read = 0;

    // Initialize class variables
    head = NULL;
    file_name = "save.txt";

    records_read = read_file();

    // Print messages for files
    if(records_read < 0)
    {
        std::cout << "'" << file_name << " was not found.\n";
        std::cout << "Therefore, no records have been added to the list and '" << file_name << "'will be created.\n";
    }
    else if(records_read == 0) // else if records_read == 0
    {
        std::cout << "'" << file_name << "' has been found but it is empty\n";
        std::cout << "Therefore, no records have been added to the database\n";
    }
    else // else if records_read > 0
    {
        std::cout << "'" << file_name << "' has been read." << records_read << "records had been added to the database\n";
    }
    std::cout << "--------------------\n";
}

llist_star::llist_star(std::string file)
{
    // llist_star custom constructor variables
    int records_read = 0;

    // Initialize class variables
    head = NULL;
    file_name = file;

    records_read = read_file();

    // Print messages for files
    if(records_read < 0)
    {
        std::cout << "'" << file_name << " was not found.\n";
        std::cout << "Therefore, no records have been added to the list and '" << file_name << "' will be created.\n";
    }
    else if(records_read == 0) // else if records_read == 0
    {
        std::cout << "'" << file_name << "' has been found but is empty.\n";
        std::cout << "Therefore, no records have been added to the database.\n";
    }
    else // else if records_read > 0
    {
        std::cout << "'" << file_name << "' has been read. " << records_read << " records have been added to the database.\n";
    } 
    std::cout << "--------------------\n";
} 

llist_star::~llist_star()
{
    // Deconstructor function calls
    write_file();
    delete_all_records();
} 

int llist_star::read_file()
{
    
    // read_file variables
    std::ifstream read_file(file_name.c_str()); // To read information from file
    struct star_data* temp = NULL;
    struct star_data* curr = NULL;
    struct star_data* prev = NULL;
    int file_char_length = 0;
    int count_data = 0;
    std::string dummy = "";

    // if not open
    if(!read_file.is_open()) 
    {
        read_file.close();
        return -1;
    }

    read_file.seekg(0, read_file.end); // Move read pointer to end of the file
    file_char_length = read_file.tellg(); // Return file pointer position

    // if it is empty
    if(file_char_length == 0) 
    {
        read_file.close();
        return 0;
    } 

    read_file.seekg(0, read_file.beg); // Reset file pointer to beginning

    do{ // do while !read_file.eof()

        // do while temporary variables
        std::string color = "";
        temp = new star_data;
        curr = head;

        std::getline(read_file >> std::ws, temp->name);
        std::getline(read_file, temp->color, '$');
        read_file >> temp->Mass; 
        read_file >> temp->life_time;

        // For not to count empty records
        if(temp->life_time!= 0)
        {
        ++count_data; 
        }

        // To read every record in the file
        while(curr != NULL)
        {
            prev = curr;
            curr = curr->next;
        } 
        if(prev == NULL)
        {
            temp->next = head;
            head = temp;
        }
        else // else if previous != NULL
        {
            prev->next = temp;
            temp->next = curr;
        }  

    } while(!read_file.eof()); 

    read_file.close();
    return count_data; 
    
}

int llist_star::write_file()
{
    // write_file variables
    std::ofstream write_file(file_name.c_str());
    star_data* curr = head;
    int count_data = 0;

    // if database is empty
    if(head == NULL) 
    {
        std::cout << "The database is empty. Therefore, no records have been added to file: " << file_name << '\n';
        write_file.close();
        return -1;
    }  

    do{  // do while curr != NULL
        if(curr->name != ""){
        write_file << curr->name << "\n";
        write_file << curr->color << "$" << "\n";
        write_file << curr->Mass << "\n";

        if(curr->next != NULL)
        {
            // To keep the same format from reading
            write_file << curr->life_time << "\n\n";
        }
        else // else if curr->start == NULL
        {
            // To keep the same format from reading
            write_file << curr->life_time << "\n";
        } 
        ++count_data;
        }
        curr = curr->next;
        
    } while(curr != NULL); 

    std::cout << count_data << " records have been recorded to file: " << file_name << "\n";
    write_file.close();
    return 0; 
}


void llist_star::reverse_datas()
{
    // reverse_datas variables
    struct star_data* prev = NULL;
    struct star_data* curr = head;
    struct star_data* temp = NULL;
    
    while(curr != NULL)
    {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    head = prev;
    
}

void llist_star::delete_all_records()
{
    // delete_all_records variables
    struct star_data* temp = head;
    struct star_data* index = NULL;
    int records_deleted = 0;

    std::cout << "--------------------\n";

    // if database is not empty
    if(head != NULL) 
    {
        while(index != NULL)
        {
            temp = index;
            index = index->next;
            head = index;
            delete temp;
            ++records_deleted;
        } 
        std::cout << records_deleted << " records removed from the memory.\n";
    }
    else // else if head == NULL
    {
        std::cout << "The Database is empty. Therefore, no records have been removed.\n";
    } 

    std::cout << "--------------------\n";
    return; 
}

int llist_star::add_data(std::string input_name, std::string input_color, double input_mass, double input_life_time)
{
    // add_data variables
    struct star_data* newStar;

    newStar = new star_data;
    newStar->name = input_name;
    newStar->color = input_color;
    newStar->Mass = input_mass;
    newStar->life_time = input_life_time;
    newStar->next = NULL;

    // 1. There is no element
    if(head == NULL) 
    {
        head = newStar;
    
        std::cout << "--------------------\n";
        std::cout << "Record has been added.\n";
        std::cout << "--------------------\n";
        
        return 1;
    }

    struct star_data* curr = head;

    // 2. There ara some elements
    while(curr != NULL && curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = newStar;     
   
    std::cout << "--------------------\n";
    std::cout << "Record has been added.\n";
    std::cout << "--------------------\n";
    return 1; 

}

int llist_star::print_data(std::string input_name)
{
    // print_data variables
    struct star_data* curr = head;
    int found_data = 0;
    int datas_pos = 0;

    std::cout << "--------------------\n";

    // if database is empty
    if(head == NULL)
    {
        std::cout << "The database is empty. Therefore, no records of " << input_name << "exist.\n";
        std::cout << "--------------------\n";
        return -1;
    } 

    while(curr != NULL)
    {
        ++datas_pos;
        if(input_name == curr->name)
        {
            ++found_data;
            std::cout << "====================\n";
            std::cout << "Record #" << datas_pos << " of:\n";
            std::cout << "Name: " << curr->name << "\n";
            std::cout << "Color: " << curr->color << '\n';
            std::cout << "Mass: " << curr->Mass << '\n';
            std::cout << "Life Time: " << curr->life_time << '\n';
        } 
        
        curr = curr->next;
    } 

    // if not found
    if(found_data == 0)
    {
        std::cout << "No records of " << input_name << " found.\n";
    }

    // else if found
    else
    {
        std::cout << found_data << " records of " << input_name << " printed." << "\n";
    } 

    std::cout << "--------------------\n";
    return 1; 
}

int llist_star::modify_data(std::string input_name, std::string input_color, double input_mass, double input_lifetime)
{
    // modify_data variables
    struct star_data* curr = head;
    int modified_datas = 0;

    std::cout << "--------------------\n";

    // If database is empty
    if(head == NULL)
    {
        std::cout << "The Database is empty. Therefore, no records of " << input_name << " exist.\n";
        std::cout << "--------------------\n";
        return -1;
    }
    // If not empty, search for the input name
    while(curr != NULL)
    {
        if(input_name == curr->name)
        {
            curr->color = input_color;
            curr->Mass = input_mass;
            curr->life_time = input_lifetime;
            ++modified_datas;
            break; 
        }
        curr = curr->next;
    }
    if(modified_datas == 0)
    {
        std::cout << "No datas of" << input_color << " found.\n";
    }
    else
    {
        std::cout << modified_datas << " records of " << input_name << " records_modified.\n";
    }
    std::cout << "--------------------\n";
    return 1;
    
}

void llist_star::print_all_datas()
{
    // print all records variables
    struct star_data* curr = head;
    int count_data = 0;
    
    std::cout << "--------------------\n";

    // If database is empty
    if(head == NULL)
    {
        std::cout << "The database is empty. Therefore, no records have been printed \n";
        std::cout << "--------------------\n";
        return; 
    } 

    // If not empty print every record till the end
    while(curr != NULL)
    {
        if(curr->Mass != 0.0) // to avoid empty spaces
        { 
        ++count_data;
        std::cout << "====================\n";
        std::cout << "Record #" <<  count_data << '\n';
        std::cout << "Name: " <<  curr->name << '\n';
        std::cout << "Color: " <<  curr->color << '\n';
        std::cout << "Mass: " << curr->Mass << '\n';
        std::cout << "LifeTime: " << curr->life_time << '\n'; 
        }

        curr = curr->next;
    }
    std::cout << count_data << " Records printed. \n";
    std::cout << "--------------------\n";
    return; 
}

int llist_star::delete_data(std::string input_name)
{
    // delete record variables
    struct star_data* curr = head;
    struct star_data* prev = head;
    bool found_deleted_data = false;

    std::cout << "--------------------\n";

    // if list is empty
    if(head == NULL)
    {
        std::cout << "The Database is empty. Therefore, no records of " << input_name << " exist.\n";
        std::cout << "--------------------\n";
        return -1; 
    } 

    // if not empty search for the input name
    while(curr != NULL)
    {
        if(curr->name == input_name)
        {
            found_deleted_data = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    // if not found
    if(!found_deleted_data)
    {
        std::cout << "No records of " << input_name << " found.\n";
        return 1;
    }

    // 1. if it is the first or the only element 
    if(curr == prev)
    {
        head = curr->next;
        delete curr;
        return 1;
    }
    // 2. it is either middle or the last element
    else
    {
        prev->next = curr->next;
        delete curr;
        std::cout << found_deleted_data << " records of " << input_name << " records deleted.\n";
        return 1;
    }
    
}