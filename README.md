# webserv

## STRUCTURE
- Class:
    + 'Server' => the HTTP server (webserv: conatain all +> server blocks, clients )
    + 'Cluster' => server block in the config file
    + 'Client' => conncted client include all his imformation (requested server block, request object, response object) get dropped when finish serving ..
    + 'Request' => contain request information of a client
    + 'Response' => same as request, contain response info

## TODO

- [x] Server creation
- [x] Request parsing
- [x] POST request uploading
- [ ] Response
