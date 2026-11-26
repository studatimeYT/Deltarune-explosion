#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        auto gm = GameManager::get();

        // Death effect 19 is stored as index 18 internally
        bool usingEffect19 = (gm->m_playerDeathEffect == 18);

        if (usingEffect19 && player) {
            // Play custom sound
            FMODAudioEngine::sharedEngine()->playEffect("explode_11.ogg"_spr);

            auto playerPos = player->getPosition();

            std::string firstName = fmt::format("boom-explosion_{:02d}.png", 1) + "_spr";
            auto explosionSprite = CCSprite::create(firstName.c_str());

            if (explosionSprite) {
                explosionSprite->setPosition(playerPos);
                explosionSprite->setScale(1.5f);

                auto animation = CCAnimation::create();

                for (int i = 1; i <= 17; i++) {
                    std::string frameName = fmt::format("boom-explosion_{:02d}.png", i) + "_spr";
                    auto tex = CCTextureCache::sharedTextureCache()->addImage(frameName.c_str(), false);
                    if (tex) {
                        auto spriteFrame = CCSpriteFrame::createWithTexture(
                            tex,
                            CCRectMake(0, 0, tex->getContentSize().width, tex->getContentSize().height)
                        );
                        animation->addSpriteFrame(spriteFrame);
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
            }
        }

        PlayLayer::destroyPlayer(player, object);
    }
};
