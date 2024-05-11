#ifndef JOIN_HPP
#define JOIN_HPP

#include<iostream>
#include<string>
#include<vector>


class JoinCommand
{
    private:
        
    public:
        JoinCommand();
        ~JoinCommand();
        void JoinConstruction(std::string buffer);
};

JoinCommand::JoinCommand()
{
}

JoinCommand::~JoinCommand()
{
}


#endif