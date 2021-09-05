/* 
*实现一个自己的decoder,编码工作其实就是把pkt的数据拷贝到frame
*作者：缪国凯（MK） 
*821486004@qq.com 
*2015-6-5 
*/ 
#include "avcodec.h"
 
static av_cold int yyy_init_decoder(AVCodecContext *avctx)
{
	printf("init yyy decoder\n");
	return 0;
}
 
static int yyy_decode(AVCodecContext *avctx, void *data, int *got_frame,
	AVPacket *avpkt)
{
	AVFrame   *frame   = (AVFrame*)data;
	//AVPicture *picture = (AVPicture*)data;
	const uint8_t *buf             = avpkt->data;
	int buf_size                   = avpkt->size;
 
	int size = avpicture_get_size(avctx->pix_fmt, avctx->width,
		avctx->height);

    printf("avpicture_get_size size:%d buf_size:%d\n",size, buf_size);
 
	frame->pict_type        = AV_PICTURE_TYPE_I;
	frame->key_frame        = 1;
    
	
	frame->buf[0] = av_buffer_alloc(size);
	
	memcpy(frame->buf[0]->data, buf, buf_size);
#if 0 
	int res = 0;
	if ((res = avpicture_fill(picture, frame->buf[0]->data, avctx->pix_fmt,
		avctx->width, avctx->height)) < 0) 
	{
			av_buffer_unref(&frame->buf[0]);
			return res;
	}
#else
#endif
 
	*got_frame = 1;
	return 0;
}
 
static av_cold int yyy_close_decoder(AVCodecContext *avctx)
{
	printf("close yyy decoder\n");
	return 0;
}
 
AVCodec ff_yyy_decoder = {
	.name           = "yyy",
	.long_name      = "yyy decoder",
	.type           = AVMEDIA_TYPE_VIDEO,
	.id             = AV_CODEC_ID_YYY,
	.capabilities	= AV_CODEC_CAP_PARAM_CHANGE,	
	.init           = yyy_init_decoder,	
	.decode			= yyy_decode,
	.close          = yyy_close_decoder,
};
