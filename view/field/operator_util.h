#ifndef OPERATORUTIL_H
#define OPERATORUTIL_H

namespace OperatorUtil {
    enum Operator {GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, EQUAL, UNDEFINED};

    template <class T>
    bool compare(Operator, const T&, const T&);
}

template <class T>
bool OperatorUtil::compare(Operator op, const T& t1, const T& t2) {
    switch (op) {
        case GREATER:
            return t1 > t2;
        case GREATER_EQUAL:
            return t1 >= t2;
        case LESS:
            return t1 < t2;
        case LESS_EQUAL:
            return t1 <= t2;
        case EQUAL:
            return t1 == t2;
        case UNDEFINED:
            return true;
    }
    return false;
}

#endif // OPERATORUTIL_H