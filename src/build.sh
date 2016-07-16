#!/bin/bash

sed 's/${file_base_name}/'"$1"'/g;s/${file_name}/'"$2"'/g' Makefile.tmpl > Makefile

