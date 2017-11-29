# Projekt z předmětů IFJ a IAL
# Překladač jazyka IFJ17

# Makefile

# Autoři: Daniel Švub (xsvubd00), Jan Zwierz (xzwier00)

PRJ=parser
#
CFLAGS=-Wall -std=c99 -pedantic -lm

$(PRJ): $(PRJ).c
	gcc $(CFLAGS) -o $@ $(PRJ).c

clean:
	rm -f $(PRJ)
#
