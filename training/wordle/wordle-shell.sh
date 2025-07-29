#!/bin/bash
echo "Welcome to Wordle Server!"
echo "Type 'wordle' to start the game or 'exit' to quit"

while true; do
    read -p "> " cmd
    case "$cmd" in
        wordle*)
            # Check if wordle executable exists
            if [ -x "/usr/local/bin/wordle" ]; then
                /usr/local/bin/wordle
            else
                echo "Error: Wordle executable not found"
            fi
            ;;
        exit*)
            echo "Goodbye!"
            exit 0
            ;;
        *)
            echo "Available commands: wordle, exit"
            ;;
    esac
done
