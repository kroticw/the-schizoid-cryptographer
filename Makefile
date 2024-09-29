.PHONY: build
build:
	@clang++ . -o program

.PHONY: run
run:
	@./program