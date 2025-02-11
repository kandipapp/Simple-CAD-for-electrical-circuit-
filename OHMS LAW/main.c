#include "EugeneOoi_Coursework2.h"

//PLEASE READ THROUGH THE README FILE TO USE THIS PROGRAM
int menu = 1;


int main()
{
    while (menu == 1){
        printMenu();  //Displays menu to the user
        int choice = validChoice() ; // Ensures user input valid option (1-5)
        switch (choice) {
            case 1: createCircuit(); break;  // Define a new circuit, circuit created here are saved to tempCircuit.cir
            case 2: loadCircuit(); break;    // Load a saved circuit data to tempCircuit.cir
            case 3: saveCircuit(); break;    // Save the data of current circuit (tempCircuit.cir) onto another file
            case 4: analyzeCircuit(); break; // Generate a report using the latest data from tempCircuit.cir
            case 5: exitMenu(); break;       // Break out of the loop, menu is no longer display
            default: printf("\nInvalid Input, please insert the correct choice\n");
        }
    }
}
