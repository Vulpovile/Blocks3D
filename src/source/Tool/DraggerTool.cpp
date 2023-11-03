#include "Tool/DraggerTool.h"
#include "Application.h"
#include "DataModelV2/SelectionService.h"

DraggerTool::DraggerTool(void)
{
	createHandles();
}

DraggerTool::~DraggerTool(void)
{
}

void DraggerTool::onButton1MouseDown(Mouse mouse)
{
	grabHandle(mouse);
	if(handleGrabbed == -1)
	{
		ArrowTool::onButton1MouseDown(mouse);
		createHandles();
	} else
	{
		printf("GRABBED HANDLE!");
	}
}
void DraggerTool::onButton1MouseUp(Mouse mouse)
{
	ArrowTool::onButton1MouseUp(mouse);
	createHandles();
}

void DraggerTool::onMouseMoved(Mouse mouse)
{
	if(handleGrabbed != -1)
	{
		std::vector<Instance *> selection = g_dataModel->getSelectionService()->getSelection();

		if(selection.size() == 1)
		{
			PartInstance* part = dynamic_cast<PartInstance*>(selection[0]);
			if(part)
			{
				Ray ray = G3D::Ray::fromOriginAndDirection(part->getPosition(), part->getCFrame().lookVector()*100);

				switch(handleGrabbed){
					case 0:
					case 1:
						ray = G3D::Ray::fromOriginAndDirection(part->getPosition(), part->getCFrame().upVector()*100);
						break;
					case 2:
					case 3:
						ray = G3D::Ray::fromOriginAndDirection(part->getPosition(), part->getCFrame().lookVector()*100);
						break;
					case 4:
					case 5:
						ray = G3D::Ray::fromOriginAndDirection(part->getPosition(), part->getCFrame().leftVector()*100);
						break;
				}

				CenterOffset = handles[handleGrabbed].center;

				Vector3 intersection1 = ray.intersection(mouse.getPlane());
				Vector3 intersection2 = ray.intersection(mouse.getInversePlane());
				

				if(intersection1.isFinite())
				{
					intersection1.x = (ceil(intersection1.x / 1) * 1);
					intersection1.y = (ceil(intersection1.y / 1) * 1);
					intersection1.z = (ceil(intersection1.z / 1) * 1);

					if ( ((int)part->getSize().x)%2 == 1 )
						intersection1.x += 0.5;

					//intersection1.y = mouse.getPlane() + part->getSize().y/2 - 0.5;

					if ( ((int)part->getSize().z)%2 == 1 )
						intersection1.z += 0.5;

					part->setPosition(intersection1 + (part->getPosition() - CenterOffset));
				}
				else if(intersection2.isFinite())
				{
					intersection2.x = (ceil(intersection2.x / 1) * 1);
					intersection2.y = (ceil(intersection2.y / 1) * 1);
					intersection2.z = (ceil(intersection2.z / 1) * 1);

					if ( ((int)part->getSize().x)%2 == 1) 
						intersection2.x += 0.5;

					//intersection2.y = mouse.getInversePlane() + part->getSize().y/2 - 0.5;

					part->setPosition(intersection2 + (part->getPosition() - CenterOffset));
				}

				float offset = 2;

				center = part->getPosition();
				Vector3 size = part->getSize();
				CoordinateFrame cFrame = part->getCFrame();

				handles[0].center = center + cFrame.upVector()*(size.y/2+offset);
				handles[1].center = center - cFrame.upVector()*(size.y/2+offset);

				handles[2].center = center + cFrame.lookVector()*(size.z/2+offset);
				handles[3].center = center - cFrame.lookVector()*(size.z/2+offset);

				handles[4].center = center + cFrame.leftVector()*(size.x/2+offset);
				handles[5].center = center - cFrame.leftVector()*(size.x/2+offset);
			}
		}
	}
	else ArrowTool::onMouseMoved(mouse);
}

void DraggerTool::onSelect(Mouse mouse)
{
	ArrowTool::onSelect(mouse);
	createHandles();
}

void DraggerTool::onKeyDown(int key)
{
	ArrowTool::onKeyDown(key);
}

void DraggerTool::onKeyUp(int key)
{
	ArrowTool::onKeyUp(key);
}

void DraggerTool::grabHandle(Mouse mouse)
{
	handleGrabbed = -1;
	if(hasHandles)
	{
		G3D::Ray ray = mouse.getRay();
		float distance = G3D::inf();
		for(int i = 0; i < 6; i++)
		{
			float newDistance = ray.intersectionTime(handles[i]);
			if(isFinite(newDistance) && newDistance < distance)
			{
				distance = newDistance;
				handleGrabbed = i; 
			}
		}
	}
}

void DraggerTool::createHandles()
{
	handleGrabbed = -1;
	hasHandles = false;
	std::vector<Instance *> selection = g_dataModel->getSelectionService()->getSelection();
	if(selection.size() == 1)
	{
		if(PartInstance* part = dynamic_cast<PartInstance*>(selection[0]))
		{
			hasHandles = true;

			float offset = 2;

			center = part->getPosition();
			Vector3 size = part->getSize();

			CoordinateFrame cFrame = part->getCFrame();

			handles[0] = Sphere(center + cFrame.upVector()*(size.y/2+offset), 1);
			handles[1] = Sphere(center - cFrame.upVector()*(size.y/2+offset), 1);

			handles[2] = Sphere(center + cFrame.lookVector()*(size.z/2+offset), 1);
			handles[3] = Sphere(center - cFrame.lookVector()*(size.z/2+offset), 1);

			handles[4] = Sphere(center + cFrame.leftVector()*(size.x/2+offset), 1);
			handles[5] = Sphere(center - cFrame.leftVector()*(size.x/2+offset), 1);
		}
	}
}

void DraggerTool::render(RenderDevice * rd, Mouse mouse)
{
	if(hasHandles)
	{
		for(int i = 0; i < 6; i++)
		{
			G3D::Draw::arrow(center, handles[i].center-center, rd, Color3::orange(), 2);
		}
	}

	std::vector<Instance *> selection = g_dataModel->getSelectionService()->getSelection();
	for(size_t i = 0; i < selection.size(); i++)
	{
		if(PartInstance* part = dynamic_cast<PartInstance*>(selection[i]))
		{
			//Ray ray = G3D::Ray::fromOriginAndDirection(part->getPosition(), part->getCFrame().lookVector()*100);
			//Vector3 intersection1 = ray.intersection(mouse.getPlane());
			//Vector3 intersection2 = ray.intersection(mouse.getInversePlane());
			//if(intersection1.isFinite())
			//{
			//	Draw::sphere(Sphere(intersection1, 2), rd);
			//}
			//else if(intersection2.isFinite())
			//{
			//	Draw::sphere(Sphere(intersection2, 2), rd);
			//}
		}
	}
}