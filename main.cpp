#include "WindowManager.hpp"
#include "ObjectManager.hpp"

int main()
{
	ObjectManager	objectManager;
	WindowManager	windowManager(&objectManager);

	Angle	angle;
	angle.SetDegAngle(-30.f);
	angle.Display();
//	std::thread tObjectUpdate(launchObjectManager, &objectManager);
	windowManager.Run();
//objectManager.Stop();
//	tObjectUpdate.join();
	return 0;
}
