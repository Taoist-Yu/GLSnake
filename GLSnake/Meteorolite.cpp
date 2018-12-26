#include "Meteorolite.h"
#include "Random.h"
#include "Time.h"

Meteorolite::Meteorolite(Scene * scene, GameObject * parent)
	: GameObject(scene, "model/Meteorolite/meteorolite.obj", "meteorolite.vert", "meteorolite.frag", parent)
{
	Mesh* mesh = this->model->meshes[0];
	tag = Tag::barrier;
}

Meteorolite::~Meteorolite()
{
}

void Meteorolite::Update()
{
	timeVal += Time.GetUnscaledDeltaTime();
	transform.SetRotation(
		360 * sin(timeVal/10),
		360 * cos(timeVal/10),
		360 * sin(timeVal/10 + glm::radians(45.f))
	);
}
