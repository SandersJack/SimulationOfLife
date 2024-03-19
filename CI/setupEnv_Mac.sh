#!/bin/bash
echo "Installing Packages"
brew install glew glfw

git submodule update --init --recursive