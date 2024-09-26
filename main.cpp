#include <Windows.h>
#include<iostream>
#include <chrono>
#include "application/application.h"
#include "gpu/gpu.h"
#include "gpu/dataStructures.h"
#include "gpu/shader/defaultShader.h"
#include "gpu/shader/textureShader.h"
#include "gpu/shader/lightShader.h"
#include "application/image.h"
#include "application/camera.h"
#include "application/model.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup" )


//uint32_t WIDTH = 800;
//uint32_t HEIGHT = 600;

////���������Σ��������Զ�Ӧvbo
//uint32_t positionVbo0 = 0;
//uint32_t positionVbo1 = 0;
//uint32_t positionVbo2 = 0;
//
//uint32_t colorVbo0 = 0;
//uint32_t colorVbo1 = 0;
//uint32_t colorVbo2 = 0;
//
//uint32_t uvVbo = 0;
//
////�����ε�indices
//uint32_t ebo = 0;
//
////����������ר��vao
//uint32_t vao0 = 0;
//uint32_t vao1 = 0;
//uint32_t vao2 = 0;
//
////ʹ�õ�Shader
//DefaultShader* shader = nullptr;
//
////mvp�任����
//math::mat4f modelMatrix;
//math::mat4f viewMatrix;
//math::mat4f perspectiveMatrix;
//
//float angle = 0.0f;
//float scale = 1.f;
//float cameraZ = 2.0;
//
//void transform() {
//	angle += 0.003f;
//	//scale += 0.001;
//	//cameraZ -= 0.01f;
//
//	//ģ�ͱ任
//	modelMatrix = math::rotate(math::mat4f(1.0f), angle, math::vec3f{ 0.0f, 1.0f, 0.0f });
//    //modelMatrix = math::scale(modelMatrix, scale, scale, scale);
//
//	//��ͼ�任
//	auto cameraModelMatrix = math::translate(math::mat4f(1.0f), math::vec3f{ 0.0f, 0.0f, cameraZ });
//	viewMatrix = math::inverse(cameraModelMatrix);
//}
//
//void render() {
//	transform();
//	shader->mModelMatrix = modelMatrix;
//	shader->mViewMatrix = viewMatrix;
//	shader->mProjectionMatrix = perspectiveMatrix;
//
//	sgl->clear();
//	sgl->useProgram(shader);
//	
//	//��͸����������Ȼ��ƣ�zΪ-0.8
//	sgl->bindVertexArray(vao1);
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
//	sgl->drawElement(DRAW_TRIANGLES, 0, 3);
//
//	//͸��������,zΪ-0.5
//	sgl->bindVertexArray(vao2);
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
//	sgl->drawElement(DRAW_TRIANGLES, 0, 3);
//
//	//͸��������,zΪ0
//	sgl->bindVertexArray(vao0);
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
//	sgl->drawElement(DRAW_TRIANGLES, 0, 3);
//}
//
//void prepare() {
//	shader = new DefaultShader();
//
//	perspectiveMatrix = math::perspective(60.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//
//	auto cameraModelMatrix = math::translate(math::mat4f(1.0f), math::vec3f{ 0.0f, 0.0f, 3.0f });
//	viewMatrix = math::inverse(cameraModelMatrix);
//
//	//sgl->enable(CULL_FACE);
//	sgl->disable(CULL_FACE);
//	sgl->frontFace(FRONT_FACE_CCW);
//	sgl->cullFace(BACK_FACE);
//
//	sgl->enable(DEPTH_TEST);
//	sgl->enable(BLENDING);
//	//��һ��������
//	float positions0[] = {
//		-0.5f, 0.0f, 0.0f,
//		0.5f, 0.0f, 0.0f,
//		0.25f, 0.5f, 0.0f,
//	};
//
//	float colors0[] = {
//		1.0f, 0.0f, 0.0f, 0.3f,
//		0.0f, 1.0f, 0.0f, 0.3f,
//		0.0f, 0.0f, 1.0f, 0.3f,
//	};
//
//	//�ڶ���������
//	float positions1[] = {
//		0.3f, 0.0f, -0.8f,
//		0.8f, 0.0f, -0.8f,
//		0.45f, 0.5f, -0.8f,
//	};
//
//	float colors1[] = {
//		1.0f, 1.0f, 0.0f, 1.0f,
//		1.0f, 1.0f, 0.0f, 1.0f,
//		1.0f, 1.0f, 0.0f, 1.0f,
//	};
//
//	//������������
//	float positions2[] = {
//		0.5f, 0.0f, -0.5f,
//		1.0f, 0.0f, -0.5f,
//		0.75f, 0.5f, -0.5f,
//	};
//
//	float colors2[] = {
//		0.0f, 0.0f, 1.0f, 0.5f,
//		0.0f, 0.0f, 1.0f, 0.5f,
//		0.0f, 0.0f, 1.0f, 0.5f,
//	};
//
//	float uvs[] = {
//		0.0f, 0.0f,
//		0.0f, 1.0f,
//		1.0f, 0.0f,
//	};
//
//	uint32_t indices[] = { 0, 1, 2 };
//
//	//����indices��Ӧebo, ���߹���
//	ebo = sgl->genBuffer();
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
//	sgl->bufferData(ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 3, indices);
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, 0);
//
//	//����uv��Ӧ��vbo�����߹���
//	uvVbo = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, uvVbo);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 6, uvs);
//	sgl->bindBuffer(ARRAY_BUFFER, 0);
//
//	//����vao���Ұ�
//	vao0 = sgl->genVertexArray();
//	sgl->bindVertexArray(vao0);
//
//	//position0
//	positionVbo0 = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, positionVbo0);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 9, positions0);
//	sgl->vertexAttributePointer(0, 3, 3 * sizeof(float), 0);
//
//	//color0
//	colorVbo0 = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, colorVbo0);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 12, colors0);
//	sgl->vertexAttributePointer(1, 4, 4 * sizeof(float), 0);
//
//	//uv
//	sgl->bindBuffer(ARRAY_BUFFER, uvVbo);
//	sgl->vertexAttributePointer(2, 2, 2 * sizeof(float), 0);
//
//	sgl->bindBuffer(ARRAY_BUFFER, 0);
//	sgl->bindVertexArray(0);
//
//
//	//����vao���Ұ�
//	vao1 = sgl->genVertexArray();
//	sgl->bindVertexArray(vao1);
//
//	//position1
//	positionVbo1 = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, positionVbo1);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 9, positions1);
//	sgl->vertexAttributePointer(0, 3, 3 * sizeof(float), 0);
//
//	//color0
//	colorVbo1 = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, colorVbo1);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 12, colors1);
//	sgl->vertexAttributePointer(1, 4, 4 * sizeof(float), 0);
//
//	//uv
//	sgl->bindBuffer(ARRAY_BUFFER, uvVbo);
//	sgl->vertexAttributePointer(2, 2, 2 * sizeof(float), 0);
//
//	sgl->bindBuffer(ARRAY_BUFFER, 0);
//	sgl->bindVertexArray(0);
//
//	//����vao���Ұ�
//	vao2 = sgl->genVertexArray();
//	sgl->bindVertexArray(vao2);
//
//	//position1
//	positionVbo2 = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, positionVbo2);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 9, positions2);
//	sgl->vertexAttributePointer(0, 3, 3 * sizeof(float), 0);
//
//	//color0
//	colorVbo2 = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, colorVbo2);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 12, colors2);
//	sgl->vertexAttributePointer(1, 4, 4 * sizeof(float), 0);
//
//	//uv
//	sgl->bindBuffer(ARRAY_BUFFER, uvVbo);
//	sgl->vertexAttributePointer(2, 2, 2 * sizeof(float), 0);
//
//	sgl->bindBuffer(ARRAY_BUFFER, 0);
//	sgl->bindVertexArray(0);
//
//}


