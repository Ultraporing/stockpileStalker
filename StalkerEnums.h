#pragma once

struct ReturnReason
{
	enum Reason
	{
		Done, Error, ExitRequest
	};
	Reason r_;
	ReturnReason(Reason r) : r_(r) {}
	operator Reason () const { return r_; }
	private:
	//prevent automatic conversion for any other built-in types such as bool, int, etc
	template<typename T>
	operator T () const;
};

struct ScreenTypes
{
	enum Type
	{
		None, SplashScreen, MainScreen, Credits
	};
	Type t_;
	ScreenTypes(Type t) : t_(t) {}
	operator Type () const { return t_; }
	private:
	//prevent automatic conversion for any other built-in types such as bool, int, etc
	template<typename T>
	operator T () const;
};