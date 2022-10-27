.PHONY: build
build:
	@ g++ -I src/core/ -I src/config src/config/*.cpp src/core/*cpp src/*.cpp -o main -std=c++11

.PHONY: exec
exec:
	@ ./main

.PHONY: run
run:
	@ make build
	@ make exec