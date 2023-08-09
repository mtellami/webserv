#include "Client.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char **init_env(Request req, std::string path) {
  std::vector<std::string> env_vars;
  if (req.getContentLength().compare(""))
    env_vars.push_back("CONTENT_LENGTH = " + req.getContentLength());
  //    env_vars.push_back("CONTENT_TYPE = " + req.getContentType());
  if (req.get_query().compare(""))
    env_vars.push_back("QUERY_STRING = " + req.get_query());
  env_vars.push_back("REQUEST_METHOD = " + req.get_method());
  env_vars.push_back("SERVER_PROTOCOL = " + req.get_protocol());
  env_vars.push_back("PATH_INFO = " + path);

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

  if (client->done_cgi())
    return;
  client->set_done_cgi(true);
  std::map<std::string, std::string> cgi(
      client->get_cluster().get_conf().loc[loc].cgi);
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

    int pid = fork();
    if (pid < 0)
      std::cerr << "fork() failed!" << std::endl;
    else if (pid == 0) {
      // duping the stdin is needed in order to pass stdin params to script,
      // body is needed first.
      execve(args[0], args, env);
    } else if (pid > 0) {
      // checks on timeouts should be added!!
      waitpid(pid, NULL, WNOHANG);
    }
  }

  // else   -->  that means no bin is available to run the script;
}

// NEED TO ADD:
//   [x]  getters in Client class
//   [x]  a var to check weither the script is running
//   [ ]  fun to keep on track the timeout
//   [ ]  check if we already runned the script
//   [ ] read more on rfc
//   [ ] parse new header
//   [ ]
