#!/bin/bash

if [ -f sigma-store ]; then
  echo "Removing existing executable..."
  rm sigma-store
fi

make 2>&1 | tee build.log

if [ $? -eq 0 ]; then
  echo "Build successful. Cleaning up object files..."
  find . -name "*.o" -type f -delete
  echo "Object files removed. Running the executable..."
    
  ./sigma-store
else
  echo "Build failed. Please check the errors."
fi