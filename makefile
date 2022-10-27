.PHONY: build
build:
	@ g++ src/*.cpp -o main -std=c++11

.PHONY: exec
exec:
	@ ./main

.PHONY: run
run:
	@ make build
	@ make exec