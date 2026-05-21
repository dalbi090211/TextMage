#pragma once

class IStatusEvent abstract {
public :
	virtual void execute() = 0;
	virtual ~IStatusEvent() {}
};	