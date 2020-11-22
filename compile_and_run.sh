#!/bin/bash

g++ -o boids.out \
    main.cpp\
    utils/utils.cpp\
    headers/utils.hpp\
 -lSDL2  && ./boids.out
