#!/bin/bash

# Script to compile, clean, and run the game

CODE_DIR="CODE"
MAKEFILE="$CODE_DIR/Makefile"
TARGET="$CODE_DIR/bin/puzzle_game"

function build_game() {
    make -C "$CODE_DIR" build
}

function clean_game() {
    make -C "$CODE_DIR" clean
}

function rebuild_game() {
    make -C "$CODE_DIR" rebuild
}

function run_game() {
    if [ ! -f "$TARGET" ]; then
        echo "Game not built. Building now..."
        build_game
    fi
    "$TARGET"
}

function show_help() {
    echo "Usage: $0 [option]"
    echo "Options:"
    echo "  build    - Compile the game"
    echo "  clean    - Clean build files"
    echo "  rebuild  - Clean and compile the game"
    echo "  run      - Run the game"
    echo "  help     - Show this help message"
}

case "$1" in
    build)
        build_game
        ;;
    clean)
        clean_game
        ;;
    rebuild)
        rebuild_game
        ;;
    run)
        run_game
        ;;
    help)
        show_help
        ;;
    *)
        echo "Invalid option. Use '$0 help' to see available options."
        ;;
esac
