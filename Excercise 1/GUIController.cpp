//
//  GUI.cpp
//  Excercise 1
//
//  Created by Karl Petersson on 2014-03-18.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#include "GUIController.h"

GUIController::GUIController(Camera *camera, Light *light, Material *material, bool *flipNormals, bool *shouldLoadFile, std::string *filenameToLoad) :
m_flipNormalsCheck("flip normals"),
m_box1(Gtk::ORIENTATION_VERTICAL),
m_tabsLabel1("Light"),
m_tabsLabel2("Material"),
m_lightsContainer(Gtk::ORIENTATION_VERTICAL),
m_materialContainer(Gtk::ORIENTATION_VERTICAL)
{
    
    this->camera = camera;
    this->light = light;
    this->material = material;
    this->flipNormals = flipNormals;
    this->shouldLoadFile = shouldLoadFile;
    this->filenameToLoad = filenameToLoad;
    
    // Sets the border width of the window.
    set_border_width(10);
    set_default_size(400, 200);

    set_title("ModelViewer Settings");
    
    m_settingsLabel.set_text("Settings");
    m_settingsLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    
    m_modelLabel.set_text("Model");
    m_modelLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
    
    m_Entry.set_max_length(50);
    m_Entry.set_text("type model name here");
    m_Entry.select_region(0, m_Entry.get_text_length());
    m_loadButton.set_label("Load");
    
    m_tabs.set_border_width(10);
    
    
    //Fill the combo:
    m_movementCombo.append("Normal movement");
    m_movementCombo.append("Bezier movement");
    m_movementCombo.set_active(0);
    
  //  add(m_projectionCombo);
    
    m_box1.pack_start(m_modelLabel, Gtk::PACK_SHRINK);
    m_box1.pack_start(m_Entry, Gtk::PACK_SHRINK);
    m_box1.pack_start(m_loadButton, Gtk::PACK_SHRINK);

    m_box1.pack_start(m_settingsLabel, Gtk::PACK_SHRINK);

    m_box1.pack_start(m_movementCombo, Gtk::PACK_SHRINK);
    m_box1.pack_start(m_flipNormalsCheck, Gtk::PACK_SHRINK);
    m_box1.pack_start(m_tabs);
    
    initLightsTab();
    initMaterialsTab();
    registerSignalHandlers();
    
    // The final step is to display this newly created widget...
    //m_button.show();
    add(m_box1);

    show_all_children();

}

GUIController::~GUIController()
{
}

void GUIController::initLightsTab() {
    
    m_lightPositionX.set_range(-1000.0, 1000.0);
    m_lightPositionX.set_digits(1.0);
    m_lightPositionX.set_increments(1.0, 0.0);
    m_lightPositionX.set_value(1.0);
    
    m_lightPositionY.set_range(-1000.0, 1000.0);
    m_lightPositionY.set_digits(1.0);
    m_lightPositionY.set_increments(1.0, 0.0);
    m_lightPositionY.set_value(1.0);
    
    m_lightPositionZ.set_range(-1000.0, 1000.0);
    m_lightPositionZ.set_digits(1.0);
    m_lightPositionZ.set_increments(1.0, 0.0);
    m_lightPositionZ.set_value(1.0);
    
    m_lightsContainer.pack_start(m_lightPositionX, Gtk::PACK_SHRINK);
    m_lightsContainer.pack_start(m_lightPositionY, Gtk::PACK_SHRINK);
    m_lightsContainer.pack_start(m_lightPositionZ, Gtk::PACK_SHRINK);

    m_lightRedChannel.set_range(0, 255);
    m_lightBlueChannel.set_range(0, 255);
    m_lightGreenChannel.set_range(0, 255);
    
    m_lightRedChannel.set_value(255);
    m_lightBlueChannel.set_value(255);
    m_lightGreenChannel.set_value(255);

    m_lightColorLabel.set_text("Color");
    m_lightPositionLabel.set_text("Position");
    
    m_lightsContainer.pack_start(m_lightColorLabel, Gtk::PACK_SHRINK);
    m_lightsContainer.pack_start(m_lightRedChannel, Gtk::PACK_SHRINK);
    m_lightsContainer.pack_start(m_lightBlueChannel, Gtk::PACK_SHRINK);
    m_lightsContainer.pack_start(m_lightGreenChannel, Gtk::PACK_SHRINK);
    
    m_tabs.append_page(m_lightsContainer, m_tabsLabel1);

}

