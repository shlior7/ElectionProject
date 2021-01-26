#include <exception>
#include <string>
#include <iostream>
#pragma once

class Except : virtual public std::exception {

protected:

    std::string error_message;      ///< Error message

public:
        Except(){}
        Except(const std::string& msg) :
        error_message(msg+"\n")
    {}
    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~Except() = default;

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char* what() const throw () {
        return error_message.c_str();
    }
};


class Not_Found :virtual public Except {

protected:

   // std::string error_message;      ///< Error message

public:

    explicit
    Not_Found(const std::string& msg)
    {
        error_message = msg + " Not Found!";
    }
    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~Not_Found() = default;
    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char* what() const throw () {
        return error_message.c_str();
    }
};


class Already_Exists:virtual public Except {

protected:

    //std::string error_message;      ///< Error message

public:
    explicit
        Already_Exists(const std::string& msg)
    {
        error_message = msg + " Already Exists!";
    }
    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~Already_Exists() = default;

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char* what() const throw () {
        return error_message.c_str();
    }
};


class Added :virtual public Except {

protected:

   // std::string error_message;      ///< Error message

public:

    explicit
        Added(const std::string& msg)
    {
        error_message = msg + " Added Successfully!";
    }
    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~Added() = default;
   /** Returns a pointer to the (constant) error description.
    *  @return A pointer to a const char*. The underlying memory
    *  is in possession of the Except object. Callers must
    *  not attempt to free the memory.
    */
    virtual const char* what() const throw () {
        return error_message.c_str();
    }
};
