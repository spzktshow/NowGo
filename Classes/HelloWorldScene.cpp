#include "HelloWorldScene.h"
#include "platform/CCFileUtils.h"
#include "moonSugar/MSActor.h"
#include "moonSugar/TypeConver.h"
#include "CCActionInterval.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Demo", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    //sprite->setScaleX(-1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("Hero.ExportJson");
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(fullPath, this, schedule_selector(HelloWorld::onLoadedComplete));
    return true;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Released key code %d", keyCode);
    if ((int)keyCode == 100 || (int)keyCode == 97)
    {
        //cancel direct
        log("cancel direct");
        moonsugar::BehaviorCancelDirectEvent * cancelDirect = new moonsugar::BehaviorCancelDirectEvent(CANCEL_DIRECT_EVENT);
        actor->executeEvent(cancelDirect);
        cancelDirect = nullptr;
    }
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d pressed", keyCode);
    if ((int)keyCode == 100)
    {
        //direct right
        log("direct right");
        moonsugar::BehaviorDirectEvent * directRight = new moonsugar::BehaviorDirectEvent(DIRECT_EVENT);
        directRight->directType = DIRECT_TYPE_RIGHT;
        actor->executeEvent(directRight);
        directRight = nullptr;
    }
    else if ((int)keyCode == 97)
    {
        //direct left
        log("direct left");
        moonsugar::BehaviorDirectEvent * directLeft = new moonsugar::BehaviorDirectEvent(DIRECT_EVENT);
        directLeft->directType = DIRECT_TYPE_LEFT;
        actor->executeEvent(directLeft);
        directLeft = nullptr;
    }
    else if ((int)keyCode == 106)
    {
        log("normal attack");
        moonsugar::BehaviorNormalAttackEvent *normalAttack = new moonsugar::BehaviorNormalAttackEvent(NORMAL_ATTACK_EVENT);
        actor->executeEvent(normalAttack);
        normalAttack = nullptr;
    }
    else if ((int)keyCode == 32)
    {
        moonsugar::BehaviorJumpEvent *jump = new moonsugar::BehaviorJumpEvent(JUMP_EVENT);
        actor->executeEvent(jump);
        jump = nullptr;
    }
}

void HelloWorld::onLoadedComplete(float percent)
{
    if (percent >= 1)
    {
        CCLOG("%s", "loadComplete");
        Size visibleSize = Director::getInstance()->getVisibleSize();
        cocostudio::Armature * arm = cocostudio::Armature::create("Hero");
        cocos2d::Point *postionP = new cocos2d::Point(visibleSize.width * 0.5, visibleSize.height * .5);
        arm->setPosition(*postionP);
        arm->setTag(1);
        addChild(arm);
        arm->getAnimation()->play("loading");
        //loading, run, attack, smitten, death
//        cocos2d::Action * action = cocos2d::MoveTo::create(0.2f, cocos2d::Point(visibleSize.width * 0.5, visibleSize.height * .5 + 100));
        actor = new moonsugar::Actor();
        actor->entry = arm;
        actor->position = postionP;
    }
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
