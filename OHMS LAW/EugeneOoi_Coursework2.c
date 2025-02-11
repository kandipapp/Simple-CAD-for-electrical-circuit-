#include "EugeneOoi_Coursework2.h"

extern int menu;

struct valueVIR{            // a struct that stores the variables need in calculating Series and Parallel circuit
    double voltageValue;
    int N;
    double *resistorValue;
    double resistorTotal;
    double resistorTotalPA;
    int *nodes;
    double *currentBranch ;
    double currentValue;
} Series, Parallel;

struct valueVIR seriesCircuit(){
    struct valueVIR Series;

    Series.voltageValue = validDecimal("\nEnter the value of the Voltage Source: "); //Voltage
    Series.N = validInteger("Enter the number of Resistor: ");                     //Number of Resistor (size of N)

    Series.resistorValue = (double*)malloc(Series.N*sizeof(double));               //Allocate memory (size) for the array of Resistor Value with size of N
    Series.nodes = (int*)malloc((Series.N+1)*sizeof(int));                         //Allocate memory (size) for the array of nodes with size of N

    Series.resistorTotal = 0;

    for (int i=0 ; i<=Series.N ; i++){  // Initialize the number of Nodes, 1,2,3,4,.......
        Series.nodes[i] = i+1;
    }
    for (int i=0 ; i< Series.N ; i++){
        char resistorPrompt[100];
        sprintf(resistorPrompt, "Enter value for Resistor %d: ", i + 1);
        Series.resistorValue[i] = validDecimal(resistorPrompt);    //User inputs the resistor value (element) by sequence in to the array
        Series.resistorTotal += Series.resistorValue[i];           //Total resistance in circuit = Sum of all the elements in the array
    }

    Series.currentValue = (Series.voltageValue)/(Series.resistorTotal);  //Current flowing through circuit = Voltage/Total Resistance
    return Series;              //Return all the variables
}

struct valueVIR parallelCircuit(){
    struct valueVIR Parallel;

    Parallel.voltageValue = validDecimal("\nEnter the value of the Voltage Source: ");  //Voltage
    Parallel.N = validInteger("Enter the number of Resistor: ");                      //Number of Resistor, N

    Parallel.resistorValue = (double*)malloc(Parallel.N*sizeof(double)); //Allocate memory(size)for the array of Resistor Value with size of N
    Parallel.currentBranch = (double*)malloc(Parallel.N*sizeof(double)); //Allocate memory(size) for the array of branch currents with size of N
    Parallel.nodes= (int*)malloc(2*sizeof(int)); //Allocate memory(size)for the array of nodes with size of 2
    // For parallel circuit in this coursework, the total nodes is always 2, so only 2 spaces are allocated for the array to store 2 node values

    Parallel.resistorTotal = 0; // Initializes Equivalent Resistance

    Parallel.nodes[0] = 1;  // Start node
    Parallel.nodes[1] = 2;  // End node

    for (int i=0 ; i<Parallel.N ; i++){
        char resistorPrompt[100];
        sprintf(resistorPrompt, "Enter value for Resistor %d: ", i + 1);

        Parallel.resistorValue[i] = validDecimal(resistorPrompt); //Resistance Value for each resistor in array
        if (Parallel.resistorValue[i] !=  0 ){ //If the denominator is not o
            Parallel.resistorTotal += 1/(Parallel.resistorValue[i]);  //Total Resistance before raising to power of -1
        }else{ // If the denominator is 0, means that the resistance is 0, so it will skip for calculating 1/0
            Parallel.resistorTotal += 0 ;
        }
    }
    Parallel.resistorTotalPA = 1/(Parallel.resistorTotal);        //Total Resistance in Parallel Circuit
    Parallel.currentValue = (Parallel.voltageValue)/(Parallel.resistorTotalPA);

    for (int i=0 ; i<Parallel.N ; i++){
        Parallel.currentBranch[i] = Parallel.voltageValue/Parallel.resistorValue[i];
    }
    return Parallel;
}

void printMenu(){
    printf("\n|-------------------------------------------------------|\n");
    printf("|  Welcome to the CAD software for Electrical Circuit   |\n");
    printf("|   1. Create a Circuit                                 |\n");
    printf("|   2. Load a Circuit                                   |\n");
    printf("|   3. Save current Circuit                             |\n");
    printf("|   4. Analyze and print a Report                       |\n");
    printf("|   5. Exit the Program                                 |\n");
    printf("|-------------------------------------------------------|\n");
}

int validChoice(){
    int option;
    printf("\nPlease select your option (1-5)\n");
    printf("Option: ");
    if (scanf("%d", &option) != 1){
        while (getchar()!= '\n');
        return -1;
    }
    if (option >=1 && option <=5){
        return (option);
    }else{
        while (getchar()!= '\n');
        return -1;
    }
}

