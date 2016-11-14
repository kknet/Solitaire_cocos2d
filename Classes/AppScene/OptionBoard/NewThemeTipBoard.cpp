#include "NewThemeTipBoard.h"
#include "ClientCtrl.h"
#include"cocostudio/CocoStudio.h"
#include "CSBHelper.h"

bool NewThemeTipBoard::init()
{
	if (!OptionBaseBoard::init(kNewThemeTipBoard))
	{
		return false;
	}
	initRootCSBNode();
	handleButton();
	updateLanguage();
	return true;
}


void NewThemeTipBoard::initRootCSBNode()
{
	bool isPort = ClientCtrl::share()->isPortrait();
	string csbName = "cocostudio/port/NewTheme_port.csb";
	if (!isPort)
	{
		csbName = "cocostudio/land/NewTheme_land.csb";
	}
	m_rootCSBNode = CSLoader::createNode(csbName);
	ST_RETURN_IF(!m_rootCSBNode);
	m_rootCSBNode->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(m_rootCSBNode);
}

void NewThemeTipBoard::handleButton()
{
	//button
	CSBHelper::registerButton(m_rootCSBNode, "ButtonClose", CC_CALLBACK_2(NewThemeTipBoard::btnCloseCallBack, this));
	CSBHelper::registerButton(m_rootCSBNode, "ButtonOk", CC_CALLBACK_2(NewThemeTipBoard::btnOkCallBack, this));

}

void NewThemeTipBoard::updateLanguage()
{
	//title
	string titleStr = STLang::shared()->getValue("NEW BACKDROP");
	titleStr = STLabelBMFont::convertAllLetterToCapital(titleStr);
	CSBHelper::updateFntTextToLabel(m_rootCSBNode, "TextTitle", titleStr, -1.0f, TextHAlignment::LEFT, Color3B(1, 1, 1), -1.0f, Color4B(0, 0, 0, 100));

	//CANCEL menu
	string cancelStr = STLang::shared()->getValue("Later");
	CSBHelper::updateFntTextToLabel(m_rootCSBNode, "TextClose", cancelStr, -1.0f, TextHAlignment::LEFT, Color3B(1, 1, 1), -1.0f, Color4B(0, 0, 0, 100));

	//ok menu
	string okStr = STLang::shared()->getValue("OK");
	CSBHelper::updateFntTextToLabel(m_rootCSBNode, "TextOk", okStr, -1.0f, TextHAlignment::LEFT, Color3B(1, 1, 1), -1.0f, Color4B(0, 0, 0, 100));

	//invite info
	string infoStr = STLang::shared()->getValue("change to new backdrop?");
	Size bgSize = getBgSize();
	float maxWidth = bgSize.width*0.9;
	CSBHelper::updateFntTextToLabel(m_rootCSBNode, "TextInfo", infoStr, maxWidth, TextHAlignment::LEFT);
}


void NewThemeTipBoard::closeEffect()
{
	OptionBaseBoard::closeEffect();
	Size winSize = CLDWinSize();
	float dt = 0.2f;
	Vec2 endPos = this->getPosition() + Vec2(winSize.width*1.0, 0);
	MoveTo *mvTo = MoveTo::create(dt, endPos);
	ST_RETURN_IF(!mvTo);
	EaseElasticOut *ease = EaseElasticOut::create(mvTo);
	ST_RETURN_IF(!ease);
	CallFunc *callFunc = CallFunc::create(this, callfunc_selector(NewThemeTipBoard::removeSelfCallFunc));
	ST_RETURN_IF(!callFunc);
	Sequence *seq = Sequence::create(mvTo, callFunc, NULL);
	ST_RETURN_IF(!seq);
	this->runAction(seq);
	ClientCtrl::share()->playSound(SOUND_MENU_OUT);

}
void NewThemeTipBoard::btnCloseCallBack(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		closeEffect();
		break;

	case Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}


void NewThemeTipBoard::btnOkCallBack(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		closeEffect();
		NotificationCenter::getInstance()->postNotification(ST_CHANGE_TO_NEW_THEME);
		break;

	case Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}
