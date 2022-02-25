# APD - Tema 1
# Octombrie 2021

build:
	@echo "Building..."
	@gcc -o testapd testapd.c -lm -Wall -lpthread
	@echo "Done"

build_debug:
	@echo "Building debug..."
	@gcc -o testapd testapd.c -lm -Wall -O0 -g3 -DDEBUG -lpthread
	@echo "Done"

clean:
	@echo "Cleaning..."
	@rm -rf testapd
	@echo "Done"
