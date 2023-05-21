#include "CIntegerGetter.h"

int CIntegerGetter::getFromUser(int min, int max) {
    std::string input;
    int number;

    while (true) {
        std::cout << "Enter an integer between " << min << " and " << max << ": ";
        std::getline(std::cin, input);

        //If end of file is detected, stop the program completely.
        if(std::cin.eof()){
            std::cin.clear();
            throw std::invalid_argument("EOF before exit detected.\n");
        }

        // Create a stringstream to parse the input
        std::stringstream ss(input);

        // Try to extract an integer from the stringstream
        if (ss >> number) {
            // Check if there are any remaining characters after the integer
            char remaining;
            if (ss >> remaining || number < min || number > max) {
                std::cout << "Invalid input. Please enter an integer from "<< min << " to " << max << std::endl;
            } else {
                break;  // Valid integer input, exit the loop
            }
        } else {
            std::cout << "Invalid input. Please enter an integer from "<< min << " to " << max << std::endl;
        }
    }

    return number;
}
