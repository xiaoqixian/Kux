
## **Kux**
---
### **Kux is a multi-threads dowoloader**

#### **Run**
Make sure you already have installed gcc/g++ compiler. So you are ale to compile source files by gcc command, don't forget to link pthread lib. If make or cmake tools are installed on your machine, compile source files with them would be much easier.

1. clone this project

2. `mkdir build && cd build`

3. for cmake users, `cmake ..`

4. `make all`

#### Main modules of this project

1. parse url. Parse a http url given by the user, so the downloader can build a request with it. Query string '?'and frament '#' are both not supported.

2. open url and build connection

3. Get resource. When the connection has been established, the downloader send a http request to the server for resource request.

3. Download files with multi-threads to a certain file.

4. Store breakpoint. When some enmergency happens like weak internet connection, downloader need to store the breakpoint so it can continue downloading after the enmergency fixed.

5. download speed monitor

