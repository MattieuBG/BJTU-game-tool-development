#include	<sstream>
#include	"Client.hpp"
#include	"RTypeSfml.h"
#include	"RTypeAudio.h"
#include	"Usleep.hpp"
#include	"Menu.hpp"

Client::Client()
{
  this->_gui = new RTypeSfml;
  this->_audio = new RTypeAudio;
  this->_gui->init(800, 600, "R-Type");
}

Client::~Client()
{
  this->_gui->quit();
}

void			Client::run(bool intro)
{
  Menu			menu;

  this->_audio->Play("audio/starwars.ogg");
  if (intro == true)
    this->intro();
  menu.run(this->_gui, this->_audio);
}

void			Client::intro()
{
  int			nb = 0;
  int			jump = 0;
  int			part = 1;
  std::ostringstream	convert;
  
  while (part <= 12)
    {
      convert.str("");
      convert << part;
      this->_gui->getImageHeight("sprites/intro/video/part"+convert.str()+"/sprite_intro.gif");
      part += 1;
    }
  part = 1;
  while (this->_gui->wait() !=36 && nb <= 297)
    {
      if (!(nb % 25) && part < 12)
	{
	  jump = 0;
	  part += 1;
	}
      convert.str("");
      convert << part;
      this->_gui->clear();
      this->_gui->draw(0, 32, "sprites/intro/video/part"+convert.str()+"/sprite_intro.gif", 255, 1, 0, jump * 540, 960, 540);
      this->_gui->display();
      Usleep::call(60);
      nb++;
      jump++;
    }
}
