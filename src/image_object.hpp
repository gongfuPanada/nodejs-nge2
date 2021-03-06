/**
 * @file  image_object.hpp
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/02 13:47:26
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _IMAGE_OBJECT_HPP
#define _IMAGE_OBJECT_HPP

namespace wrapper {
	class Image : public HandleWrap<Image> {
	public:
		Image() : HandleWrap<Image>() {
			img_ = NULL;
			V8::AdjustAmountOfExternalAllocatedMemory(getExternalAllocatedSize());
		}
		virtual ~Image() {
			V8::AdjustAmountOfExternalAllocatedMemory(-getExternalAllocatedSize());
			if (img_)
				::image_free(img_);
		}

		inline static void Init(Handle<Object> target) {
			HandleWrap<Image>::Init("ImageHandle", target);
		}

		int getExternalAllocatedSize() {
			if (img_)
				return sizeof(Image) + sizeof(image_t) + (img_->w * img_->h * img_->bpb);

			return sizeof(Image);
		}

		void updateProp();

		image_p img_;
	};
}

#define CHECK_IMG_ARG(pos)						\
	CHECK_WRAPPED_OBJ_ARG(Image, pos)

#define GET_IMG_ARG(var, pos)					\
	GET_WRAPPED_OBJ_ARG(Image, var, pos)

#define CREATE_IMG(var)										\
	Local<Object> var##__ = Image::NewInstance()->ToObject();	\
	UNWRAP_OBJ(Image, var, var##__)

#define CHECK_IMG_AND_RETURN(var)				\
	if (var->img_)								\
		return scope.Close(var##__);			\
	else										\
		return Undefined()

#endif /* _IMAGE_OBJECT_HPP */
