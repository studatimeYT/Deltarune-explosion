#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fmt/format.h>
#include <Geode/ui/Notification.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        auto gm = GameManager::get();
        int effectId = gm->m_playerDeathEffect;

        // Call the original function FIRST so the default death happens
        PlayLayer::destroyPlayer(player, object);

        // Now, spawn our explosion ON TOP of the default one
        if ((effectId == 17 || effectId == 18 || effectId == 19) && player) {
            Notification::create(fmt::format("Died! ID: {}", effectId), NotificationIcon::Info)->show();
            
            FMODAudioEngine::sharedEngine()->playEffect("explode_11.ogg"_spr);

            auto playerPos = player->getPosition();
            
            // Try to load the first image
            auto explosionSprite = CCSprite::create("boom-explosion_01.png"_spr);
            
            if (explosionSprite) {
                Notification::create("Image Found!", NotificationIcon::Success)->show();
                explosionSprite->setPosition(playerPos);
                explosionSprite->setScale(1.5f);

                auto animation = CCAnimation::create();

                for (int i = 1; i <= 17; i++) {
                    std::string frameName = fmt::format("boom-explosion_{:02d}.png", i) + "_spr";
                    auto tempSprite = CCSprite::create(frameName.c_str());
                    if (tempSprite) {
                        animation->addSpriteFrame(tempSprite->displayFrame());
                    }
                }

                animation->setDelayPerUnit(0.04f);
                animation->setRestoreOriginalFrame(false);

                auto animateAction = CCAnimate::create(animation);
                auto removeAction  = CCRemoveSelf::create();
                auto sequence      = CCSequence::create(animateAction, removeAction, nullptr);

                explosionSprite->runAction(sequence);

                if (this->m_objectLayer) {
                    this->m_objectLayer->addChild(explosionSprite, 100);
                } else {
                    this->addChild(explosionSprite, 100);
                }
            } else {
                // If it can't find the image, show a red popup
                Notification::create("Image NOT Found!", NotificationIcon::Error)->show();
            }
        }
    }
};