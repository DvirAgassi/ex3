/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

typedef struct BestBrand{
    int brand_num;
    int brand_sales;
} BestBrand;

typedef struct BestType{
    int type_num;
    int type_sales;
} BestType;

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void initialize_minus_one(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

int max(int a, int b);

void add_one(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

void add_all(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

int added_all(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

int next_available_day = 0;

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    initialize_minus_one(cube); // use the function to make all values in the array to -1
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                add_one(days, cube);
                break;
            case addAll:
                add_all(days, cube);
                break;
            case stats:
                break;
            case print:
                break;
            case insights:
                break;
            case deltas:
                break;
            case done:
                break;
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


void initialize_minus_one(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
  for (int i = 0; i < DAYS_IN_YEAR; i++) {
      for (int j = 0; j < NUM_OF_BRANDS; j++) {
        for (int k = 0; k < NUM_OF_TYPES; k++) {
          cube[i][j][k] = -1;
        }
      }
    }
}

// find the max num func
int max(int a, int b) {
    return (a > b) ? a : b;
}

void add_one(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int brand_name;
    int types[NUM_OF_TYPES];
    int result = scanf("%d %d %d %d %d", &brand_name, &types[0], &types[1], &types[2], &types[3]);
    while (result != 5 || (brand_name < 0 || brand_name > NUM_OF_BRANDS)) {
      while(getchar() != '\n');
      printf("This brand is not valid\n");
      result = scanf("%d %d %d %d %d", &brand_name, &types[0], &types[1], &types[2], &types[3]);
    }
    
    int type_place = 0; // if you entered a brand it means you have a type as well, so just a random type to see if the place is not -1
    // check if there is already info in this day for this brand
    if (cube[next_available_day][brand_name][type_place] != -1) {
      printf("This brand is not valid\n");
    }
    else {
      days[brand_name] = next_available_day;
      for (int i = 0; i < NUM_OF_TYPES; i++) {
        cube[next_available_day][brand_name][i] = types[i];
      }
    }
}

void add_all(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
  int type_place = 0; // if you entered a brand it means you have a type as well, so just a random type to see if the place is not -1
  while (added_all(days, cube)) {
    printf("No data for brands ");
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
      if (cube[next_available_day][i][type_place] == -1)
        printf("%s ", brands[i]);
    }
    printf("\nPlease complete the data\n");
    
    add_one(days, cube);
  }
  next_available_day++;
}

int added_all(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
  // check if all the brands in next_available_day have info inside to see if you put everything already
  int all_added = 0;
  int type_place = 0; // if you entered a brand it means you have a type as well, so just a random type to see if the place is not -1
  for (int i = 0; i < NUM_OF_BRANDS; i++) {
    if (cube[next_available_day][i][type_place] == -1)
      break;
    // it will get inside only if all the brands are not -1 on that day anymore
    if (i + 1 == NUM_OF_BRANDS && cube[next_available_day][i][type_place] != -1) {
      all_added = 1;
    }
  }
}

void get_stats(int days[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    printf("What day would you like to analyze?");
    int day;
    scanf("%d", &day);
    while (!(day >= 0 && day < 365)) {
        printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
        scanf("%d", &day);
    }
    printf("In day number %d:\n", day);
    int total = sales_total(day, cube);
    printf("The sales total was %d:\n", total);
    BestBrand b_b = best_brand(day, cube);
    printf("The best sold brand with %d sales was %d\n", b_b.brand_sales, b_b.brand_num);
    BestType b_t = best_brand(day, cube);
    printf("The best sold brand with %d sales was %d\n", b_t.type_sales, b_t.type_num);
}

BestBrand best_brand(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    BestBrand b_b = {0, 0};
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        int count = 0;
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (cube[day][i][j] != -1) {
                count += cube[day][i][j];
            }
        }
        if (count > b_b.brand_sales) {
            b_b.brand_num = i;
            b_b.brand_sales = count;      
        }
    }
    return b_b;
}

BestType best_type(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    BestType b_t = {0, 0};
    int types[NUM_OF_TYPES] = {0};

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (cube[day][i][j] != -1) {
                types[j] += cube[day][i][j];
            }
        }
    }

    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (types[i] > b_t.type_sales) {
            b_t.type_num = i;
            b_t.type_sales = types[i];        
        }
    }

    return b_t;
}

int sales_total(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int total = 0;
    
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            total += cube[day][i][j];
        }
    }

    return total;
}
