// Author : Daniyal Ahmed
// Date Started: Sept 16 2017

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib> // for exit() <<<< ????



/*
* Inputs pTMR, pTDY, and pTDY_YSD
*		pTDY and pTDY_YSD are calculated by theoremProbs
*		pTMR is found in the calculation()
* Outputs the final probability of Increase, decrease, or constant price tomorrow
*/
double theorem(double pTMR, double pTDY, double pTDY_YSD)
{
	double pTMR_TDY = ((pTMR * pTDY_YSD) / pTDY);
	return (pTMR_TDY * 100);
}


/**
* Inputs the vector of prices
* Outputs a vector of all the increase decrease constant counters
*/
std::vector<double> counters(std::vector<double> prices)
{
	double inc = 0.00;
	double dec = 0.00;
	double con = 0.00;
	double inc_inc = 0.00;
	double inc_dec = 0.00;
	double inc_con = 0.00;
	double dec_inc = 0.00;
	double dec_dec = 0.00;
	double dec_con = 0.00;
	double con_inc = 0.00;
	double con_dec = 0.00;
	double con_con = 0.00;
	double inc3 = 0.00;
	double inc2dec = 0.00;
	double inc2con = 0.00;



	for (int i = 2; i < prices.size(); i++) {

		if (i == (prices.size() - 1)) {
			if (prices[i] > prices[i - 1]) {
				inc = inc + 1;
			}
			else if (prices[i] < prices[i - 1]) {
				dec = dec + 1;
			}
			else if (prices[i] == prices[i - 1]) {
				con = con + 1;
			}
		}

		if (prices[i - 1] > prices[i - 2]) {
			inc = inc + 1;
			if (prices[i] > prices[i - 1]) {
				inc_inc = inc_inc + 1;
			}
			else if (prices[i] < prices[i - 1]) {
				inc_dec = inc_dec + 1;
			}
			else if (prices[i] == prices[i - 1]) {
				inc_con = inc_con + 1;
			}
		}
		else if (prices[i - 1] < prices[i - 2]) {
			dec = dec + 1;
			if (prices[i] > prices[i - 1]) {
				dec_inc = dec_inc + 1;
			}
			else if (prices[i] < prices[i - 1]) {
				dec_dec = dec_dec + 1;
			}
			else if (prices[i] == prices[i - 1]) {
				dec_con = dec_con + 1;
			}
		}
		else if (prices[i - 1] == prices[i - 2]) {
			con = con + 1;
			if (prices[i] > prices[i - 1]) {
				con_inc = con_inc + 1;
			}
			else if (prices[i] < prices[i - 1]) {
				con_dec = con_dec + 1;
			}
			else if (prices[i] == prices[i - 1]) {
				con_con = con_con + 1;
			}
		}
	
	}

	std::vector<double> countersVector = { inc, dec,con, inc_inc, inc_dec, inc_con, dec_inc, dec_dec, dec_con,
		con_inc, con_dec, con_con };

	return countersVector;
}

/**
* Inputs the vector of counters and number of prices
* Outputs a vector with all the probabilities i.e. pINC, pDEC, pCON
*/
std::vector<double> probabilities(std::vector<double>countersVector, double numofPrices)
{
	double pINC = countersVector[0] / numofPrices;
	double pDEC = countersVector[1] / numofPrices;
	double pCON = countersVector[2] / numofPrices;
	double pINC_INC = countersVector[3] / numofPrices;
	double pINC_DEC = countersVector[4] / numofPrices;
	double pINC_CON = countersVector[5] / numofPrices;
	double pDEC_INC = countersVector[6] / numofPrices;
	double pDEC_DEC = countersVector[7] / numofPrices;
	double pDEC_CON = countersVector[8] / numofPrices;
	double pCON_INC = countersVector[9] / numofPrices;
	double pCON_DEC = countersVector[10] / numofPrices;
	double pCON_CON = countersVector[11] / numofPrices;

	std::vector<double> probabilitiesVector = { pINC,pDEC,pCON,pINC_INC,pINC_DEC,pINC_CON,pDEC_INC, pDEC_DEC,pDEC_CON,
		pCON_INC, pCON_DEC, pCON_CON };

	return probabilitiesVector;
}

/**
* Inputs vector of prices and probabilities
* Outputs vector with pTDY and pTDY_YSD
*/
std::vector<double> theoremProbs(std::vector<double> prices, std::vector<double> probabilitiesVector)
{
	double pTDY_YSD = 0.00;
	double pTDY = 0.00;

	int TDY = prices.size() - 1;
	int YSD = prices.size() - 2;
	int DBY = prices.size() - 3;

	if (prices[TDY] > prices[YSD]) {
		pTDY = probabilitiesVector[0];
		if (prices[YSD] > prices[DBY]) {
			pTDY_YSD = probabilitiesVector[3];
		}
		else if (prices[YSD] < prices[DBY]) {
			pTDY_YSD = probabilitiesVector[4];
		}
		else if (prices[YSD] == prices[DBY]) {
			pTDY_YSD = probabilitiesVector[5];
		}
	}
	else if (prices[TDY] < prices[YSD]) {
		pTDY = probabilitiesVector[1];
		if (prices[YSD] > prices[DBY]) {
			pTDY_YSD = probabilitiesVector[6];
		}
		else if (prices[YSD] < prices[DBY]) {
			pTDY_YSD = probabilitiesVector[7];
		}
		else if (prices[YSD] == prices[DBY]) {
			pTDY_YSD = probabilitiesVector[8];
		}
	}
	else if (prices[TDY] == prices[YSD]) {
		pTDY = probabilitiesVector[2];
		if (prices[YSD] > prices[DBY]) {
			pTDY_YSD = probabilitiesVector[9];
		}
		else if (prices[YSD] < prices[DBY]) {
			pTDY_YSD = probabilitiesVector[10];
		}
		else if (prices[YSD] == prices[DBY]) {
			pTDY_YSD = probabilitiesVector[11];
		}
	}

	std::vector<double> theoremProbsVector = { pTDY, pTDY_YSD };

	return theoremProbsVector;
}

