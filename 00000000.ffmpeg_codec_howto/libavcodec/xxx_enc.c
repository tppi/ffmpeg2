/* 
*实现一个自己的encoder,编码工作其实就是把frame的数据拷贝到pkt
*作者：缪国凯（MK） 
*821486004@qq.com 
*2015-6-4 
*/ 
 
 
#include "avcodec.h"
#include "libavutil/pixdesc.h"
 
static av_cold int xxx_encode_init(AVCodecContext *avctx)
{
	printf("init xxx encoder\n");
	const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(avctx->pix_fmt);
 
	avctx->coded_frame = av_frame_alloc();
	avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;
	avctx->bits_per_coded_sample = av_get_bits_per_pixel(desc);
	if(!avctx->codec_tag)
		avctx->codec_tag = avcodec_pix_fmt_to_codec_tag(avctx->pix_fmt);
 	return 0;
}
 
static int xxx_encode(AVCodecContext *avctx, AVPacket *pkt,
	const AVFrame *frame, int *got_packet)
{
	int ret = avpicture_get_size(avctx->pix_fmt, avctx->width, avctx->height);
 
	if (ret < 0)
		return ret;
 
	if (pkt->data == NULL && pkt->size == 0)
	{
		av_new_packet(pkt,ret);
		pkt->size = ret;
	}
 
// 	if ((ret = ff_alloc_packet2(avctx, pkt, ret)) < 0)
// 		return ret;
 
	if ((ret = avpicture_layout((const AVPicture *)frame, avctx->pix_fmt, avctx->width,
		avctx->height, pkt->data, pkt->size)) < 0)
		return ret;
 
	pkt->flags |= AV_PKT_FLAG_KEY;
	*got_packet = 1;
	return 0;
}
 
static av_cold int xxx_close(AVCodecContext *avctx)
{
	printf("close xxx encoder\n");
	av_frame_free(&avctx->coded_frame);
	return 0;
}
 
AVCodec ff_xxx_encoder = {
	.name           = "xxx",
	.long_name      = NULL_IF_CONFIG_SMALL("xxx encoder"),
	.type           = AVMEDIA_TYPE_VIDEO,
	.id             = AV_CODEC_ID_XXX,
	.init           = xxx_encode_init,
    .encode2        = xxx_encode,
    .close          = xxx_close,
};
