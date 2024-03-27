#!/bin/bash

echo "Installing Packages"

sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglew-dev
sudo apt-get install libglfw3 libglfw3-dev

git submodule update --init --recursive