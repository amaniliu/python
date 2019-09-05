#include "HCameraLists.h"
#include "UsbLists.h"
#include "HCameraPythonZ.h"


  std::list<std::shared_ptr<IHCamera>> HCameraLists::FindAll()
  {
	  std::list<std::shared_ptr<IHCamera>> cameraLists;
	  std::list<std::shared_ptr<IUsb>> usbs = UsbLists::find_vid_pid(0, 0);

	  for (auto i = usbs.begin(); i != usbs.end(); i++)
		  cameraLists.push_back(std::shared_ptr<IHCamera>(new HCameraPythonZ(*i)));

	  return cameraLists;
  }