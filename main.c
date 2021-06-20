//
//  main.c
//  Finance Tracker Corkery
//
//  Created by Gavin Corkery on 12/14/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct financeInput {
    char date[15];
    char place[30];
    char category[15];
    char amount[8];
};

int inputFinanceData(struct financeInput data[]);
void makeReport(int count, struct financeInput data[], float *fooddrinkCat, float *entCat, float *billCat, float *transCat, float *totalAmount, float *totalPercent);
void makeCategory(int count, struct financeInput data[], float *fooddrinkCat, float *entCat, float *billCat, float *transCat, float *totalAmount, float *totalPercent);

int main() {
    int count;
    float fooddrinkCat = 0.0, entCat = 0.0, billCat = 0.0, transCat = 0.0, totalAmount = 0.0, totalPercent = 0.0;
    
    struct financeInput data[8];
    
    
    count = inputFinanceData(data);
    makeCategory(count, data, &fooddrinkCat, &entCat, &billCat, &transCat, &totalAmount, &totalPercent);
    makeReport(count, data, &fooddrinkCat, &entCat, &billCat, &transCat, &totalAmount, &totalPercent);
}

int inputFinanceData(struct financeInput data[])
{
    
    FILE *rp;
    
    rp = fopen("data2.txt", "r");
    
    if (rp == NULL)
    {
        printf("Error reading file... Closing program.");
        exit(0);
    }
    
    int x = 0;
    char line[1000];
    char *sp;
    int count = 0;
    
    while (  fgets(line, 1000, rp) )
    {
        count++;
        
        sp = strtok(line, ",");
        strcpy(data[x].date, sp);
        
        sp = strtok(NULL, ",");
        strcpy(data[x].place, sp);
        
        sp = strtok(NULL, ",");
        strcpy(data[x].category, sp);
        
        sp = strtok(NULL, ",");
        strcpy(data[x].amount, sp);
        
        
         
        x++;
        
        
        if (x == 8)
        {
            break;
        }
        
    }
    fclose(rp);
    return count;
}

void makeCategory(int count, struct financeInput data[], float *fooddrinkCat, float *entCat, float *billCat, float *transCat, float *totalAmount, float *totalPercent)
    {
        int x = 0;
        
        while (x < count)
        {
            if (strcmp(data[x].category, "FoodDrink") == 0)
            {
                *fooddrinkCat = *fooddrinkCat + atof(data[x].amount);
            }
            if (strcmp(data[x].category, "Entertainment") == 0)
            {
                *entCat = *entCat + atof(data[x].amount);
            }
            if (strcmp(data[x].category, "Bill") == 0)
            {
                *billCat = *billCat + atof(data[x].amount);
            }
            if (strcmp(data[x].category, "Transportation") == 0)
            {
                *transCat = *transCat + atof(data[x].amount);
            }
            x++;
        }
        *totalAmount = *transCat + *billCat + *entCat + *fooddrinkCat;
    }

void makeReport(int count, struct financeInput data[], float *fooddrinkCat, float *entCat, float *billCat, float *transCat, float *totalAmount, float *totalPercent)
    {
        FILE *rp;
        int x;
        
        rp = fopen("output.txt", "w");
        
        if (rp == NULL)
        {
            printf("Error writing file... Program ending.");
            exit(0);
        }
        
        fprintf(rp, "\n\t-------------- Transaction List ----------------\n");
        
        for (x = 0; x < count; x++)
        {
            fprintf(rp, "%-5s      %-20s %-15s \t%-2s  \n", data[x].date, data[x].place, data[x].category, data[x].amount);
        }
        
        float billPercent = (*billCat / *totalAmount) * 100;
        float foodPercent = (*fooddrinkCat / *totalAmount) * 100;
        float entPercent = (*entCat / *totalAmount) * 100;
        float transPercent = (*transCat / *totalAmount) * 100;
        
        fprintf(rp, "\n--------Total Spending ---------\n");
        
        fprintf(rp, "\n\nTotal Bills:              $%.2f", *billCat);
        fprintf(rp, "\nBill Percentage:            %.2f", billPercent);
        fprintf(rp, "\n\nTotal Food/Drink:          $%.2f", *fooddrinkCat);
        fprintf(rp, "\nFood/Drink Percent:         %.2f", foodPercent);
        fprintf(rp, "\n\nTotal Entertainment:       $%.2f", *entCat);
        fprintf(rp, "\nEntertainment Percent:      %.2f", entPercent);
        fprintf(rp, "\n\nTotal Transportation:      $%.2f", *transCat);
        fprintf(rp, "\nTransportation Percent:      %.2f", transPercent);
        
        fprintf(rp, "\n-----------------------------------");
        
        fprintf(rp, "\nTotal Spent:               $%.2f", *totalAmount);
        
        fclose(rp);
    }

