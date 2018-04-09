#!/bin/bash

rsync -e 'ssh -p 10022' -t * zso@localhost:~/zad1/
