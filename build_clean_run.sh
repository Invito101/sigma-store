#!/bin/bash

# Run `make` to build the executable
make 2>&1 | tee build.log

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build successful. Cleaning up object files..."
  # Remove all .o files
  find . -name "*.o" -type f -delete
  echo "Object files removed. Running the executable..."
    
  # Run the executable (replace 'program' with your executable's name)
  ./sigma-store
else
  echo "Build failed. Please check the errors."
fi