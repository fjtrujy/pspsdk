# First stage
ARG BASE_DOCKER_IMAGE

FROM $BASE_DOCKER_IMAGE

COPY . /src

RUN apk add build-base autoconf automake zlib-dev
RUN cd /src && \
    ./bootstrap && \
    ./configure && \
    make -j $(getconf _NPROCESSORS_ONLN) clean && \
    make -j $(getconf _NPROCESSORS_ONLN) && \
    make -j $(getconf _NPROCESSORS_ONLN) install

# Second stage
FROM alpine:latest

ENV PSPDEV /usr/local/pspdev
ENV PATH $PATH:${PSPDEV}/bin

COPY --from=0 ${PSPDEV} ${PSPDEV}
