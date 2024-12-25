#! /bin/bash

stty -F /tmp/uart 115200 -raw
screen $(readlink /tmp/uart)