double validDecimal(const char *prompt){
    while(true){
        double valueDEC;
        printf("%s", prompt);
        if (scanf("%lf", &valueDEC) != 1){
            while (getchar()!= '\n');   // Clear the input buffer
            printf("Invalid input, please put a valid value\n");
        }else if( valueDEC < 0){
            while (getchar() != '\n');  // Clear the input buffer
            printf("Invalid input, please insert a positive value\n");
        }else{
            return valueDEC;
        }
    }
}

int validInteger(const char *prompt){
    while(true){
        int valueINT;
        printf("%s", prompt);
        if (scanf("%d", &valueINT) != 1){
            while (getchar()!= '\n');   // Clear the input buffer
            printf("Invalid input, please put a valid value\n");
        }else if( valueINT < 0 ){
            while (getchar() != '\n');  // Clear the input buffer
            printf("Invalid input, please put a positive integer\n");
        }else{
            return valueINT;
        }
    }
}

void listSavedCircuits(const char *path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.cir", path);  // Look for .cir files

    hFind = FindFirstFile(searchPath, &findFileData);  // Start searching
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No saved circuits found in '%s'\n", path);
        return;
    }

    printf("Available saved circuits in '%s':\n", path);
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            printf("- %s\n", findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData));  // Find next file

    FindClose(hFind);  // Close the handle
}

void readAndSaveToNewFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return;
    }
    char line[1000];

    while (fgets(line, sizeof(line), inputFile)) {
        fprintf(outputFile, "%s", line);
    }

    fclose(inputFile);  // Close the input file
    fclose(outputFile);  // Close the output file
}

void reportSeries(){
    int firstNode, lastNode;
    double totalResistance =0, totalCurrent =0, powCon, totalVolt=0;
    char garbageLabel[100];

    FILE *analyzeFile = fopen("tempCircuit.cir", "r");
    if (analyzeFile==NULL){
        perror("Error opening file to analyze");
        return;
    }

    fscanf(analyzeFile, "%s", garbageLabel);
    fscanf(analyzeFile, "%s", garbageLabel);

    fscanf(analyzeFile, "%s %d %*s %lf", garbageLabel, &lastNode, &totalVolt);

    int numResistors = lastNode - 1;

    double*voltageDrops = (double*)malloc(numResistors*sizeof(double));
    double*resistorValues = (double*)malloc(numResistors*sizeof(double));
    double *powerConsumptions = (double*)malloc(numResistors*sizeof(double));

    if (voltageDrops == NULL || resistorValues == NULL || powerConsumptions == NULL) {
        perror("Memory allocation failed");  // Use for debugging
        fclose(analyzeFile);
        return;
    }

    for (int i =0; i<numResistors ; i++){
        int startNode, endNode ;
        double resistance;

        fscanf(analyzeFile, "%s %d %d %lf",garbageLabel, &startNode, &endNode, &resistance);

        resistorValues[i] = resistance;     // Store resistance value
        totalResistance += resistance;
    }

    totalCurrent = totalVolt / totalResistance ;

    for (int i = 0; i < numResistors; i++) {
        voltageDrops[i] = totalCurrent * resistorValues[i];
        powerConsumptions[i] = totalCurrent * totalCurrent * resistorValues[i];
    }

    powCon = totalVolt * totalCurrent ;

    printf("\nSeries Circuit Analysis:\n");
    printf("------------------------------------------------------------\n");
    printf("| Resistor | Resistance (Ohms) | Voltage Drop (V) | Power (W) |\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < numResistors; i++) {
        printf("| R%-8d | %-17.2lf | %-15.2lf | %-8.2lf |\n", i + 1, resistorValues[i], voltageDrops[i], powerConsumptions[i]);
    }
    printf("------------------------------------------------------------\n");
    printf("Total Voltage: %.2lf V\n", totalVolt);
    printf("Total Resistance: %.2lf Ohms\n", totalResistance);
    printf("Total Current: %.2lf A\n", totalCurrent);
    printf("Total Power Consumption: %.2lf W\n", powCon);

    free(voltageDrops);
    free(resistorValues);
    free(powerConsumptions);

    fclose(analyzeFile);
}

