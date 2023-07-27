#ifndef CONF_HPP
#define CONF_HPP

#include <iostream>
#include <string> 
#include <cstdlib>  

class conf 
{
  private:
    std::string _name;

  public:
    conf()
    {
      std::cout << "Class created!!" << std::endl;
    };
    ~conf()
    {
      std::cout << "Class destroyed !" << std::endl;
   };
    std::string pub;
};

void  getConf(char *str, class conf& config);
void  getConf(char *str);

#endif
