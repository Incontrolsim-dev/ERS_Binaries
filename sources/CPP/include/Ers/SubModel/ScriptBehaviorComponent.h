#pragma once

#include "Entity.h"
#include "Ers/IO/Serializer.h"
#include "Ers/Utility/Util.h"

namespace Ers
{

    /// @brief The CoreComponent class is there to identify components inheriting as a core component
    class ScriptBehaviorComponent
    {
      public:
        EntityID ConnectedEntity = 0;

        ScriptBehaviorComponent()                                          = default; // Force Users to inherit from component
        ScriptBehaviorComponent(const ScriptBehaviorComponent&)            = delete;
        ScriptBehaviorComponent(ScriptBehaviorComponent&&)                 = delete;
        ScriptBehaviorComponent& operator=(const ScriptBehaviorComponent&) = delete;
        ScriptBehaviorComponent& operator=(ScriptBehaviorComponent&&)      = delete;

        virtual ~ScriptBehaviorComponent() {}

        virtual void OnCreation() {}

        virtual void OnAwake() {}

        virtual void OnStart() {}

        virtual void OnUpdate() {}

        virtual void OnLateUpdate() {}

        virtual void OnDestroy() {}

        /// @brief Called before a child entity is added to a parent.
        ///
        /// Is called on the child.
        /// @param newParent The parent entity the child is about to enter.
        virtual void OnEntering(EntityID newParent) {};

        /// @brief Called after a child entity is added to a parent.
        ///
        /// Is called on the parent.
        /// @param newChild The newly added child.
        virtual void OnEntered(EntityID newChild) {};

        /// @brief Called before a child entity is removed from a parent.
        ///
        /// Is called on the child.
        /// @param oldParent The parent entity the child is about to leave.
        virtual void OnExiting(EntityID oldParent) {};

        /// @brief Called after a child entity is removed from a parent.
        ///
        /// Is called on the parent.
        /// @param oldChild The previously present child.
        virtual void OnExited(EntityID oldChild) {};

        /// @brief Called after an input channel is ready, given that this script's entity has a ResourceComponent.
        /// @param inputChannel The entity with the input channel that is ready.
        virtual void OnInputChannelReady(EntityID inputChannel) {};

        /// @brief Called after an output channel is ready, given that this script's entity has a ResourceComponent.
        /// @param outputChannel The entity with the output channel that is ready.
        virtual void OnOutputChannelReady(EntityID outputChannel) {};

        /// @brief Called after an entity is passed by a ResourceComponent. It will be added as a child.
        /// @param outputChannel The entity with the input channel that received the child.
        /// @param child The child that has been passed.
        virtual void OnReceive(EntityID inputChannel, EntityID child) {};

        virtual void OnSubModelMove(EntityID entity) { ConnectedEntity = entity; }

        virtual void Serialization(Ers::Serializer serializer) {};
    };

} // namespace Ers
