#!/bin/bash

file="$1"

[ -f "$file" ] || { echo "Feil: Filen $file finnes ikke."; exit 1; }

size=$(stat -c "%s" "$file")

while true; do
    sleep 60
    new_size=$(stat -c "%s" "$file")

    [ "$new_size" -ne "$size" ] && { echo "Filen $file har endret størrelse."; exit 0; }
done
