/*
Name: Aditya Aggarwal
Email: aditya.iitrpr@gmail.com
Contact: 8968972320
*/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define PERIOD_12 12
#define PERIOD_26 26
#define TRADE_SIZE 1000 // Number of shares to trade

vector<double> calculate_ema(vector<double> prices, int n, int period)
{
	vector<double> ema(n);
	double alpha = 2.0 / (period + 1);
	ema[period - 1] = prices[period - 1];
	for (int i = period; i < n; i++)
	{
		ema[i] = alpha * prices[i] + (1 - alpha) * ema[i - 1];
	}
	return ema;
}

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
	// Declaration of variable like trade_status and high/low for previous days; high_prev_day is populated with 0 and will later be filled according to dataset and simmilarly low_prev_day is poulated with infinity that is 1e+9 and later be modified according to dataset.

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
	vector<double> closes;
	for (int i = 0; i < candlesticks.size(); i++)
	{
		closes.push_back(candlesticks[i].close);
	}
	vector<double> ema12;
	vector<double> ema26;
	ema12 = calculate_ema(closes, closes.size(), PERIOD_12);
	ema26 = calculate_ema(closes, closes.size(), PERIOD_26);

	int position = 0; // 0 for no trade, 1 for long, -1 for short
	double buy_price = 0;
	double profit = 0;
	for (int i = PERIOD_26; i < candlesticks.size(); i++)
	{
		// Long entry signal
		if (ema12[i - 1] < ema26[i - 1] && ema12[i] > ema26[i])
		{
			position = 1;
			buy_price = closes[i];
		}
		// Long exit signal
		else if (ema12[i - 1] > ema26[i - 1] && ema12[i] < ema26[i])
		{
			if (position == 1)
			{
				double sell_price = closes[i];
				profit += TRADE_SIZE * (sell_price - buy_price);
				position = 0;
			}
		}
		// Short entry signal
		else if (ema12[i - 1] > ema26[i - 1] && ema12[i] < ema26[i])
		{
			position = -1;
			buy_price = closes[i];
		}
		// Short exit signal
		else if (ema12[i - 1] < ema26[i - 1] && ema12[i] > ema26[i])
		{
			if (position == -1)
			{
				double sell_price = closes[i];
				profit += TRADE_SIZE * (buy_price - sell_price);
				position = 0;
			}
		}
	}
	printf("Total profit: %f\n", profit);
}
