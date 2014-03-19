//
//  GUI.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-18.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__GUIController__
#define __Excercise_1__GUIController__

#include <iostream>
/*#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/notebook.h>
#include <gtkmm/box.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>*/
#include <gtkmm.h>
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



class GUIController : public Gtk::Window {
private:
    void initLightsTab();
    void initMaterialsTab();
    void registerSignalHandlers();

public:
    
    int buttonState;
    
    Camera *camera;
    Light *light;
    Material *material;
    VertexBuffer *vertices;
    bool *flipNormals;
    bool *shouldLoadFile;
    std::string *filenameToLoad;

    Gtk::Label m_settingsLabel;
    Gtk::Label m_modelLabel;
    Gtk::Label m_tabsLabel1;
    Gtk::Label m_tabsLabel2;
    
    Gtk::Label m_materialAmbientLabel;
    Gtk::Label m_materialDiffuseLabel;
    Gtk::Label m_materialSpecularLabel;
    Gtk::Label m_materialShininessLabel;
    
    Gtk::Label m_lightColorLabel;
    Gtk::Label m_lightPositionLabel;

    Gtk::Box m_box1;
    Gtk::Box m_lightsContainer;
    Gtk::Box m_materialContainer;
    
    Gtk::CheckButton m_flipNormalsCheck;
    Gtk::Notebook m_tabs;
    
    Gtk::Scale m_lightRedChannel;
    Gtk::Scale m_lightBlueChannel;
    Gtk::Scale m_lightGreenChannel;
    
    Gtk::SpinButton m_lightPositionX;
    Gtk::SpinButton m_lightPositionY;
    Gtk::SpinButton m_lightPositionZ;
    
    Gtk::Scale m_materialDiffuseRedChannel;
    Gtk::Scale m_materialDiffuseBlueChannel;
    Gtk::Scale m_materialDiffuseGreenChannel;

    Gtk::Scale m_materialAmbientRedChannel;
    Gtk::Scale m_materialAmbientBlueChannel;
    Gtk::Scale m_materialAmbientGreenChannel;

    Gtk::Scale m_materialSpecularRedChannel;
    Gtk::Scale m_materialSpecularBlueChannel;
    Gtk::Scale m_materialSpecularGreenChannel;
    
    Gtk::Scale m_materialShininess;
    Gtk::Button m_loadButton;
    
    Gtk::Entry m_Entry;
    
    GUIController(Camera *camera, Light *light, Material *material, bool *flipNormals, bool *shouldLoadFile, std::string *filenameToLoad);
    virtual ~GUIController();
protected:
    //Signal handlers:
    void on_flipNormalsCheck_clicked();
    void on_movementCombo_changed();
    void on_tabs_switch_tab(Gtk::Widget* page, guint page_num);
    void on_light_changed();
    void on_material_changed();
    void on_spinbutton_digits_changed();
    void on_loadbutton_clicked();
    
    //Member widgets:
    Gtk::Button m_button;
    Gtk::ComboBoxText m_movementCombo;

};

#endif /* defined(__Excercise_1__GUIController__) */
