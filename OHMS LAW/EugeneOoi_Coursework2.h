#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>


void printMenu();

// Helper Functions
int validChoice();

// Circuit operation functions
void createCircuit();
void loadCircuit();
void saveCircuit();
void analyzeCircuit();
void exitMenu();

// Circuit editing/creating functions
struct valueVIR parallelCircuit();
struct valueVIR seriesCircuit();

// Helper Functions
double validDecimal(const char *prompt);   //Ensures user inputs a valid positive decimal number.
int validInteger(const char *prompt);      //Ensures user inputs a valid positive integer.
void listSavedCircuits(const char *path);  //Displays a list of available .cir files in the directory.
void readAndSaveToNewFile(const char *inputFileName, const char *outputFileName);  //Copies contents of one file to another.

// Analysis functions
void reportSeries();   //Analyzes a series circuit. Calculates total resistance, current, voltage drops across each resistor, and power consumption.
void reportParallel(); //Analyzes a parallel circuit. Calculates equivalent resistance, branch currents, and power consumption.

