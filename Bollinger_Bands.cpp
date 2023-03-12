/*
Name: Aditya Aggarwal
Email: aditya.iitrpr@gmail.com
Contact: 8968972320
*/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define TRADE_SIZE 1000     // Number of shares to trade
#define BOLLINGER_PERIOD 20 // Number of periods to use for Bollinger Bands
#define STOP_LOSS_PERCENT 1 // Stop loss percentage for trades

// Struct to represent a single candlestick
typedef struct
{
	char time[20];
	float open;
	float high;
	float low;
	float close;
} Candlestick;

// Calculate the simple moving average
double sma(vector<double> prices, int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += prices[i];
	}
	return sum / n;
}

// Calculate the standard deviation
double stdev(vector<double> prices, int n)
{
	double sum = 0;
	double average = sma(prices, n);
	for (int i = 0; i < n; i++)
	{
		sum += pow(prices[i] - average, 2);
	}
	return sqrt(sum / n);
}

// Calculate the upper and lower Bollinger Bands
pair<double, double> bollinger_bands(vector<double> prices, int n)
{
	double sma_val = sma(prices, n);
	double stdev_val = stdev(prices, n);
	double upper_band = sma_val + 2 * stdev_val;
	double lower_band = sma_val - 2 * stdev_val;
	return make_pair(upper_band, lower_band);
}

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

	int position = 0;
	double buy_price = 0;
	double profit = 0;
	for (int i = BOLLINGER_PERIOD; i < candlesticks.size(); i++)
	{
		// Calculate the upper and lower Bollinger Bands
		vector<double> prices(closes.begin() + i - BOLLINGER_PERIOD, closes.begin() + i);
		pair<double, double> bands = bollinger_bands(prices, BOLLINGER_PERIOD);

		// Long entry signal
		if (closes[i - 1] < bands.second && closes[i] > bands.second)
		{
			position = 1;
			buy_price = closes[i];
		}
// Long exit signal
		else if (closes[i - 1] > bands.first && closes[i] < bands.first)
		{
			if (position == 1)
			{
				profit += (closes[i] - buy_price) * TRADE_SIZE;
				position = 0;
				buy_price = 0;
			}
		}
// Stop loss
		else if (position == 1 && closes[i] < buy_price * (1 - STOP_LOSS_PERCENT / 100.0))
		{
			profit += (closes[i] - buy_price) * TRADE_SIZE;
			position = 0;
			buy_price = 0;
		}
	}
	printf("Profit made: Rs%.2f\n", profit);
	return 0;
}
