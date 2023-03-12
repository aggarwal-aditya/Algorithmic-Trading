Trading Strategies for NIFTY Data Analysis
==========================================

This project includes the implementation of various trading strategies to analyze NIFTY data from 26th October 2020 to 18th January 2021. The strategies that have been implemented are as follows:

Strategy 1: Bollinger Method
----------------------------

This strategy is based on the Bollinger Bands indicator, which helps to identify potential buying and selling opportunities in the market. The upper and lower bands are drawn around a simple moving average, and when the price crosses the upper or lower band, it is considered to be overbought or oversold, respectively.

Strategy 2: Buy and Hold
---------------

The Buy and Hold strategy involves buying a security and holding it for a long period of time, regardless of market conditions. This project uses the Buy and Hold strategy as a benchmark to compare the performance of other trading strategies.


Strategy 3: EMA Crossover
-------------------------

This strategy is based on the crossover of two exponential moving averages (EMA) with different time periods. A bullish crossover is generated when the shorter EMA crosses above the longer EMA, and a bearish crossover is generated when the shorter EMA crosses below the longer EMA.

Strategy 4: Fixed Stop Loss and Take Profit Percentage
------------------------------------------------------

In this strategy, a fixed percentage is set for the stop loss and take profit levels. When the price reaches the take profit level, the trade is closed, and when it reaches the stop loss level, the trade is also closed. This strategy helps to minimize losses and maximize profits.

Strategy 5: Previous Day High/Low Breakout
------------------------------------------

This strategy involves analyzing the previous day's high and low prices to determine potential buying opportunities. If the price of the current day crosses the high of the previous day, a "Buy" signal is generated, and 10 stocks are bought at that price. The target price is set at the Buy price plus the difference between the previous day's high and low, and the stop loss is set at the Buy price minus one-fourth of the difference between the previous day's high and low. Once the target or stop loss level is reached, the trade is closed, and the signal becomes inactive until another buying opportunity arises.


| Strategy | Profit/Loss | ROI |
| --- | --- | --- |
| Buy and Hold | Rs 2287350 | 19.20% |
| Previous Day High/Low Breakout | Rs 1528400 | 12.83% |
| Fixed Stop Loss (1%) and Take Profit (2%) Percentage | Rs -54801.75 | -0.46% |
| Fixed Stop Loss (1%) and Take Profit (5%) Percentage | Rs 1480599.50 | 12.43% |
| Fixed Stop Loss (1%) and Take Profit (10%) Percentage | Rs 610549.75 | 5.12% |
| Exponential Moving Average Crossover | Rs 499652.34 | 4.20% |
| Bollinger Bands | Rs 3864846.68 | 32.45% |


#Assumptions:

-   The initial investment is considered to be Rs 11,918,000, which is the equivalent of 1000 trades of Nifty stocks at the first tick data price.
-   All profits and losses are calculated based on this initial investment.