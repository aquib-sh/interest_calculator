#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TRUE = 0;
const char *COMPOUND_INTEREST = "compound";
const int CHAR_SIZE = sizeof(char);

unsigned int AMOUNT, DURATION;
float INTEREST_RATE;
char *INTEREST_TYPE;

void 
help(void)
{
   printf("USAGE: interest_calc AMOUNT INTEREST_TYPE INTEREST_RATE DURATION\n\n");
   printf("Example: interest_calc 50000 compound 10 24\n");
   printf("AMOUNT is the numeric amount to calculate interest on\n");
   printf("INTEREST_TYPE can be 'simple' or 'compound'\n");
   printf("INTEREST_RATE is the %% of interest\n");
   printf("DURATION is the duration of interest in months\n");
}

int 
calculate_return(
        unsigned int initial_amount, 
        unsigned int duration, 
        float interest_rate,
        char *interest_type)
{
    unsigned int final_amount = initial_amount;
    float interest = 0;
    float simple_interest = 0;
    const unsigned int cfreq = 12; //compounding frequency in months
    
    // Determine the interest type
    int is_compound = strcmp(interest_type, COMPOUND_INTEREST)==TRUE;

    if (!is_compound) {
        simple_interest = ((interest_rate/100)*initial_amount);
    }

    unsigned int current_month = 1;

    while (current_month <= duration) {
        
        if (current_month % cfreq == 0) {
            // Calculate interest based on if it's compound or simple
            if (is_compound) {
                interest = ((interest_rate/100)*final_amount);
            }
            else {
                interest = simple_interest;
            }

            final_amount += interest;
            printf("Interest at %d months = %.2f total balance = %d\n", current_month, interest, final_amount);
        }
        current_month++;
    }
    return final_amount;
}


int main(int argc, char *argv[])
{
    if (argc < 5) 
    {
        if ((argc == 2) && (strcmp(argv[1], "help")==TRUE)) {
            help();
            return 0;
        }
        printf("Please specify the all the arguments'\n");
        printf("Try 'interest_calc help' for more information\n");
        return 1;
    }

    AMOUNT = atoi(argv[1]);
    INTEREST_TYPE = argv[2];
    INTEREST_RATE = atof(argv[3]);
    DURATION = atoi(argv[4]);

    printf("Calculating return on $%d with %.2f%% %s interest after duration of %d months\n",
            AMOUNT, INTEREST_RATE, INTEREST_TYPE, DURATION);

    int final_amount = calculate_return(AMOUNT, DURATION, INTEREST_RATE, INTEREST_TYPE);
    printf("\nFINAL RETURN = $%d\n", final_amount);

    return 0;
}