/*
* Inputs vector of prices
* computes magnitude of change using the formula
*		(Sum of Magnitude of Individual Increases) / (Amount of Increases)
*/
int magnitude(std::vector<double> prices)
{
	int count_increase = 0;
	double total_increase = 0.00;
	double avg_increase = 0.00;

	int count_decrease = 0;
	double total_decrease = 0.00;
	double avg_decrease = 0.00;

	int count_constant = 0;
	double total_constant = 0.00;
	double avg_constant = 0.00;

	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] > prices[i - 1]) {
			count_increase = count_increase + 1;
			total_increase = total_increase + (prices[i] - prices[i - 1]);
		}
	}
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] < prices[i - 1]) {
			count_decrease = count_decrease + 1;
			total_decrease = total_decrease + (prices[i] - prices[i - 1]);
		}
	}
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] == prices[i - 1]) {
			count_constant = count_constant + 1;
			total_constant = total_constant + (prices[i] - prices[i - 1]);
		}
	}

	avg_increase = total_increase / count_increase;
	avg_decrease = total_decrease / count_decrease;
	avg_constant = total_constant / count_constant;

	/*
	std::cout << ">>> AVG INC:" << " " << avg_increase << '\n';
	std::cout << ">>> AVG DEC:" << " " << avg_decrease << '\n';
	std::cout << ">>> AVG CON:" << " " << avg_constant << '\n';
	*/
	return 0;
}

/*
* Inputs prices and ticker from main()
* Outputs final probabilities
*/
int calculation(std::vector<double> prices, std::string ticker) {
	double numofPrices = prices.size() - 1.00;

	std::vector<double> countersVector = counters(prices);

	std::vector<double> probabilitiesVector = probabilities(countersVector, numofPrices);
	double pTMRinc = probabilitiesVector[0];
	double pTMRdec = probabilitiesVector[1];
	double pTMRcon = probabilitiesVector[2];

	std::vector<double> theoremProbsVector = theoremProbs(prices, probabilitiesVector);
	double pTDY = theoremProbsVector[0];
	double pTDY_YSD = theoremProbsVector[1];

	double TMR_INC = theorem(pTMRinc, pTDY, pTDY_YSD);
	double TMR_DEC = theorem(pTMRdec, pTDY, pTDY_YSD);
	double TMR_CON = theorem(pTMRcon, pTDY, pTDY_YSD);

	
	std::cout << '\n';
	std::cout << ">>> TICKER: " << ticker << '\n';
	std::cout << '\n';
	std::cout << ">>> Number of Historical Data Entries:" << " " << prices.size() << '\n';
	std::cout << '\n';
	std::cout << ">>> What will happen to the stock price tomorrow?" << '\n';
	std::cout << '\n';
	std::cout << ">>> PROBABILITY OF INCREASE:" << '\n';
	std::cout << ">>> " << TMR_INC << "%" << '\n';
	std::cout << ">>> PROBABILITY OF DECREASE:" << '\n';
	std::cout << ">>> " << TMR_DEC << "%" << '\n';
	std::cout << ">>> PROBABILITY OF REMAINING CONSTANT:" << '\n';
	std::cout << ">>> " << TMR_CON << "%" << '\n';
	std::cout << '\n';
	magnitude(prices);
	std::cout << "|**********************************************************************************************************************| " << '\n';
	

	std::ofstream outFile;

	outFile.open(ticker.append("-prob.csv"));

	outFile << "Prob,Value\n";
	outFile << "Increase," << TMR_INC << '\n';
	outFile << "Decrease," << TMR_DEC << '\n';
	outFile << "Constant," << TMR_CON << '\n';


	outFile.close();

	return 0;
}

/*
* Inputs the name of the csv file
* Outputs a vector of doubles with the prices
*/
std::vector<double> makePrices(std::string fileName)
{
	std::ifstream inf(fileName);

	std::vector<double> pricesVector;

	if (!inf) {
		std::cerr << "Uh oh, the CSV could not be opened for reading!" << std::endl;
		exit(1);
	}
	while (inf)
	{
		std::string temp;
		getline(inf, temp);
		if (temp.size() > 0) {
			double d = std::stod(temp);
			pricesVector.push_back(d);
		}
	}

	return pricesVector;
}

int main()
{
	std::cout << "|**********************************************************************************************************************| " << '\n';
	std::cout << "|******************************************* PROBABILITY ANALYSIS PROTOTYPE *******************************************| " << '\n';
	std::cout << "|**************************************************** BUILD 3.01 ******************************************************| " << '\n';
	std::cout << "|**********************************************************************************************************************| " << '\n';

	std::string ticker;
	std::cout << "Input Ticker: ";
	std::cin >> ticker;
	std::string tempTicker = ticker;
	std::string fileName = tempTicker.append(".csv");

	std::vector<double> prices1 = { 66.46, 66.34, 66.82, 66.37, 66.56, 66.89, 67.80, 68.25, 67.88, 67.80 };
	std::vector<double> prices2 = { 824.00, 815.00, 823.13, 820.92, 825.50, 830.53, 831.73, 832.95, 837.70, 839.77 };

	std::vector<double> prices3 = makePrices(fileName);


	calculation(prices3, ticker);


	std::cout << "|******************************************************** END *********************************************************| " << '\n';
	std::cout << "|**********************************************************************************************************************| " << '\n';

	return 0;
}