void GUIController::initMaterialsTab() {
    m_materialDiffuseRedChannel.set_range(0, 255);
    m_materialDiffuseBlueChannel.set_range(0, 255);
    m_materialDiffuseGreenChannel.set_range(0, 255);

    m_materialAmbientRedChannel.set_range(0, 255);
    m_materialAmbientBlueChannel.set_range(0, 255);
    m_materialAmbientGreenChannel.set_range(0, 255);
    
    m_materialSpecularRedChannel.set_range(0, 255);
    m_materialSpecularBlueChannel.set_range(0, 255);
    m_materialSpecularGreenChannel.set_range(0, 255);
    
    m_materialDiffuseLabel.set_text("Diffuse");
    m_materialAmbientLabel.set_text("Ambient");
    m_materialSpecularLabel.set_text("Specular");
    m_materialShininessLabel.set_text("Shininess");
    
    m_materialShininess.set_range(0, 500);
    
    m_materialDiffuseRedChannel.set_value(240);
    m_materialDiffuseBlueChannel.set_value(220);
    m_materialDiffuseGreenChannel.set_value(220);
    
    m_materialAmbientRedChannel.set_value(5);
    m_materialAmbientBlueChannel.set_value(5);
    m_materialAmbientGreenChannel.set_value(5);
    
    m_materialSpecularRedChannel.set_value(255);
    m_materialSpecularBlueChannel.set_value(255);
    m_materialSpecularGreenChannel.set_value(255);
    
    m_materialShininess.set_value(250);
    
    m_materialContainer.pack_start(m_materialDiffuseLabel);
    m_materialContainer.pack_start(m_materialDiffuseRedChannel);
    m_materialContainer.pack_start(m_materialDiffuseBlueChannel);
    m_materialContainer.pack_start(m_materialDiffuseGreenChannel);
    
    m_materialContainer.pack_start(m_materialAmbientLabel);
    m_materialContainer.pack_start(m_materialAmbientRedChannel);
    m_materialContainer.pack_start(m_materialAmbientBlueChannel);
    m_materialContainer.pack_start(m_materialAmbientGreenChannel);
    
    m_materialContainer.pack_start(m_materialSpecularLabel);
    m_materialContainer.pack_start(m_materialSpecularRedChannel);
    m_materialContainer.pack_start(m_materialSpecularBlueChannel);
    m_materialContainer.pack_start(m_materialSpecularGreenChannel);

    m_materialContainer.pack_start(m_materialShininessLabel);
    m_materialContainer.pack_start(m_materialShininess);
    
    m_tabs.append_page(m_materialContainer, m_tabsLabel2);

    
}

void GUIController::registerSignalHandlers() {
    m_movementCombo.signal_changed().connect(sigc::mem_fun(*this,
                                                           &GUIController::on_movementCombo_changed) );
    
    m_flipNormalsCheck.signal_clicked().connect(sigc::mem_fun(*this,
                                                              &GUIController::on_flipNormalsCheck_clicked));
    
    m_tabs.signal_switch_page().connect(sigc::mem_fun(*this,
                                                      &GUIController::on_tabs_switch_tab) );
    
    m_lightRedChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                             &GUIController::on_light_changed));
    
    m_lightBlueChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                   &GUIController::on_light_changed));
    
    m_lightGreenChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                   &GUIController::on_light_changed));
    
    m_materialDiffuseRedChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                     &GUIController::on_material_changed));
    m_materialDiffuseBlueChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                             &GUIController::on_material_changed));
    m_materialDiffuseGreenChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                             &GUIController::on_material_changed));
    m_materialAmbientRedChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                               &GUIController::on_material_changed));
    m_materialAmbientBlueChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                               &GUIController::on_material_changed));
    m_materialAmbientGreenChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                               &GUIController::on_material_changed));
    m_materialSpecularRedChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                               &GUIController::on_material_changed));
    m_materialSpecularBlueChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                              &GUIController::on_material_changed));
    
    m_materialSpecularGreenChannel.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                              &GUIController::on_material_changed));
    m_materialShininess.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                                &GUIController::on_material_changed));

    m_lightPositionX.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                     &GUIController::on_spinbutton_digits_changed));
    
    m_lightPositionY.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                  &GUIController::on_spinbutton_digits_changed));

    m_lightPositionZ.signal_value_changed().connect(sigc::mem_fun(*this,
                                                                  &GUIController::on_spinbutton_digits_changed));

    m_loadButton.signal_clicked().connect(sigc::mem_fun(*this, &GUIController::on_loadbutton_clicked));
    
}

void GUIController::on_movementCombo_changed() {
    Glib::ustring text = m_movementCombo.get_active_text();
    
    if(text == "Bezier movement") {
        camera->useBezierMovement = true;
    } else {
        camera->useBezierMovement = false;
    }

    //if(!(text.empty()))
    //    std::cout << "Combo changed: " << idx << std::endl;
}


void GUIController::on_flipNormalsCheck_clicked() {
    *flipNormals = true;
}

void GUIController::on_loadbutton_clicked() {
    std::cout << m_Entry.get_text() << std::endl;
    *filenameToLoad = m_Entry.get_text();
    *shouldLoadFile = true;
}

void GUIController::on_light_changed() {
    this->light->data.l_color.x = m_lightRedChannel.get_value() / 255;
    this->light->data.l_color.y = m_lightBlueChannel.get_value() / 255;
    this->light->data.l_color.z = m_lightGreenChannel.get_value() / 255;
}

void GUIController::on_spinbutton_digits_changed() {
    this->light->data.l_pos.x = m_lightPositionX.get_value();
    this->light->data.l_pos.y = m_lightPositionY.get_value();
    this->light->data.l_pos.z = m_lightPositionZ.get_value();
}

/*glm::vec4 ambient;
glm::vec4 diffuse;
glm::vec4 specular;
float shininess;*/

void GUIController::on_material_changed() {
    this->material->ambient.x = m_materialAmbientRedChannel.get_value() / 255;
    this->material->ambient.y = m_materialAmbientBlueChannel.get_value() / 255;
    this->material->ambient.z = m_materialAmbientGreenChannel.get_value() / 255;
    
    this->material->diffuse.x = m_materialDiffuseRedChannel.get_value() / 255;
    this->material->diffuse.y = m_materialDiffuseBlueChannel.get_value() / 255;
    this->material->diffuse.z = m_materialDiffuseGreenChannel.get_value() / 255;

    this->material->specular.x = m_materialSpecularRedChannel.get_value() / 255;
    this->material->specular.y = m_materialSpecularBlueChannel.get_value() / 255;
    this->material->specular.z = m_materialSpecularGreenChannel.get_value() / 255;
    
    this->material->shininess = m_materialShininess.get_value() / 1;

}

void GUIController::on_tabs_switch_tab(Gtk::Widget* page, guint page_num)
{
    std::cout << "Switched to tab with index " << page_num << std::endl;
    
    //You can also use m_Notebook.get_current_page() to get this index.
}