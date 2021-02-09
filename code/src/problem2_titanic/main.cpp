////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for Problem 2: Titanic.
/// \author     Georgii Zhulikov
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       01.02.2021
///             This code is for educational purposes of the course "Introduction
///             to programming" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// 1) Define an alias VecStrings for the std::vector<std::string> datatype
/// using the typedef keyword.
///
/// 2) Create a function called toCountSurvived that obtains an input stream
/// object (given by reference) istream& (input.csv), reads the whole file
/// line by line and saves surnames ("Braund; Mr. Owen Harris" will be just
/// "Braund") of survived people from input.csv (Survived column).
/// The function returns data of type VecStrings -- vector of surnames of survivors.
///
/// Use intermediate functions in task 2 to do the following:
/// 2.1) Extract data (surname and whether the person survived or not) from one line of input.
/// 2.2) Extract surname from a string containing full name.
/// 
///
/// 3) Create a function printVec.
/// The function prints the content of the given vector out to the standard output.
/// It should takes a vector as argument by reference and print the value of the 
/// elements as well as their enumeration.
/// 1) Name_1
/// 2) Name_2
/// ...
/// N) Name_n
///
///
///
/// 4) Create a function called getFareForClass that takes an input stream object
/// istream& and an integer number representing class (Pclass, 1 to 3), reads the stream 
/// until the end and returns the mean fare value of people of the given class.
/// The function returns a single value of type double -- the mean fair value.
/// Use at least two intermediate functions in problem 4.
///
///
/// Additional problems
///
/// 5) Create a function called genThreeDigitNumber(const int& randomState).
/// The function returns a random three digit number as std::string.
/// Use:
/// std::mt19937 gen(randomState);
/// std::uniform_int_distribution<int> distr(0,9);
/// int rNum = distr(gen); // random number
///
/// 6) Create a new vector newVec as VecStrings and fill it with random numbers.
/// newVec size should be the same as the size of the vector obtained from toCountSurvived
///
///
///   Workshop 8
///
/// 6) Reverse the vector containing names of surviving passengers using std::reverse.
/// Sort this vector using std::sort
/// Include library <algorithm> to access these functions.
///
/// 7) Implement a function printVecIter that takes two vector iterators as arguments
/// and prints the elements of the underlying vector. The iterators should represent
/// the start and the end of the vector.
///
/// 8) Use a regular iterator and a reverse iterator (.rbegin()) to print the vector 
/// containing survivor names in a straightforward order and in a reverse order
/// with the function printVecIter.
/// 
/// 9) Using the sorted list of surnames find the first and last surname that starts with
/// the letter "H".
/// Create a new vector and use functions std::find and std::copy to copy all surnames
/// starting with "H" into it.
///
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>


/// 1) Define an alias VecStrings for the std::vector<std::string> datatype
/// using the typedef keyword.
//typedef std::vector<std::string> VecStrings;
 // ^ is a keyword which is used when we want to create “another name” (alias) for an existing data type

using VecStrings = std::vector<std::string>;
 // ^ is a keyword which allows to do the same as the typedef does, and even more (a bit more modern approach)

// named constant provinding a text representation of a survived attribute
const std::string SURVIVED_ATTR = "1";


/// 2) Create a function called toCountSurvived that obtains an input stream
/// object (given by reference) istream& (input.csv), reads the whole file
/// line by line and saves surnames ("Braund; Mr. Owen Harris" will be just
/// "Braund") of survived people from input.csv (Survived column).
/// The function returns data of type VecStrings -- vector of surnames of survivors.

VecStrings toCountSurvived(std::istream& istr)
{
    bool skipLine = true;   // the flag indicates whether the current line (read from the file)
                            // is skipped or not. By setting it to true initially, we do skip the
                            // very first line

    VecStrings survivedPassengersSurnames;

    while (istr             // (bool)istr means the the stream is treated as a logical expression (implicitly) that return TRUE whenever the stream IS in a good mood (state), otherwise returns FALSE
                            // works almost like istr.good() except of eofbit flag (and, actually, goodbit flag as well)
           && !istr.eof())  // checks the presence of Enf-of-File flag individually
    {
        std::string curPassenger;      // a string storing the information about current passenger
        //istr >> curPassenger          // we can't use the operator>> to read data containing spaces, because the only prefix before the very first space will be read

        //std::stringstream ss;
        // ss.getline()
             // ^^ ANY_STREAM.getline() deals with unsafe and inconvinient c-string (null-terminated strings), and it's better to use std::getline() instead
             // STREAM.getline() and std::getline() methods ARE NOT the SAME
        std::getline(istr, curPassenger);

        if (skipLine)                   // if we are asked (by whom?) to skip the current line, let's do that
        {
            skipLine = false;           // we have to prevent skipping the further lines, so we need to set the value of this “slipping” flag to FALSE
            continue;                   // go to the next iteration immediately, skipping the rest part of the loop body below this line
        }

        // some operations with the current line
        // what we need to do is to parse the current line considering commas , as a separator

        std::stringstream curPassengerStream(curPassenger);     // here we treat a string as to be a stream, and can apply corresponded operations
        std::string attr;                                       // a string storing a currently read attribute
        std::getline(curPassengerStream, attr, ',');            // https://www.cplusplus.com/reference/string/string/getline/?kw=getline
        // ^^ the very first attribute that is read by the statement above is being skipped, because it represents the passenger's ID, which is not needed for us


        // the second call of getline() extracts the second attribute corresponding to Survived
        std::getline(curPassengerStream, attr, ',');
        bool survived = (attr == SURVIVED_ATTR); //"1";         // if survived attribute is 0, it meanse that the passenger dies in the Titanic crash
                                                                // appearing of "0" means presence of so-called “magic” constant, which must be avoid (use name constants instead)

        std::getline(curPassengerStream, attr, ',');            // skip another attribute, passenger class

        // now we are ready to read the full name of the passenger
        std::getline(curPassengerStream, attr, ',');            //
    }

    return survivedPassengersSurnames;
}







int main ()
{
                                    // e.g. may provide the absolute path
                                    // "/user/liza/..../data/problem2_titanic/titanic.csv"
    const std::string INP_FILE_NAME = "../../data/problem2_titanic/titanic.csv";
    std::ifstream inputFile;
    inputFile.open(INP_FILE_NAME);

    if (!inputFile.is_open())
    {
        std::cerr << "Can't ope the titanic file for reading, bye-bye";
        return 1;           // 1 indicate an abnormal termination of the program
    }

    // if we reach this very line, it means that the file is open correctly
    toCountSurvived(inputFile);     // we put an ifstream object AS an istream object, because any ifstream object IS istream object, but vice versa (the inheritance looks like ifstream --|> istream)


    // if were working with fstream which allows both to read and write, we would need to specify std::ios_base::in flag
    // to “show” that we are aiming to read from the file only
//    std::fstream f;
//    f.open(INP_FILE_NAME, std::ios_base::in);   //



}
