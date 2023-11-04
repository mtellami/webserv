<div align="center"

# <h1 align="center">🌐 ​&nbsp; WEBSERV &nbsp; 🌐​</h1>
> This project is about writing your own HTTP server
<hr>

</div>

# 📌​​ Introduction
HTTP (Hypertext Transfer Protocol) is a protocol for sending and receiving information over the internet. It is the foundation of the World Wide Web and is used by web browsers and web servers to communicate with each other.

An HTTP web server is a software application that listens for and responds to HTTP requests from clients (such as web browsers). The main purpose of a web server is to host web content and make it available to users over the internet.

HTTP consists of requests and responses. When a client (such as a web browser) wants to retrieve a webpage from a server, it sends an HTTP request to the server. The server then processes the request and sends back an HTTP response.

### 🔶 HTTP Request Format
An HTTP request consists of a request line, headers, and an optional message body. Here is an example of an HTTP request:

```console
  GET /index.html HTTP/1.1
  User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
  Host: www.tutorialspoint.com
  Accept-Language: en-us
  Accept-Encoding: gzip, deflate
  Connection: Keep-Alive
```
The request line consists of three parts: the method, the path, and the HTTP version. The method specifies the action that the client wants to perform, such as GET (to retrieve a resource) or POST (to submit data to the server). The path or URI specifies the location of the resource on the server. The HTTP version indicates the version of the HTTP protocol being used.

Headers contain additional information about the request, such as the hostname of the server, and the type of browser being used.

In the example above there was no message body because the GET method usually doesn't include any body.

### 🔶 HTTP Response Format
An HTTP response also consists of a status line, headers, and an optional message body. Here is an example of an HTTP response:
```console
  HTTP/1.1 200 OK
  Date: Mon, 27 Jul 2023 12:28:53 GMT
  Server: Apache/2.2.14 (Win32)
  Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
  Content-Length: 88
  Content-Type: text/html
  Connection: Closed
```
The status line consists of three parts: the HTTP version, the status code, and the reason phrase. The status code indicates the result of the request, such as 200 OK (successful) or 404 Not Found (resource not found). The reason phrase is a short description of the status code. Following is a very brief summary of what a status code denotes:

```1xx``` indicates an informational message only

```2xx``` indicates success of some kind

```3xx``` redirects the client to another URL

```4xx``` indicates an error on the client's part

```5xx``` indicates an error on the server's part

Headers contain additional information about the response, such as the type and size of the content being returned. The message body contains the actual content of the response, such as the HTML code for a webpage.

### 🔶 HTTP Methods
|       method      |                                   description                                                     |    body   |
|:-----------------:|---------------------------------------------------------------------------------------------------|:---------:|
|       GET         |  Retrieve a specific resource or a collection of resources                                        |    NO     |
|       POST        |  Perform resource-specific processing on the requested content                                    |    YES    |
|       DELETE      |  Removes target resource given by a URI                                                           |    YES    |

#### GET

HTTP GET method is used to read (or retrieve) a representation of a resource. In case of success (or non-error), GET returns a representation of the resource in response body and HTTP response status code of 200 (OK). In an error case, it most often returns a 404 (NOT FOUND) or 400 (BAD REQUEST).

#### POST

HTTP POST method is most often utilized to create new resources. On successful creation, HTTP response code 201 (Created) is returned.

#### DELETE

HTTP DELETE is stright forward. It deletes a resource specified in URI. On successful deletion, it returns HTTP response status code 204 (No Content).

Read more about HTTP methods <a href="https://www.rfc-editor.org/rfc/rfc9110.html">RFC9110#9</a>.1

# 📌​​ Web Server
A basic HTTP web server consists of several components that work together to receive and process HTTP requests from clients and send back responses. Below are the main parts of our webserver.

### 🔶 Server Core
The networking part of a web server that handles TCP connections and performs tasks such as listening for incoming requests and sending back responses. It is responsible for the low-level networking tasks of the web server, such as creating and managing sockets, handling input and output streams, and managing the flow of data between the server and clients.<br/>
IO Multiplexing is a way by which a single thread can serve multiple application requests without compromising on the performance. There could be multiple operations involved in the serving of a client request. These operations can be input/output operations or it could involve processing by the CPU.</br>

### I/O Multiplexing

Every Application request is considered as a File descriptor. It can be a read FD or write FD. A file descriptor is a number that uniquely identifies an open file in a computer’s operating system. It describes a data resource, and how that resource may be accessed. When a program asks to open a file — or another data resource, the kernel, Grants access, Creates an entry in the global file table, provides the software with the location of that entry. At least one file descriptor exists for every open file on the system.</br>
I/O multiplexing is the capability to tell the kernel that we want to be notified if one or more I/O conditions are ready, like input is ready to be read, or descriptor is capable of taking more output.

The I/O multiplexing module monitors multiple FDs at the same time and returns the list of file descriptors that are open and can be served at a particular time. The IO Multiplexing module encapsulates the IO multiplexing functions like select, poll, epoll etc. These functions give information about set of file descriptors that are ready.

### 🔶 Request parsing
The parsing part of a web server refers to the process that is responsible for interpreting and extracting information from HTTP requests. In this web server, the parsing of requests is performed by the HttpRequest class. An HttpRequest object receives an incoming request, parses it, and extracts the relevant information such as the method, path, headers, and message body(if present). If any syntax error was found in the request during parsing, error flags are set and parsing stops. 

### 🔶 Response builder
The response builder is responsible for constructing and formatting the HTTP responses that are sent back to clients in response to their requests. In this web server, the Response class is responsible for building and storing the HTTP response, including the status line, headers, and message body. The response builder may also perform tasks such as setting the appropriate status code and reason phrase based on the result of the request, adding headers to the response to provide additional information about the content or the server, and formatting the message body according to the content type and encoding of the response. For example, if the server receives a request for a webpage from a client, the server will parse the request and pass it to a Response object which will fetch the contents of the webpage and construct the HTTP response with the HTML content in the message body and the appropriate headers, such as the Content-Type and Content-Length headers.

### 🔶 Configuration File
Configuration file is a text file that contains various settings and directives that dictate how the web server should operate. These settings can include things like the port number that the web server should listen on, the location of the web server's root directory, and many other settings.
```console
server
{
  listen      127.0.0.1:8080;
  client_max_body_size 100000000;
  location
  {
    pattern   /;
    limit_except  GET ;
    root    default.d;
    autoindex on;
    index   index.html;
  }
}
```
