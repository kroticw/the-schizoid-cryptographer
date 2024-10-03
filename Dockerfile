FROM ubuntu:jammy AS build

WORKDIR /app
COPY . .

ENV DEBIAN_FRONTEND=noninteractive

# Устанавливаем CMake
RUN apt update && apt install --no-install-recommends --no-install-suggests -y gpg wget curl software-properties-common \
    && wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null \
    && apt-add-repository "deb https://apt.kitware.com/ubuntu/ jammy main" \
    && apt update && apt install --no-install-recommends --no-install-suggests -y build-essential pkg-config make cmake

    #     && echo "deb https://apt.kitware.com/ubuntu/ jammy main" > /etc/apt/sources.list.d/apt.tpkitware.com.list \

# Компиляция
RUN (rm -rf build/ || :) && mkdir -p build/ && cd build && cmake .. && cmake --build .

FROM gcr.io/distroless/cc-debian12:latest AS final
COPY --from=build /app/build/the_schizoid_cryptographer /the_schizoid_cryptographer

CMD ["/the_schizoid_cryptographer"]
ENTRYPOINT ["/the_schizoid_cryptographer"]