#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Person.h"

std::vector<std::string> tokenize(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    int start, end;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            tokens.push_back(csvLine.substr(start, end - start));
        else
            tokens.push_back(csvLine.substr(start));
        start = end + 1;
    } while (end != std::string::npos);

    return tokens;
}

std::vector<Person> parseFile(std::string fileName)
{
    // Open the file
    std::ifstream file{fileName};
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    // Vector of Person objects
    std::vector<Person> persons;

    // Parse file line by line
    std::string line;
    std::vector<std::string> tokens;
    while (std::getline(file, line))
    {
        // Tokenize the line
        tokens = tokenize(line, ',');

        // If the line does not have 5 tokens, skip it
        if (tokens.size() != 4)
        {
            std::cout << "Invalid line: " << line << std::endl;
            continue;
        }

        // Declare 5 variables for order book entry
        std::string name;
        int age;
        Gender gender;
        double salary;

        // Try to parse gender
        try
        {
            gender = stringToGender(tokens[2]);
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid gender in line: " << line << std::endl;
            continue;
        }

        // Try to convert the tokens to floats
        try
        {
            age = std::stoi(tokens[1]);
            salary = std::stod(tokens[3]);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Invalid numbers in line: " << line << std::endl;
            continue;
        }

        // Assign the first token to the name
        name = tokens[0];

        Person p{name, age, gender, salary};
        persons.push_back(p);
    }
    file.close();

    return persons;
}

double calculateAverageSalary(const std::vector<Person> &persons)
{
    double sum = 0;
    for (const Person &p : persons)
        sum += p.salary_;
    return sum / persons.size();
}

double calculateAverageAge(const std::vector<Person> &persons)
{
    double sum = 0;
    for (const Person &p : persons)
        sum += p.age_;
    return sum / persons.size();
}

void printPerson(const Person &p)
{
    std::cout << p.name_ << ", " << p.age_ << ", " << (p.gender_ == Gender::male ? "male" : "female") << ", " << p.salary_ << std::endl;
}

void printPersons(const std::vector<Person> &persons)
{
    std::cout << std::endl
              << "All persons: " << std::endl;
    for (const Person &p : persons)
        printPerson(p);

    // Print total persons, average age and average salary
    std::cout << std::endl
              << "Total persons: " << persons.size() << std::endl
              << "Average age: " << calculateAverageAge(persons) << std::endl
              << "Average salary: " << calculateAverageSalary(persons) << std::endl;
}

int main()
{

    // Print all persons (each person on a single line)
    std::vector<Person> persons = parseFile("data/persons.csv");
    printPersons(persons);

    return 0;
}
