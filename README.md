# NPU - Nice Part Usage

The following repository contains a C++ backend framework to support the NPU system.
Currently all API request are centralized in a single service, but in the future we will use the microservice architecture, where each service will be responsible for a specific domain. Fx, we will have the User domain, Scoring domain, Search domain, etc.

## File tree
NPU/  
│── src/  
│$~~~$├── main.cpp $~~~$ # Entry point of the backend  
│$~~~$├── creation_api/  
│$~~~~~~$ - NPU creation source files  
│$~~~$├── user_api/  
│$~~~~~~$ - User data handling source files  
│── include/  
│$~~~$├── crow_all.h $~~~~~$# Crow library (if not using external dependency   manager)  
│── CMakeLists.txt $~~~$ # CMake build configuration  
│── README.md $~~~~~$ # Project documentation  
│── .gitignore $~~~~~~~~~$ # Ignore compiled files & database  


## REST API
We use the Crow lightweight web framework (which is similar to Flask).


## Test unit
To be implemented

## Docker
The package is containerized with docker container. See `/Dockerfile`.
