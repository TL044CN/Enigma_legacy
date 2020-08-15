#pragma once

//include this header in Enigma applications to make Enigma available

//--Basics--
#include "Enigma/Application.h"
#include "Enigma/Layer.h"
#include "Enigma/Log.h"
#include "Enigma/Core/Timestep.h"
#include "Enigma/ImGui/ImGuiLayer.h"

//--Input--
#include "Enigma/Input.h"
#include "Enigma/Core/Keycodes.h"
#include "Enigma/Core/Mousecodes.h"

//--Renderer--
#include "Enigma/Renderer/Renderer.h"
#include "Enigma/Renderer/RenderCommand.h"
#include "Enigma/Renderer/Buffer.h"
#include "Enigma/Renderer/Shader.h"
#include "Enigma/Renderer/VertexArray.h"
#include "Enigma/Renderer/OrthographicCamera.h"

//--Entrypoint--
#include "Enigma/EntryPoint.h"
