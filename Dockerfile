FROM alpine:3.7

RUN mkdir include
COPY julia.c .
COPY ./include/* include
#RUN apk add build-base
RUN apk add gcc musl-dev
RUN cc -o julia julia.c -I./include -lm
RUN apk del build-base
ENTRYPOINT ["./julia"]
