#include "Monster.h"
#include <ResourceLoader.hpp>
#include <Node2D.hpp>
#include <assert.h>
#include <Sprite.hpp>
#include<SceneTree.hpp>
#include <Area2D.hpp>
#include <CollisionPolygon2D.hpp>
using namespace godot;


void Monster::_register_methods() {
	register_method((char*)"_process", &Monster::_process);
	register_method((char*)"_physics_process", &Monster::_physics_process);
	register_method("_on_HitBox2_body_entered", &Monster::_on_HitBox2_body_entered);
}

void Monster::_init() {}

Monster::Monster() {
	motion = Vector2(0, 0);
	direction = Vector2(0, 0).RIGHT;
}

void Monster::_ready() {
}

Monster::~Monster() {}

void Monster::_process(float delta) {
	//movement physics----------------------
	move_and_slide(motion, Vector2(0,0).UP);
}

void Monster::_physics_process(float delta)
{


	//Variables---------------------------------
	motion = Vector2(0,0);
	Sprite* _Monst = (Sprite*)get_node("Slime");

	//Gravity-----------------------------------
	motion.y += gravity;

	//Monster Animation
	AnimationPlayer* _Anim_mons = (AnimationPlayer*)get_node("AnimationMonster");
	_Anim_mons->play("Move");

	//Monster Mouvements
	if (is_on_wall()) {
		dir *= -1;
		if (dir < 0) {
			_Monst->set_flip_h(0);
		}
		else
			_Monst->set_flip_h(1);
	}
	motion.x += speed * dir;

	CollisionPolygon2D* DeathZone = (CollisionPolygon2D*)get_node("DeathZone");
	//Monster Death--------------
	if (Death) {
		motion.x = 0;
		DeathZone->set_disabled(true);
		_Anim_mons->play("MonstDeath");
	}
}

void Monster::_on_HitBox2_body_entered(Node* body) {
	{
		if (body->is_in_group("Player"))
		{
			Death = true;
			//queue_free();
		}
	}
}