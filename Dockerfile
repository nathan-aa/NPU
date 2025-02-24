# Use an official C++ build image with necessary dependencies
FROM debian:bullseye

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libpqxx-dev \
    libboost-all-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy application source code
COPY . .

# Build the application
RUN mkdir build && cd build && cmake .. && make

# Expose the application port
EXPOSE 8080

# Set environment variables for database connection
ENV DB_CONN="dbname=npu_db user=postgres password=yourpassword host=db" # TODO: edit db connection string

# Run the application
CMD ["./build/main"]
