//
// Created by blatnoa on 27.03.2023.
//

#ifndef INC_2023_JCO_AIRTIME_ADVANCEDCOLLISIONSPRITE_H
#define INC_2023_JCO_AIRTIME_ADVANCEDCOLLISIONSPRITE_H


#include "sprite.h"

//! A class that can be used to create advanced collisions
//!
//! This class is used to create advanced collisions.
//! This is useful for creating walls and other objects that certain entities can collide with while ignoring others.
//!
//! When colliding with another sprite, the AdvancedCollisionSprite will emit a signal and call the onCollide function on itself.
//!
//! By default the intersection rect is the scene bounding rect.
//! This can be changed by using the setCollisionOverride function.
//! This function allows the user to specify a custom rect that will be used as the intersection rect.
//! This can be useful for creating more precise collisions.
//! The collision override can be removed with the removeCollisionOverride function.
//!
//! This class also allows the creation of triggers.
//! A AdvancedCollisionSprite can be set to be a trigger with the setTrigger function.
//! Triggers are a special type of collision that don't block other sprites from intersecting with them.
//! When a sprite intersects with a trigger, the trigger will emit a signal and call the onTrigger function of the other sprite.
//! This allows for the creation of zones that can be used to trigger events.
//! For example a trigger can be used to trigger a level transition when the player enters a certain area.
//!
//! The class allows the user to specify which classes of sprites can collide with the AdvancedCollisionSprite.
//! This is done with the addCollidingClass and removeCollidingClass functions.
//! A class can be added with these functions, and then the AdvancedCollisionSprite will only collide with sprites that are of that class.
//! If no classes are in the list, the AdvancedCollisionSprite won't collide with any sprites.
//! If the list contains the string "All", the AdvancedCollisionSprite will collide with all sprites. This can be done with the collideAll function.
//!
//! The class also contains a function called getCollidingSprites.
//! This function returns a list of all sprites that are colliding with the AdvancedCollisionSprite.
//! This list only contains sprites that are of a class that is in the collidingClasses list.
//! If the list is empty, the AdvancedCollisionSprite is not colliding with any sprites.
//!
//! The onTrigger and onCollide functions can be overridden to create custom behavior when a collision or trigger occurs.
//! This is especially useful for creating custom triggers.
//! This can also be done by connecting to the notifyTrigger and notifyCollision signals.
class AdvancedCollisionSprite : public Sprite {

    Q_OBJECT

public:
    explicit AdvancedCollisionSprite(QGraphicsItem* pParent = nullptr);
    explicit AdvancedCollisionSprite(const QString& rImagePath, QGraphicsItem* pParent = nullptr);
    AdvancedCollisionSprite(const QString& rImagePath, QRectF collisionOverride, QGraphicsItem* pParent = nullptr);

    // Trigger
    inline void setTrigger(bool trigger) { isTrigger = trigger;};
    [[nodiscard]] inline bool getIsTrigger() const { return isTrigger; };

    // Colliding classes
    void addCollidingClass(const QString& className);
    inline void removeCollidingClass(const QString& className) { collidingClasses.removeOne(className); };
    void collideAll();

    virtual QList<Sprite*> getCollidingSprites(QRectF rect = QRectF()) const;

    // Intersection events
    virtual void onTrigger(Sprite* pOther);
    virtual void onCollision(Sprite* pOther);

    // Intersections checks
    virtual void reevaluateIntersects();
    virtual void reevaluateIntersects(QRectF rect);

    [[nodiscard]] QRectF collisionRect() const;

protected:
    // Trigger
    bool isTrigger = false;

    // Collision override
    QRectF collisionOverrideRect = QRectF();
    void setCollisionOverride(QRectF rect);
    void removeCollisionOverride();

    // Colliding classes
    QList<QString> collidingClasses = {"All"};

signals:
    void notifyTrigger(Sprite* pOther);
    void notifyCollision(Sprite* pOther);
};


#endif //INC_2023_JCO_AIRTIME_ADVANCEDCOLLISIONSPRITE_H
