#!/bin/bash

# List of file extensions to delete
file_formats=("exe" "o" "a")

# Check if the list is not empty
if [ ${#file_formats[@]} -eq 0 ]; then
  echo "No file formats specified for deletion."
  exit 1
fi

# Construct the find command with multiple -name conditions
# find_command="find . -type f \("
find_command="find . \("

for ext in "${file_formats[@]}"; do
  find_command+=" -name '*.$ext' -o"
done

# echo "$find_command"

# Remove the trailing -o
find_command=${find_command::-3}
# echo "$find_command"
# eval $find_command

# Add the -exec part
find_command+=" \) -exec rm -f {} \;"
# echo "$find_command"

# Execute the find command
eval $find_command

echo "All specified files have been deleted."
read