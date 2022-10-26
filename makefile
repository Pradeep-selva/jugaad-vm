.PHONY: build
build:
	@ g++ main.cpp instructions.cpp -o main -std=c++11

.PHONY: exec
exec:
	@ ./main

.PHONY: run
run:
	@ make build
	@ make exec