//Camera* camera = nullptr;
//
////���������Σ��������Զ�Ӧvbo
//uint32_t interleavedVbo = 0;
//
////�����ε�indices
//uint32_t ebo = 0;
//
////����������ר��vao
//uint32_t vao = 0;
//
////ʹ�õ�Shader
//LightShader* shader = nullptr;
//DirectionalLight directionalLight;
//math::vec3f envLight;
//
////ʹ�õ�texture
//uint32_t texture = 0;
//Image* image = nullptr;
//
////mvp�任����
//math::mat4f modelMatrix;
//
//float angle = 0.0f;
//float scale = 1.f;
//
//void transform() {
//	angle += 0.002f;
//	scale += 0.001;
//
//	//ģ�ͱ任
//	//modelMatrix = math::translate(math::mat4f(), 0.0f, 0.0f, -4.0f);
//	modelMatrix = math::rotate(math::mat4f(1.0f), angle, math::vec3f{ 0.0f, 1.0f, 0.0f });
//	//modelMatrix = math::scale(modelMatrix, scale, scale, scale);
//}
//
//void render() {
//	transform();
//	shader->mModelMatrix = modelMatrix;
//	shader->mViewMatrix = camera->getViewMatrix();
//	shader->mProjectionMatrix = camera->getProjectionMatrix();
//	shader->mDiffuseTexture = texture;
//
//	shader->mDirectionalLight = directionalLight;
//	shader->mEnvLight = envLight;
//
//	sgl->clear();
//	sgl->useProgram(shader);
//
//	sgl->bindVertexArray(vao);
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
//	sgl->drawElement(DRAW_TRIANGLES, 0, 36);
//
//}
//
//void prepare() {
//	camera = new Camera(60.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f, { 0.0f, 1.0f, 0.0f });
//	app->setCamera(camera);
//	camera->setSpeed(0.02f);
//
//	shader = new LightShader();
//	directionalLight.color = { 1.f, 1.f, 1.f };
//	//directionalLight.color = { 1.0f, 1.0f, 1.0f };
//	directionalLight.direction = { -1.0f, -0.3f, -0.7f };
//	envLight = { 0.2f, 0.2f, 0.2f };
//
//	//��������
//	image = Image::createImage("assets/textures/goku.jpg");
//	texture = sgl->genTexture();
//	sgl->bindTexture(texture);
//	sgl->texImage2D(image->mWidth, image->mHeight, image->mData);
//	sgl->texParameter(TEXTURE_FILTER, TEXTURE_FILTER_LINEAR);
//	sgl->texParameter(TEXTURE_WRAP_U, TEXTURE_WRAP_REPEAT);
//	sgl->texParameter(TEXTURE_WRAP_V, TEXTURE_WRAP_REPEAT);
//	sgl->bindTexture(0);
//
//	//sgl->enable(CULL_FACE);
//	sgl->disable(CULL_FACE);
//	//sgl->frontFace(FRONT_FACE_CCW);
//	//sgl->cullFace(BACK_FACE);
//
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//	};
//
//	uint32_t indices[] = {
//		0, 1, 2, 3, 4, 5,
//		6, 7, 8, 9, 10, 11,
//		12,13,14,15,16,17,
//		18,19,20,21,22,23,
//		24,25,26,27,28,29,
//		30,31,32,33,34,35
//	};
//
//
//	//����indices��Ӧebo
//	ebo = sgl->genBuffer();
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, ebo);
//	sgl->bufferData(ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 36, indices);
//	sgl->bindBuffer(ELEMENT_ARRAY_BUFFER, 0);
//
//	//�ܵĽ���ʽvbo
//	interleavedVbo = sgl->genBuffer();
//	sgl->bindBuffer(ARRAY_BUFFER, interleavedVbo);
//	sgl->bufferData(ARRAY_BUFFER, sizeof(float) * 288, vertices);
//
//	//����vao���Ұ�
//	vao = sgl->genVertexArray();
//	sgl->bindVertexArray(vao);
//	sgl->bindBuffer(ARRAY_BUFFER, interleavedVbo);
//
//	//position
//	sgl->vertexAttributePointer(0, 3, 8 * sizeof(float), 0);
//
//	//color
//	sgl->vertexAttributePointer(1, 4, 8 * sizeof(float), 3 * sizeof(float));
//
//	//uv
//	sgl->vertexAttributePointer(2, 2, 8 * sizeof(float), 6 * sizeof(float));
//
//	sgl->bindBuffer(ARRAY_BUFFER, 0);
//	sgl->bindVertexArray(0);
//}

