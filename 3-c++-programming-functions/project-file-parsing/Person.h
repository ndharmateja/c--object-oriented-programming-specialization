#include <algorithm>
#include <cctype>
#include <string>

enum class Gender
{
    male,
    female
};

Gender stringToGender(std::string gender)
{
    // Convert gender to lower case
    std::transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    if (gender == "male")
        return Gender::male;
    if (gender == "female")
        return Gender::female;
    throw std::invalid_argument("Invalid gender");
}

class Person
{
public:
    std::string name_;
    int age_;
    Gender gender_;
    double salary_;

    Person(const std::string &name, int age, Gender gender, double salary)
        : name_(name), age_(age), gender_(gender), salary_(salary) {}
};