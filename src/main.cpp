#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>

using namespace geode::prelude;

class $modify(kanye, MenuLayer) {
    // skidded button menu template AHHHHHHHHHHHH
    struct Fields {
        EventListener<web::WebTask> m_listener;
        CCSprite* fetchedImage = nullptr;
        CCMenuItemSpriteExtra* billy = nullptr;
    };

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto bubby = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_helpBtn_001.png"),
            this,
            menu_selector(kanye::onclick)
        );

        auto menu = this->getChildByID("bottom-menu");
        menu->addChild(bubby);

        bubby->setID("bubby2kool4u"_spr);
        menu->updateLayout();

        m_fields->billy = bubby;
        return true;
    }

    void onclick(CCObject*) {
        // trash code, took too long to make (days ew)
        m_fields->billy->setEnabled(false);

        auto req = web::WebRequest();
        m_fields->m_listener.bind([this](web::WebTask::Event* e) {
            if (web::WebResponse* res = e->getValue()) {
                if (res->ok() && res->header("Content-Type") == "image/png") {
                    auto data = res->data();
                    auto img = new CCImage();
                    if (img->initWithImageData(data.data(), data.size())) {
                        auto greg = new CCTexture2D();
                        if (greg->initWithImage(img)) {
                            auto funny = CCSprite::createWithTexture(greg);
                            funny->setPosition({0, 0});
                            funny->setAnchorPoint({0, 0});
                            funny->setOpacity(0);
                            funny->setScale(2.0f);
                            this->addChild(funny, 10);
                            m_fields->fetchedImage = funny;

                            auto sequence = CCSequence::create(
                                CCFadeIn::create(0.5f),
                                CCDelayTime::create(5.0f),
                                CCFadeOut::create(0.5f),
                                nullptr
                            );
                            funny->runAction(sequence);
                        }
                        greg->release();
                    }
                    img->release();
                } else {
                    FLAlertLayer::create(
                        // skill issue
                        "Network Error",
                        "Either you aren't connected to the internet or my website is down.",
                        "OK"
                    )->show();
                }
            }
        });

        // cloudflare
        m_fields->m_listener.setFilter(req.get("http://geometrydash.us.kg:8080/api/bubby/"));

        this->runAction(
            CCSequence::create(
                CCDelayTime::create(2.0f),
                CCCallFunc::create(this, callfunc_selector(kanye::enableButton)),
                nullptr
            )
        );
    }

    void enableButton() {
        if (m_fields->billy) {
            m_fields->billy->setEnabled(true);
        }
    }
};
