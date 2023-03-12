/*
Name: Aditya Aggarwal
Email: aditya.iitrpr@gmail.com
Contact: 8968972320
*/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define STOP_LOSS_PERCENT 0.01	 // 1%
#define TAKE_PROFIT_PERCENT 0.5 // 5%
#define TRADE_SIZE 1000			 // Number of shares to trade

// Struct to represent a single candlestick
typedef struct
{
	char time[20];
	float open;
	float high;
	float low;
	float close;
} Candlestick;

int main()
{
	// Pointer for reading data from CSV file
	ifstream data;
	// Insert File Path in the below line according to the location of CSV file in your system
	data.open("Dataset.csv");
	// Check if the file opened sucesfully else outpur error on console
	if (!data.is_open())
	{
		cout << "Coudn't Open file" << endl;
	}

	// Read the data into a dynamic array of candlesticks
	vector<Candlestick> candlesticks;
	Candlestick candle;
	char line[100];
	data.getline(line, 100);
	while (data.getline(line, 100))
	{
		sscanf(line, "%[^,],%f,%f,%f,%f", candle.time, &candle.open, &candle.high, &candle.low, &candle.close);
		candlesticks.push_back(candle);
	}
	// Close the file
	data.close();

	// Initialize variables
	int trade_direction = 0; // 0 for no trade, 1 for long, -1 for short
	float trade_price = 0.0;
	float profit = 0;
	int stop_loss = 0;
	int take_profit = 0;

	// Main trading loop
	for (int i = 1; i < candlesticks.size(); i++)
	{
		// Check for trade entry
		if (candlesticks[i].close > candlesticks[i - 1].close && trade_direction == 0)
		{
			// Enter long trade
			trade_direction = 1;
			trade_price = candlesticks[i].close;
			stop_loss = (int)(trade_price * (1 - STOP_LOSS_PERCENT));
			take_profit = (int)(trade_price * (1 + TAKE_PROFIT_PERCENT));
		}
		else if (candlesticks[i].close < candlesticks[i - 1].close && trade_direction == 0)
		{
			// Enter short trade
			trade_direction = -1;
			trade_price = candlesticks[i].close;
			stop_loss = (int)(trade_price * (1 + STOP_LOSS_PERCENT));
			take_profit = (int)(trade_price * (1 - TAKE_PROFIT_PERCENT));
		}

		// Check for trade exit
		if (trade_direction == 1 && candlesticks[i].low < stop_loss)
		{
			// Exit long trade with stop loss
			profit -= TRADE_SIZE * (trade_price - stop_loss);
			trade_direction = 0;
			trade_price = 0.0;
			stop_loss = 0;
			take_profit = 0;
		}
		else if (trade_direction == 1 && candlesticks[i].high > take_profit)
		{
			// Exit long trade with take profit
			profit += TRADE_SIZE * (take_profit - trade_price);
			trade_direction = 0;
			trade_price = 0.0;
			stop_loss = 0;
			take_profit = 0;
		}
		else if (trade_direction == -1 && candlesticks[i].high > stop_loss)
		{
			// Exit short trade with stop loss
			profit -= TRADE_SIZE * (stop_loss - trade_price);
			trade_direction = 0;
			trade_price = 0.0;
			stop_loss = 0;
			take_profit = 0;
		}
		else if (trade_direction == -1 && candlesticks[i].low < take_profit)
		{
			// Exit short trade with take profit
			profit += TRADE_SIZE * (trade_price - take_profit);
			trade_direction = 0;
			trade_price = 0.0;
			stop_loss = 0;
			take_profit = 0;
		}
	}
	// Output final results
	printf("Profit made: Rs%.2f\n", profit);
}