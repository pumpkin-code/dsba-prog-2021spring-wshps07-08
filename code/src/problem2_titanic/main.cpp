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
///     TODO: HW for 11.02.2021 — No. 4
/// 4) Create a function called getFareForClass that takes an input stream object
/// istream& and an integer number representing class (Pclass, 1 to 3), reads the stream 
/// until the end and returns the mean fare value of people of the given class.
/// The function returns a single value of type double -- the mean fair value.
/// Use at least two intermediate functions in problem 4.
///
///
///     TODO: HW for 11.02.2021  — NoNo. 5 and 6
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


// TODO: consider substitution of all “magic constants” (like comma , semicolon ; in the methods below) by named constants


// \r carriage return — a character with a code 13
// \n —  a character with code 10

//typedef std::vector<std::string> VecStrings;
using VecStrings = std::vector<std::string>;


// define some named constants in order to avoid appearing of “magic constants” in the code
//const char SURVIVED_FLAG[] = "1";
const char* SURVIVED_FLAG = "1";


// the prototype (a declaration) of the function must be presented here if we call the
// function prior to define itst body
VecStrings toCountSurvived(std::istream& passengers);


// print the lements of the given vector
// the intention is not only not to change the vector, but also to strictly prohibit
// any possibility of changing the vector, this is why we use const & (MUST BE USED!)
void printVec(const VecStrings& strVec);


int main()
{
    // want to check a correctnes of isSurvived() method
//    std::string surname;
//    bool survStatus = isSurvived("1,0,3,Braund; Mr. Owen Harris,male,22,1,0,A/5 21171,7.25,,S",
//               surname);

//    int a = 0;

    const std::string INP_FILE_NAME = "../../data/problem2_titanic/titanic.csv";
    //const std::string INP_FILE_NAME = "titanic.csv";
    std::ifstream inputFile;           // can read only from the file
    inputFile.open(INP_FILE_NAME);

    // check if the file has been opened correctly
    if (!inputFile.is_open())           // use the inverted logic
    {
        std::cerr << "The titanic file can't be open";
        return 1;                       // return the errorcode that is not eq to 0, which indicates an error situation
    }

    // if we reach this point the file is opened properly
    VecStrings survived = toCountSurvived(inputFile);         // if terms of inheritance ifstream is an extension of istream, anh thus
                                        // ifstream can be passed as an actual parameter whenever we expect istream as a formal parameter
                                        // ifstream --|> istream
    printVec(survived);                 // TODO: HW: reflect call of this function at the UML Sequence Diagram
}



// if we were using a C++ compiler prior to 11-th standard, there would be an
// insufficient copy operations while making a temporary string object
// starting with C++11 this uns. c. is eliminated by the move semnatic
// moreover, there is such an optimization technic. which is used by the
// modern compiler called the Copy Elision Optimization
std::string extractSurname(const std::string& personFullName)
{
    std::stringstream ss(personFullName);
    std::string surname;
    std::getline(ss, surname, ';');

    return surname;
}



/// 2.1) Extract data (surname and whether the person survived or not) from one line of input.
//bool extractNameAndSurv(const std::string& person, std::string& surname)
bool isSurvived(const std::string& person, std::string& surname)
{
    std::stringstream ss(person);
    std::string attrStr;                // here we are going to store extracted attributes

    // skipping the first (PassengerId) attribute
    std::getline(ss, attrStr, ',');     // e.g. attrStr == "1"

    // read the survived attribute
    std::getline(ss, attrStr, ',');
    bool survivedStatus = (attrStr == SURVIVED_FLAG); // "1";

    // skip one more line related to attribute Pclass
    std::getline(ss, attrStr, ',');

    // read the full name
    std::getline(ss, attrStr, ',');     // attrStr consits of "Braund; Mr. Owen Harris"


    // temporary for testing purpose only
    //surname = attrStr;                  // here we actully have the full name
    surname = extractSurname(attrStr);

    return survivedStatus;
}


// if we were using a C++ compiler prior to 11-th standard, there would be an
// insufficient copy operations while making a temporary string object
// starting with C++11 this uns. c. is eliminated by the move semnatic
// moreover, there is such an optimization technic. which is used by the
// modern compiler called the Copy Elision Optimization
//std::string foo()
// the same for a pair std::pair<bool, std::string>
//{

//}



/// 2) Create a function called toCountSurvived that obtains an input stream
/// object (given by reference) istream& (input.csv), reads the whole file
/// line by line and saves surnames ("Braund; Mr. Owen Harris" will be just
/// "Braund") of survived people from input.csv (Survived column).
/// The function returns data of type VecStrings -- vector of surnames of survivors.
VecStrings toCountSurvived(std::istream& passengers)
{
    bool skipLine = true;       // true if one needs to skip

    // only for example
    //bool implicitPassConversion = (bool)passengers;     // now we can convert a stream to a logical value, we to interpret its internal state somehow

    VecStrings survivors;

    while (passengers           //  almost == passengers.good()        // we can convert a steram to a logical expression implicitly, because of the operator bool defined in the std::ios::
           && !passengers.eof())
    {
        // reading regular lines
        std::string passengerInfo;                  // "1,0,3,Braund; Mr. Owen Harris,male,22,1,0,A/5 21171,7.25,,S"
        std::getline(passengers, passengerInfo);    // here we extract another line consisting of info about a single passenger (person)

        if (skipLine)
        {
            skipLine = false;   // prevent skipping all the following lines
            continue;
        }

        // retuse a code snippet from the main() function, where it was used for testing purposes
        // the idea of testing code is not only to test the “correctnes” of a developed function,
        // but also to provide an example of its usage
        std::string surname;
        bool survStatus = isSurvived(passengerInfo, surname);
        if (survStatus)
            survivors.push_back(surname);
    }

    return survivors;                     // TODO: let's return a real vector, now it's a dummy
}

void printVec(const VecStrings& strVec)
{
    // here vector<std::string>::const_reference refer to the proper const string&
    // datatype, and it can be used for sake of convenience (it allows just to
    // mention the VecStrings type alias w/t a need to recollect of what is the
    // real datatype of elements of the given container)
    for (VecStrings::const_reference s : strVec)
    //for (const std::string& s : strVec)             // it's a direct alternative (the type is the same)
        std::cout << s << "\n";
}


