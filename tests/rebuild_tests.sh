#!/usr/bin/bash

root=${0%/rebuild_tests.sh}

if [[ $1 == "" ]]; then
    cd $root
    root=.
    files=`ls */*.in`
else 
    if [ -d $1 ]; then
        files=`ls $1/*.in 2>/dev/null`
    else
        echo an argument should be a folder
        exit 1
    fi
fi

if [[ $files == "" ]]; then
    echo test files not found
    exit 2
fi

run=$root/../run
for file_ in $files; do
    file=${file_%.in}
    echo rebuilding $file
    $run x <$file.in >$file.out 
done