uint32_t WIDTH = 800;
uint32_t HEIGHT = 600;

Camera* camera = nullptr;

//ʹ�õ�Shader
LightShader* shader = nullptr;
DirectionalLight directionalLight;
math::vec3f envLight;

//ʹ�õ�ģ��
Model* model = nullptr;

float angle = 0;
void transform() {
	angle -= 0.02f;
	auto rotateMatrix = math::rotate(math::mat4f(), angle, { 0.0f,1.0f,0.0f });
	auto translateMatrix = math::translate(math::mat4f(), 0.0f, 0.0f, -5.0f);
	auto m = translateMatrix * rotateMatrix;

	m = math::scale(m, 0.1f, 0.1f, 0.1f);
	model->setModelMatrix(m);
}

void render() {
	transform();

	shader->mViewMatrix = camera->getViewMatrix();
	shader->mProjectionMatrix = camera->getProjectionMatrix();

	shader->mDirectionalLight = directionalLight;
	shader->mEnvLight = envLight;

	sgl->clear();
	sgl->useProgram(shader);
	model->draw(shader);
}

void prepare() {
	camera = new Camera(60.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f, { 0.0f, 1.0f, 0.0f });
	APP->setCamera(camera);

	shader = new LightShader();
	directionalLight.color = { 1.0f, 1.0f, 1.0f };
	directionalLight.direction = { -1.0f, -0.5f, -0.7f };
	envLight = { 0.2f, 0.2f, 0.2f };

	sgl->enable(CULL_FACE);

	model = new Model();
	model->read("assets/model/dinosaur/source/Rampaging T-Rex.glb");
	//model->read("assets/model/Fist Fight B.fbx");
    //model->read("assets/model/bag/backpack.obj");
}

/*
* 1 ��ѭ��������wWinMain������
* 2 ���幹������Ϣ�������������ϸ�ڶ���װ��application������
*/
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,		//��Ӧ�ó���ʵ�������Ψһָ����ǰ����
	_In_opt_ HINSTANCE hPrevInstance,	//������ǰһ��ʵ����һ����null
	_In_ LPWSTR    lpCmdLine,		//Ӧ�ó������в���
	_In_ int       nCmdShow)		//���������ʾ����󻯡���С�������أ����������
{
	if (!APP->initApplication(hInstance, WIDTH, HEIGHT)) {
		return -1;
	}

	//��bmpָ����ڴ����õ�sgl���� 
	sgl->initSurface(APP->getWidth(), APP->getHeight(), APP->getCanvas());

	prepare();

	bool alive = true;
	while (alive) {
		alive = APP->peekMessage();
		camera->update();

		render();
		APP->show();
	}

	delete shader;
	//Image::destroyImage(image);
	//sgl->deleteTexture(texture);
	delete camera;

	return 0;
}
