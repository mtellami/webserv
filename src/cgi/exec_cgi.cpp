#include "Client.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char **init_env(Request req, std::string path) {
  std::vector<std::string> env_vars;
  if (req.getContentLength().compare(""))
    env_vars.push_back("CONTENT_LENGTH=" + req.getContentLength());
  //    env_vars.push_back("CONTENT_TYPE = " + req.getContentType());
  if (req.get_query().compare(""))
    env_vars.push_back("QUERY_STRING=" + req.get_query());
  env_vars.push_back("REQUEST_METHOD=" + req.get_method());
  env_vars.push_back("SERVER_PROTOCOL=" + req.get_protocol());
  env_vars.push_back("PATH_INFO=" + path);

  // allocate extra space for var that should be added later and set them to
  // null;
  char **env = new char *[env_vars.size() + 1];
  for (size_t i = 0; i < env_vars.size(); i++) {
    env[i] = new char[env_vars[i].length() + 1];
    strcpy(env[i], env_vars[i].c_str());
  }
  env[env_vars.size()] = NULL;
  return env;
}

void cgi_exec(std::string path, Client *client, int loc) {

  if (!client->done_cgi())
  {}
  client->set_done_cgi(true);
  std::map<std::string, std::string> cgi(client->get_cluster().get_conf().loc[loc].cgi);
  size_t pos = path.find_last_of(".");
  while (pos < path.length() && path[pos] != '/')
    pos++;
  std::string full_path(path, 0, pos);
  char **env = init_env(client->get_req(), full_path);
  // get cgi binary to run script based on script's extension
  pos = full_path.find_last_of(".");
  std::string key(full_path, pos + 1, full_path.length() - pos);

  //  if (client.get_cluster().get_conf().location[loc].cgi[key].length())
  if (cgi[key].length()) {
    char **args = new char *[3];
    args[0] = new char[cgi[key].length() + 1];
    args[1] = new char[full_path.length() + 1];
    strcpy(args[0], cgi[key].c_str());
    strcpy(args[1], full_path.c_str());
    args[2] = NULL;
    //creating an output file
//    manually naming the file is pointless, there may be more than one script running at the same time
    int file = open("resp.html", O_CREAT | O_RDWR, 0777);

    client->pid = fork();
    if (client->pid < 0)
      std::cerr << "fork() failed!" << std::endl;
    else if (client->pid == 0) {
      // duping the stdin is needed in order to pass stdin params to script,
      dup2(file, 1);
      // body is needed first.
      execve(args[0], args, env);
    } else if (client->pid > 0) {
      // checks on timeouts should be added!!
      waitpid(client->pid, &client->stats, WNOHANG);
    }
  }

  if (!waitpid(client->pid, &client->stats, WNOHANG))
    std::cerr << "still running" << std::endl;
  if (WIFEXITED(client->stats))
    std::cout << "succeful exit" << std::endl;
  //setting cgi as done cuz we left the child
  //parsing the head from file 
  //parse_cgi_file(file, )
  std::cout << "==++--=-  " << env[0] << std::endl;
  std::cout << "==++--=-  " << env[1] << std::endl;
  // else   -->  that means no bin is available to run the script;
}

// NEED TO ADD:
//   [x]  getters in Client class
//   [x]  a var to check weither the script is running
//   [ ]  check if we already runned the script
//   [x] read more on rfc
//   [ ] parse new header
//   [ ]
//
//    CGI RESPONSE FORM:
//    message-header (one or more header fields )
//    \n (blank line)
//    Body (may be NULL )
//
//
//    script must return one of three options, we will go for *returning a document response*
//    
