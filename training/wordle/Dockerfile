FROM alpine:latest

# Install dependencies
RUN apk add --no-cache socat bash

# Copy your wordle executable
COPY wordle /usr/local/bin/wordle
RUN chmod +x /usr/local/bin/wordle

# Copy the shell script
COPY wordle-shell.sh /usr/local/bin/wordle-shell
RUN chmod +x /usr/local/bin/wordle-shell

# Run the shell via socat
CMD ["socat", "TCP-LISTEN:2323,fork,reuseaddr", "EXEC:/usr/local/bin/wordle-shell"]
