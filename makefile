.PHONY: build
build:
	@ g++ src/main.cpp src/instructions.cpp -o main -std=c++11

.PHONY: exec
exec:
	@ ./main

.PHONY: run
run:
	@ make build
	@ make exec