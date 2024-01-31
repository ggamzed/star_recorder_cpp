#include <iostream>
#include <string>
#include "star_data.h"
#include "llist_star.h"
#include "star.h"
#include <math.h>
#define LIFE_SPAN_OF_THE_SUN 10 // billion
#define MASS_OF_THE_SUN 1 
#define MASS_EXPONENT 2.5



void run_program()
{
    // run_program variables
    llist_star datas(get_file_name()); // Lets user create their own .txt file 
    std::string input_name;
    std::string input_color;
    double input_mass;
    std::string dummy = ""; 
    double input_lifetime;
    int menu_selection;
    
    display_commands();

    do{
        menu_selection = get_menu_selection();
        switch(menu_selection)
        {
            case 1: // add record
                std::cout << "--------------------\n";
                std::cout << "Add a new Record\n";
                input_name = get_name();
                input_color = get_color();
                input_mass = get_mass();
                display_life_time_commands();
                input_lifetime = return_life_time();
                
                datas.add_data(input_name, input_color, input_mass, input_lifetime);
                break;
            case 2: // printf specific record by name
                std::cout << "--------------------\n";
                std::cout << "Printf Record(s) with the same name\n";
                input_name = get_name();
                datas.print_data(input_name);
                break; // end case 2
            case 3: // modify specific record by name
                std::cout << "--------------------\n";
                std::cout << "Modify Record(s) with the same nam\n";
                input_name = get_name();
                input_color = get_color();
                input_mass = get_mass();
                display_life_time_commands();
                input_lifetime = return_life_time();
                datas.modify_data(input_name, input_color, input_mass, input_lifetime); 
                break; // end case 3
            case 4: // print all records
                std::cout << "--------------------\n";
                std::cout << "Printing Records...\n";
                datas.print_all_datas();
                break; // end case 4
            case 5: // delete specific record by name
                std::cout << "--------------------\n";
                std::cout << "Delete Record(s) with the same name\n";
                input_name = get_name();
                datas.delete_data(input_name);
                break; // end case 5
            case 6: // recursively reverse order of linked list
                std::cout << "--------------------\n";
                std::cout << "Reversing the order off all the Records...\n";
                datas.reverse_datas();
                std::cout << "Records have been reversed.\n";
                break; // end case 6
        } 
        if(menu_selection != 7)
        {
            display_commands();
        } 
    } while(menu_selection != 7); 

    return; 
}

void display_commands()
{
    // display commands
    std::cout << "Usage:\n";
    std::cout << "\t1: Add a new Record into the database.\n";
    std::cout << "\t2: Print information about a record using the name as the key. \n";
    std::cout << "\t3: Modify a record in the database using the name as the key. \n";
    std::cout << "\t4: Print all information in the database.\n";
    std::cout << "\t5: Delete an existing record from the database.\n";
	std::cout << "\t6: Reverse the order of all existing records from the database.\n";
    std::cout << "\t7: Quit the program.\n";
    std::cout << "What would you like to do?\n";
    return; 
}

void display_life_time_commands()
{
    std::cout << "Stellar's Life Time:\n";
    std::cout << "\t1: Input life time (billion):\n";
    std::cout << "\t2: Calculate life time (with Star's solar mass): \n";
}

int get_menu_selection()
{
    // get_menu_selection
    int selection = 0;

    std::cin >> selection;
    while(std::cin.fail() || selection < 1 || selection > 7) // while input is not valid
    {
        if(std::cin.fail())
        {
            std::cout << "Your input was not an integer. Please enter an integer: \n";
        }
        else if (selection < 1 || selection > 7)
        {
            std::cout << "Not a valid choice.\n";
            display_commands();
        } // end if std::cin.fail()
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> selection;
    } 
    std::cin.clear(); // clear buffer
    return selection; 
}

std::string get_name()
{
    // get name variables
    std::string name = "";

    std::cin.clear();
    std::cin.ignore(256, '\n'); // before getline 
    std::cout << "Please enter the stellar's name: ";
    std::getline(std::cin, name);
    return name; 
}

std::string get_color()
{
    // get color
    std::string color = "";
    
    std::cout << "Please enter the Star's Color:(enter '$' when you are finished)";
    std::getline(std::cin, color, '$');
    std::cin.clear();
    return color;   
    
}

double get_life_time()
{
    // get lifetime variables
    double life_time = 0.0;

    std::cout << "Please enter the Star's life time (billion): ";
    std::cin >> life_time;
    while(std::cin.fail())  // while input is invalid
    {
        std::cout << "Not an integer, please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> life_time;
    } 
    std::cin.clear();
    std::cin.ignore(256, '\n');
    return life_time; 
}

double get_mass()
{
    // get_mass variables
    double mass = 0;

    std::cout << "Please enter the Star's Solar Mass: ";
    std::cin >> mass;
    while(std::cin.fail())  // while input is invalid
    {
        std::cout << "Not an integer, please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> mass;
    } // end while std::cin.fail()
    std::cin.clear();
    std::cin.ignore(256, '\n');
    return mass; 
}

std::string get_file_name()
{
    std::string file_name = "";
    int count;

    std::cout << "Please enter your file name ('.txt' file extension will be added)";
    std::getline(std::cin, file_name);
    file_name += ".txt";
    return file_name; 
}

double calculate_life_time()
{
    double life_time = 0;

    double mass = get_mass();  // solar mass 
    double masses_ratio = MASS_OF_THE_SUN / mass;
    double result = pow(masses_ratio, MASS_EXPONENT);

    life_time = LIFE_SPAN_OF_THE_SUN * result ;

    // billion
    return life_time;
    
}

int get_life_time_selection()
{
    // get_menu_selection
    int lTselection = 0;

    std::cin >> lTselection;
    while(std::cin.fail() || lTselection < 1 || lTselection > 2) // while input is not valid
    {
        if(std::cin.fail())
        {
            std::cout << "Your input was not an integer. Please enter an integer: \n";
        }
        else if (lTselection < 1 || lTselection > 2)
        {
            std::cout << "Not a valid choice.\n";
            display_commands();
        } // end if std::cin.fail()
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> lTselection;
    } 
    std::cin.clear(); // clear buffer
    return lTselection; 
}

double return_life_time()
{
    
    int life_time_selection = get_life_time_selection();
    double life_time = 0;

    switch(life_time_selection)
    {
        case 1:
            std::cout << "--------------------\n";
            life_time = get_life_time();
            break;
        case 2:
            std::cout << "--------------------\n";
            life_time = calculate_life_time();
            break;
    }

    return life_time;
}
