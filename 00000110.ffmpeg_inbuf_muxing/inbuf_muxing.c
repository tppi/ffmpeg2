#include <stdio.h>
#include <stdbool.h>
#include "libavcodec/avcodec.h"
#include "libavutil/mem.h"    
#include "libavutil/imgutils.h"
#include "libavformat/avformat.h"

#define IN_VEDIO_FILE  "cuc_ieschool.h264"
#define IN_AUDIO_FILE  "cuc_ieschool.mp3"
#define OUT_FILE "cuc_ieschool.mp4"

int main(int argc, char **argv)
{
    AVFormatContext *in_vedio_ctx = NULL, *in_audio_ctx = NULL, *out_ctx = NULL;
    bool isVedio = true;

    avformat_open_input(&in_vedio_ctx, IN_VEDIO_FILE, NULL, NULL);
    avformat_find_stream_info(in_vedio_ctx, NULL);

    avformat_open_input(&in_audio_ctx, IN_AUDIO_FILE, NULL, NULL);
    avformat_find_stream_info(in_audio_ctx, NULL);

    avformat_alloc_output_context2(&out_ctx, NULL, NULL, OUT_FILE);

    int vedio_stream_index = -1, audio_stream_index = -1;
    vedio_stream_index = av_find_best_stream(in_vedio_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    audio_stream_index = av_find_best_stream(in_audio_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    for(int i = 0; i<2; i++) {
        AVStream *out_stream = avformat_new_stream(out_ctx, NULL);
        avcodec_parameters_from_context(out_stream->codecpar,
            isVedio ? in_vedio_ctx->streams[i]->codec : in_audio_ctx->streams[i]->codec);

        isVedio = false;
        if (out_ctx->oformat->flags & AVFMT_GLOBALHEADER) {
            out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
        }
    }

    if (!(out_ctx->oformat->flags & AVFMT_NOFILE)) {
        avio_open(&out_ctx->pb, OUT_FILE, AVIO_FLAG_READ_WRITE);
    }

    avformat_write_header(out_ctx, NULL);

    AVPacket *packet = av_packet_alloc();
    int64_t ts_a = 0, ts_b = 0;
    int64_t *ts_p = NULL;
    int out_stream_index = -1;
    AVFormatContext *cur_ctx = NULL;
    AVStream *cur_stream = NULL;
    int frame = 0;

    while (1) {
        if (av_compare_ts(ts_a, in_vedio_ctx->streams[vedio_stream_index]->time_base, ts_b, in_audio_ctx->streams[audio_stream_index]->time_base) <= 0) {
            cur_ctx = in_vedio_ctx;
            ts_p = &ts_a;
            cur_stream = in_vedio_ctx->streams[vedio_stream_index];
            out_stream_index = 0;
        } else {
            cur_ctx = in_audio_ctx;
            ts_p = &ts_b;
            cur_stream = in_audio_ctx->streams[audio_stream_index];
            out_stream_index = 1;
        }

        if (av_read_frame(cur_ctx, packet) < 0) {
            break;
        }

        if (packet->pts == AV_NOPTS_VALUE) {
            int64_t each_frame_time = (double)AV_TIME_BASE / av_q2d(cur_stream->r_frame_rate);   
            packet->pts = (double)(frame++ * each_frame_time) / (double)(av_q2d(cur_stream->time_base) * AV_TIME_BASE);  
            packet->dts = packet->pts;
            packet->duration = (double)each_frame_time / (double)(av_q2d(cur_stream->time_base) * AV_TIME_BASE);
        }
        *ts_p = packet->pts;

        av_packet_rescale_ts(packet, cur_stream->time_base, out_ctx->streams[out_stream_index]->time_base);
        packet->stream_index = out_stream_index;
        printf("write file pts = %lld, index = %d\n", packet->pts, packet->stream_index);

        av_interleaved_write_frame(out_ctx, packet);

        av_packet_unref(packet);
    }

    av_write_trailer(out_ctx);

    if (!(out_ctx->oformat->flags & AVFMT_NOFILE)) {
        avio_close(out_ctx->pb);
    }
    avformat_close_input(&in_audio_ctx);
    avformat_close_input(&in_vedio_ctx);
    avformat_free_context(out_ctx);
    av_packet_free(&packet);
    return 0;
}
