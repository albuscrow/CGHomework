#!/bin/sh

mkdir build || cd build && cmake .. && make && cd src && ./cz $1
