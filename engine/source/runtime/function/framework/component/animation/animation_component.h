#pragma once

#include "runtime/function/animation/skeleton.h"
#include "runtime/function/animation/pose.h"
#include "runtime/function/framework/component/component.h"
#include "runtime/resource/res_type/components/animation.h"
#include "runtime/function/animation/animation_FSM.h"
#include "json11.hpp"
namespace Pilot
{
    REFLECTION_TYPE(AnimationComponent)
    CLASS(AnimationComponent : public Component, WhiteListFields)
    {
        REFLECTION_BODY(AnimationComponent)

    public:
        AnimationComponent() = default;

        void postLoadResource(std::weak_ptr<GObject> parent_object) override;

        void tick(float delta_time) override;

        const AnimationResult& getResult() const;
        void                   animateBasicClip(float ratio, BasicClip* basic_clip);
        void                   blend(float desired_ratio, BlendState* blend_state);
        void                   blend1D(float desired_ratio, BlendSpace1D* blend_state);
        template<typename T>
        void updateSignal(const std::string& key, const T& value)
        {
            m_signal[key] = value;
        }

    protected:
        META(Enable)
        AnimationComponentRes m_animation_res;      // 动画资源

        Skeleton m_skeleton;                        // 运行时骨架实例
        AnimationResult       m_animation_result;   // 每帧的骨骼矩阵结果
        AnimationFSM          m_animation_fsm;      // 动画状态机
        json11::Json::object  m_signal;             // 输入信号表
        float                 m_ratio {0};          // 动画播放进度 0 - 1
    };
} // namespace Pilot
