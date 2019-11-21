#!/usr/bin/env bash

WIKI_DIR=$1
EXPORT_DIR=$2
TOKEN=$3

for file in $WIKI_DIR/*.md; do
    filename=$(basename "$file" .md)
    grip "$file" --no-inline --export $EXPORT_DIR/"$filename.html" --pass=$TOKEN

    for file2 in $WIKI_DIR/*.md; do
        filename2=$(basename "$file2" .md)

        filename_with_spaces=${filename2//-/ }

        expression="s/\[\[$filename_with_spaces]]/<a href='$filename2.html'>$filename_with_spaces<\/a>/g"

        sed -i -e "$expression" $EXPORT_DIR/"$filename.html"
    done
done
