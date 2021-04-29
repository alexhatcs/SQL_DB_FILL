#!/bin/bash

time sqlite3 "d" < "dquery.txt"
time sqlite3 "d1" < "d1query.txt"
time sqlite3 "d2" < "d2query.txt"