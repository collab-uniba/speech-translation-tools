#include "Session.h"



// Global static pointer used to ensure a single instance of the class.
Session* Session::m_pInstance = NULL; 

Session::Session(){
	this->m_luser = std::make_shared<UserList>();
	this->m_queue = std::make_shared<std::vector<MessagePTR>>();
	sound_flag = false;			//Flag to start/stop 
	tts_flag = false;				//Flag to start/stop TextToSpeech 		
	write_flag = false;			//Flag to recognize Typing
	tasto_stt_flag = false;		//Flag to activate Automatic SpeechToText
	finish_ctrl_flag = false;		//Flag to recognize CTRL press button
	automatic_stt_flag = false;

	ini = make_unique<CSimpleIniA>(); //a_bIsUtf8, a_bUseMultiKey, a_bUseMultiLine
	ini->SetUnicode();
	SI_Error rc = ini->LoadFile(SETTING_FILE);
	if (rc < 0 || ini->IsEmpty()) throw (ErrorSession("It is not possible to open the configuration file (config.ini) or is empty"));
}

Session* Session::Instance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Session;
	return m_pInstance;
}


void Session::addMsgToLog(MessagePTR msg){
	m_queue->push_back(msg);
}
/*
const char* Session::getDirectoryLog()
{
	return ini->GetValue("profile", "directory_log", NULL);
}
void Session::setDirectoryLog(const char *sv)
{
	ini->SetValue("profile", "directory_log", sv);
}*/

const char* Session::getMicLevel()
{
	return ini->GetValue("profile", "mic_level", NULL);
}

void Session::setMicLevel(const char* sv)
{
	ini->SetValue("profile", "mic_level", sv);
	ini->SaveFile(SETTING_FILE);
}

void Session::setGoogleAPIKey(const char* code){
	ini->SetValue("API_KEYS",
		"google_key", code);

	ini->SaveFile(SETTING_FILE);
}

const char* Session::getGoogleAPIKey(){
	const char *dev = ini->GetValue("API_KEYS",
		"google_key", NULL /*default*/);
	if (strlen(dev) == 0)
		throw (ErrorSession("Google Key was not added into config.ini file"));
	else return dev;
}

void Session::setLanguage(const char* lang){
	ini->SetValue("profile",
		"language_system", lang);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getLanguage(){
	return ini->GetValue("profile",
		"language_system", NULL /*default*/);
}

void Session::setNick(const char* nick){
	ini->SetValue("profile", "name", nick);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getNick(){
	return ini->GetValue("profile", "name", NULL);
}

const char* Session::getServerAddress(){
	return ini->GetValue("profile", "server", NULL);
}

void Session::setServerAddress(const char *sv){
	ini->SetValue("profile", "server", sv);
	ini->SaveFile(SETTING_FILE);
}

void Session::setNumbLanguageSelected(int v){

	ini->SetValue("profile", "no_language_selected", std::to_string(v).c_str());
	ini->SaveFile(SETTING_FILE);
}
int Session::getNumbLanguageSelected(){
	const char* tmp_srt = ini->GetValue("profile", "no_language_selected", NULL);
	return atoi(tmp_srt);
}

const char* Session::getTranslationEngine(){
	return ini->GetValue("profile", "translator_engine", NULL);
}

void  Session::setTranslationEngine(const char* sv){
	ini->SetValue("profile", "translator_engine", sv);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getBingKey(){
	const char *dev = ini->GetValue("API_KEYS", "bing_key", NULL);
	if (strlen(dev) == 0)
		throw (ErrorSession("Bing key was not added  into config.ini file"));
	else return dev;
}

const char* Session::getBingID(){
	const char *dev = ini->GetValue("API_KEYS", "bing_id", NULL);
	if (strlen(dev) == 0)
		throw (ErrorSession("Bing ID was not added into config.ini file"));
	else return dev;
}

void Session::setBingKey(const char *sv){
	ini->SetValue("API_KEYS", "bing_key", sv);
	ini->SaveFile(SETTING_FILE);
}

void Session::setBingID(const char *sv){
	ini->SetValue("API_KEYS", "bing_id", sv);
	ini->SaveFile(SETTING_FILE);
}


const char* Session::getsmtpservertxt()
{
	return ini->GetValue("email", "smtpservertxt", NULL);
}
void Session::setsmtpservertxt(const char *sv)
{
	ini->SetValue("email", "smtpservertxt", sv);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getserverporttxt()
{
	return ini->GetValue("email", "serverporttxt", NULL);
}
void Session::setserverporttxt(const char *sv)
{
	ini->SetValue("email", "serverporttxt", sv);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getusername()
{
	return ini->GetValue("email", "username", NULL);
}

void Session::setusername(const char *sv)
{
	ini->SetValue("email", "username", sv);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getpassword()
{
	return ini->GetValue("email", "password", NULL);
}

void Session::setpassword(const char *sv)
{
	ini->SetValue("email", "password", sv);
	ini->SaveFile(SETTING_FILE);
}

bool Session::getprotocol()
{
	return ini->GetBoolValue("email", "protocol", NULL);
}
void Session::setprotocol(bool sv)
{
	ini->SetBoolValue("email", "protocol", sv);
	ini->SaveFile(SETTING_FILE);
}

const char* Session::getAPPIDDragon()
{
	return ini->GetValue("dragon", "APP_ID", NULL);
}

const char* Session::getAPPKeyDragon()
{
	return ini->GetValue("dragon", "APP_KEY", NULL);
}

const char* Session::getAPPDeviceDragon()
{
	return ini->GetValue("dragon", "DEVICE_ID", NULL);
}


