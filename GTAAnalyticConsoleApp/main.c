/* GTA Analytics
 * Created by: Christian Tapnio 2020-10-17
 * C program to collect household information for a census bureau which should obtain and
 * analyze household information within the Greater Toronto Area
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "A2Functions.h"

int main() {
    int numberOfEntries;
    int option;
    household data[TOT_ENTRIES];
    srand(time(NULL));
    numberOfEntries = 0;
    //up to 3 entries
    while (numberOfEntries < 3)
    {
        printf("Data entry for household record number %d:\n", numberOfEntries + 1);
        printf("Enter the appropriate number for the region:\nDURHAM (0), PEEL (1), YORK (2)"
               "\nor enter 3 to skip user inputs to generate the rest of the records randomly\n");
        option = inputValidator(0, 3);
        if (option == 3) {
            break;
        }
        data[numberOfEntries++] = setHouseholdUser(option);
    }
    for (; numberOfEntries < TOT_ENTRIES; numberOfEntries++){
        data[numberOfEntries] = setHouseholdRand();
    }
    printHouseholdData(data);

    while (RUN)
    {
        //user menu
        puts("\nMenu:\n1. Households by region"
             "\n2. Households by race"
             "\n3. Average household income"
             "\n4. Average household by town and region"
             "\n5. Average household income by race"
             "\n6. Percentage of households below poverty"
             "\n7. Percentage of households below poverty by race"
             "\n8. Percentage of households below poverty by town and region"
             "\n0. Exit"
             "\nEnter your option: \n");

        option = inputValidator(0, 8);
        switch (option){
            case 0 :
                return 0;
            case 1 :
                householdByRegion(data);
                continue;
            case 2 :
                householdByRace(data);
                continue;
            case 3 :
                avgHouseholdIncome(data);
                continue;
            case 4 :
                avgIncomeByTownRegion(data);
                continue;
            case 5 :
                avgIncomeByRace(data);
                continue;
            case 6 :
                householdBelowPoverty(data);
                continue;
            case 7 :
                householdPovertyByRace(data);
                continue;
            case 8 :
                householdPovertyByTownRegion(data);
                continue;
            default:
                printf("Invalid Option! Please enter the Correct number.\n");
        }

    }//while loop ends here

}
