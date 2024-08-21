#pragma once
#include <string>
#include "Date.h"
#include "User.h"

class Admin : public User {
    public:
    //Constructor
    Admin();

    //Destructor
    ~Admin();

    void viewUser();
    void viewCarpool();

};