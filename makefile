.PHONY: build
build:
	@ g++ -I src/headers/ src/headers/*cpp src/*.cpp -o main -std=c++11

.PHONY: exec
exec:
	@ ./main

.PHONY: run
run:
	@ make build
	@ make exec