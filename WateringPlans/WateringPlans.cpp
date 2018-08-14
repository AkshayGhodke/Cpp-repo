//============================================================================
// Name        : WaterPlants.cpp
// Author      : Akshay Dilip Ghodke
// Version     :
// Copyright   : Your copyright notice
// Description : Watering Plants in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	const int UNITS_PER_CAN = 3;
	const string INPUT_FILE_NAME = "counts.txt";

	// Variables

	int number_of_step_units_for_near;

	int number_of_step_units_for_far;

	int x = 0; 								// Variable Count for no. of times that are needed to go to the Faucet

	int temp;								// Temporary variable to keep the track of earlier count of No. of Steps

	int plant_count;

	int current_plant;						// Variable for tracking current Plant No.

	int number_of_steps = 0;

	int water_hold = UNITS_PER_CAN + 1; 	// One more than the Max units of water that the CAN can hold for calculating Water Amount

	int number_of_step_units = 0;

	int faucet_count;						// Fixed Count for no. of times that are needed to go to the Faucet

	// Code for taking input (No. of plants) from the text file

	ifstream input;
	input.open(INPUT_FILE_NAME.c_str());

	if (input.fail())
	{
		cout << "Failed to open " << INPUT_FILE_NAME << endl;

		return -1;
	}

	// Loop for the inputs from the text file

	do
	{
		input >> plant_count;

		if (plant_count > 0)  			// Checking if the input is greater than or equal to 0
		{
			// Calculating No. of rounds to Faucet

			if (plant_count % UNITS_PER_CAN == 0)
			{
				faucet_count = plant_count / UNITS_PER_CAN;
			}
			else
			{
				faucet_count = plant_count / UNITS_PER_CAN + 1;
			}

			// Plan Near

			cout << endl;
			cout << "==========================" << endl;
			cout << " Plan Near with " << plant_count << " plants" << endl;
			cout << "==========================" << endl;
			cout << endl;
			cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
			cout << "---------  ----------  ----------  ---------------" << endl;

			// Initializing variables for Plan near

			current_plant = 0;
			number_of_steps = 0;
			number_of_step_units = 0;
			x = 0;

			// Logic for Plan Near

			while ( x != faucet_count )
			{

				water_hold--;   										// Decrementing the Count for units of Water that CAN can hold

				/* Need to go to the Faucet in two condition:
				   i) The CAN is empty
				  ii) All the plants have been Watered
				*/

				if (water_hold == 0 || current_plant == plant_count)
				{
					temp = number_of_steps;
					number_of_steps = number_of_steps + current_plant;	// Current No. of steps
					number_of_step_units = number_of_step_units + (number_of_steps - temp) * water_hold;   	// Current No. of step-units

					cout << "FAUCET" << setw(11) << number_of_steps << setw(11)	<< water_hold << setw(16) << number_of_step_units << endl;

					x++;												// Incrementing the Faucet count to match the while condition
					water_hold = UNITS_PER_CAN + 1;										// Setting CAN capacity back to Max + 1
				}
				else
				{
					current_plant++;
					temp = number_of_steps;

					if (water_hold != UNITS_PER_CAN)
					{
						number_of_steps++;
					}
					else
					{
						number_of_steps = number_of_steps + current_plant;
					}
					number_of_step_units = number_of_step_units + ((number_of_steps - temp) * water_hold);

					cout << "Plant" << setw(3) << current_plant << setw(9) << number_of_steps << setw(11) << water_hold << setw(16) << number_of_step_units << endl;
				}

			}

			number_of_step_units_for_near = number_of_step_units;

			cout << endl;
			cout << "Plan Near: Total steps = " << number_of_steps << ", total step-units = " << number_of_step_units << endl;

			// Plan Far

			cout << endl;
			cout << "=========================" << endl;
			cout << " Plan Far with " << plant_count << " plants" << endl;
			cout << "=========================" << endl;
			cout << endl;
			cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
			cout << "---------  ----------  ----------  ---------------" << endl;

			// Initializing Variables for Far Plan

			current_plant = plant_count + 1;
			number_of_steps = 0;
			number_of_step_units = 0;
			x = 0;

			// Logic for Plan Far

			while (x != faucet_count)
			{
				water_hold--;

				if (water_hold == 0 || current_plant == 1)
				{
					temp = number_of_steps;
					number_of_steps = number_of_steps + current_plant;
					number_of_step_units = number_of_step_units + ((number_of_steps - temp) * water_hold);

					cout << "FAUCET" << setw(11) << number_of_steps << setw(11) << water_hold << setw(16) << number_of_step_units << endl;

					x++;
					water_hold = UNITS_PER_CAN + 1;
				}
				else
				{
					current_plant --;
					temp = number_of_steps;

					if (water_hold != UNITS_PER_CAN)
					{
						number_of_steps ++;
					}
					else
					{
						number_of_steps = number_of_steps + current_plant;
					}

					number_of_step_units = number_of_step_units	+ (( number_of_steps - temp ) * water_hold);

					cout << "Plant" << setw(3) << current_plant << setw(9) << number_of_steps << setw(11) << water_hold << setw(16) << number_of_step_units << endl;
				}

			}

			number_of_step_units_for_far = number_of_step_units;

			// Logic For Deciding Better plan

			cout << endl;
			cout << "Plan Far: Total steps = " << number_of_steps << ", total step-units = " << number_of_step_units << endl;
			cout << endl;
			cout << "*** With " << plant_count << " plants, ";

			if (number_of_step_units_for_near > number_of_step_units_for_far)
			{
				cout << "Plan Far is better with " << (number_of_step_units_for_near - number_of_step_units_for_far) << " fewer step-units." << endl;
			}
			else if (number_of_step_units_for_near < number_of_step_units_for_far)
			{
				cout << "Plan Near is better with " << (number_of_step_units_for_far - number_of_step_units_for_near) << " fewer step-units." << endl;
			}
			else
			{
				cout << " Both plans are equally better" << endl;
			}
		}

	} while (plant_count > 0);

	return 0;
}
/*Observations : For Can with 3 units Capacity
 * 				 1) Starting from 1 plant we get Both plans as Equally better
 * 				 2) Starting from 2 plants and every third plant from there we get near plan as better by 2 fewer steps
 * 				 3) For all the Finite multiples of 3 the near plan proves to be better by n*2 fewer steps
 * 				 4) For all Number of Plants one more than three's multiple the far plan proves to be better by (n - 1)*2 fewer steps
 *
 * 				 For Can with 4 units Capacity
 * 				 1) For Most inputs Plan Far is better.
 */