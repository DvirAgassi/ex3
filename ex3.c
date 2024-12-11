/******************
Name: Dvir Agassi
ID: 215786328
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

// struct to get the best brand (ex3)
typedef struct BestBrand{
    int brand_num;
    int brand_sales;
} BestBrand;

// struct to get the best type (ex)
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

void add_one(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

void add_all(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

int added_all(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

void get_stats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

BestBrand best_brand(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

BestType best_type(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

int sales_total(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

void print_sales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

void give_insights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

void check_deltas(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

// a variable to find what is the next available day
int next_available_day = 0;

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
     // use the function to make all values in the array to -1
    initialize_minus_one(cube);
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                // add one brand to cube
                add_one(cube);
                break;
            case addAll:
                // add all brands to cube
                add_all(cube);
                break;
            case stats:
                // get the stats from the cube
                get_stats(cube);
                break;
            case print:
                // print all sells
                print_sales(cube);
                break;
            case insights:
                // print best sellers
                give_insights(cube);
                break;
            case deltas:
                // print the average between days
                check_deltas(cube);
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
    // make all the cells -1
  for (int i = 0; i < DAYS_IN_YEAR; i++) {
      for (int j = 0; j < NUM_OF_BRANDS; j++) {
        for (int k = 0; k < NUM_OF_TYPES; k++) {
          cube[i][j][k] = -1;
        }
      }
    }
}

void add_one(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int brand_name;
    int types[NUM_OF_TYPES];
    // get the brand num and all the sales for types
    int result = scanf("%d %d %d %d %d", &brand_name, &types[0], &types[1], &types[2], &types[3]);
    while (result != 5 || (brand_name < 0 || brand_name > NUM_OF_BRANDS)) {
      while(getchar() != '\n');
      printf("This brand is not valid\n");
      break;
    }
    
    int type_place = 0; // if you entered a brand it means you have a type as well, so just a random type to see if the place is not -1
    // check if there is already info in this day for this brand
    if (cube[next_available_day][brand_name][type_place] != -1) {
      printf("This brand is not valid\n");
    }
    else {
      // enter this brand to the cube in the next available day
      for (int i = 0; i < NUM_OF_TYPES; i++) {
        cube[next_available_day][brand_name][i] = types[i];
      }
    }
}

void add_all(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
  int type_place = 0; // if you entered a brand it means you have a type as well, so just a random type to see if the place is not -1
    // do this loop until you entered all the brands for that day
  while (!added_all(cube)) {
    printf("No data for brands ");
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
      if (cube[next_available_day][i][type_place] == -1)
        printf("%s ", brands[i]);
    }
    printf("\nPlease complete the data\n");

      // add the brand
    add_one(cube);
  }
    // you entered all the brands for the day so you can move forward to the next day
  next_available_day++;
}

int added_all(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
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
  // return if all the brands has info for that day
  return all_added;
}

void get_stats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    printf("What day would you like to analyze?\n");
    int day;
    scanf("%d", &day);
    // check if the day is too low/high or invalid (has -1 inside)
    while (!(day > 0 && day <= 365) || cube[day-1][0][0] == -1) {
        printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
        scanf("%d", &day);
    }
    printf("In day number %d:\n", day);
    // get the anount of total sales
    int total = sales_total(day-1, cube);
    printf("The sales total was %d\n", total);
    // get the best brand (needs both the name and the amount so I made it a struct)
    BestBrand b_b = best_brand(day-1, cube);
    printf("The best sold brand with %d sales was %s\n", b_b.brand_sales, brands[b_b.brand_num]);
    // get the best type (needs both the name and the amount so I made it a struct)
    BestType b_t = best_type(day-1, cube);
    printf("The best sold type with %d sales was %s\n", b_t.type_sales, types[b_t.type_num]);
}

BestBrand best_brand(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    BestBrand b_b = {0, 0};
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        int count = 0;
        // make the count the sum of sales for that brand
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (cube[day][i][j] != -1) {
                count += cube[day][i][j];
            }
        }
        // check if the sum of that brand is better from the last one, if yes, make it the best one for now
        if (count > b_b.brand_sales) {
            b_b.brand_num = i;
            b_b.brand_sales = count;      
        }
    }
    // return the best brand
    return b_b;
}

BestType best_type(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    BestType b_t = {0, 0};
    int types[NUM_OF_TYPES] = {0};

    // make the array that each place has the sum of all types that day
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (cube[day][i][j] != -1) {
                types[j] += cube[day][i][j];
            }
        }
    }

    // check for the type with most sum
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (types[i] > b_t.type_sales) {
            b_t.type_num = i;
            b_t.type_sales = types[i];        
        }
    }

    // return best type
    return b_t;
}

int sales_total(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    // check for total of susm that day
    int total = 0;
    
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            total += cube[day][i][j];
        }
    }

    return total;
}

void print_sales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    // print the sales for all the cube array
    printf("*****************************************\n\n");
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Sales for %s:\n", brands[i]);
        for (int j = 0; j < next_available_day; j++) {
            printf("Day %d- ", j+1);
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                printf("%s: ", types[k]);
                printf("%d ", cube[j][i][k]);
            }
            printf("\n");
        }
    }
    printf("\n*****************************************\n");
}

void give_insights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int check_brands[NUM_OF_BRANDS] = {0};
    int check_types[NUM_OF_TYPES] = {0};
    int check_days[DAYS_IN_YEAR] = {0};
    int best_brand = 0, best_type = 0, best_day = 0;

    // check every cell in the cube and enter the info into the arrays we created
    for (int i = 0; i < next_available_day; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                if (cube[i][j][k] != -1) {
                    check_brands[j] += cube[i][j][k];
                    check_types[k] += cube[i][j][k];
                    check_days[i] += cube[i][j][k];
                }
            }
        }
    }
    
    // find brand with most sales
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (check_brands[i] > check_brands[best_brand]) {
            best_brand = i;
        }
    }
    
    // find type with most sales
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (check_types[i] > check_types[best_type]) {
            best_type = i;
        }
    }

    // find day with most sales
    for (int i = 0; i < next_available_day; i++) {
        if (check_days[i] > check_days[best_day]) {
            best_day = i;
        }
    }

    printf("The best-selling brand overall is %s: %d$\n", brands[best_brand], check_brands[best_brand]);
    printf("The best-selling type of car is %s: %d$\n", types[best_type], check_types[best_type]);
    printf("The most profitable day was day number %d: %d$\n", best_day + 1, check_days[best_day]);
}

void check_deltas(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int check_brands[DAYS_IN_YEAR][NUM_OF_BRANDS] = {0};
    int sum_change_brands[DAYS_IN_YEAR][NUM_OF_BRANDS] = {0};
    float average_brand[NUM_OF_BRANDS] = {0};

    // enter the check_brands the amount we got every day from each brand
    for (int i = 0; i < next_available_day; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                if (cube[i][j][k] != -1) {
                    check_brands[i][j] += cube[i][j][k];
                }
            }
        }
    }
    
    // enter the sum_brands the change we got every day between this day and the day after it
    for (int i = 0; i < next_available_day - 1; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            sum_change_brands[i][j] = check_brands[i + 1][j] - check_brands[i][j];
        }
    }
    
    // calculate the average
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < next_available_day - 1; j++) {
            average_brand[i] += sum_change_brands[j][i];
        }
        average_brand[i] /= (next_available_day - 1);
    }

    // print the amounts (floats)
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Brand: %s, Average Delta: %f\n", brands[i], average_brand[i]);
    }
}
