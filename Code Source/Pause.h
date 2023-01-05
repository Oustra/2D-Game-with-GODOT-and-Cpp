#pragma once
#include <Godot.hpp>
#include <Input.hpp>
#include <Node2D.hpp>
#include <control.h>
#include <Control.hpp>
#include <SceneTree.hpp>
#include <CanvasLayer.hpp>
#include <VisibilityEnabler2D.hpp>
#include <VisibilityEnabler.hpp>

using namespace godot;

class Pause : public Control {
    GODOT_CLASS(Pause,Control)

private:
    // Private member variables and functions go here.

public:
    static void _register_methods() {
        register_method("_on_CONTINUE_pressed", &Pause::_on_CONTINUE_pressed);
        register_method("_on_QUIT_pressed", &Pause::_on_QUIT_pressed);
    }

    Pause() {
        // Constructor code goes here.
    }

    ~Pause() {
        // Destructor code goes here.
    }

    void _init() {
        // Initialization code goes here.
    }

    void _on_CONTINUE_pressed() {
        get_tree()->set_pause(false);
        set_visible(false);
    }

    void _on_QUIT_pressed() {
        get_tree()->quit();
    }

};