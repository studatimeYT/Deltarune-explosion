#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        auto gm = GameManager::get();
        int effectId = gm->m_playerDeathEffect;

        // Call original death first
        PlayLayer::destroyPlayer(player, object);

        // Only replace specific death effects
        if ((effectId == 17 || effectId == 18 || effectId == 19) && player) {
            // Play the explosion sound
            FMODAudioEngine::sharedEngine()->playEffect("explode_11.ogg"_spr);

            auto playerPos = player->getPosition();

            auto explosionSprite = CCSprite::create("boom-explosion_01.png"_spr);
            if (!explosionSprite) return;

            explosionSprite->setPosition(playerPos);
            explosionSprite->setScale(1.5f);

            auto animation = CCAnimation::create();
            animation->setDelayPerUnit(0.04f);
            animation->setRestoreOriginalFrame(false);

            // Load all frames (01 to 18)
            for (int i = 1; i <= 18; i++) {
                auto frameName = fmt::format("boom-explosion_{:02d}.png"_spr, i);
                auto frame = CCSpriteFrameCache::get()->spriteFrameByName(frameName.c_str());
                if (frame) {
                    animation->addSpriteFrame(frame);
                }
            }

            auto animateAction = CCAnimate::create(animation);
            auto removeAction  = CCRemoveSelf::create();
            auto sequence      = CCSequence::create(animateAction, removeAction, nullptr);

            explosionSprite->runAction(sequence);

            if (this->m_objectLayer) {
                this->m_objectLayer->addChild(explosionSprite, 100);
            } else {
                this->addChild(explosionSprite, 100);
            }
        }
    }
};