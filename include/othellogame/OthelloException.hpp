// OthelloException.hpp
//
// ICS 46 Winter 2019
// Project #2: Black and White
//
// An exception that is thrown by OthelloGameState when, for example,
// invalid moves are made.

#ifndef OTHELLOEXCEPTION_HPP
#define OTHELLOEXCEPTION_HPP

#include <string>



class OthelloException
{
public:
    explicit OthelloException(const std::string& reason)
        : reason_{reason}
    {
    }


    std::string reason() const { return reason_; }


private:
    std::string reason_;
};



#endif // OTHELLOEXCEPTION_HPP

