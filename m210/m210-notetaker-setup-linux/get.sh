#!/bin/bash

$1./m210drivers get > /dev/null 2>&1
mv raw.note $1 > /dev/null 2>&1
