#include "RFPlayer.h"

#include "DisplayManager.h"
#include "Billboard.h"
#include "TTFManager.h"
#include "Texture.h"
#include "StringProc.h"

#ifdef WIN32
#include <windows.h>
#endif //WIN32
#include <GL/gl.h>

RFPlayer::RFPlayer()
{
	score = 0;
	time = 30;
	scoreHUD = Billboard(0.3,Vec3f(-5,-6,-1),true);
	timeHUD = Billboard(0.3,Vec3f(-5,6,-1),true);
	font = TTFManager::instance()->getFont("BankGothic-Regular.ttf",100);
	font->Draw("Score:  0", &scoreTEX);
	font->Draw("Time: 30.0", &timeTEX);

}

bool RFPlayer::Update()
{
	static int TIME = time;

	time -= DisplayManager::instance()->getDtSecs();
	if((int)time != TIME)
	{
		TIME = time;
		font->Draw("Time: "+StringProc::intToString(time), &timeTEX);
	}
	return (time <= 0);
}

void RFPlayer::collect(const TimeStar &star)
{
	score++;
	time += star.getValue();
	font->Draw("Score: "+StringProc::intToString(score), &scoreTEX);
}

void RFPlayer::Draw()
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	scoreTEX.UseThisTexture();
	scoreHUD.Draw();
	timeTEX.UseThisTexture();
	timeHUD.Draw();

	glColor3f(1,1,1);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

}
