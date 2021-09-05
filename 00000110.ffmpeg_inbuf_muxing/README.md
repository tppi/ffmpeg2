
Check out the muxing sample; the key is to keep track of your audio/video timestamps and write the next one in time using av_interleaved_write_frame.

### build
```gcc inbuf_muxing.c -o inbuf_muxing `pkg-config --cflags --libs libavdevice libavformat libavfilter libavcodec libswresample libswscale libavutil` -lx264```

### inbuf AVIOContext or File as Input Source
./inbuf_muxing

### reference
[1] https://github.com/slmax2017/ffmpeg_mp4_h264_mux（bug)  
[2] https://github.com/Akagi201/ffmpeg-muxer (bug)  
[3] doc/examples/muxing.c (还是ffmpeg自带的examples靠谱，不过要去掉编码的部分才好用，直接mux编码好的数据帧)  
[4] https://stackoverflow.com/questions/15239124/muxing-a-h-264-annex-b-aac-stream-using-libavformat-with-vcopy-acopy
