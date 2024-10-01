# SimpleServerClient

This C++ project demonstrates a simple client-server file transfer using Boost.Asio for networking. The server sends a file (`response.txt`) to connected clients, which save it with a unique timestamp.

## Features

- Multi-threaded server that handles multiple client connections.
- Client that receives the file and saves it with a unique name.
- Uses Boost.Asio for TCP connections.
- CMake-based build system.

## Requirements

- C++17 or higher
- CMake 3.10 or higher
- Boost libraries (specifically `Boost::system`)

## Project Structure

- `server.cpp`: Implements the multi-threaded server.
- `client.cpp`: Implements the client.
- `response.txt`: Sample file sent from the server to the client.
- `CMakeLists.txt`: CMake configuration for building the project.

## Building the Project

1. Clone the repository:

```bash
git clone -b TCP_Server https://github.com/Bohdanperl/SimpleServerClient.git
cd SimpleServerClient
```
2. Create a build directory and navigate to it:

```bash
mkdir build
cd build
```
3. Generate the build files with CMake:

```bash
cmake ..
```

4. Build the project:

```bash
cmake --build .
```

## Usage
1. Start the server:

```bash
./server
```

2. In a separate terminal, run the client:
 ```bash
./client
```
The client will connect to the server, receive the file, and save it with a unique timestamp.


## Server Output:
```bash
Server started on port 12345...
Client connected.
Sending file...
File sent.
```

## Client Output:
```bash
Connecting to server...
Receiving file and saving as received_response1234567890.txt
File received successfully.
```
The client will save the received file in the same directory with a unique name like received_response1234567890.txt.

## Contributing

Feel free to fork this project and submit pull requests with any improvements or bug fixes.


