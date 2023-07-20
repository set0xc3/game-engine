#!/bin/bash

echo '[' > compile_commands.json
for file in cdb/*.json; do
  chunk="$(cat $file | sed -n '/{/,/}/p')"
  echo "$chunk" >> compile_commands.json
done
sed -i '$s/.$//' compile_commands.json
echo ']' >> compile_commands.json