void reportParallel(){
    int firstNode, lastNode;
    double totalResistance =0, voltageDrops, powCon, totalVolt=0, sumReciprocals=0;
    char garbageLabel[100];

    FILE *analyzeFile = fopen("tempCircuit.cir", "r");
    if (analyzeFile==NULL){
        perror("Error opening file to analyze");
        return;
    }

    fscanf(analyzeFile, "%s", garbageLabel);
    fscanf(analyzeFile, "%s", garbageLabel);

    fscanf(analyzeFile, "%s %d %*s %lf", garbageLabel, &lastNode, &totalVolt);

    int numResistors = 0;
    while (fscanf(analyzeFile, "%s", garbageLabel)==1){
        if (strcmp(garbageLabel, "END")==0){
            break;
        }
        numResistors++;
        fscanf(analyzeFile, "%*[^\n]");
    }

    double *branchCurrents = (double*)malloc(numResistors*sizeof(double));
    double*resistorValues = (double*)malloc(numResistors*sizeof(double));
    double*powerConsumptions = (double*)malloc(numResistors*sizeof(double));

    if (branchCurrents == NULL || resistorValues == NULL || powerConsumptions == NULL) {
        perror("Memory allocation failed"); //Use for debugging
        fclose(analyzeFile);
        return;
    }

    rewind(analyzeFile);
    fscanf(analyzeFile, "%s", garbageLabel);  // Skip "START"
    fscanf(analyzeFile, "%s", garbageLabel);  // Skip "PARALLEL"
    fscanf(analyzeFile, "%s %d %*s %lf", garbageLabel, &lastNode, &totalVolt);

    for (int i =0; i<numResistors ; i++){
        int startNode, endNode ;
        double resistance;

        fscanf(analyzeFile, "%s %d %d %lf",garbageLabel, &startNode, &endNode, &resistance);

        resistorValues[i] = resistance;     // Store resistance value
        sumReciprocals += 1.0/resistorValues[i];
    }

    totalResistance = 1.0/sumReciprocals ;


    for (int i = 0; i < numResistors; i++) {
        branchCurrents[i] = totalVolt / resistorValues[i];
        powerConsumptions[i] = branchCurrents[i] * branchCurrents[i] * resistorValues[i] ;
    }

    powCon = totalVolt * totalVolt * (1.0/totalResistance);

    // Print Report
    printf("\nParallel Circuit Analysis:\n");
    printf("------------------------------------------------------------\n");
    printf("| Resistor | Resistance (Ohms) | Branch Current (A) | Power (W) |\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < numResistors; i++) {
        printf("| R%-8d | %-17.2lf | %-18.2lf | %-8.2lf |\n", i + 1, resistorValues[i], branchCurrents[i], powerConsumptions[i]);
    }
    printf("------------------------------------------------------------\n");
    printf("Total Voltage: %.2lf V\n", totalVolt);
    printf("Total Resistance: %.2lf Ohms\n", totalResistance);
    printf("Total Power Consumption: %.2lf W\n", powCon);

    free(branchCurrents);
    free(resistorValues);
    free(powerConsumptions);

    fclose(analyzeFile);
}

void createCircuit(){
    char circuitType[100];

    FILE * temporaryFile = fopen("tempCircuit.cir", "w");
    if (temporaryFile == NULL) {
        printf("Error: Could not create file.\n");
        return;
    }

    fprintf(temporaryFile, "START\n");

    printf("\nCreating a Circuit.................................................\n");
    printf("Would you like a series or a parallel circuit ?\n");
    printf("[SERIES/PARALLEL] ? : ");
    scanf("%99s", circuitType);

    while (true){
        if ( strcmp(circuitType, "SERIES")==0 ){
            Series = seriesCircuit();

            fprintf(temporaryFile, "SERIES\n");
            fprintf(temporaryFile, "V_%d %d DC %.2lf\n", Series.nodes[0], Series.nodes[Series.N], Series.voltageValue);

            for (int i = 0; i < Series.N; i++) {
                fprintf(temporaryFile, "R%d %d %d %.2lf\n", i + 1, Series.nodes[i], Series.nodes[i + 1], Series.resistorValue[i]);
            }

            free(Series.resistorValue); //Free the memory for resistorValue array
            free(Series.nodes);         //Free the memory for nodes array

            fprintf(temporaryFile, "END\n");
            fclose(temporaryFile);

            printf("\nVoltage Source Value : %.2lf Volts\n", Series.voltageValue);
            printf("Equivalent Resistance: %.2lf Ohms\n", Series.resistorTotal);
            printf("Current              : %.2lf Amps\n", Series.currentValue);
            break;

        } else if( strcmp(circuitType, "PARALLEL")==0 ){
            Parallel = parallelCircuit();

            fprintf(temporaryFile, "PARALLEL\n");
            fprintf(temporaryFile, "V_%d %d DC %.2lf\n", Parallel.nodes[0], Parallel.nodes[1], Parallel.voltageValue);

            for (int i = 0; i < Parallel.N; i++) {
                fprintf(temporaryFile, "R%d %d %d %.2lf\n", i + 1, Parallel.nodes[0], Parallel.nodes[1], Parallel.resistorValue[i]);
            }

            free(Parallel.resistorValue); //Free the memory for resistorValue array
            free(Parallel.nodes);         //Free the memory for nodes array
            free(Parallel.currentBranch); //Free the memory for currentBranch array

            fprintf(temporaryFile, "END\n");
            fclose(temporaryFile);

            printf("\nVoltage Source Value : %.2lf Volts\n", Parallel.voltageValue);
            printf("Equivalent Resistance: %.2lf Ohms\n", Parallel.resistorTotalPA);
            printf("Equivalent Current   : %.2lf Amps\n", Parallel.currentValue);
            break;

        } else {
            printf("Invalid input, please enter \"SERIES\" or \"PARALLEL\": ");
            while (getchar() != '\n');
            scanf("%99s", circuitType);
        }
    }
}

