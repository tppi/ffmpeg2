### build
gcc inbuf_avio.c -o inbuf_avio `pkg-config --cflags --libs libavdevice libavformat libavfilter libavcodec libswresample libswscale libavutil` -lx264  

### Custom AVIOContext or File as Input Source
./inbuf_avio source.200kbps.768x320.flv  
./inbuf_avio  
