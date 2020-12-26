/* GTA Analytics
 * Created by: Christian Tapnio 2020-10-17
 * C program to collect household information for a census bureau which should obtain and
 * analyze household information within the Greater Toronto Area
 * */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "A2Functions.h"

//Used for out of range inputs
int inputValidator(int min, int max) {
    int value;
    while (RUN){
        if (scanf(" %d", &value) == 1 && value >= min && value <= max) {
            return value;
        } else if (value == 9) {
            exit(1);
        } else {
            printf("Invalid data. You should enter one integer in the range of %d "
                   "to %d or enter 9 to exit. Try again\n", min, max);
        }
    }
}//inputValidator function ends

//function for generating the random inputs ranging from min to max
int generateRand(int min, int max) {
    int result;
    result = (rand() % (max - min + 1)) + min;
    return result;
}//generateRand function ends

//function for setting one household record
household setHouseholdUser(int choice) {
    household data;
    int hNumber = 0;
    int hIncome = 0;
    char buffer[BUFFER_SIZE];
    int ctr = 0;
    //setting region name
    if (choice == 0) {
        data.regionName = Durham;
    } else if (choice == 1) {
        data.regionName = Peel;
    } else if (choice == 2) {
        data.regionName = York;
    } // end of region if

    //setting town name based on selected region
    if (data.regionName == Peel) {
        puts("Enter the appropriate number for the town:\nMississauga (1), Brampton (0): ");
        choice = inputValidator(0, 1);
        if (choice == 0) {
            data.townName = Mississauga;
        } else if (choice == 1) {
            data.townName = Brampton;
        }
    } else if (data.regionName == York) {
        printf("Enter appropriate number for town:\nMaple (0), Vaughan (1): ");
        choice = inputValidator(0, 1);
        if (choice == 0) {
            data.townName = Maple;
        } else {
            data.townName = Vaughan;
        }
    } else if (data.regionName == Durham) {
        printf("Enter appropriate number for town:\nWhitby (0), Oshawa (1): ");
        choice = inputValidator(0, 1);

        if (choice == 0) {
            data.townName = Whitby;
        } else {
            data.townName = Oshawa;
        }
    }

    //Set race based on user input
    printf("Enter appropriate number for race:\nCaucasian (0), Indigenous (1), "
           "African American (2), Asian (3), Other (4): ");
    choice = inputValidator(0, 4);
    if (choice == 0) {
        data.raceName = Caucasian;
    } else if (choice == 1) {
        data.raceName = Indigenous;
    } else if (choice == 2) {
        data.raceName = AfricanAmerican;
    } else if (choice == 3) {
        data.raceName = Asian;
    } else if (choice == 4) {
        data.raceName = Other;
    }

    //set household size and income based on user input
    printf("Enter family(household) size and total annual income (to the nearest hundred) separated by space/tab: \n");
    while (ctr != 2) {
        fgets(buffer, sizeof(buffer), stdin);
        ctr = sscanf(buffer, "%d%d", &hNumber, &hIncome);

        if (hNumber < 0 || hIncome < 0 || hNumber > INT_MAX || hIncome > INT_MAX){
            puts("Try again");
            continue;
        }

    }
    data.numberOfPeople = hNumber;
    data.annualIncome = hIncome;

    return data;

}//setHouseholdUser function ends

//function for randomly generated household record
household setHouseholdRand() {
    household randomData;
    //randomly generated numbers from genarateRand as basis for setting random data
    randomData.regionName = generateRand(0, 2);
    if (randomData.regionName == Peel) {
        randomData.townName = generateRand(0, 4);
    } else if (randomData.regionName == York) {
        randomData.townName = generateRand(5, 9);
    } else if (randomData.regionName == Durham) {
        randomData.townName = generateRand(10, 15);
    }
    randomData.raceName = generateRand(0, 4);
    randomData.numberOfPeople = generateRand(1, 10);
    randomData.annualIncome = generateRand(1, 100000);

    return randomData;

}//setHouseholdRand function ends


//function for displaying total household by region
void householdByRegion(household *data) {
    int ctr[3];
    int i;
    for (i = 0; i < 3; i++){
        ctr[i] = 0;
    }
    for (i = 0; i < TOT_ENTRIES; i++){
        ctr[data[i].regionName]++;
    }
    printf("\nHouseholds by Region\n");
    printf("Household in Peel Region: %d\n", ctr[0]);
    printf("Household in York Region: %d\n", ctr[1]);
    printf("Household in Durham Region: %d\n", ctr[2]);
}//householdByRegion function ends




