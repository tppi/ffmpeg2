### avio + decode 
inbuf AVIOContext + H264 decode

### decoder
> avcodec_decode_video2  

> avcodec_send_packet
> avcodec_receive_frame

### example
```
ret = avcodec_send_packet(dec_ctx, pkt);
while (ret >= 0) {
    ret = avcodec_receive_frame(dec_ctx, frame);
}
```

```
/* Decode video frame */
avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
```

### build
gcc inbuf_decode.c -o inbuf_decode `pkg-config --cflags --libs libavdevice libavformat libavfilter libavcodec libswresample libswscale libavutil` -lx264  

### inbuf AVIOContext or File as Input Source
./inbuf_decode test.h264  
./inbuf_decode  

### reference
ffmpeg-4.1/doc/examples/avio_reading.c  
ffmpeg-4.1/tests/api/api-h264-test.c  
ffmpeg-4.1/tests/api/api-band-test.c

