#ifndef CPIPE_H
#define CPIPE_H

#include <string>
#include <vector>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/


// connects to xboard and evaluates the inputs


class CPipe
{
    public:
        CPipe();
        virtual ~CPipe();
        std::string getLastMessage();
		void run();
		
    protected:
		void xboard();
		void protover(std::string version);
		void featureResponse(bool accepted);

    private:
		std::vector <std::string> messageStack;
};

#endif // CPIPE_H
