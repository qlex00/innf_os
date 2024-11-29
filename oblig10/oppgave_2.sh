#!/bin/bash

[ -d "$1" -a -w "$1" ] || { echo "Feil: $1 er ikke en gyldig katalog med skrivetilgang"; exit 1; }
[ -d "$2" -a -w "$2" ] || { echo "Feil: $2 er ikke en gyldig katalog med skrivetilgang"; exit 1; }

antall=$(mv "$1"/*.mp3 "$2" 2>/dev/null | wc -l)

echo "Flyttet $antall mp3-filer fra $1 til $2"
