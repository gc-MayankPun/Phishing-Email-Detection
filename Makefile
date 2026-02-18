CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = src/main.c src/parser.c src/url.c src/dns.c src/blacklist.c src/scoring.c
OBJ = $(SRC:.c=.o)

detector: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o detector

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f detector src/*.o
