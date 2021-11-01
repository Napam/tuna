#!/bin/bash

make  && ./$(grep -oP "OUT_FILE = \K[\w\.]+" Makefile)
