.PHONY: build
build:
	@rm -r build || :
	 mkdir build && cd build
	@cmake .. && cmake --build .

.PHONY: run
run:
	@./program