#! /bin/bash

key="$(curl 127.0.0.1:3002)"
echo $key

if [ -z $key ]
then
      echo "\$key is empty"
else
      echo "\$key is NOT empty"
fi