#!/bin/bash

g++ -o boids.out \
    main.cpp\
    utils.cpp\
    utils.h\
 -lSDL2  && ./boids.out
