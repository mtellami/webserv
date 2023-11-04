# <h1 align="center">🌐 ​&nbsp; WEBSERV &nbsp; 🌐​</h1>

# Introduction
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

In the example above there was no message body because GET method usually doesn't include any body.

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
|         GET       |  Retrieve a specific resource or a collection of resources, should not affect the data/resource   |     NO    |
