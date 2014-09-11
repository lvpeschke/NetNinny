# Lab2: Net Ninny

## Questions?
- How to handle 2-3-… word combinations? --> find()
- Forking really necessary? Or threads okay?
- State machine by character to parse the messages?


## Teaching session

### Advice
- use one port per msg on the client side (recv)
- backlog: 10
- if sending failed (check first), send again
- use the header 'Connection: close' and enforce it on HTTP 1.1!

- look at 'Content-type: text' in the response msg before parsing
- only filter urls and text!
- if abusive content found, send 301, then new request for the error page, then forward

### Setup
- Set the browser to 127.0.0.1 + port number
- use port > 1024
- use only IPv4

### Architecture
Server | Client |
---|---|
get GET request + forward response to client | send GET to server + get response|
url filtering | content filtering|


## What needs to be done
#### Martin
* constants
* parse the http: method, url, version, etc.
* object http_request as an abstract object + to_string method 


#### Lena
* starting the client part: entirely separated: get IP of the current interface and send hardcoded message to real server + get response
