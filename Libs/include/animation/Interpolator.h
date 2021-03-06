#if !defined(__IZANAGI_ANIMATION_INTERPOLATOR_H__)
#define __IZANAGI_ANIMATION_INTERPOLATOR_H__

#include "izDefs.h"
#include "izStd.h"

#include "Timeline.h"

namespace izanagi
{
namespace animation
{
    class CInterpolator : public CObject {
        friend class CStoryBoard;

    protected:
        CInterpolator();
        virtual ~CInterpolator() {}

        IZ_DEFINE_INTERNAL_RELEASE();

    public:
        IZ_FLOAT GetValue(const CTimeline& timeline);

    private:
        PURE_VIRTUAL(IZ_FLOAT GetValueEx(IZ_FLOAT time, IZ_FLOAT duration));

    protected:
        IMemoryAllocator* m_Allocator;

        IZ_FLOAT m_From;
        IZ_FLOAT m_To;
    };
}   // namespace animation
}   // namespace izanagi

#endif  // #if !defined(__IZANAGI_ANIMATION_INTERPOLATOR_H__)
