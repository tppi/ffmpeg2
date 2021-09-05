### SRS v4.x support hevc(h.265) RTMP streaming
```
wnpllrzodiac commented on 26 Apr 2020 •

Patch FFmpeg

About ffplay with hecv-rtmp/flv player, please read https://github.com/young-I/CDN-Union_H265

About ffmpeg/ffplay build, please read https://github.com/wnpllrzodiac/FFmpeg

git clone -b n3.2.4_hevc_flv https://github.com/wnpllrzodiac/FFmpeg
cd FFmpeg
./configure --ADD_YOUR_FFMPEG_BUILD_PARAMS

SRS

./objs/srs -c conf/hevc.conf

    Notice: could add "hls_vcodec" option "h264" or "hevc"(not Mandatory)

publish

Publish stream by (my ffmpeg hecv branch ONLY support codec copy publish)

ffmpeg -re -i test_hevc.mp4 -c copy -f flv rtmp://192.168.1.1/slive/ggg

play

    RTMP: ffplay rtmp://192.168.1.1/slive/ggg
    HTTP-FLV: ffplay http://192.168.1.1:8080/slive/ggg.flv
    HLS: ffplay http://192.168.1.1:8080/slive/ggg.m3u8

 Metadata:
    major_brand     : isom
    minor_version   : 512
    compatible_brands: isomiso2mp41
Lavf57.56.101       :     nan    :  0.000 fd=   0 aq=    0KB vq=    0KB sq=    0B f=0/0
  Duration: N/A, start: 0.083000, bitrate: N/A
    Stream #0:0: Audio: aac (LC), 48000 Hz, stereo, fltp
    Stream #0:1: Video: hevc (Main), yuv420p(tv), 720x480, 24.42 fps, 23.98 tbr, 1k tbn, 23.98 tbc
   1.72 M-V:  0.000 fd=   0 aq=    0KB vq=  120KB sq=    0B f=0/0
```
### reference
[1] https://github.com/ossrs/srs/pull/1721

