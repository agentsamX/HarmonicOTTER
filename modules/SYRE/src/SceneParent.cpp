#include"SceneParent.h"
syre::SceneParent::SceneParent()
{

}

syre::SceneParent::~SceneParent()
{
}
void syre::SceneParent::Start()
{
}
int syre::SceneParent::Update()
{
    return 0;
}

void syre::SceneParent::ImGUIUpdate()
{
}

bool syre::SceneParent::GetWon()
{
    return won;
}

int syre::SceneParent::GetID()
{
    return -1;
}

Camera::sptr& syre::SceneParent::GetCam()
{
    // TODO: insert return statement here
    return camera;
}