//This function for displaying number of households by race
void householdByRace(household *data) {
    int counter[5];
    for (int ctr = 0; ctr < 5; ctr++){
        counter[ctr] = 0;
    }
    for (int dex = 0; dex < TOT_ENTRIES; dex++){
        counter[data[dex].raceName]++;
    }
    printf("\nHouseholds by Race\n");
    printf("Caucasian: %d\n", counter[0]);
    printf("Indigenous: %d\n", counter[1]);
    printf("African American: %d\n", counter[2]);
    printf("Asian: %d\n", counter[3]);
    printf("Other: %d\n", counter[4]);
}//householdByRace function ends



//function for displaying average household income
void avgHouseholdIncome(household *data) {
    int averageIncome = 0;
    for (int dex = 0; dex < TOT_ENTRIES; dex++){
        averageIncome += data[dex].annualIncome;
    }
    printf("\nAverage Income\n");
    printf("Average household income: %d\n", averageIncome / TOT_ENTRIES);
}//avgHouseholdIncome function ends



//function for displaying average household income by region
void avgIncomeByTownRegion(household *data) {

    float totalTowns[6] = {0};//6 given towns
    float counter[6] = {0};//counter for each town name
    for (int j = 0; j < TOT_ENTRIES; j++) {
        totalTowns[data[j].townName] += (float)data[j].annualIncome;
        counter[data[j].townName]++;
    }
    float brampton = totalTowns[0] / counter[0];
    float mississauga = totalTowns[1] / counter[1];
    float maple = totalTowns[2] / counter[2];
    float vaughan = totalTowns[3] / counter[3];
    float whitby = totalTowns[4] / counter[4];
    float oshawa = totalTowns[5] / counter[5];

    puts("\nPeel Region:\n");
    printf("Average annual income of Brampton: %.2f\n", brampton);
    printf("Average annual income of Mississauga: %.2f\n", mississauga);

    puts("York Region:\n");
    printf("Average annual income of Maple: %.2f\n", maple);
    printf("Average annual income of Vaughan: %.2f\n", vaughan);

    puts("Durham Region:\n");
    printf("Average annual income of Whitby: %.2f\n", whitby);
    printf("Average annual income of Oshawa: %.2f\n", oshawa);

}//avgIncomeByTownRegion function ends

//function for displaying average household income by Race
void avgIncomeByRace(household *data) {
    int totalRace[5];//5 given races
    int counter[5];
    for (int i = 0; i < 5; i++) {
        totalRace[i] = 0;
        counter[i] = 0;
    }
    for (int i = 0; i < TOT_ENTRIES; i++) {
        totalRace[data[i].raceName] += data[i].annualIncome;
        counter[data[i].raceName]++;
    }

    int caucasians = (totalRace[0] / counter[0]);
    int indigenous = (totalRace[1] / counter[1]);
    int americans = (totalRace[2] / counter[2]);
    int asians = (totalRace[3] / counter[3]);
    int others = (totalRace[4] / counter[4]);

    printf("\nAverage income by Race\n");
    printf("Average annual income of Caucasians: %d\n", caucasians);
    printf("Average annual income of Indigenous: %d\n", indigenous);
    printf("Average annual income of African Americans: %d\n", americans);
    printf("Average annual income of Asians: %d\n", asians);
    printf("Average annual income of Others: %d\n", others);

}//avgIncomeByRace ends here

//function for household poverty indication
int belowPoverty(household entry) {
    /* return CONDITIONS:
     * household == 1 && annual income < 15000,
     * household == 2 && annual income < 20000,
     * household == 3 && annual income < 25000,
     * household == 4 && annual income < 30000,
     * household == 5 && annual income < 40000
     */
    return (
            (entry.numberOfPeople == 1 && entry.annualIncome < 15000)
            || (entry.numberOfPeople == 2 && entry.annualIncome < 20000)
            || (entry.numberOfPeople == 3 && entry.annualIncome < 25000)
            || (entry.numberOfPeople == 4 && entry.annualIncome < 30000)
            || (entry.numberOfPeople >= 5 && entry.annualIncome < 40000)

    );
}//belowPoverty Function ends here

//This function calculate the percentage of household below poverty
void householdBelowPoverty(household *data) {
    double cntBelowPoverty = 0;
    for (int dex = 0; dex < TOT_ENTRIES; dex++){
        if (belowPoverty(data[dex])){
            cntBelowPoverty++;
        }
    }
    double percentage = cntBelowPoverty / TOT_ENTRIES * 100;
    printf("\nPercentage Household below Poverty\n");
    printf("Number of households below poverty line are: %.2f%%\n", percentage);
}//householdBelowPoverty ends here


