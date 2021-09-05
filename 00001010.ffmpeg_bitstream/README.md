https://ffmpeg.org/ffmpeg-bitstream-filters.html

ffmpeg -i INPUT.mp4 -codec copy -bsf:v h264_mp4toannexb OUTPUT.ts  
ffmpeg -i INPUT.mp4 -codec copy -bsf:v hevc_mp4toannexb OUTPUT.ts  

```
Known work around for me: use container for input file without PTS limits (streaming container). One of them, known me, is MPEG-TS. So, you can simple convert your MP4 file to the MPEG-TS:

ffmpeg -i input.mp4 -c copy -bsf:v h264_mp4toannexb -f mpegts input.ts

And use next command to compose infinity file:

ffmpeg -re -stream_loop -1 -i input.ts -c copy -strict -2 -bsf:a aac_adtstoasc -y output.mp4
```
