/*
Name: Aditya Aggarwal
Email: aditya.iitrpr@gmail.com
Contact: 8968972320
*/
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define TRADE_SIZE 1000

int main()
{
    //Pointer for reading data from CSV file
    ifstream data;
    //Insert File Path in the below line according to the location of CSV file in your system
    data.open("Dataset.csv");
    //Check if the file opened sucesfully else outpur error on console
    if (!data.is_open())
    {
        cout << "Coudn't Open file" << endl;
    }
    // Declaration of variable like trade_status and high/low for previous days; high_prev_day is populated with 0 and will later be filled according to dataset and simmilarly low_prev_day is poulated with infinity that is 1e+9 and later be modified according to dataset.

    string trade_status = "inactive";
    double high_prev_day = 0;
    double low_prev_day = 1e+9;
    long long stratergy_count = 0;

    //Declaration of variables high/low this day to store current days high low which will updated to prev day high/low on the next day

    double high_this_day = 0;
    double low_this_day = 1e+9;

    //Declaration of total_spent and total_sold to evaluate profits
    double total_spent = 0;
    double total_sold = 0;

    //minute_counter to keep track when the next day comes
    int minute_count = 0;

    //Variable declaration to store buy_price to plan when to execute stratergy 1
    double buy_price;

    //Vector to read each line of data
    vector<string> row;

    //Skipping line 1 of data which contains the names of fields
    string s;
    for (int i = 0; i < 1; i++)
    {
        getline(data, s);
    }

    //Prepopulating the prev_day_high/low with 26th October 2020 data; the variable names are self explanatory
    //The for loop runs for 375 times which is the number of entries in a single day.
    for (int i = 0; i < 375; i++)
    {
        double first_day_open, first_day_high, first_day_low, first_day_close;
        string one_minute_details;
        string each_one_minute_detail;
        row.clear();
        getline(data, one_minute_details);
        //Reading each line of CSV file and splitting it whenver ',' is found and storing in vector
        stringstream s(one_minute_details);
        while (getline(s, each_one_minute_detail, ','))
        {
            row.push_back(each_one_minute_detail);
        }

        //Converting strings to respective float values
        first_day_open = stod(row[1]);
        first_day_high = stod(row[2]);
        first_day_low = stod(row[3]);
        first_day_close = stod(row[4]);

        //Calculating max and min values of first day i.e. 26th October by comparing the current min/max value with each minutes min/max value and updating the record if required
        high_prev_day = fmax(high_prev_day, first_day_high);
        low_prev_day = fmin(low_prev_day, first_day_low);
    }
    //Since Data is not provided 25th October, previous day high is not known for 26th October so I have started the analysis from 27th October taking 26th October as baseline for prev_day_high/low

    //Reading data from file till End of File (EOF)
    while (data.good())
    {

        //Reading Each line of CSV and then splitting it wherever a ',' is encountered and converion of strings to floats/doubles
        string one_minute_details, date_time;
        string each_one_minute_detail;
        double open, high, low, close;
        row.clear();
        getline(data, one_minute_details);
        stringstream s(one_minute_details);
        while (getline(s, each_one_minute_detail, ','))
        {
            row.push_back(each_one_minute_detail);
        }
        open = stod(row[1]);
        high = stod(row[2]);
        low = stod(row[3]);
        close = stod(row[4]);
        date_time = row[0];

        //When date changes to next day set high/low prev day as high/low this day and set high this day as 0  and low this day as 1e+9
        if (minute_count == 375)
        {
            minute_count = 0;
            high_prev_day = high_this_day;
            low_prev_day = low_this_day;
            high_this_day = 0;
            low_this_day = 1e+9;
        }

        //Calculating max and min values of current day by comparing the current min/max value with each minutes min/max value and updating the record if required
        high_this_day = fmax(high, high_this_day);
        low_this_day = fmin(low, low_this_day);

        //Checking if its good time to buy by comparing high of this minute with high of previous day & calculating total spent money to evaluate profits.
        if (trade_status == "inactive" && high > high_prev_day)
        {
            trade_status = "active";
            stratergy_count++;
            total_spent += TRADE_SIZE * close;
            buy_price = close;
            cout << "Stratergy 1 occured at " << date_time << " Status= " << trade_status << endl;
        }

        //Checking for stop loss by comparing low of this minute with buy price, high and low of previous day.
        //Caluating sell price to evaluate profits
        else if (trade_status == "active" && low < buy_price - ((high_prev_day - low_prev_day) / 4.0))
        {
            trade_status = "inactive";
            stratergy_count++;
            total_sold += TRADE_SIZE * close;
            cout << "Stratergy 1 occured at " << date_time << " Status= " << trade_status << " Stop Loss " << endl;
        }


        //Checking if its the right time to sell the stock or should we hold it by comparing high price of this minute and buy price, previous day high/low prices.
        //Calculating the selling price to evaluate profits
        else if (trade_status == "active" && high > buy_price + ((high_prev_day - low_prev_day)))
        {
            trade_status = "inactive";
            stratergy_count++;
            total_sold += TRADE_SIZE * close;
            cout << "Stratergy 1 occured at " << date_time << " Status= " << trade_status << " Sold for profit" << endl;

        }
        //Updating the minute count
        minute_count++;

    }
    //Printing to console the number of times startergy 1 occurs and the net profits for trader
    cout << endl << endl;
    cout << "Stratergy 1 occured for a total of " << stratergy_count << " times , in the given time period" << endl;
    cout << setprecision(20) << "Net Profit made by trader is Rs" << (total_sold / 1.0) - (total_spent / 1.0) << endl;
    if (trade_status == "active")
    {
        cout.precision(20);
        cout << "Trader also holds stocks worth " << buy_price << " which are not sold as of now" << endl;
    }

}

