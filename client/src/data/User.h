#ifndef CLIENTTSFRM_H
#define CLIENTTSFRM_H

#include <wx/string.h>
#include <memory>




class User{
public:
	User(wxString name, unsigned short color, unsigned short used, unsigned short speak, unsigned short write, wxString lang):
	_name(name), _color(color), _speak(speak), _write(write), _lang(lang){ }
	~User(){}

	void setName( wxString _name) { this->_name = _name; }
	wxString getName() { return this->_name; }
	void setColor( unsigned short _color) { this->_color = _color; }
	unsigned short getColor() { return this->_color; }
	void setUsed( unsigned short _used) { this->_used = _used; }
	unsigned short getUsed() { return this->_used; }
	void setSpeak( unsigned short _speak ) { this->_speak = _speak; }
	unsigned short getSpeak() { return this->_speak; }
	void setWrite ( unsigned short write ) { this->_write = write; }
	unsigned short getWrite() { return this->_write; }
	void setLang( wxString _lang) { this->_lang =  _lang; }
	wxString getLang() { return this->_lang; }

private:
	wxString _name;
	unsigned short _color;
	unsigned short _used = 0;
	unsigned short _speak = 0;
	unsigned short _write = 0;
	wxString _lang;

};

typedef std::shared_ptr<User> UserPTR;


#endif
