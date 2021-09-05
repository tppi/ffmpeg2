#!/bin/sh

APP = encode_video
APP1 = decode_video

INCLUDE = \
-I ../bin/include 

LIB = \
-L ../bin/lib


SRC = encode_video.c
SRC1 = decode_video.c

CFLAGS = -g -O0 -lstdc++

LDFLAGS = -lavformat -lavdevice -lavfilter -lavcodec -lavutil -lswscale -lswresample -lm -pthread -ldl -lz -llzma -lx264

out: 
	gcc $(SRC) -o $(APP) $(LIB) $(INCLUDE) $(CFLAGS) $(LDFLAGS)
	gcc $(SRC1) -o $(APP1) $(LIB) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

clean:
	rm encode_video decode_video #main main1




