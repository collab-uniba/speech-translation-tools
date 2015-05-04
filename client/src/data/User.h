#pragma once

#include <wx/string.h>
#include <memory>


class User{
public:
	User(wxString name, unsigned short color, unsigned short used, unsigned short speak, unsigned short write, wxString lang):
	m_name(name), m_color(color), m_speak(speak), m_write(write), m_lang(lang){ }
	~User(){}

	void setName( wxString m_name) { this->m_name = m_name; }
	wxString getName() { return this->m_name; }
	void setColor( unsigned short m_color) { this->m_color = m_color; }
	unsigned short getColor() { return this->m_color; }
	void setUsed( unsigned short m_used) { this->m_used = m_used; }
	unsigned short getUsed() { return this->m_used; }
	void setSpeak( unsigned short m_speak ) { this->m_speak = m_speak; }
	unsigned short getSpeak() { return this->m_speak; }
	void setWrite ( unsigned short write ) { this->m_write = write; }
	unsigned short getWrite() { return this->m_write; }
	void setLang( wxString m_lang) { this->m_lang =  m_lang; }
	wxString getLang() { return this->m_lang; }

private:
	wxString m_name;
	unsigned short m_color;
	unsigned short m_used = 0;
	unsigned short m_speak = 0;
	unsigned short m_write = 0;
	wxString m_lang;

};

typedef std::shared_ptr<User> UserPTR;

