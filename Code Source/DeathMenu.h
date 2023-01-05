#pragma once
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <Node2D.hpp>
#include <control.h>
#include <Control.hpp>
#include <SceneTree.hpp>

using namespace godot;

class DeathMenu : public Control {
    GODOT_CLASS(DeathMenu, Control)

private:
    // Private member variables and functions go here.

public:
    static void _register_methods() {
        register_method("_on_Replay_pressed", &DeathMenu::_on_Replay_pressed);
    }

    DeathMenu() {
        // Constructor code goes here.
    }

    ~DeathMenu() {
        // Destructor code goes here.
    }

    void _init() {
        // Initialization code goes here.
    }

    void _on_Replay_pressed() {
        get_tree()->change_scene("res://Menu.tscn");
    }
};
