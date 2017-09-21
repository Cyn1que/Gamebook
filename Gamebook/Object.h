#pragma once

class APlayer;
class ANonPlayerChar;



//! \brief Class representing general concept of Object in game world that allows interaction between varying types of objects
class OObject
{
public:
	//! \brief Abstract function that enables objects to interact with each other using Double Dispatch pattern
	virtual void InteractWith(OObject &) = 0;
	//! \brief Abstract function that enables any object interact with APlayer using Double Dispatch pattern
	virtual void InteractWith(APlayer &) = 0;
};

