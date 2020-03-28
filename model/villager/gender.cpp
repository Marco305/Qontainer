#include "gender.h"

Gender::Gender(unsigned int index, const std::string& name) : index_(index), name_(name) {}

bool Gender::operator==(const Gender& gender) const {
    return index_ == gender.index_;
}

bool Gender::operator!=(const Gender& gender) const {
    return !(gender == *this);
}

unsigned int Gender::index() const {
    return index_;
}

std::string Gender::name() const {
    return name_;
}

std::vector<const Gender*> Gender::vector() {
    return std::vector<const Gender*>({&MALE, &FEMALE, &OTHER});
}

const Gender Gender::MALE = Gender(GenderEnum::MALE, "Male");
const Gender Gender::FEMALE = Gender(GenderEnum::FEMALE, "Female");
const Gender Gender::OTHER = Gender(GenderEnum::OTHER, "Other");
