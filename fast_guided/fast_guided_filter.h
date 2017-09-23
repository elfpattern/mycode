#ifndef __FAST_GUIDED_FILTER_H_
#define __FAST_GUIDED_FILTER_H_

#define use_sse (1)	// 1: use sse to get faster  0: slower than sse


/*******************************************************************
** ������:     fast_guided_filter
** ��������:   guided filter
** note:       2017.03.16Ŀǰֻ֧�ֵ�ͨ��
**			   eg: r = 4, (try sr = r/4 to sr = r),(try rp=0.1^2, 0.2^2, 0.4^2)
**
**             (MIN(w, h) / sr) > 1
**			   (int)(r / sr + 0.5f) >= 1
**
** ����:       [in]      src:                          ������˲�ͼ��,��ͨ��
**             [in]      guidance:                     ���뵼��ͼ��,��ͨ��
**             [in/out]  dst:                          ����˲���ͼ��,��ͨ��
**             [in]      w:                            ͼ����
**             [in]      h:                            ͼ��߶�
**             [in]      c:                            ͼ��ͨ����,Ŀǰֻ֧�ֵ�ͨ��
**             [in]      r:                            �˲����ڰ뾶
**             [in]      rp:                           �涨������
**             [in]      sr:                           ��������
** ����:                                               ����ö��ֵ
********************************************************************/

/*
@function    fast_guided_filter
@param       [in]      src:						  input image,single channel
@param       [in]      guidance:                  guided image,single channel
@param       [in/out]  dst:                       output image,single channel
@param       [in]      w:                         width of image
@param       [in]      h:                         height of image
@param       [in]      c:						  channel of image, only c = 1
@param       [in]      r:						  local window radius
@param       [in]      rp:			              regularization parameter:eps
@param       [in]	   sr:                        subsampling ratio, sr>1:downscale, 0<sr<1:upscale
@return��										  0:ok; 1:error
@brief��

eg: r = 4, (try sr = r/4 to sr=r),(try rp=0.1^2, 0.2^2, 0.4^2)
try:(src,guidance,dst,w,h,1,4,0.01,4)
condition: (MIN(w, h) / sr) > 1
condition: (int)(r / sr + 0.5f) >= 1
*/
int fast_guided_filter(unsigned char *src, unsigned char *guidance, unsigned char *dst,
	int w, int h, int c, int r, float rp, float sr);

#endif