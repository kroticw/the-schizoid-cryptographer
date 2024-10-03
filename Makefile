.PHONY: build
build:
	@(rm -r build || :) && mkdir build
	@cd build && cmake .. && cmake --build .

.PHONY: run
run:
	@./program

.PHONY: docker.build
docker.build:
	@docker build --platform linux/amd64 --tag crypt:latest -f Dockerfile --target final .

# Ожидается наличие папки test/ и файла test/input.txt
.PHONY: docker.run
docker.run: docker.build
	@docker run --rm -v ./test:/test crypt:latest e /test/input.txt /test/output.txt
