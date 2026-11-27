#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        auto gm = GameManager::get();
        
        // Print the ID to the Geode console
        int effectId = gm->m_playerDeathEffect;
        log::info("Player died. Current death effect ID is: {}", effectId);

        // Let's check for BOTH 18 and 19 so we can see which one works
        if ((effectId == 18 || effectId == 19) && player) {
            log::info("Matching Death Effect detected! Trying to play sound...");
            FMODAudioEngine::sharedEngine()->playEffect("explode_11.ogg"_spr);

            auto playerPos = player->getPosition();
            
            // Safer way to create the sprite
            auto firstSpriteName = fmt::format("boom-explosion_{:02d}.png", 1) + "_spr";
            auto explosionSprite = CCSprite::create(firstSpriteName.c_str());

            if (explosionSprite) {
                log::info("Sprite loaded successfully!");
                explosionSprite->setPosition(playerPos);
                explosionSprite->setScale(1.5f);

                auto animation = CCAnimation::create();

                for (int i = 1; i <= 17; i++) {
                    std::string frameName = fmt::format("boom-explosion_{:02d}.png", i) + "_spr";
                    
                    // Create a temporary sprite to grab the frame safely
                    auto tempSprite = CCSprite::create(frameName.c_str());
                    if (tempSprite) {
                        animation->addSpriteFrame(tempSprite->displayFrame());
                    } else {
                        log::error("Failed to load frame: {}", frameName);
                    }
                }

                animation->setDelayPerUnit(0.04f);
                animation->setRestoreOriginalFrame(false);

                auto animateAction = CCAnimate::create(animation);
                auto removeAction  = CCRemoveSelf::create();
                auto sequence      = CCSequence::create(animateAction, removeAction, nullptr);

                explosionSprite->runAction(sequence);

                // Add to the object layer
                if (this->m_objectLayer) {
                    this->m_objectLayer->addChild(explosionSprite, 100);
                } else {
                    this->addChild(explosionSprite, 100);
                }
            } else {
                log::error("Failed to create the FIRST explosion sprite! Check your resources folder.");
            }
        }

        // Always call original so the player actually dies
        PlayLayer::destroyPlayer(player, object);
    }
};