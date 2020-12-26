/* GTA Analytics
 * Created by: Christian Tapnio 2020-10-17
 * C program to collect household information for a census bureau which should obtain and
 * analyze household information within the Greater Toronto Area
 * */

#ifndef CHRISTIANTAPNIOASSIGN2_A2FUNCTIONS_H
#define CHRISTIANTAPNIOASSIGN2_A2FUNCTIONS_H
#define RUN 1
#define TOT_ENTRIES 100
#define BUFFER_SIZE 120

enum regions {Peel, York, Durham};
enum towns {Brampton, Mississauga, Maple, Vaughan, Whitby, Oshawa};
enum races { Caucasian, Indigenous, AfricanAmerican, Asian, Other};

typedef struct data {
    enum regions regionName;
    enum towns townName;
    enum races raceName;
    int numberOfPeople;
    int annualIncome;
} household;

//function prototypes
int inputValidator(int min, int max);
int generateRand(int min, int max);

household setHouseholdUser();
household setHouseholdRand();

void householdByRegion(household *data);
void householdByRace(household *data);

void avgHouseholdIncome(household *data);
void avgIncomeByTownRegion(household *data);
void avgIncomeByRace(household *data);

void householdBelowPoverty(household *data);
void householdPovertyByRace(household *data);
void householdPovertyByTownRegion(household *data);
int belowPoverty(household entry);

void printHouseholdData(household *data);

#endif //CHRISTIANTAPNIOASSIGN2_A2FUNCTIONS_H