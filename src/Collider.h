#pragma once
#include "Callback.h"
#include "ColliderManager.h"
#include "ECS.h"
#include "Transform.h"

class Collider : public Component {
public:
    void init() override;
    void update(float dt) override;

    const TAG& getTag();
    void setTag(const TAG& tag);

    const COLLIDER_TYPE& getType();
    void setType(const COLLIDER_TYPE& type);

    void setRadius(float radius);
    float getRadius();

    const FRect& getCollider();
    void setCollider(const FRect& rect);

    void needAutoUpdate(bool enable);
    void recalculateCollider();

    void setCallback(CallbackEntity callback);
    void onCollision(Entity* entity);

private:
    TAG _tag;
    COLLIDER_TYPE _type;
    // CIRCLE
    float _radius;
    // BOX
    FRect _collider;

    Transform* _transform;

    bool _needAutoUpdate;
    FPoint _currentPosition;

    CallbackEntity _callback;
};