//function for calculating percentage of household below poverty by race
void householdPovertyByRace(household *data) {
    double countBelowPoverty[5];
    int counter[5];
    for (int dex = 0; dex < 5; dex++) {
        countBelowPoverty[dex] = 0;
        counter[dex] = 0;
    }
    for (int cnt = 0; cnt < TOT_ENTRIES; cnt++) {
        if (belowPoverty(data[cnt])){
            countBelowPoverty[data[cnt].raceName]++;
        }
        counter[data[cnt].raceName]++;
    }
    double caucasians = countBelowPoverty[0] / counter[0] * 100;
    double indigenous = countBelowPoverty[1] / counter[1] * 100;
    double americans = countBelowPoverty[2] / counter[2] * 100;
    double asians = countBelowPoverty[3] / counter[3] * 100;
    double others = countBelowPoverty[4] / counter[4] * 100;

    printf("\nPercentage Households below poverty by Race:\n");
    printf("Households below poverty line of Caucasians: %.2f%%\n", caucasians);
    printf("Households below poverty line of Indigenous: %.2f%%\n", indigenous);
    printf("Households below poverty line of African Americans: %.2f%%\n", americans);
    printf("Households below poverty line of Asians: %.2f%%\n", asians);
    printf("Households below poverty line of Others: %.2f%%\n", others);

}//householdPovertyByRace ends here

//function for calculating percentage of below poverty line by town and region
void householdPovertyByTownRegion(household *data) {
    double countBelowPoverty[6];
    int ctr[6];
    for (int dex = 0; dex < 6; dex++) {
        countBelowPoverty[dex] = 0;
        ctr[dex] = 0;
    }
    for (int dex = 0; dex < TOT_ENTRIES; dex++) {
        if (belowPoverty(data[dex])){
            countBelowPoverty[data[dex].townName]++;
        }
        ctr[data[dex].townName]++;
    }
    double brampton = countBelowPoverty[0] / ctr[0] * 100;
    double mississauga = countBelowPoverty[1] / ctr[1] * 100;
    double maple = countBelowPoverty[2] / ctr[2] * 100;
    double vaughan = countBelowPoverty[3] / ctr[3] * 100;
    double whitby = countBelowPoverty[4] / ctr[4] * 100;
    double oshawa = countBelowPoverty[5] / ctr[5] * 100;

    printf("\nNumber of household below poverty by Town and Region\n");
    printf("\nPeel Region\n");
    printf("Number of households below poverty line of Brampton: %.2f%%\n", brampton);
    printf("Number of households below poverty line of Mississauga: %.2f%%\n", mississauga);

    printf("\nYork Region\n");
    printf("Number of households below poverty line of Maple: %.2f%%\n", maple);
    printf("Number of households below poverty line of Vaughan: %.2f%%\n", vaughan);

    printf("\nDurham Region\n");
    printf("Number of households below poverty line of Whitby: %.2f%%\n", whitby);
    printf("Number of households below poverty line of Oshawa: %.2f%%\n", oshawa);

}//householdPovertyByTownRegion function ends here


//print function for household data
void printHouseholdData(household *data) {
    printf("\nHousehold Data for Census\n\n");
    printf("%5s%15s%15s%15s%19s%19s\n", "Number", "Income", "FamilySize", "Race", "Region", "Town");
    for (int i = 0; i < TOT_ENTRIES; i++) {
        printf("%5d%15d%10d", i + 1, data[i].annualIncome, data[i].numberOfPeople);

        if (data[i].raceName == Caucasian) {
            printf("%20s", "Caucasian");
        } else if (data[i].raceName == Indigenous) {
            printf("%20s", "Indigenous");
        } else if (data[i].raceName == AfricanAmerican) {
            printf("%20s", "African American");
        } else if (data[i].raceName == Asian) {
            printf("%20s", "Asian");
        } else if (data[i].raceName == Other) {
            printf("%20s", "Other");
        }

        if (data[i].regionName == Durham) {
            printf("%20s", "Durham");
        } else if (data[i].regionName == Peel) {
            printf("%20s", "Peel");
        } else if (data[i].regionName == York) {
            printf("%20s", "York");
        }

        if (data[i].regionName == Whitby) {
            printf("%20s", "Whitby");
        }
        if (data[i].regionName == Brampton) {
            printf("%20s", "Brampton");
        }
        if (data[i].regionName == Mississauga) {
            printf("%20s", "Mississauga");
        }
        if (data[i].regionName == Vaughan) {
            printf("%20s", "Vaughan");
        }
        if (data[i].regionName == Oshawa) {
            printf("%20s", "Oshawa");
        }
        if (data[i].regionName == Maple) {
            printf("%20s", "Maple");
        }

        printf("\n");

    }

}//printHouseholdData function ends here