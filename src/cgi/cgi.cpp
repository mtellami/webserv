#include <unistd.h>
#include "../../include/Request.hpp"
#include "../parse/parsing.hpp"

void cgi_exec(std::string path, locations loc, Request req, char **env)
{
  (void)req;
  int pid = fork();
  size_t pos = path.find_last_of('.');
  if (pos == std::string::npos) {
    std::cerr << "Error: file extension invalid!" << std::endl;
    exit(1);
  }
  std::string extension(path, pos+1, path.length() - pos);
  const char *binary =loc.cgi[extension].c_str();
  char *arg[2];
  strcpy(arg[0], path.c_str());

  arg[1] = NULL;
  if (pid == 0)
  {
    execve(binary, arg ,env);
    std::cerr << "Error: execve failed!" << std::endl;
    exit (EXIT_FAILURE);
  }
  else {

    //wait for child
  }
  
}

 void cgi_exec(std::string file, std::map<std::string, std::string> cgi, Request req)
{
    
  size_t pos = file.find_last_of('.');
  if (pos == std::string::npos)
  {
    std::cerr << "Error: file extension invalid!" << std::endl;
    exit(1);
  }

  int pid = fork();
}
