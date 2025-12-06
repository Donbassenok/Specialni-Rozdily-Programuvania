#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

mkdir -p "$PROJECT_DIR/build"
cd "$PROJECT_DIR/build"

cmake "$PROJECT_DIR"
make -j4

echo "Build complete."