void loadCircuit(){
    char fileName[1000];
    printf("Loading a Circuit..........................\n");

    //Path for the folder that stores all the .cir files
    //Editor need to put their folder path for folder that stores all the .cir files
    char folderPath[MAX_PATH] = "C:\\Users\\eugen\\OneDrive\\Desktop\\EugeneOoi_Coursework2";  //<-------Put your folder path here
    listSavedCircuits(folderPath);             // List all .cir files in the folder

    printf("Please type your circuit file name to open the circuit file: ");
    scanf("%s", fileName);
    readAndSaveToNewFile(fileName, "tempCircuit.cir");
}

void saveCircuit(){
     char fileSaveName[10000];
     char fileNewName[10000];

     printf("Saving Circuit..................\n");
     printf("Type in your circuit name or use a default name\n");
     printf("Name (or type DEFAULT) : ");
     scanf("%s", fileSaveName);


     if (strcmp(fileSaveName, "DEFAULT")== 0){
        //Open the tempCircuit file to read data so that the default name of file can be based on the data
        //This can generate different default file name for different circuits
        FILE *inputFile = fopen("tempCircuit.cir", "r");

        char circuitType[50];
        char voltageType[50];
        double voltageValue;
        char resistorDetails[50000] = "";  // To accumulate resistor details
        char line[1000];

         while (fgets(line, sizeof(line), inputFile)) {
            if (strstr(line, "START")) {
                continue;  // Skip the START line
            }
            if (strstr(line, "SERIES") || strstr(line, "PARALLEL")) {
                sscanf(line, "%s", circuitType);  // Extract circuit type
            } else if (strstr(line, "V_")) {
                sscanf(line, "%*s %*d %*s %lf", &voltageValue);  // Extract voltage value
                sscanf(line, "%*s %*d %s", voltageType);         // Extract voltage type (e.g., DC)
            } else if (strstr(line, "R")) {
                char resistor[50];
                double resistance;
                sscanf(line, "%s %*d %*d %lf", resistor, &resistance);
                char resistorSnippet[50];
                snprintf(resistorSnippet, sizeof(resistorSnippet), "%s%.0lf", resistor, resistance);
                strcat(resistorDetails, resistorSnippet);  // Append resistor details
            }
        }
        fclose(inputFile);
        snprintf(fileNewName, sizeof(fileNewName), "%s%s%.2lf%s.cir",circuitType, voltageType, voltageValue, resistorDetails);
     }else{
        snprintf(fileNewName, sizeof(fileNewName), "%s.cir", fileSaveName);
     }

     printf("Saving to file: %s\n", fileNewName);
     readAndSaveToNewFile("tempCircuit.cir", fileNewName);
}

void analyzeCircuit(){
     char typeCircuit[10000] ; // Buffer for circuit type input
     printf("Analyzing circuit......................................\n");
     printf("Please specify the type of circuit (series or parallel)\n");
     printf("[SERIES/PARALLEL] : ");
     while (true) {
        if (scanf("%s", typeCircuit) == 1) {
            // Convert input to uppercase for case-insensitive comparison
            for (int i = 0; typeCircuit[i] != '\0'; i++) {
                typeCircuit[i] = toupper(typeCircuit[i]);
            }
            // Check for valid circuit type
            if (strcmp(typeCircuit, "SERIES") == 0) {
                reportSeries();
                return;  // Exit after processing
            } else if (strcmp(typeCircuit, "PARALLEL") == 0) {
                reportParallel();
                return;  // Exit after processing
            }
        }

        // If input is invalid, prompt again
        while (getchar() != '\n');  // Clear input buffer
        printf("Invalid Input, please enter the type of circuit [SERIES/PARALLEL] : ");
    }
}

void exitMenu(){
     printf("Exiting the program....................................................");
     menu = 0;
}
