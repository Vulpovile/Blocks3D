#include "ButtonListener.h"

#define CURSOR 0
#define ARROWS 1
#define RESIZE 2

class ModeSelectionListener : public ButtonListener {
public:
	void onButton1MouseClick(BaseButtonInstance*);
};
