# Enigma
## Enigma Engine
### A small Application Engine, capable of doing pretty much anything.

More of a Pet Project for training how to use Libs correctly.

## Usage:
The User does not have direct access to `void main()`, so Applications have to use the Entry Point of the Engine

```c++
//First include the Header File (and any other includes you might want to have):
#include "Enigma/Enigma.h"

//then create a new Layer to store Applciation specific things. You can push multiple layers and overlays into an Applicaiton
class MyLayer : public Enigma::Layer(){
	MyLayer()
  : Layer("myLayer"), m_CameraController(1080.0f, 720.0f) {
  
  }
	virtual ~MyLayer() = default;

  //This is the Initialization step. It happens when the new Layer is pushed into the Application
	virtual void OnAttach() override {
  
  }
  
  //This is the Destruction step. It Happens when the new Layer is removed from the Applicaiton
	virtual void OnDetach() override {
    
  }
  
  //This is the Update Step. It happens every Engine Iteration and returns a Timestep, that you can use for Syncronizing your Code with Realtime
	void OnUpdate(Enigma::Timestep t) override {
  
  }
  
  //This is the DearImGui Render Step. It happens evers Engine Tick, whenever ImGui has to update.
	virtual void OnImGuiRender() override {
  
  }
  
  //This is an Event Handeling Step. You can add a Dispatcher into there to handle special events yourself
	void OnEvent(Enigma::Event& e) override {
  
  }
  private:
  //Here you can add all your Process relevant variables
  //like this Camera Controller
  Enigma::OrthographicCameraController m_CameraController;
}

//then create a new Enigma application, initialized with all you're neat Layers
class MyApplication : public Enigma::Application {
  MyApplication(){
    PushLayer(new MyLayer());
  }
  
  ~MyApplication() {}
}

//overwrite the Create Application Function to bind the newly defined Application to the Enigma Engine. Enigma handles the rest.
Enigma::Application* CreateApplication(){
  return new MyApplication();
}
```
