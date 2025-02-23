# Nice Part Usage

The following repository contains a C++ backend framework to support the NPU system.

## File tree
npu-backend/
│── src/
│   ├── main.cpp          # Entry point of the backend
│   ├── routes.cpp        # API endpoint handlers
│   ├── routes.h          # Declarations for API endpoints
│   ├── database.cpp      # Database interactions (SQLite)
│   ├── database.h        # Database function declarations
│── include/
│   ├── crow_all.h        # Crow library (if not using external dependency manager)
│── db/
│   ├── npu.db            # SQLite database file (auto-generated)
│── CMakeLists.txt        # CMake build configuration
│── README.md             # Project documentation
│── .gitignore            # Ignore compiled files & database


## REST API
We used the Crow lightweight web framework (which is similar to Flask).


## Test unit
To be implemented

## Docker
The package is containeraized with docker container. See `/Dockerfile`.
