#pragma once
class LoginWarnings
{
private:
	bool HostnameEmpty;
	bool NicknameEmpty;

public:
	LoginWarnings();
	~LoginWarnings();

	bool IsHostnameEmpty() { return HostnameEmpty; }
	bool IsNicknameEmpty() { return NicknameEmpty; }

	void SetHostnameEmpty(bool value) { HostnameEmpty = value; }
	void SetNicknameEmpty(bool value) { NicknameEmpty = value; }
};

