#ifndef GENDER_H
#define GENDER_H

#include <string>
#include <vector>

class Gender {
private:
    const unsigned int index_;
    const std::string name_;

    Gender(unsigned int, const std::string&);

public:
    Gender() = default;

    bool operator==(const Gender&) const;

    bool operator!=(const Gender&) const;

    unsigned int index() const;

    std::string name() const;

    static std::vector<const Gender*> vector();

    static const Gender MALE, FEMALE, OTHER;
};

enum GenderEnum {MALE, FEMALE, OTHER};

#endif // GENDER_H